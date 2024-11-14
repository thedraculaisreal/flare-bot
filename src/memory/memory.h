#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <iostream>

class Memory
{
	uintptr_t get_module_base_address(const char* lpsz_module_name, DWORD pid);

public:
	HANDLE process_handle;
	uintptr_t base_address;
	void read_mem();
	void find_exe();
};

inline Memory mem;