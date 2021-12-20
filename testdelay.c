#include <windows.h>
#include <delayimp.h>
#include <stdio.h>

FARPROC WINAPI dllDelayLoadHook(unsigned dliNotify, PDelayLoadInfo pdli)
{
	if (dliNotify == dliNotePreLoadLibrary)
	{
		fprintf(stderr, "loading %s\n", pdli->szDll);
		return (FARPROC)LoadLibraryExA(pdli->szDll, NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
	}

	return NULL;
}

//TODO: understand why this is `const` under MSVC but not GCC
PfnDliHook __pfnDliNotifyHook2 = dllDelayLoadHook;

int
main(int argc, int argv)
{
	setvbuf(stderr, NULL, _IONBF, 0);
	fprintf(stderr, "start\n");
	DWORD handle;
	DWORD ret = GetFileVersionInfoSizeW(L"kernel32.dll", &handle);
	fprintf(stderr, "ret = %d\n", ret);
	return 0;
}
