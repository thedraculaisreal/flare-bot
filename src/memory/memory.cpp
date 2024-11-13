#include "memory.h"
#include <tchar.h>

DWORD Memory::get_module_base_address(const char* lpsz_module_name, DWORD pid)
{
	DWORD module_base_address{ 0 };
	HANDLE h_snapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid) };
	MODULEENTRY32 module_entry32{ 0 };
	module_entry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(h_snapshot, &module_entry32))
	{
		do {
			if (strcmp(module_entry32.szModule, lpsz_module_name) == 0)
			{
				module_base_address = (DWORD)module_entry32.modBaseAddr;
				break;
			}

		} while (Module32Next(h_snapshot, &module_entry32));
	}
	CloseHandle(h_snapshot);
	return module_base_address;
}

void Memory::find_exe()
{
	HWND h_game_window{ FindWindow(NULL, "Flare") };
	if (!h_game_window)
	{
		printf("Failed to get handle to window, %ld", GetLastError());
		return;
	}

	DWORD pid{ NULL };
	GetWindowThreadProcessId(h_game_window, &pid);

	HANDLE process_handle{ OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid) };
	if (process_handle == INVALID_HANDLE_VALUE)
	{
		printf("Faield to open process, %ld", GetLastError());
		return;
	}

	base_address = get_module_base_address("flare.exe", pid);
	if (!base_address)
	{
		printf("failed to get base_address of flare.exe exiting...\n");
		CloseHandle(process_handle);
		exit(1);
	}
	printf("Base Address: %d", base_address);
}