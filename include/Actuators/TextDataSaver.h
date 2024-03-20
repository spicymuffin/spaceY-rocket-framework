#ifndef TEXTDATASAVER_H
#define TEXTDATASAVER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

#include "RocketModule.h"
#include "Actuator.h"

using namespace std;

/**
 * @brief
 * saves text data to a file. is a rocket module. is an actuator because performs actions
 */
class TextDataSaver : public RocketModule, public Actuator
{
public:
    /**
     * @brief Construct a new TextDataSaver object
     *
     * @param _name TextDataSaver's name
     * @param _updateFrequency TextDataSaver update frequency (-1 if non-updating)
     * @param _directoryPath text data's destination txt file path
     * @param _fileNamePostfix text data's filename postfix
     */
    TextDataSaver(string _name, int _updateFrequency, string _directoryPath, string _fileNamePostfix);

    /**
     * @brief
     * dumps line to file. (write to memory immediately)
     * @param _line
     */
    void dumpLine(string _line);

    /**
     * @brief
     * does nothing currently (textDataSavers should be updated manually)
     * @return int update status
     */
    int update() { return 0; };

private:
    ofstream dumpFile;
    string dumpFilePath;
    string directoryPath;
};

#endif