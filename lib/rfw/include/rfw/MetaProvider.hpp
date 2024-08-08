#ifndef __RFW_METAPROVIDER
#define __RFW_METAPROVIDER

#include "tusb.h"
#include "utils.h"

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
			providers.insert(std::make_pair(label, provider));
		}

		template <typename I>
		std::shared_ptr<I> getProvider(const std::string &label)
		{
			for (auto &p : providers)
			{
				tud_cdc_printf("Provider in loop: %c\r\n", p.first.c_str()[0], p.first.c_str()[1]);
				tud_cdc_write_flush();
			}

			auto provider = providers.find(label);
			if (provider == providers.end())
			{
				return nullptr;
			}

			tud_cdc_printf("Provider found: %s\r\n", label.c_str());
			tud_cdc_write_flush();

			auto castedProvider = std::dynamic_pointer_cast<I>(provider->second);
			if (!castedProvider)
			{
				tud_cdc_printf("Provider uncastable: %s\r\n", label.c_str());
				tud_cdc_write_flush();
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
				auto castedProvider = std::dynamic_pointer_cast<I>(provider.second);
				if (!castedProvider)
				{
					continue;
				}

				if (bestProvider == nullptr)
				{
					bestProvider = castedProvider;
					continue;
				}

				if (compare(bestProvider, castedProvider) < 0)
				{
					bestProvider = castedProvider;
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

		MetaProvider(MetaProvider const &) = delete;
		void operator=(MetaProvider const &) = delete;

	private:
		MetaProvider() {}
		std::map<std::string, std::shared_ptr<Base>> providers;
	};

	namespace
	{
		template <typename I>
		int _getLast(std::shared_ptr<I> _a, std::shared_ptr<I> _b)
		{
			return -1;
		}
	}

	template <typename I>
	std::function<int(std::shared_ptr<I>, std::shared_ptr<I>)> GetLast(_getLast<I>);
}

#endif // __RFW_METAPROVIDER