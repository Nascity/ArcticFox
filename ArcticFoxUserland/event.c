#include <Windows.h>

#include "event.h"

HANDLE	g_SharedMemEvent;

BOOL
InitEvent(
	VOID
)
{
	// create event object
	g_SharedMemEvent = OpenEventW(
		SYNCHRONIZE, FALSE, EVENT_NAME
	);

	if (g_SharedMemEvent == NULL)
		return FALSE;
	return TRUE;
}

VOID
WaitForEvent(
	VOID
)
{
	DWORD	dwResult;

	while (TRUE)
	{
		dwResult = WaitForSingleObject(
			g_SharedMemEvent, INFINITE
		);

		if (dwResult == WAIT_OBJECT_0)
			return;
	}
}

VOID
ResetEvent(
	VOID
)
{
	ResetEvent(g_SharedMemEvent);
}