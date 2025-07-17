#include "helper.h"

VOID
CopyUnicodeStringToWchar(
	PCUNICODE_STRING	Source,
	PWSTR				Dest,
	SIZE_T				DestLen
)
{
	SIZE_T	CopyLen;

	if (!Source || !Dest || DestLen == 0)
		return;

	CopyLen = Source->Length / sizeof(WCHAR);

	if (CopyLen >= DestLen)
		CopyLen = DestLen - 1;

	RtlStringCchCopyNW(
		Dest, DestLen,
		Source->Buffer, CopyLen
	);

	Dest[CopyLen] = 0;
}