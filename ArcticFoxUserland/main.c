#include <stdio.h>
#include <Windows.h>

#include "../data.h"
#include "csv.h"
#include "event.h"
#include "shared_mem.h"
#include "process.h"

#define TIMEOUT		10

BOOL
Init(
	VOID
)
{
	INT		i;

	// initialize stuff
	i = 0;
	while (!InitEvent())
	{
		i++;
		if (i >= TIMEOUT)
			return FALSE;
		Sleep(5000);
	}
	wprintf(L"InitEvent successful.\n");

	i = 0;
	while (!InitSharedMem())
	{
		i++;
		if (i >= TIMEOUT)
			return FALSE;
		Sleep(5000);
	}
	wprintf(L"InitSharedMem successful.\n");

	i = 0;
	while (!InitCSV())
	{
		i++;
		if (i >= TIMEOUT)
			return FALSE;
		Sleep(5000);
	}
	wprintf(L"InitCSV successful.\n");

	return TRUE;
}

INT
wmain(
	INT		argc,
	LPWSTR	argv[]
)
{
	BEHAVIOUR_DATA	bd = { 0, };
	
	if (!Init())
		return -1;

	if (argc == 2)
		TrackProcess(argv[1]);

	while (TRUE)
	{
		ReadFromSharedMem(
			&bd, sizeof(bd)
		);

		WriteCSV(&bd);
	}

	return 0;
}