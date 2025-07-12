#include <stdio.h>
#include <Windows.h>

#include "event.h"
#include "shared_mem.h"
#include "../data.h"

INT
wmain(
	INT		argc,
	LPWSTR	argv[]
)
{
	BEHAVIOUR_DATA	bd;

	// initialize stuff
	while (!InitEvent())
	{
		wprintf(L"InitEvent %d\n", GetLastError());
		Sleep(5000);
	}
	wprintf(L"InitEvent successful.\n");

	while (!InitSharedMem())
	{
		wprintf(L"InitSharedMem %d\n", GetLastError());
		Sleep(5000);
	}
	wprintf(L"InitSharedMem successful.\n");

	while (TRUE)
	{
		ReadFromSharedMem(
			&bd, sizeof(bd)
		);

		wprintf(L"Kernel says: %s\n", bd.szTest);
	}

	return 0;
}