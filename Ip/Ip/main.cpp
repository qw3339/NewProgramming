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
//BOOL checMask(DWORD mask)
//{
//	//DWORD  pattern = 1 << 32;
//	for (int i = 0; i < 32; i++)
//	{
//
//	}
//	return TRUE;
//}
//INT CountOnes(DWORD mask)
//{
//	INT zero_bits = 0;
//	DWORD power;
//	for (int i = 1; i ; i<<=1,zero_bits++)
//	{
//		if (mask & i)
//		{
//			power = i;
//			break;
//			
//		}
//	}
//	return 32-zero_bits;
//}

CHAR* ParseAddress(CHAR sz_addres[], CONST CHAR sz_description[], DWORD dw_address)
{
	sprintf
	(
		sz_addres,
		"%s%i.%i.%i.%i",sz_description,
		FIRST_IPADDRESS(dw_address),
		SECOND_IPADDRESS(dw_address),
		THIRD_IPADDRESS(dw_address),
		FOURTH_IPADDRESS(dw_address)

	);
	return sz_addres;


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

		HWND hIPaddares = GetDlgItem(hwnd, IDC_IPADDRESS);
		SetFocus(hIPaddares);
	}
	break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_IPADDRESS: 
		{
			CONST INT SIZE = 256;
			CHAR sz_info[SIZE]{};

			HWND hIPaddress = GetDlgItem(hwnd, IDC_IPADDRESS);
			HWND hStaticInfo = GetDlgItem(hwnd, IDC_STATIC_INFO);
			HWND hEditPrefix = GetDlgItem(hwnd, IDC_EDIT_PREFIX);


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
				SendMessage(hIPaddress, IPM_GETADDRESS, 0, (LPARAM)&dw_address);
				INT first = FIRST_IPADDRESS(dw_address);
				INT second = SECOND_IPADDRESS(dw_address);
				INT third =  THIRD_IPADDRESS(dw_address);
				INT fourth =  FOURTH_IPADDRESS(dw_address);

				sprintf_s(sz_info, SIZE, "Info:\nFirst: %i, Second: %i, Third: %i, Forth: %i", first, second, third,  fourth);
				SendMessage(hStaticInfo, WM_SETTEXT, 0, (LPARAM)sz_info);

				/////////////////////////////////////////////////////////////////
				if (first < 128)SendMessage(hEditPrefix, WM_SETTEXT, 0, (LPARAM)"8");
				else if(first< 192)SendMessage(hEditPrefix, WM_SETTEXT, 0, (LPARAM)"16");
				else if (first < 224)SendMessage(hEditPrefix, WM_SETTEXT, 0, (LPARAM)"24");



			}
		}			

		break;
		case IDC_IPMASK: 
		{
			//if(HIWORD(wParam) == EN_CHANGE)
			//{ 
			//	HWND hIPmask = GetDlgItem(hwnd, IDC_IPMASK);
			//	HWND hEditPrefix = GetDlgItem(hwnd, IDC_EDIT_PREFIX);
			//	DWORD dw_mask = 0;
			//	SendMessage(hIPmask, IPM_GETADDRESS, 0, (LPARAM)&dw_mask);
			//	INT prefix = CountOnes(dw_mask);
			//	CHAR sz_prefix[3] = {}; //sz_ - string zero(строкаб заканчивающаяся нулем)
			//	sprintf(sz_prefix, "%i", prefix);

			//	SendMessage(hEditPrefix, WM_SETTEXT, 0, (LPARAM)sz_prefix);
			//	//SendMessage(hIPmask, IPM_SETADDRESS, 0, dw_mask >> (32 - prefix) << (32 - prefix));
			//}
			
		}
		break;

		case IDC_EDIT_PREFIX:
		{
			HWND hIPAddress = GetDlgItem(hwnd, IDC_IPADDRESS);
			HWND hEditPrefix = GetDlgItem(hwnd, IDC_EDIT_PREFIX);
			HWND hIPmask = GetDlgItem(hwnd, IDC_IPMASK);
			HWND hStaticInfo = GetDlgItem(hwnd, IDC_STATIC_INFO);
			//DWORD dw_mask = UINT_MAX;
			DWORD dw_mask = ~0;
			if (HIWORD(wParam) == EN_CHANGE)
			{
				CONST INT SIZE_PREFIX = 8;
				CHAR sz_buffer[SIZE_PREFIX];
				SendMessage(hEditPrefix, WM_GETTEXT, SIZE_PREFIX, (LPARAM)sz_buffer);
				//MessageBox(hwnd, sz_buffer, "Prefix", MB_OK | MB_ICONINFORMATION);
				INT shift = atoi(sz_buffer);

				//dw_mask >>= (32 - shift);//Функция atoi() преобразует ASCII-строку в занчение типа int
				//dw_mask <<= (32 - shift);
				//SendMessage(hIPmask, IPM_SETADDRESS, 0, dw_mask);
				SendMessage(hIPmask, IPM_SETADDRESS, 0, dw_mask /* >> (32 - shift)*/ <<= (32 - shift));
				
				////////////////////////////////// Info //////////////////


				CONST INT SIZE = 256;
				CHAR sz_info[SIZE]{};
				CHAR sz_network_address[SIZE]{};
				CHAR sz_droadcast_address[SIZE]{};
				CHAR sz_nuber_of_hosts[SIZE]{};
				CHAR sz_start_address[SIZE]="Начальный IP-адрес";
				CHAR sz_last_address[SIZE]="Последний IP-адрес";

				DWORD dw_address = 0;
				SendMessage(hIPAddress, IPM_GETADDRESS, 0, (LPARAM)&dw_address);
				DWORD dw_network_address = dw_address & dw_mask;

				ParseAddress(sz_network_address, "Адрес сети:\t\t\t", dw_network_address);
				//sprintf
				//(
				//	sz_network_address, 
				//	"Адрес сети:\t\t\t%i.%i.%i.%i",
				//	FIRST_IPADDRESS(dw_network_address),
				//	SECOND_IPADDRESS(dw_network_address),
				//	THIRD_IPADDRESS(dw_network_address),
				//	FOURTH_IPADDRESS(dw_network_address)

				//);
				DWORD dw_droadcast_address = ~dw_mask | dw_network_address;
				ParseAddress(sz_droadcast_address, "Широковещательный адрес:\t", dw_droadcast_address);
				//sprintf
				//(
				//	sz_droadcast_address, 
				//	"Широковещательный адрес:\t%i.%i.%i.%i",
				//	FIRST_IPADDRESS(dw_droadcast_address),
				//	SECOND_IPADDRESS(dw_droadcast_address),
				//	THIRD_IPADDRESS(dw_droadcast_address),
				//	FOURTH_IPADDRESS(dw_droadcast_address)

				//
				//);
				DWORD dw_nuber_of_hosts = dw_droadcast_address - dw_network_address - 1;
				ParseAddress(sz_nuber_of_hosts, "Широковещательный адрес:\t", dw_nuber_of_hosts);
				//sprintf
				//(
				//	sz_nuber_of_hosts,
				//	"Количество узлов:\t\t%u",
				//	dw_nuber_of_hosts


				//);
				ParseAddress(sz_start_address, "Начальный IP-адрес:\t\t", dw_network_address + 1);
				ParseAddress(sz_last_address, "Последний IP-адрес:\t\t", dw_droadcast_address - 1);

				sprintf
				(
					sz_info,
					"Info:\n%s\n%s\n%s\n%s\n%s",
					sz_network_address,
					sz_droadcast_address,
					sz_nuber_of_hosts,
					sz_start_address,
					sz_last_address


				);



				SendMessage( hStaticInfo, WM_SETTEXT, 0, (LPARAM)sz_info);

			
			}
		}
		break;

		case IDOK:  MessageBox(hwnd,"Была нажата кнопка OK","Info", MB_OK | MB_ICONINFORMATION);  
			break;
			//MB_OK | MB_ICONINFORMATION - | это or
			// || - логическое OR
			// | - побитовое OR
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;

	case WM_NOTIFY:
	{
		HWND hIPmask = GetDlgItem(hwnd, IDC_IPMASK);
		HWND hEditPrefix = GetDlgItem(hwnd, IDC_EDIT_PREFIX);
		switch (LOWORD(wParam))
		{
			case IDC_IPMASK:
			{

				DWORD dw_mask = 0;
				SendMessage(hIPmask, IPM_GETADDRESS, 0, (LPARAM)&dw_mask);
				int i = 32;
				for (; dw_mask & 1 ^ 1; i--)dw_mask >>= 1;
				CHAR sz_prefix[5]{};
				sprintf(sz_prefix, "%i", i);

				SendMessage(hEditPrefix, WM_SETTEXT, 0, (LPARAM)sz_prefix);

			}
			break;
			
		}
		break;

	}
	break;
	case WM_CLOSE:

		EndDialog(hwnd, 0);
		break;

	}

	return FALSE;

} 



