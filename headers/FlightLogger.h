#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class FlightLogger
{
public:
    struct moduleTickLog;
    struct actionEntry;

    FlightLogger(string _name)
    {
        name = _name;
    };

    void dumpTickBuffer()
    {
        for (int i = 0; i < tickBuffer.size(); i++)
        {
            // TODO: convert tickBuffer entries to strings
        }
    };

    void appendToTickBuffer(moduleTickLog _moduleTickLog)
    {
        tickBuffer.push_back(_moduleTickLog);
        // tickBuffer.insert(tickBuffer.end(), _extendBuffer.begin(), _extendBuffer.end());
    };

    struct actionEntry
    {
        int timestamp;
        string content;
    };

    struct moduleTickLog
    {
        int tickNumber;
        string moduleName;
        vector<actionEntry> buffer;
    };

private:
    ofstream dumpFile;

    vector<moduleTickLog> tickBuffer;
    string name;
};