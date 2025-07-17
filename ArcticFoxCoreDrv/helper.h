#pragma once

#include <ntddk.h>
#include <wdm.h>
#include <ntstrsafe.h>

VOID
CopyUnicodeStringToWchar(
	PCUNICODE_STRING	Source,
	PWSTR				Dest,
	SIZE_T				DestCount
);