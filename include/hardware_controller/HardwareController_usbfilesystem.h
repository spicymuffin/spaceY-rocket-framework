#ifndef HARDWARECONTROLLER_USBFILESYSTEM_H
#define HARDWARECONTROLLER_USBFILESYSTEM_H

#include "param.h"

// base_class
#include "base_class/HardwareController.h"

// implements
#include "control_interface/IFileSystemContol.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

class HardwareController_usbfilesystem : public HardwareController,
    public IFileSystemContol
{
public:
    HardwareController_usbfilesystem(const char* _hardwaremodelName);
    void open() override;
    const int update() override;

private:
protected:
};

#endif