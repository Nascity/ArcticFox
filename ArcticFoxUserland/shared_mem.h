#pragma once

#include <Windows.h>
#include "../data.h"

#define SHARED_MEM_NAME	L"ArcticFoxSharedMem"

BOOL
InitSharedMem(
	VOID
);

VOID
ReadFromSharedMem(
	LPVOID	pBuffer,
	SIZE_T	stBufferSize
);