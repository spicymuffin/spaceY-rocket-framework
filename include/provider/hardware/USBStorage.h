#ifndef __RFW_HARDWARE_USBSTORAGE_H
#define __RFW_HARDWARE_USBSTORAGE_H

#include "tusb.h"

#include <rfw/io/FileSystem.h>

class USBStorage : public virtual RFW::FileSystem
{
public:
	USBStorage();
	virtual ~USBStorage() override;
	void init() override;
	void update() override;
};

#endif // __RFW_HARDWARE_USBSTORAGE_H