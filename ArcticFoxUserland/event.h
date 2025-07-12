#pragma once

#include <Windows.h>

#define EVENT_NAME		L"ArcticFoxEvent"

BOOL
InitEvent(
	VOID
);

VOID
WaitForEvent(
	VOID
);

VOID
ResetEvent2(
	VOID
);