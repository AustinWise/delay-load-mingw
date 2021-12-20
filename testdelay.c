#include <windows.h>
#include <delayimp.h>
#include <stdio.h>

// For delay-loaded DLLs,
// use LOAD_LIBRARY_SEARCH_SYSTEM32 to avoid DLL search order hijacking.
FARPROC WINAPI dllDelayLoadHook(unsigned dliNotify, PDelayLoadInfo pdli)
{
	if (dliNotify == dliNotePreLoadLibrary)
	{
		// Windows 7 without KB2533623 does not support the LOAD_LIBRARY_SEARCH_SYSTEM32 flag.
		// That is is OK, because the delay load handler will interrupt the NULL return value
		// to mean that it should perform a normal LoadLibrary.
		fprintf(stderr, "loading %s\n", pdli->szDll);
		return (FARPROC)LoadLibraryExA(pdli->szDll, NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
	}

	return NULL;
}

#ifndef DELAYIMP_INSECURE_WRITABLE_HOOKS
//const
#endif
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
