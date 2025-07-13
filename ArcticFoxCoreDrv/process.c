#include <ntddk.h>
#include <wdm.h>

#include <ntstrsafe.h>	// temp

#include "../data.h"
#include "shared_mem.h"
#include "process.h"

// DO NOT CALL WriteToSharedMem IN HERE!!!
// KERNEL PANICS AHEAD!!!
// THIS FUNCTION RUNS IN DIFFERENT PROCESS'S CONTEXT!!!
VOID
ProcessNotify(
	HANDLE	hParent,
	HANDLE	hChild,
	BOOLEAN	bCreate
)
{
	PARCTIC_FOX_WORK_ITEM	FoxWorkItem;

	FoxWorkItem = ExAllocatePool2(
		POOL_FLAG_NON_PAGED,
		sizeof(ARCTIC_FOX_WORK_ITEM),
		FOX_WORK_ITEM_TAG
	);
	if (FoxWorkItem)
	{
		DbgPrint("[AF] PROCESS,%lld,%lld,%d\n",
			(ULONG_PTR)hParent,
			(ULONG_PTR)hChild,
			bCreate
		);

		RtlStringCbPrintfW(
			FoxWorkItem->Behaviour.szCsv,
			64,
			L"PROCESS,%lld,%lld,%d\n",
			(ULONG_PTR)hParent,
			(ULONG_PTR)hChild,
			bCreate
		);

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