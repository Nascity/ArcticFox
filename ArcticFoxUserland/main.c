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
	if (!InitEvent())
		return -1;
	if (!InitSharedMem())
		return -2;

	ReadFromSharedMem(
		&bd, sizeof(bd)
	);

	wprintf(L"Kernel says: %s\n", bd.szTest);

	return 0;
}