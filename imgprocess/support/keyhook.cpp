#include "Windows.h"
#include <iostream>
using namespace std;

HHOOK hookHandle;

LRESULT CALLBACK keyHandler(int nCode, WPARAM wParam, LPARAM lParam);

int main(int argc, char* argv[]) {

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