#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

#include "RocketModule.h"
#include "Actuator.h"

using namespace std;

// https://stackoverflow.com/questions/19132894/writing-to-file-line-by-line-vs-writing-whole-text-at-once
// apparently making a write buffer is useless so we're not going
// to do that.

class TextDataSaver : public RocketModule, public Actuator
{
public:
    TextDataSaver(string _name, int _updateFrequency, string _directoryPath, string _fileNamePostfix) : RocketModule(_name, _updateFrequency)
    {
        directoryPath = _directoryPath;

        time_t now;
        tm *tmp;
        char time_string_char[64];
        time(&now);
        tmp = localtime(&now);
        strftime(time_string_char, sizeof(time_string_char), "%F@%H-%M-%S", tmp);
        string time_string(time_string_char);

        dumpFilePath = directoryPath + '\\' + time_string + "_" + _fileNamePostfix;
        dumpFile.open(dumpFilePath);
    };

    ~TextDataSaver(){

    };

    void dumpLine(string _line)
    {
        dumpFile << _line + '\n';
    }

    int update() { return 0; };

private:
    ofstream dumpFile;
    string dumpFilePath;
    string directoryPath;
};