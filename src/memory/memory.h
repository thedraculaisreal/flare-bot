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
	void write_mem();
};

inline Memory mem;

class Player
{
public:

	float x_value{ NULL };
	float y_value{ NULL };
	int x_value_cursor{ NULL };
	int y_value_cursor{ NULL };
	uintptr_t local_player{ NULL };
	uintptr_t base_pointer_cursor{ NULL };

};

inline Player player;

class Entity
{
public:

	float x_value;
	float y_value;
};

inline Entity entity;