#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

int main() {
	DWORD pid;
	HANDLE sProc = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0), hThd;
	THREADENTRY32 te32= {0};
	te32.dwSize = sizeof( THREADENTRY32 );
	
	printf("[INPUT]TARGET PROCESS PID : ");
	scanf("%d", &pid);
	
	if( !Thread32First(sProc, &te32)) {
		CloseHandle(sProc); // Handle clear
	}
	
	while(Thread32Next(sProc, &te32)) {
		if( te32.th32OwnerProcessID == pid) {
				printf("타켓 프로세스를 찾았습니다!.");
				hThd = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID); // found Target Process Thread
				if( hThd != NULL) {
					SuspendThread(hThd);
					CloseHandle(hThd);
					return 1;
				}
			}
	}
	
	CloseHandle(sProc);
	
	return 0;
}
