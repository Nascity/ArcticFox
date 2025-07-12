#pragma once

VOID
WriteToSharedMem(
	PVOID	pData,
	SIZE_T	stWriteSize
);

VOID
ProcessActivityLogger(
	PVOID	Context
);