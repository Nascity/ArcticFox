#pragma once

#include <ntddk.h>
#include <wdm.h>

VOID
ProcessNotify(
	HANDLE	hParent,
	HANDLE	hChild,
	BOOLEAN	bCreate
);