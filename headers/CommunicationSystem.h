#include <iostream>
#include <string>
#include <vector>

using namespace std;

// comms module spec:
class CommunicationSystem
{
public:
    void update();           // checks wether there are new messages or nah
    void sendBytes(byte *a); // sends bytes to earth
    void generateAccesibilityTree()
    {
    }

private:
    string name; // name of the comms system
    int updateRate;
    vector<RocketMoudule> accessible; // modules the interfaces of which are exposed to this comms module.
};
