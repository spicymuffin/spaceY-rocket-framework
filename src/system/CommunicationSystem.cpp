#include "base_class/RocketModule.h"
#include "system/CommunicationSystem.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

CommunicationSystem::CommunicationSystem(const char *_name,
                                         int _updateFrequency,
                                         RocketModule *_accessible,
                                         const char *_communicationProtocolPath)
{
    strcpy(name, _name);
    updateFrequency = _updateFrequency;
    accessible = _accessible;
    strcpy(communicationProtocolPath, _communicationProtocolPath);
}

void CommunicationSystem::update()
{
    /// TODO: communicate with physical thing and read.
}

int CommunicationSystem::sendBytes(char *a, int len)
{
}

int interpret(char *a)
{
}