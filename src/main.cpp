#include <memory>

#include "param.h"

#include <pico/stdlib.h>

#include <rfw/MetaProvider.hpp>

#include "provider/hardware/DS3231.h"
#include "provider/hardware/BHI360.h"
#include "provider/hardware/USBStorage.h"
#include "provider/hardware/USBDebug.h"
#include "provider/software/LogWriter.h"

#include "usb.h"

#include "utils.h"

int usb_init_status = 0;

// ----------------------------------------
//                 commms
// ----------------------------------------

// comms protocol specification
// everything is a transaction. only the ground station can initiate a transaction

// groundstation-sent packet format
// $<16bit provider id><16 bit command id><16bit arg>#

// rocket-sent packet format
// $<16bit provider id><16 bit command id><variable length data><16bit CRC>#


char comms_rcv_buffer[COMMS_RCV_BUFFER_SIZE];
uint16_t comms_rcv_buffer_write_ptr = 0;
uint16_t comms_rcv_buffer_read_ptr = 0;

// ----------------------------------------
//               validation
// ----------------------------------------

enum packet_validation_state
{
	expecting_marker_start,
	in_packet,
	expecting_marker_end,
};

packet_validation_state vs = expecting_marker_start;

uint16_t packet_validation_ptr = 0;
bool start_marker_found = false;
uint16_t oldest_start_marker_ptr = 0;

uint8_t packet_data_segment_read_cnt = 0;
uint16_t packet_data_segment_start_ptr = 0;

// ----------------------------------------
// 			   packet parsing
// ----------------------------------------

struct packet_parse_result
{
	uint16_t provider_id;
	uint16_t command_id;
	uint16_t argument;
};

packet_parse_result ppr;


// ----------------------------------------
//			  buffer utilities
// ----------------------------------------


inline void comms_rcv_buffer_move_ptr_right(uint16_t& ptr, uint16_t dst)
{
	ptr = (ptr + dst) % COMMS_RCV_BUFFER_SIZE;
}

inline void comms_rcv_buffer_move_ptr_left(uint16_t& ptr, uint16_t dst)
{
	// handling potential negative result by adding COMMS_RCV_BUFFER_SIZE before modulo
	ptr = (ptr + COMMS_RCV_BUFFER_SIZE - dst) % COMMS_RCV_BUFFER_SIZE;
}

inline char comms_rcv_buffer_peek_right(uint16_t ptr, uint16_t dst)
{
	return comms_rcv_buffer[(ptr + dst) % COMMS_RCV_BUFFER_SIZE];
}

inline char comms_rcv_buffer_peek_left(uint16_t ptr, uint16_t dst)
{
	return comms_rcv_buffer[(ptr + COMMS_RCV_BUFFER_SIZE - dst) % COMMS_RCV_BUFFER_SIZE];
}


void comms_init()
{
	uart_init(uart0, COMMS_UART_BAUD_RATE);
	gpio_set_function(COMMS_UART_TX_PIN, GPIO_FUNC_UART);
	gpio_set_function(COMMS_UART_RX_PIN, GPIO_FUNC_UART);
	uart_set_fifo_enabled(uart0, true);
}


packet_parse_result parse_packet(uint16_t packet_data_segment_start_ptr)
{
	packet_parse_result tmp;

	tmp.provider_id = assemble_uint16(
		comms_rcv_buffer_peek_right(packet_data_segment_start_ptr, 0),
		comms_rcv_buffer_peek_right(packet_data_segment_start_ptr, 1)
	);

	tmp.command_id = assemble_uint16(
		comms_rcv_buffer_peek_right(packet_data_segment_start_ptr, 2),
		comms_rcv_buffer_peek_right(packet_data_segment_start_ptr, 3)
	);

	tmp.argument = assemble_uint16(
		comms_rcv_buffer_peek_right(packet_data_segment_start_ptr, 4),
		comms_rcv_buffer_peek_right(packet_data_segment_start_ptr, 5)
	);

	return tmp;
}


void comms_update()
{
	// read in from uart fifo
	while (uart_is_readable(uart0))
	{
		comms_rcv_buffer[comms_rcv_buffer_write_ptr] = uart_getc(uart0);
		comms_rcv_buffer_move_ptr_right(comms_rcv_buffer_write_ptr, 1);

		for (
			packet_validation_ptr = (comms_rcv_buffer_write_ptr + COMMS_RCV_BUFFER_SIZE - 1) % COMMS_RCV_BUFFER_SIZE;
			packet_validation_ptr != comms_rcv_buffer_write_ptr;
			comms_rcv_buffer_move_ptr_right(packet_validation_ptr, 1)
			)
		{
			char current = comms_rcv_buffer[packet_validation_ptr];

			// record the oldest start marker pointer that we have found inside the packet that we are currently validating
			// because it might be the start of a new (valid) packet
			if (current == MARKER_START && !start_marker_found && vs != expecting_marker_start)
			{
				start_marker_found = true;
				oldest_start_marker_ptr = packet_validation_ptr;
			}

			switch (vs)
			{
			case expecting_marker_start:

				// packet started
				if (current == MARKER_START)
				{
					vs = in_packet;
				}
				// else the packet is bad, ignore the character
				break;

			case in_packet:

				// we read one character of the data segment
				packet_data_segment_read_cnt++;

				// if it's the first character of the data segment, record the start pointer
				if (packet_data_segment_read_cnt == 1)
				{
					packet_data_segment_start_ptr = packet_validation_ptr;
				}
				// if it's the last character of the data segment, move to the next state
				else if (packet_data_segment_read_cnt == PACKET_LENGTH)
				{
					// reset the data segment read counter for later
					packet_data_segment_read_cnt = 0;
					vs = expecting_marker_end;
				}
				break;

			case expecting_marker_end:

				// packet is valid
				if (current == MARKER_END)
				{
					ppr = parse_packet(packet_data_segment_start_ptr);
					vs = expecting_marker_start;

					// start execution of the command specified in parsed packet
					// execute_command(ppr.provider_id, ppr.command_id, ppr.argument);
				}
				// packet ended prematurely
				else
				{
					// move validation pointer to the oldest start marker
					// because it might be the start of a new (valid) packet
					packet_validation_ptr = oldest_start_marker_ptr;
					vs = expecting_marker_start;
				}

				break;
			}
		}
	}
}


int logic_main()
{
	return 0;
}


int main()
{
	RFW::MetaProvider provider = RFW::MetaProvider::getInstance();

	// Since some providers depend on others, we need to register them first
	std::shared_ptr<USBDebug> usbDebug = std::make_shared<USBDebug>();
	provider.registerProvider("USBDebug", usbDebug);

	std::shared_ptr<DS3231> ds3231 = std::make_shared<DS3231>();
	provider.registerProvider("DS3231", ds3231);

	std::shared_ptr<BHI360> bhi360 = std::make_shared<BHI360>();
	provider.registerProvider("BHI360", bhi360);

	std::shared_ptr<USBStorage> usbStorage = std::make_shared<USBStorage>();
	provider.registerProvider("USBStorage", usbStorage);

	std::shared_ptr<LogWriter> logWriter = std::make_shared<LogWriter>();
	provider.registerProvider("LogWriter", logWriter);

	// Initialization phase - this resolves dependencies and initializes the providers
	usbDebug->init();
	ds3231->init();
	bhi360->init();
	usbStorage->init();
	logWriter->init();

	while (true)
	{
		comms_update();
		// This will update all the things that need updating
		provider.update();
	}
}