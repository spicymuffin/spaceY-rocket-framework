#ifndef FLIGHTLOGGER_H
#define FLIGHTLOGGER_H

#include "param.h"

/**
 * @brief
 * flightlogger. creates logs, that contain data abt the rocket's state changes and
 * modules' warning/error/debug messages. designed for post-flight analysis.
 *
 */
class FlightLogger
{
public:
    /**
     * @brief
     * action log entry. used by modules to describe what happened at given timestamp
     * [timestamp]. [content] contains data on what happened.
     */
    struct actionEntry
    {
        long long timestamp;
        char content[ACTION_ENTRY_MAX_LEN];
    };

    /**
     * @brief
     * module's tick's information container. [moduleName] is the owner-module's name.
     * [buffer] is the action entries that happened during tick no. [tickNumber]
     */
    struct moduleTickLog
    {
        int tickNumber;
        char *moduleName;
        actionEntry buffer[MAX_ACTION_ENTRIES_PER_TICK];
    };

    /**
     * @brief Construct a new FlightLogger object
     *
     * @param _name name of the flight logger (for debugging purposes)
     * @param _directoryPath path to flight logs directory
     * @param _fileNamePostfix filename postfix
     */
    FlightLogger(char *_name,
                 char *_directoryPath,
                 char *_fileNamePostfix);

    /**
     * @brief Get the name of the flight logger object
     *
     * @return char* the name of the flight logger object
     */
    char *getName();

    /**
     * @brief dumps buffer contents generated during this tick to a file
     *
     */
    void dumpTickBuffer();

    /**
     * @brief appends a moduleTickLog struct to buffer
     *
     * @param _moduleTickLog moduleTickLog to append
     */
    void appendToTickBuffer(moduleTickLog _moduleTickLog);

private:
    /// TODO: fix filesystem
    // ofstream dumpFile;
    char *dumpFilePath;
    char *directoryPath;

    /// TODO: dump to file asap
    moduleTickLog tickBuffer[32];
    char *name;
};

#endif