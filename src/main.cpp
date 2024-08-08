#include <memory>

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>

#include <rfw/MetaProvider.hpp>

#include "provider/hardware/DS3231.h"
#include "provider/hardware/BHI360.h"
#include "provider/hardware/USBStorage.h"
#include "provider/hardware/USBDebug.h"
#include "provider/software/LogWriter.h"

#include "bsp/board_api.h"
#include "usb.h"
#include "tusb.h"

int usb_init_status = 0;

void logic_main()
{
}

int main()
{
	board_init();
	cyw43_arch_init();

	RFW::MetaProvider &provider = RFW::MetaProvider::getInstance();

	// Since some providers depend on others, we need to register them first
	std::shared_ptr<USBDebug> usbDebug = std::make_shared<USBDebug>();
	provider.registerProvider("DEBUG", usbDebug);

	std::shared_ptr<DS3231> ds3231 = std::make_shared<DS3231>();
	provider.registerProvider("DS3231", ds3231);

	std::shared_ptr<BHI360> bhi360 = std::make_shared<BHI360>();
	provider.registerProvider("BHI360", bhi360);

	std::shared_ptr<USBStorage> usbStorage = std::make_shared<USBStorage>();
	provider.registerProvider("USBStorage", usbStorage);

	std::shared_ptr<LogWriter> logWriter = std::make_shared<LogWriter>();
	provider.registerProvider("LogWriter", logWriter);

	// Initialization phase - this resolves dependencies and initializes the providers
	usbDebug->init();
	usbStorage->init();

	ds3231->init();
	bhi360->init();
	logWriter->init();

	multicore_reset_core1();

	while (true)
	{
		// This will update all the things that need updating
		provider.update();
	}
}