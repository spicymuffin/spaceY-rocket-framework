#ifndef __RFW_HARDWARE_USBSTORAGE_H
#define __RFW_HARDWARE_USBSTORAGE_H

#include "tusb.h"

#include <rfw/io/FileSystem.h>

class USBStorage : public virtual RFW::FileSystem
{
public:
	USBStorage();
	void update() override;
	virtual ~USBStorage() = default;
};

#endif // __RFW_HARDWARE_USBSTORAGE_H