#pragma once

#include "../data.h"

#define FOX_WORK_ITEM_TAG	'afox'

typedef struct
{
	WORK_QUEUE_ITEM		WorkItem;
	BEHAVIOUR_DATA		Behavior;
}	ARCTIC_FOX_WORK_ITEM, *PARCTIC_FOX_WORK_ITEM;

VOID
ProcessNotifyRoutine(
	PEPROCESS 	Process,
	HANDLE		ProcessId,
	PPS_CREATE_NOTIFY_INFO	CreateInfo
);