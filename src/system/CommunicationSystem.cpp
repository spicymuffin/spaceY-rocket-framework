#include <iostream>
#include <string>
#include <vector>

#include "system/base_class/RocketModule.h"
#include "system/CommunicationSystem.h"

using namespace std;

CommunicationSystem::CommunicationSystem(string _name,
                                         int _updateFrequency,
                                         vector<RocketModule *> _accessible,
                                         string _communicationProtocolPath)
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

int interpret(string a);