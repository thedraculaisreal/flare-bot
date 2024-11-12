#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>

class Memory
{
	DWORD base_address;
	DWORD get_module_base_address(const char* lpsz_module_name, DWORD pid);

public:

	void find_exe();
};

inline Memory mem;