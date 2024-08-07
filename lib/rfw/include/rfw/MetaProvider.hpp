#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <functional>
#include <type_traits>

#include "base/Base.h"
#include "base/Update.h"

namespace RFW
{
	class MetaProvider
	{
	public:
		static MetaProvider &getInstance()
		{
			static MetaProvider instance;
			return instance;
		}

		template <class T, typename = std::enable_if_t<std::is_base_of_v<Base, T>>>
		void registerProvider(const std::string &label, std::shared_ptr<T> provider)
		{
			if (providers.find(label) != providers.end())
			{
				throw std::runtime_error("Provider with label " + label + " already exists");
			}
			providers[label] = provider;
		}

		template <typename I>
		std::shared_ptr<I> getProvider(const std::string &label)
		{
			auto provider = providers.find(label);
			if (provider == providers.end())
			{
				return nullptr;
			}

			auto castedProvider = std::dynamic_pointer_cast<I>(provider->second);
			if (!castedProvider)
			{
				return nullptr;
			}

			return castedProvider;
		}

		template <typename I>
		std::shared_ptr<I> getBestProvider(std::function<int(std::shared_ptr<I>, std::shared_ptr<I>)> compare)
		{
			std::shared_ptr<I> bestProvider = nullptr;
			for (const auto &provider : providers)
			{
				auto castedProvider = std::dynamic_pointer_cast<I>(provider);
				if (!castedProvider)
				{
					continue;
				}

				if (bestProvider == nullptr)
				{
					bestProvider = provider;
					continue;
				}

				if (compare(bestProvider, castedProvider) < 0)
				{
					bestProvider = provider;
				}
			}
			return bestProvider;
		}

		void update()
		{
			for (auto &provider : providers)
			{
				auto castedProvider = std::dynamic_pointer_cast<Update>(provider.second);
				if (!castedProvider)
				{
					continue;
				}

				castedProvider->update();
			}
		}

	private:
		MetaProvider() = default;
		std::map<std::string, std::shared_ptr<Base>> providers;
	};
}