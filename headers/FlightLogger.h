#include <iostream>
#include <string>
#include <vector>

using namespace std;

class FlightLogger
{
public:
    FlightLogger(string _name)
    {
        name = _name;
    };

    void dumpTickBuffer()
    {
        for (int i = 0; i < buffer.size(); i++)
        {
            
        }
    };

private:
    ofstream dumpFile;

    vector<string> buffer;
    string name;
};