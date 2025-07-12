#pragma once

#include <wdm.h>

#define AF_ASSERT(status)	do { NT_ASSERT(NT_SUCCESS(status)); if (!NT_SUCCESS(status)) return status; } while (0)