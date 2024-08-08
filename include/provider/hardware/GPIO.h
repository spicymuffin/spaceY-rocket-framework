/*
 * TODO: This is a core module, so it should be placed in rfw-pico or other
 */
#ifndef __RFW_HARDWARE_GPIO_H
#define __RFW_HARDWARE_GPIO_H

#include <rfw/base/Update.h>

#include <pico/stdlib.h>

class GPIO : public virtual RFW::Update
{
public:
	GPIO();
	virtual ~GPIO() override = default;
	void init() override;
	void set_pin(uint8_t pin, bool value);
	bool get_pin(uint8_t pin);
	void update() override;
};

#endif // __RFW_HARDWARE_GPIO_H