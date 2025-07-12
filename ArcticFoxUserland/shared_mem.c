#include <Windows.h>

#include "event.h"
#include "shared_mem.h"

HANDLE	g_FileMapping;
LPVOID	g_SharedMemAddr;

BOOL
InitSharedMem(
	VOID
)
{
	g_FileMapping = OpenFileMappingW(
		FILE_MAP_READ,
		FALSE,
		SHARED_MEM_NAME
	);

	if (g_FileMapping == NULL)
		return FALSE;
	
	g_SharedMemAddr = MapViewOfFile(
		g_FileMapping,
		FILE_MAP_READ,
		0, 0, 0
	);

	if (g_SharedMemAddr == NULL)
	{
		CloseHandle(g_FileMapping);
		return FALSE;
	}
	return TRUE;
}

VOID
ReadFromSharedMem(
	LPVOID	pBuffer,
	SIZE_T	stBufferSize
)
{
	WaitForEvent();

	RtlCopyMemory(
		pBuffer,
		g_SharedMemAddr,
		stBufferSize
	);

	ResetEvent2();
}