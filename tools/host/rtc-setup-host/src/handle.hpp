#ifndef __HANDLE_HPP
#define __HANDLE_HPP

#include <Windows.h>

class unique_handle
{
	HANDLE _handle;

public:
	unique_handle() : _handle{INVALID_HANDLE_VALUE} {}
	unique_handle(HANDLE handle) : _handle{handle} {}
	~unique_handle() { CloseHandle(_handle); }

	HANDLE get() const { return _handle; }
};

class unique_key
{
	HKEY _key;

public:
	unique_key() : _key{0} {}
	unique_key(HKEY key) : _key{key} {}
	~unique_key() { RegCloseKey(_key); }

	HKEY get() const { return _key; }
	const bool is_valid() const { return _key != 0; }
};

#endif // __HANDLE_HPP