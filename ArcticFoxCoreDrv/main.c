#include <Ntddk.h>
#include <wdm.h>
#include <assert.h>

#include "af_assert.h"
#include "init.h"
#include "process.h"

VOID
ArcticFoxUnload(
	__in	PDRIVER_OBJECT	DriverObject
)
{
	UNREFERENCED_PARAMETER(DriverObject);

	// remove the notify routine
	PsSetCreateProcessNotifyRoutineEx(
		ProcessNotifyRoutine, TRUE
	);

	NT_ASSERT(NT_SUCCESS(CleanUpSharedMemoryEvent()));
	NT_ASSERT(NT_SUCCESS(CleanUpSharedMemory()));

	DbgPrint("[AF] Driver unloaded.\n");
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

	// make communicating tunnel for user mode application
	Status = InitSharedMemory();
	AF_ASSERT(Status);
	DbgPrint("[AF] Shared memory initialized.\n");

	// make the event
	Status = InitSharedMemoryEvent();
	AF_ASSERT(Status);
	DbgPrint("[AF] Event initialized.\n");

	// register the notify function
	Status = PsSetCreateProcessNotifyRoutineEx(
		ProcessNotifyRoutine, FALSE
	);
	AF_ASSERT(Status);
	DbgPrint("[AF] Process notify routine registered.\n");

	DbgPrint("[AF] All set!\n");
	return STATUS_SUCCESS;
}