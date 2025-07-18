#include <Windows.h>
#include <stdio.h>

#include "csv.h"

HANDLE	hCSV;

BOOL
InitCSV(
	VOID
)
{
	hCSV = CreateFileW(
		FILE_NAME,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hCSV == INVALID_HANDLE_VALUE)
		return FALSE;
	return TRUE;
}

VOID
WriteCSV(
	PBEHAVIOUR_DATA	pbd
)
{
	WCHAR	szBuffer[BEHAVIOUR_DATA_SIZE];
	
	if (pbd->DataType == PROCESS_BEHAVIOUR)
	{
		// parent PID, child PID, image file name, cmdline
		swprintf(
			szBuffer,
			BEHAVIOUR_DATA_SIZE,
			L"PROCESS,%lld,%lld,%s,%s\n",
			pbd->Data.ProcessData.ulParentPid,
			pbd->Data.ProcessData.ulChildPid,
			pbd->Data.ProcessData.szImageFileName,
			pbd->Data.ProcessData.szCommandLine
		);
	}
	else if (pbd->DataType == TRACK_PROCESS)
	{
		swprintf(
			szBuffer,
			BEHAVIOUR_DATA_SIZE,
			L"TRACK,%ud\n",
			pbd->Data.TrackProcessData.dwProcessId
		);
	}

	wprintf(L"Kernel said: %s", szBuffer);

	WriteFile(
		hCSV,
		szBuffer,
		wcslen(szBuffer) * sizeof(WCHAR),
		NULL,
		NULL
	);
}