#pragma once

#include "../data.h"

#define FILE_NAME	L"log.csv"

BOOL
InitCSV(
	VOID
);

VOID
WriteCSV(
	PBEHAVIOUR_DATA	pbd
);