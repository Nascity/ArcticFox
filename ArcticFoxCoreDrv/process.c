#include <ntddk.h>
#include <wdm.h>

#include "../data.h"
#include "helper.h"
#include "shared_mem.h"
#include "process.h"

VOID
InitProcessBehaviorStruct(
	PPS_CREATE_NOTIFY_INFO	CreateInfo,
	PBEHAVIOUR_DATA			Behavior
)
{
	Behavior->DataType = PROCESS_BEHAVIOUR;
	Behavior->Data.ProcessData.ulParentPid = (ULONG_PTR)CreateInfo->ParentProcessId;
	Behavior->Data.ProcessData.ulChildPid = (ULONG_PTR)CreateInfo->CreatingThreadId.UniqueProcess;

	CopyUnicodeStringToWchar(
		CreateInfo->ImageFileName,
		Behavior->Data.ProcessData.szImageFileName,
		IMAGE_FILE_NAME_LEN
	);
	CopyUnicodeStringToWchar(
		CreateInfo->CommandLine,
		Behavior->Data.ProcessData.szCommandLine,
		COMMAND_LINE_LEN
	);

	DbgPrint(
		"[AF] ParentPID: %lld, ChildPID: %lld, ImageFile: %wZ, CmdLine: %wZ",
		(ULONG_PTR)CreateInfo->ParentProcessId,
		(ULONG_PTR)CreateInfo->CreatingThreadId.UniqueProcess,
		CreateInfo->ImageFileName, CreateInfo->CommandLine
	);
}

// DO NOT CALL WriteToSharedMem IN HERE!!!
// KERNEL PANICS AHEAD!!!
// THIS FUNCTION RUNS IN DIFFERENT PROCESS'S CONTEXT!!!
VOID
ProcessNotifyRoutine(
	PEPROCESS 	Process,
	HANDLE		ProcessId,
	PPS_CREATE_NOTIFY_INFO	CreateInfo
)
{
	PARCTIC_FOX_WORK_ITEM	FoxWorkItem;

	UNREFERENCED_PARAMETER(Process);
	UNREFERENCED_PARAMETER(ProcessId);

	if (!CreateInfo)
	{
		DbgPrint("[AF] CreateInfo is null.\n");
		return;
	}
	else if (CreateInfo->IsSubsystemProcess)
	{
		DbgPrint("[AF] Subsystem!\n");
		return;
	}

	FoxWorkItem = ExAllocatePool2(
		POOL_FLAG_NON_PAGED,
		sizeof(ARCTIC_FOX_WORK_ITEM),
		FOX_WORK_ITEM_TAG
	);
	if (FoxWorkItem)
	{
		InitProcessBehaviorStruct(CreateInfo, &FoxWorkItem->Behavior);

		ExInitializeWorkItem(
			&FoxWorkItem->WorkItem,
			ProcessActivityLogger,
			FoxWorkItem
		);

		ExQueueWorkItem(
			&FoxWorkItem->WorkItem,
			DelayedWorkQueue
		);
	}
}