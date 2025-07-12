#pragma once

#include <wdm.h>

#define AF_ASSERT(status)	do { NT_ASSERT(NT_SUCCESS(status)); if (!NT_SUCCESS(status)) { DbgPrint("[AF] Assert failure at %s:%d.\n", __FILE__, __LINE__); return status; } } while (0)