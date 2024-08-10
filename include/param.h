#ifndef __PARAM_H
#define __PARAM_H

// ----------------------------------
//         packet structure
// ----------------------------------

#define PROVIDER_ID_LENGTH              2               // in bytes
#define COMMAND_ID_LENGTH               2
#define ARGUMENT_LENGTH                 2

#define PACKET_LENGTH                   (PROVIDER_ID_LENGTH + COMMAND_ID_LENGTH + ARGUMENT_LENGTH) // 6 bytes

// ----------------------------------
//          packet markers
// ----------------------------------

#define MARKER_START                    '$'             // packet start marker
#define MARKER_END                      '#'             // packet end marker

// ----------------------------------
//        main comms buffer
// ----------------------------------

#define COMMS_RCV_BUFFER_SIZE           1024

// ----------------------------------
//            comms uart
// ----------------------------------

#define COMMS_UART_BAUD_RATE            9600
#define COMMS_UART_TX_PIN               0
#define COMMS_UART_RX_PIN               1

#endif // __PARAM_H