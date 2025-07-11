#include <Ntddk.h>
#include <wdm.h>

#include "af_assert.h"
#include "init.h"

HANDLE	g_SharedMemHandle;
PVOID	g_SharedMemAddress;

NTSTATUS
InitSharedMemory(
	VOID
)
/*
* This function makes shared memory for
* communication between the driver and
* the user mode process.
*/
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

	stViewSize = 0;
	return ZwMapViewOfSection(
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
}