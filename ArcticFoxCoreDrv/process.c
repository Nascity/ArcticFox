#include <ntddk.h>
#include <wdm.h>

#include <ntstrsafe.h>	// temp

#include "shared_mem.h"
#include "process.h"
#include "../data.h"

VOID
ProcessNotify(
	HANDLE	hParent,
	HANDLE	hChild,
	BOOLEAN	bCreate
)
{
	BEHAVIOUR_DATA	bd;

	RtlStringCbPrintfW(
		bd.szTest,
		64,
		L"parent: %lld, child: %lld, (%d)",
		(ULONG_PTR)hParent,
		(ULONG_PTR)hChild,
		bCreate
	);
}