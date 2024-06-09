#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<CommCtrl.h>
#include<cstdio>
#include"resource.h"

 



BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;


}

//Процедура окна - это самая обычная функция, которая вызываеться при запуске окна
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//Все принимаемы параметры - числовое значение длинной 4 байта.
	//HWND - Handler to Window (обработчик окна) - это числоб  которое инденифицирует окно.
	//Любые обращения к окну можно выполнить только через его обработчик
	//uMsg - Messege, сообщение, которое отправляеться к окну.
	//wParam,Iparam - параметры сообщения. Они еще делятся на LOWORD и HIWORD
	//LOWORD - младшее слово. HIWORD - старшее слово
	//WORD(слово)- это два байта 
	
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND nUpDown = GetDlgItem(hwnd, IDC_SPIN_PREFIC); 

		//Функция GetDlgItem()  получает HWND элеменат интерфэйса по его ID
		SendMessage(nUpDown, UDM_SETRANGE32, 0, 32);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_IPADDRESS: 
		{
			CONST INT SIZE = 256;
			CHAR sz_info[SIZE]{};

			HWND hIPaddres = GetDlgItem(hwnd, IDC_IPADDRESS);
			HWND hStaticInfo = GetDlgItem(hwnd, IDC_STATIC_INFO);
			//EN_ - Edit notification (Уведомление)  
			if (HIWORD(wParam) == EN_CHANGE)
			{
				//BYTE = 8 bui; CHAR
				//WORD = 2 bitea (16 bit); SHORT
				//DWORD - Double Word двойное слово = 4 Bytes(32 bit); INT
				//QWORD - Quad Word учетверенное слово = 8 bites(64 bit); LONG LONG
				//TBYTE - Ten Bytes десять байт = 80 bit;  
				//DQWORD - Double Quad Word двойное учетверенное слово = 128 bit
				DWORD dw_address;
				SendMessage(hIPaddres, IPM_GETADDRESS, 0, (LPARAM)&dw_address);
				INT first = FIRST_IPADDRESS(dw_address);
				INT second = SECOND_IPADDRESS(dw_address);
				INT third =  THIRD_IPADDRESS(dw_address);
				INT fourth =  FOURTH_IPADDRESS(dw_address);

				sprintf_s(sz_info, SIZE, "Info:\nFirst: %i, Second: %i, Third: %i, Forth: %i", first, second, third,  fourth);
				SendMessage(hStaticInfo, WM_SETTEXT, 0, (LPARAM)sz_info);


			}
		}			

		break;
		case IDOK: MessageBox(hwnd,"Была нажата кнопка OK","Info", MB_OK | MB_ICONINFORMATION); break;
			//MB_OK | MB_ICONINFORMATION - | это or
			// || - логическое OR
			// | - побитовое OR
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:

		EndDialog(hwnd, 0);

	}
	return FALSE;

} 



