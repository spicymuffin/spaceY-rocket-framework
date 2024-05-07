#ifndef COMMUNICATIONSYSTEM_H
#define COMMUNICATIONSYSTEM_H

#include <iostream>
#include <string>
#include <vector>

#include "base_class/RocketModule.h"

using namespace std;

// comms module spec:
class CommunicationSystem
{
public:
    CommunicationSystem(string _name,
                        int _updateFrequency,
                        vector<RocketModule *> _accessible,
                        string _communicationProtocolPath);
    void update();          // checks wether there are new messages or nah
    int sendBytes(byte *a); // sends bytes to earth

private:
    string name; // name of the comms system
    int updateFrequency;
    vector<RocketModule *> accessible; // modules the interfaces of which are exposed to this comms module.
    string communicationProtocolPath;
};

#endif