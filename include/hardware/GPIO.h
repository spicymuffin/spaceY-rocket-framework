/*
 * TODO: This is a core module, so it should be placed in rfw-pico or other
 */
#ifndef __RFW_PROVIDER_GPIO_H
#define __RFW_PROVIDER_GPIO_H

#include <rfw/base/Update.h>

#include <pico/stdlib.h>

class GPIO : public virtual RFW::Update
{
public:
	GPIO();
	void set_pin(uint8_t pin, bool value);
	bool get_pin(uint8_t pin);
	void update() override;
};

#endif