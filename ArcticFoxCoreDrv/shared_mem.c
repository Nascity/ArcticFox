#include <ntifs.h>

#include "../data.h"
#include "af_assert.h"
#include "init.h"
#include "shared_mem.h"
#include "process.h"

HANDLE	g_SharedMemHandle;
PVOID	g_SharedMemAddress;
HANDLE	g_SharedMemEventHandle;

NTSTATUS
InitSharedMemory(
	VOID
)
{
	UNICODE_STRING		usSectionName;
	LARGE_INTEGER		liMaxSize;
	OBJECT_ATTRIBUTES	ObjectAttribute;
	NTSTATUS			Status;
	SIZE_T				stViewSize;

	liMaxSize.QuadPart = SHARED_MEM_SIZE;

	RtlInitUnicodeString(
		&usSectionName,
		SHARED_MEM_NAME
	);

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
	if (Status == STATUS_OBJECT_NAME_COLLISION)
	{
		Status = ZwOpenSection(
			&g_SharedMemHandle,
			SECTION_ALL_ACCESS,
			&ObjectAttribute
		);
	}
	AF_ASSERT(Status);

	// create map view of section
	stViewSize = SHARED_MEM_SIZE;
	Status = ZwMapViewOfSection(
		g_SharedMemHandle,
		ZwCurrentProcess(),
		&g_SharedMemAddress,
		0,
		SHARED_MEM_SIZE,
		NULL,
		&stViewSize,
		ViewShare,
		0,
		PAGE_READWRITE
	);
	AF_ASSERT(Status);

	return STATUS_SUCCESS;
}

NTSTATUS
InitSharedMemoryEvent(
	VOID
)
{
	UNICODE_STRING		uiEventName = RTL_CONSTANT_STRING(EVENT_NAME);
	OBJECT_ATTRIBUTES	ObjectAttribute;
	NTSTATUS			Status;

	InitializeObjectAttributes(
		&ObjectAttribute,
		&uiEventName,
		OBJ_KERNEL_HANDLE,
		NULL,
		NULL
	);

	Status = ZwCreateEvent(
		&g_SharedMemEventHandle,
		EVENT_ALL_ACCESS,
		&ObjectAttribute,
		NotificationEvent,
		FALSE
	);
	if (Status == STATUS_OBJECT_NAME_COLLISION)
	{
		Status = ZwOpenEvent(
			&g_SharedMemEventHandle,
			EVENT_ALL_ACCESS,
			&ObjectAttribute
		);
	}
	AF_ASSERT(Status);

	return STATUS_SUCCESS;
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
		g_SharedMemAddress,
		pData,
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

VOID
ProcessActivityLogger(
	PVOID	Context
)
{
	PARCTIC_FOX_WORK_ITEM	FoxWorkItem;

	FoxWorkItem = (PARCTIC_FOX_WORK_ITEM)Context;

	if (g_SharedMemAddress)
	{
		WriteToSharedMem(
			&FoxWorkItem->Behaviour,
			sizeof(BEHAVIOUR_DATA)
		);
	}

	ExFreePoolWithTag(
		FoxWorkItem,
		FOX_WORK_ITEM_TAG
	);
}