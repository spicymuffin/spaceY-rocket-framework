#ifndef TEXTDATASAVER_H
#define TEXTDATASAVER_H

#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"

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
    TextDataSaver(char* _name, int _updateFrequency, char* _directoryPath, char* _fileNamePostfix);

    /**
     * @brief
     * dumps line to file. (write to memory immediately)
     * @param _line
     */
    void dumpLine(char* _line);

    /**
     * @brief
     * does nothing currently (textDataSavers should be updated manually)
     * @return int update status
     */
    int update() { return 0; };

private:
    ofstream dumpFile;
    char* dumpFilePath;
    char* directoryPath;
};

#endif