#pragma once

#define SHARED_MEM_NAME	L"\\Sessions\\1\\BaseNamedObjects\\ArcticFoxSharedMem"
#define SHARED_MEM_SIZE	4096

#define EVENT_NAME	L"\\Sessions\\1\\BaseNamedObjects\\ArcticFoxEvent"

NTSTATUS
InitSharedMemory(
	VOID
);

NTSTATUS
InitSharedMemoryEvent(
	VOID
);

NTSTATUS
CleanUpSharedMemory(
	VOID
);

NTSTATUS
CleanUpSharedMemoryEvent(
	VOID
);