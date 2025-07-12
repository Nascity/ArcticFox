#pragma once

#include <wdm.h>

#define SHARED_MEM_NAME	L"\\BaseNamedObjects\\ArcticFoxSharedMem"
#define SHARED_MEM_SIZE	4096

#define EVENT_NAME	L"\\BaseNamedObjects\\ArcticFoxEvent"

NTSTATUS
InitSharedMemory(
	VOID
);

NTSTATUS
InitSharedMemoryEvent(
	VOID
);