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
    struct ActionEntry
    {
        long long timestamp;
        char content[ACTION_ENTRY_MAX_LEN];
    };

    /**
     * @brief
     * module's tick's information container. [moduleName] is the owner-module's name.
     * [buffer] is the action entries that happened during tick no. [tickNumber]
     */
    struct ModuleTickLog
    {
        int tickNumber;
        char* moduleName;
        ActionEntry buffer[MAX_ACTION_ENTRIES_PER_TICK];
    };

    /**
     * @brief Construct a new FlightLogger object
     *
     * @param _name name of the flight logger (for debugging purposes)
     * @param _directoryPath path to flight logs directory
     * @param _fileNamePostfix filename postfix
     */
    FlightLogger(char* _name,
        char* _directoryPath,
        char* _fileNamePostfix);

    /**
     * @brief Get the name of the flight logger object
     *
     * @return char* the name of the flight logger object
     */
    char* get_name();

    /**
     * @brief dumps buffer contents generated during this tick to a file
     *
     */
    void dumpTickBuffer();

    /**
     * @brief appends a ModuleTickLog struct to buffer
     *
     * @param _moduleTickLog ModuleTickLog to append
     */
    void appendToTickBuffer(ModuleTickLog _moduleTickLog);

private:
    /// TODO: fix filesystem
    // ofstream dumpFile;
    char* filepath;
    char* dirpath;

    /// TODO: dump to file asap
    ModuleTickLog tickBuffer[32];
    char* name;
};

#endif