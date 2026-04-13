#include <windows.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "specials.c"
#define BUFF_SIZE 16
#define PASTEL_PINK RGB(255, 182, 193)
#define PASTEL_BLUE RGB(173, 216, 230)
#define PASTEL_GREEN RGB(152, 251, 152)
#define PASTEL_YELLOW RGB(255, 255, 224)
#define path "specials.txt"
HHOOK hMouseHook;
int mouseButtonToMap = 0; //determines which button to map.
int isTargetButtonOne = 0;//these to are helping with that. I'm a D rank programmer
int	isTargetButtonTwo = 0;
WORD keyToMapOne = 'e'; //can't figure out how to do this with an array and pointers so I'm going the 80IQ rout with 2 variables one for each button we're remapping
WORD keyToMapTwo = 'f'; //this 2 variables store what key we are remapping to. 

void setBuffEmpty(char* target, int length){//helper function to clean up an array just in case.
	for (int x = 0; x<length;x++){
		target[x] = '\0';
}
return;
}
int determineButton(char* buff){//what Special (like ctrl/shift etc) button we are switching our extra mouse to. If no match is found returns -1. Check specials.c for a list of special buttons.
	for(int x = 0; specials[x].name;x++){
		if(!strcmp(buff, specials[x].name)){
					return x;
		}
	}
	return -1;
}
LRESULT activateButton(int buttonToActivate, WPARAM wParam){//activates the mapping. 
	INPUT input = {0};
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = buttonToActivate;
	if (wParam == WM_XBUTTONDOWN) {
		input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY; // key press, works for holding
		SendInput(1, &input, sizeof(INPUT));			
		return 1;//this should prevent original button activation, but for some reason I had to move it to the parent function to achieve that.
	}else if (wParam == WM_XBUTTONUP){
		input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP; //key release.
		SendInput(1, &input, sizeof(INPUT));
		return 1;
	}
	return 1;
}
HBRUSH SetBackgroundColor(COLORREF color) {
    return CreateSolidBrush(color);
}
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {//holds button press event.
    if (nCode >= 0) {
		MSLLHOOKSTRUCT* mouseInfo = (MSLLHOOKSTRUCT*)lParam;
		if(isTargetButtonOne && HIWORD(mouseInfo->mouseData) == XBUTTON1){
			return activateButton(keyToMapOne, wParam);
		}else if(isTargetButtonTwo && HIWORD(mouseInfo->mouseData) == XBUTTON2){
			return activateButton(keyToMapTwo, wParam);
		}
    }
    return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { //Main logic for buttons. wParam numbers are taken from WinMain
	WORD* keyToMap[2] = {&keyToMapOne,&keyToMapTwo}; //helps with changing button the variables. 
    switch (uMsg) {
        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
				mouseButtonToMap = 1;
                isTargetButtonOne = 1;
            } else if (LOWORD(wParam) == 2) {
				mouseButtonToMap = 2;
                isTargetButtonTwo = 1;
            } else if (LOWORD(wParam) == 3) {				
                char buffer[BUFF_SIZE];
				setBuffEmpty(buffer,BUFF_SIZE);
                GetDlgItemText(hwnd, 1002, buffer, BUFF_SIZE);
                if(!mouseButtonToMap){
					MessageBox(hwnd, "Please select a button to map.", "Error", MB_OK | MB_ICONERROR);
				}else if (isalpha(buffer[0])) {
					char message[256];
					if(buffer[1]){//special key entered - in text field more than one letter
						int specialIndex = determineButton(buffer);
						if(specialIndex<0){ //couldn't match to any special key. Check specials.c;
							MessageBox(hwnd, "Invalid key. Please enter a valid alphabet key.", "Error", MB_OK | MB_ICONERROR);
						}else{//map mouse button to a special key, example shift/control/alt
							*keyToMap[mouseButtonToMap-1] = specials[specialIndex].value;
							sprintf(message,"Mouse button %d is now mapped to '%s'.\n ", mouseButtonToMap,specials[specialIndex].name);
							MessageBox(hwnd, message, "Mapping Set", MB_OK);
							}
					}else{//map button to a regular key, for axample a "c";
						*keyToMap[mouseButtonToMap-1] = toupper(buffer[0]);//in case input is lowerCase switching to upperCase. It's neccessary because c and C are different integers.
						sprintf(message,"Mouse button %d is now mapped to '%c'.",mouseButtonToMap, buffer[0]);
						MessageBox(hwnd, message, "Mapping Set", MB_OK);
					}
                    
				}else{
                    MessageBox(hwnd, "Invalid key. Please enter a valid alphabet key.", "Error", MB_OK | MB_ICONERROR);
                }
            }else if (LOWORD(wParam) == 4){//reset button mappings
				mouseButtonToMap = 0;
				isTargetButtonOne = 0;
				isTargetButtonTwo = 0;
				keyToMapOne = 'e';
				keyToMapTwo = 'f'; 
				MessageBox(hwnd,"Button Mappings have been reset.","Mapping reset", MB_OK);
			}
            break;
        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wParam;
            SetBkColor(hdcStatic, PASTEL_YELLOW);
            return (INT_PTR)SetBackgroundColor(PASTEL_YELLOW);
        }
        case WM_CTLCOLORBTN: {
            HDC hdcButton = (HDC)wParam;
            SetBkColor(hdcButton, PASTEL_GREEN);
            return (INT_PTR)SetBackgroundColor(PASTEL_GREEN);
        }
        case WM_CTLCOLOREDIT: {
            HDC hdcEdit = (HDC)wParam;
            SetBkColor(hdcEdit, PASTEL_BLUE);
            return (INT_PTR)SetBackgroundColor(PASTEL_BLUE);
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char* CLASS_NAME = "Mouse Remapper";
    
    
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = SetBackgroundColor(PASTEL_PINK); 
    
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Mouse Mapper Simple",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 250,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    
    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    
    CreateWindow("STATIC", "Select Mouse Button:", WS_VISIBLE | WS_CHILD, 20, 20, 200, 20, hwnd, NULL, hInstance, NULL);
    HWND button1 = CreateWindow("BUTTON", "Side Button 1", WS_VISIBLE | WS_CHILD, 20, 50, 100, 30, hwnd, (HMENU)1, hInstance, NULL);
    HWND button2 = CreateWindow("BUTTON", "Side Button 2", WS_VISIBLE | WS_CHILD, 140, 50, 100, 30, hwnd, (HMENU)2, hInstance, NULL);
    
    CreateWindow("STATIC", "Enter Key to Map:", WS_VISIBLE | WS_CHILD, 20, 100, 200, 20, hwnd, NULL, hInstance, NULL);
    HWND editBox = CreateWindow("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 130, 100, 20, hwnd, (HMENU)1002, hInstance, NULL);
    HWND setButton = CreateWindow("BUTTON", "Set Mapping", WS_VISIBLE | WS_CHILD, 140, 130, 100, 30, hwnd, (HMENU)3, hInstance, NULL);
	HWND button3 = CreateWindow("BUTTON", "Reset", WS_VISIBLE | WS_CHILD, 70, 170, 100, 30, hwnd, (HMENU)4, hInstance,NULL);
    
    HFONT hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
    SendMessage(button1, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(button2, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(button3, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(editBox, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(setButton, WM_SETFONT, (WPARAM)hFont, TRUE);
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    
    hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInstance, 0);
    if (hMouseHook == NULL) {
        MessageBox(NULL, "Failed to set mouse hook. Please run as administrator.", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    
    
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    
    UnhookWindowsHookEx(hMouseHook);
    
    return 0;
}
