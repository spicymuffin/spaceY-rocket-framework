#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

class FlightLogger
{
public:
    struct moduleTickLog;
    struct actionEntry;

    FlightLogger(string _name, string _directoryPath, string _fileNamePostfix)
    {
        name = _name;
        directoryPath = _directoryPath;

        time_t now;
        tm *tmp;
        char time_string_char[64];
        time(&now);
        tmp = localtime(&now);
        strftime(time_string_char, sizeof(time_string_char), "%F@%H-%M-%S", tmp);
        string time_string(time_string_char);

        dumpFilePath = directoryPath + '/' + time_string + '_' + _fileNamePostfix;
        dumpFile.open(dumpFilePath);

        strftime(time_string_char, sizeof(time_string_char), "%c", tmp);
        time_string = string(time_string_char);

        dumpFile << "log for " << time_string << endl;
    };

    string getName() { return name; };

    void dumpTickBuffer()
    {
        for (int i = 0; i < static_cast<int>(tickBuffer.size()); i++)
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
    string dumpFilePath;
    string directoryPath;

    vector<moduleTickLog> tickBuffer;
    string name;
};