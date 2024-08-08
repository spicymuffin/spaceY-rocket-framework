#include <memory>

#include <pico/stdlib.h>

#include <rfw/MetaProvider.hpp>

#include "provider/hardware/DS3231.h"
#include "provider/hardware/BHI360.h"
#include "provider/software/LogWriter.h"

int main()
{
	RFW::MetaProvider provider = RFW::MetaProvider::getInstance();

	// Since some providers depend on others, we need to register them first
	std::shared_ptr<DS3231> ds3231 = std::make_shared<DS3231>();
	provider.registerProvider("DS3231", ds3231);

	std::shared_ptr<BHI360> bhi360 = std::make_shared<BHI360>();
	provider.registerProvider("BHI360", bhi360);

	std::shared_ptr<LogWriter> logWriter = std::make_shared<LogWriter>();
	provider.registerProvider("LogWriter", logWriter);

	// Initialization phase - this resolves dependencies and initializes the providers
	ds3231->init();
	logWriter->init();
	bhi360->init();

	while (true)
	{
		// This will update all the things that need updating
		provider.update();
	}
}