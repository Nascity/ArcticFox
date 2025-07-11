#include <Ntddk.h>
#include <wdm.h>
#include <assert.h>

#include "af_assert.h"
#include "init.h"

VOID
ArcticFoxUnload(
	__in	PDRIVER_OBJECT	DriverObject
)
{
	UNREFERENCED_PARAMETER(DriverObject);
}

NTSTATUS
DriverEntry(
	__in	PDRIVER_OBJECT	DriverObject,
	__in	PUNICODE_STRING	RegistryPath
)
{
	NTSTATUS	Status;

	UNREFERENCED_PARAMETER(RegistryPath);

	// register the unload function
	DriverObject->DriverUnload = ArcticFoxUnload;

	Status = InitSharedMemory();
	AF_ASSERT(Status);

	return STATUS_SUCCESS;
}