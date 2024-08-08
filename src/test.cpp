#include <stdio.h>

#include <pico/stdlib.h>

#include <map>
#include <string>
#include <memory>

class Provider
{
public:
	static Provider &getInstance()
	{
		static Provider instance;
		return instance;
	}

private:
	Provider() = default;
	std::map<std::string, std::shared_ptr<int>> providers;
};

int main()
{
	std::map<std::string, std::shared_ptr<int>> providers;
}