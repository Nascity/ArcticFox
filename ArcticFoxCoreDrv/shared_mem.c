#include <ntifs.h>

#include "af_assert.h"
#include "init.h"
#include "shared_mem.h"

HANDLE	g_SharedMemHandle;
PVOID	g_SharedMemAddress;
HANDLE	g_SharedMemEventHandle;

NTSTATUS
InitSharedMemory(
	VOID
)
{
	UNICODE_STRING		usSectionName = RTL_CONSTANT_STRING(SHARED_MEM_NAME);
	LARGE_INTEGER		liMaxSize;
	OBJECT_ATTRIBUTES	ObjectAttribute;
	NTSTATUS			Status;
	SIZE_T				stViewSize;

	liMaxSize.QuadPart = SHARED_MEM_SIZE;

	InitializeObjectAttributes(
		&ObjectAttribute, &usSectionName,
		OBJ_KERNEL_HANDLE, NULL, NULL
	);

	// create section object
	Status = ZwCreateSection(
		&g_SharedMemHandle,
		SECTION_ALL_ACCESS,
		&ObjectAttribute,
		&liMaxSize,
		PAGE_READWRITE,
		SEC_COMMIT,
		NULL
	);
	AF_ASSERT(Status);

	// create map view of section
	stViewSize = 0;
	Status = ZwMapViewOfSection(
		g_SharedMemHandle,
		ZwCurrentProcess(),
		&g_SharedMemAddress,
		0,
		0,
		NULL,
		&stViewSize,
		ViewShare,
		0,
		PAGE_READWRITE
	);
	AF_ASSERT(Status);

	return TRUE;
}

NTSTATUS
InitSharedMemoryEvent(
	VOID
)
{
	UNICODE_STRING		uiEventName = RTL_CONSTANT_STRING(EVENT_NAME);
	OBJECT_ATTRIBUTES	ObjectAttribute;

	InitializeObjectAttributes(
		&ObjectAttribute,
		&uiEventName,
		OBJ_KERNEL_HANDLE,
		NULL,
		NULL
	);

	return ZwCreateEvent(
		&g_SharedMemEventHandle,
		EVENT_ALL_ACCESS,
		&ObjectAttribute,
		NotificationEvent,
		FALSE
	);
}

VOID
WriteToSharedMem(
	PVOID	pData,
	SIZE_T	stWriteSize
)
{
	SIZE_T	stRealSize;

	if (stWriteSize >= SHARED_MEM_SIZE)
		stRealSize = SHARED_MEM_SIZE;
	else
		stRealSize = stWriteSize;

	RtlCopyMemory(
		pData,
		g_SharedMemAddress,
		stRealSize
	);

	ZwSetEvent(
		g_SharedMemEventHandle,
		NULL
	);
}

NTSTATUS
CleanUpSharedMemory(
	VOID
)
{
	return ZwClose(g_SharedMemHandle);
}

NTSTATUS
CleanUpSharedMemoryEvent(
	VOID
)
{
	return ZwClose(g_SharedMemEventHandle);
}