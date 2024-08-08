#include <memory>

#include <pico/stdlib.h>

#include <rfw/MetaProvider.hpp>

#include "provider/hardware/DS3231.h"
#include "provider/software/LogWriter.h"

int main()
{
	RFW::MetaProvider provider = RFW::MetaProvider::getInstance();

	std::shared_ptr<DS3231> ds3231 = std::make_shared<DS3231>();
	provider.registerProvider("DS3231", ds3231);

	std::shared_ptr<LogWriter> logWriter = std::make_shared<LogWriter>();
	provider.registerProvider("LogWriter", logWriter);
}