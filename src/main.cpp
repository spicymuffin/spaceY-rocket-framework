#include <memory>

#include <pico/stdlib.h>

#include <rfw/MetaProvider.hpp>

#include "provider/DS3231.h"

int main()
{
	RFW::MetaProvider provider = RFW::MetaProvider::getInstance();

	std::shared_ptr<DS3231> ds3231 = std::make_shared<DS3231>();
	provider.registerProvider(ds3231);
}