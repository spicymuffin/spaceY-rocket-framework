#ifndef TEXTDATASAVER_H
#define TEXTDATASAVER_H

#include "param.h"

#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"

class TextDataSaver : public RocketModule, public Actuator
{
public:
    TextDataSaver(char *_name,
                  int _updateFrequency,
                  char *_directoryPath,
                  char *_fileNamePostfix);

    void dumpLine(char *_line);

    int update() { return 0; };

private:
    /// TODO: fix filesystem
    // ofstream dumpFile;
    char *dumpFilePath;
    char *directoryPath;
};

#endif