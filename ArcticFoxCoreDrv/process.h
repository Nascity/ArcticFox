#pragma once

#include "../data.h"

#define FOX_WORK_ITEM_TAG	'afox'

typedef struct
{
	WORK_QUEUE_ITEM		WorkItem;
	BEHAVIOUR_DATA		Behaviour;
}	ARCTIC_FOX_WORK_ITEM, *PARCTIC_FOX_WORK_ITEM;

VOID
ProcessNotify(
	HANDLE	hParent,
	HANDLE	hChild,
	BOOLEAN	bCreate
);