//#include<iostream>
//#include<windows.h>
//using namespace std;
//
//BOOL WINAPI handler(DWORD signal){
//	if(signal == CTRL_C_EVENT){
//		std::cout<<"you can't close me!\n";
//		return TRUE;
//	}
//	return FALSE;
//	}
//	
//	
//int main(){
//	
//	SetConsoleCtrlHandler(handler, TRUE);
//	
//	while(true){
//		std::cout<<"Running..\n";
//		sleep(1000);
//	}
//}



//-------------------------------------------------------------


#include<iostream>
#include<windows.h>
using namespace std;


int main(){
	STARTUPINFOA si{};
	PROCESS_INFORMATION pi{};
	
	si.cb = sizeof(si);
	
	char command[] = "cmd.exe /C echo I am the child";
	
	if(CreateProcessA(nullptr, command, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)){
		std::cout << "Iam the parent\n";
	}
	
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	
}

