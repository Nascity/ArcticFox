#pragma once

#define BEHAVIOUR_DATA_SIZE	4096
#define IMAGE_FILE_NAME_LEN	256
#define COMMAND_LINE_LEN	1024

typedef struct
{
	enum { PROCESS_BEHAVIOUR } DataType;
	union
	{
		struct
		{
			unsigned long long	ulParentPid;
			unsigned long long	ulChildPid;
			wchar_t	szImageFileName[IMAGE_FILE_NAME_LEN];
			wchar_t	szCommandLine[COMMAND_LINE_LEN];
		} ProcessData;
	} Data;
}	BEHAVIOUR_DATA, *PBEHAVIOUR_DATA;