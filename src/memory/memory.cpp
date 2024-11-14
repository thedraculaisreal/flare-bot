#include "memory.h"
#include <tchar.h>

uintptr_t Memory::get_module_base_address(const char* lpsz_module_name, DWORD pid)
{
	uintptr_t module_base_address{ 0 };
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
		exit(1);
	}

	DWORD pid{ NULL };
	GetWindowThreadProcessId(h_game_window, &pid);

	process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (process_handle == INVALID_HANDLE_VALUE)
	{
		printf("Faield to open process, %ld", GetLastError());
		exit(1);
	}

	base_address = get_module_base_address("flare.exe", pid);
	if (!base_address)
	{
		printf("failed to get base_address of flare.exe exiting...\n");
		CloseHandle(process_handle);
		exit(1);
	}
}

void Memory::read_mem()
{
	ReadProcessMemory(process_handle, reinterpret_cast<LPCVOID>(base_address + 0x1CD278), &player.local_player, sizeof(player.local_player), NULL);
	ReadProcessMemory(process_handle, reinterpret_cast<LPCVOID>(base_address + 0x1CD29C), &player.base_pointer_cursor, sizeof(player.base_pointer_cursor), NULL);
	ReadProcessMemory(process_handle, reinterpret_cast<LPCVOID>(player.base_pointer_cursor + 0x868), &player.x_value_cursor, sizeof(player.x_value_cursor), NULL);
	ReadProcessMemory(process_handle, reinterpret_cast<LPCVOID>(player.base_pointer_cursor + 0x86C), &player.y_value_cursor, sizeof(player.y_value_cursor), NULL);
	ReadProcessMemory(process_handle, reinterpret_cast<LPCVOID>(player.local_player + 0x250), &player.x_value, sizeof(player.x_value), NULL);
	ReadProcessMemory(process_handle, reinterpret_cast<LPCVOID>(player.local_player + 0x24C), &player.y_value, sizeof(player.y_value), NULL);

	std::cout << "base_address: " << std::hex << mem.base_address << "\n";
	std::cout << "local_player addr: " << std::hex << player.local_player << '\n';
	std::cout << "cursor x value: " << std::dec << player.x_value_cursor << '\n';
	std::cout << "cursor y value: " << std::dec << player.y_value_cursor << '\n';
	std::cout << "x_value: " << std::dec << player.x_value << '\n';
	std::cout << "y_value: " << std::dec << player.y_value << '\n';
}