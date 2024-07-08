#ifndef COMMUNICATIONSYSTEM_H
#define COMMUNICATIONSYSTEM_H

#include "base_class/RocketModule.h"

#include "param.h"

// comms module spec:
class CommunicationSystem
{
public:
    CommunicationSystem(const char* _name,
        int _updateFrequency,
        RocketModule* _accessible,
        const char* _communicationProtocolPath);
    void update();                   // checks wether there are new messages or nah
    int sendBytes(char* a, int len); // sends bytes to earth

private:
    char name[COMMS_SYS_MAX_NAME_LEN] = ""; // name of the comms system
    int updateFrequency;
    RocketModule* accessible; // modules the interfaces of which are exposed to this comms module.
    char communicationProtocolPath[COMMS_PRTCL_MAX_PATH_LEN] = "";
};

#endif