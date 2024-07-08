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
    int send_bytes(char* a, int len); // sends bytes to earth

private:
    char name[COMMS_SYS_MAX_NAME_LEN] = ""; // name of the comms system
    int update_frequency;
    RocketModule* accessible; // modules the interfaces of which are exposed to this comms module.
    char communication_protocol_path[COMMS_PRTCL_MAX_PATH_LEN] = "";
};

#endif