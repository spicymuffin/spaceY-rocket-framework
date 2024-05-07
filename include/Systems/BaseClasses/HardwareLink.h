#ifndef HARDWARELINK_H
#define HARDWARELINK_H

using namespace std;

#include <string>

class HardwareLink
{
public:
    HardwareLink(string _hardwareName);

private:
protected:
    string hardwareName;
};

#endif