#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <locale>
#include <codecvt>
#include <vector>

#ifdef _WIN32

#include <Windows.h>
#include <SetupAPI.h>
#include <devguid.h>
#include <io.h>
#include <fcntl.h>
#include <conio.h>

#include "handle.hpp"

#elif __linux__

#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <ncurses.h>

#else
#error "Unsupported platform"
#endif

#define LIST_PORTS_FILTER_USB 0x01

typedef struct
{
	unsigned long index;
	std::wstring name;
} SerialPort;

std::vector<SerialPort> list_ports(int flags = 0)
{
	std::vector<SerialPort> ports;

#ifdef _WIN32
#ifdef _DEBUG
	wprintf(L"Windows detected\n");
	wprintf(L"Listing COM ports with GetCommPorts\n");
#endif
	ULONG port_count, port_count_next = 0;
	GetCommPorts(NULL, 0, &port_count);

	std::unique_ptr<ULONG[]> port_list(new ULONG[port_count]);
	GetCommPorts(NULL, port_count, &port_count_next);
	if (port_count_next != port_count)
	{
		wprintf(L"Error: COM port count mismatch\n");
		return ports;
	}

	wprintf(L"Found %d COM ports\n", port_count);

	SP_DEVICE_INTERFACE_DATA spDeviceInterfaceData;
	SP_DEVINFO_DATA spDevInfoData;

	unique_handle hDeviceInfo(SetupDiGetClassDevs(&GUID_DEVCLASS_PORTS, 0, nullptr, DIGCF_PRESENT));

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
	for (ULONG i = 0; i < port_count; ++i)
	{
		ZeroMemory(&spDeviceInterfaceData, sizeof(spDeviceInterfaceData));
		spDeviceInterfaceData.cbSize = sizeof(spDeviceInterfaceData);

		ZeroMemory(&spDevInfoData, sizeof(spDevInfoData));
		spDevInfoData.cbSize = sizeof(spDevInfoData);

		if (!SetupDiEnumDeviceInfo(hDeviceInfo.get(), i, &spDevInfoData))
		{
			wprintf(L"Error: Failed to get Device Info for COM%d\n", i);
#ifdef _DEBUG
			wprintf(L"SetupdiEnumDeviceInfo Failed, Error code: %d\n", GetLastError());
#endif
			continue;
		}

		DWORD lname = 0;
		DWORD lnameError = 0;
		if (!SetupDiGetDeviceRegistryProperty(hDeviceInfo.get(), &spDevInfoData, SPDRP_FRIENDLYNAME, NULL, NULL, NULL, &lname) && (lnameError = GetLastError()) != ERROR_INSUFFICIENT_BUFFER)
		{
			wprintf(L"Error: Failed to get Device Registry Property Length for COM%d\n", i);
#ifdef _DEBUG
			wprintf(L"SetupDiGetDeviceRegistryProperty Failed, Error code: %d\n", GetLastError());
#endif
			continue;
		}

#ifdef _DEBUG
		wprintf(L"COM #%d Name Length: %d Bytes\n", i, lname);
#endif

		std::unique_ptr<BYTE[]> name(new BYTE[lname + 1]);
		name[lname] = 0;
		if (!SetupDiGetDeviceRegistryProperty(hDeviceInfo.get(), &spDevInfoData, SPDRP_FRIENDLYNAME, NULL, name.get(), lname, NULL))
		{
			wprintf(L"Error: Failed to get Device Registry Property for COM%d\n", i);
#ifdef _DEBUG
			wprintf(L"SetupDiGetDeviceRegistryProperty Failed, Error code: %d\n", GetLastError());
#endif
			continue;
		}

		std::wstring wname(reinterpret_cast<wchar_t *>(name.get()), lname / 2);
		ports.push_back({i, wname});
	}
#elif defined(__linux__)

#endif

	return ports;
}

#ifdef _WIN32
wchar_t getkey()
{
	return _getwch();
}
#else
bool kbhit()
{
	struct pollfd fds;
	fds.fd = STDIN_FILENO;
	fds.events = POLLIN;
	poll(&fds, 1, 0);
	return fds.revents & POLLIN;
}

wchar_t getkey()
{
	wchar_t key;
	read(STDIN_FILENO, &key, sizeof(key));
	return key;
}

void set_nonblocking_io()
{
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}
#endif

int main()
{
#ifdef _WIN32
	_setmode(_fileno(stdout), _O_U16TEXT);
#endif

	std::vector<SerialPort> ports = list_ports();

	wprintf(L"\n");
	wprintf(L"Press \"R\" to reload the list\n");
#ifdef __linux__
	wprintf(L"Press \"U\" to show only USB serial ports\n");
#endif
	wprintf(L"\n");

	unsigned long flags = 0;
	wchar_t key;
	int index = 0;

	for (unsigned i = 0; i < ports.size(); ++i)
	{
		wprintf(L"[%02d] %ls\n", i, ports[i].name.c_str());
	}

	while (true)
	{
		if (kbhit())
		{
			key = getkey();

			if (key == L'R')
			{
				ports = list_ports(flags);
				wprintf(L"%c", key);
			}
#ifdef __linux__
			else if (key == L'U')
			{
				flags = LIST_PORTS_FILTER_USB;
				ports = list_ports(flags);
				wprintf(L"%c", key);
			}
#endif
			else if (key >= L'0' && key <= L'9')
			{
				index = index * 10 + key - L'0';
				wprintf(L"%c", key);
			}
			else if (key == L'\n' || key == L'\r')
			{
				wprintf(L"%c", key);
				break;
			}
			else if (key == 0x08)
			{
				wprintf(L"%c %c", key, key);
				index /= 10;
			}
		}
	}
	wprintf(L"Selected index: %d\n", index);

	return 0;
}