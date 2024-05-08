#include "base_class/HardwareLink.h"

#include "param.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

HardwareLink::HardwareLink(const char *_hardwareName)
{
    strcpy(hardwareName, _hardwareName);
}