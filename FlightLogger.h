#include <iostream>
#include <string>
#include <vector>

using namespace std;

class FlightLogger
{
public:
    FlightLogger(string _name, int _bufferSize)
    {
        name = _name;
        bufferSize = _bufferSize;
    };

    void writeData(){

    };

private:
    int bufferSize;
    vector<int> buffer;
    string name;
};