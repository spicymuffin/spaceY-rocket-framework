#include "system/CommunicationSystem.h"

#include "base_class/RocketModule.h"

#include "param.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

CommunicationSystem::CommunicationSystem(const char* _name,
    int _updateFrequency,
    RocketModule* _accessible,
    const char* _communicationProtocolPath)
{
    strcpy(name, _name);
    update_frequency = _updateFrequency;
    accessible = _accessible;
    strcpy(communication_protocol_path, _communicationProtocolPath);
}

void CommunicationSystem::update()
{
    /// TODO: read the uart buffer, decode, execute
}

int CommunicationSystem::send_bytes(char* a, int len)
{
    return 0;
}

int interpret(char* a)
{
    return 0;
}