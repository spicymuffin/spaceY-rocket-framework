// main
#define RM_TABLE_LEN                        32      // max rocket modules
#define HC_TABLE_LEN                        16      // max hardware controllers
#define ENDLESS                             false   // should the main loop run indefinitely?
#define TEST_DURATION                       30
#define REFRESH_RATE                        128      // main loop target refresh rate (Hz)

// debug
#define DEBUG                               true    // debugging mode on or off

// hardwarecontroller
#define HARDWARE_MAX_NAME_LEN               16      // hardware name max length

// rocket module
#define RM_MAX_NAME_LEN                     16      // rocket module name max length

// comms system
#define COMMS_SYS_MAX_NAME_LEN              16      // communication system max length
#define COMMS_ACCESSIBLE_RM_TABLE_LEN       32
#define COMMS_PRTCL_MAX_PATH_LEN            64

// flight logger
#define ACTION_ENTRY_MAX_LEN                64
#define MAX_ACTION_ENTRIES_PER_TICK         16

// generic data receiver
#define DR_BUFFER_LENGTH                    16