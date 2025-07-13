#include <Windows.h>

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
	WriteFile(
		hCSV,
		pbd->szCsv,
		BEHAVIOUR_DATA_SIZE,
		NULL,
		NULL
	);
}