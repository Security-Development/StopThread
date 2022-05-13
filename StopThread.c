#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

int main() {
	DWORD pid;
	HANDLE sProc, hThd;
	THREADENTRY32 te32= {0};
	te32.dwSize = sizeof( THREADENTRY32 );
	
	printf("[INPUT]TARGET PROCESS PID : ");
	scanf("%d", &pid);

	sProc = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);
	
	if( !Thread32First(sProc, &te32)) {
		CloseHandle(sProc); // Handle clear
	}
	
	while(Thread32Next(sProc, &te32)) {
		if( te32.th32OwnerProcessID == pid) {
				printf("[+] Thread Id : 0x%x\n", te32.th32ThreadID);
				hThd = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID); // found Target Process Thread
					SuspendThread(hThd);
					printf("Stop!!\n\n");
			}
	}
	
	CloseHandle(sProc);
	
	return 0;
}
