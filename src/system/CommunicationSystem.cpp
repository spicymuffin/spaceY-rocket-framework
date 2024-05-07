#include "base_class/RocketModule.h"
#include "system/CommunicationSystem.h"

CommunicationSystem::CommunicationSystem(char* _name,
                                         int _updateFrequency,
                                         vector<RocketModule *> _accessible,
                                         char* _communicationProtocolPath)
{
    name = _name;
    updateFrequency = _updateFrequency;
    accessible = _accessible;
    communicationProtocolPath = _communicationProtocolPath;
}

void CommunicationSystem::update()
{
    /// TODO: communicate with physical thing and read.
}

int CommunicationSystem::sendBytes(byte *a)
{
}

int interpret(char* a);