#ifndef COMMUNICATIONSYSTEM_H
#define COMMUNICATIONSYSTEM_H

#include "base_class/RocketModule.h"

// comms module spec:
class CommunicationSystem
{
public:
    CommunicationSystem(char* _name,
                        int _updateFrequency,
                        vector<RocketModule *> _accessible,
                        char* _communicationProtocolPath);
    void update();          // checks wether there are new messages or nah
    int sendBytes(byte *a); // sends bytes to earth

private:
    char* name; // name of the comms system
    int updateFrequency;
    vector<RocketModule *> accessible; // modules the interfaces of which are exposed to this comms module.
    char* communicationProtocolPath;
};

#endif