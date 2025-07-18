#include "csv.h"
#include "process.h"

VOID
TrackProcess(
	LPWSTR	szProcessName
)
{
	STARTUPINFOW		si;
	PROCESS_INFORMATION	pi;
	BEHAVIOUR_DATA		bd;

	if (!CreateProcessW(
		szProcessName,
		NULL, NULL, NULL,
		FALSE, 0, NULL,
		NULL, &si, &pi
	))
		return;

	bd.DataType = TRACK_PROCESS;
	bd.Data.TrackProcessData.dwProcessId = pi.dwProcessId;

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	WriteCSV(&bd);
}