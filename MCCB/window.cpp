#include "functions.h"
#include <iostream>
#include <windows.h>


extern _3D OP; //��ȡȫ�ֱ���OP����ʾͶӰ����
extern HANDLE hStdin;// ����̨������
extern HANDLE hStdout;
extern HWND owner;
extern DWORD mode;// ����̨����ģʽ
extern HWND hwnd;
extern CONSOLE_SCREEN_BUFFER_INFO csbi;// ����̨��Ļ��������Ϣ
extern int _mode;// ����̨����ģʽ
extern COORD setwindowsize; // ���ÿ���̨���ڴ�С


// Ӱ�ع��
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(hStdout, &cursor_info);
}

inline void getConsoleSize(HANDLE hConsole, COORD& size) { // ��ȡ����̨���ڴ�С
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    size = csbi.dwSize;
}

inline void SetConsoleFontSize(HANDLE hConsole, SHORT fontSize) {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    if (!GetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
        std::cerr << "�޷���ȡ��ǰ����̨������Ϣ��" << std::endl;
        return;
    }
    cfi.dwFontSize.Y = fontSize; // ���������С
    if (!SetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
        std::cerr << "�޷����ÿ���̨�����С��" << std::endl;
    }
}

inline void adjustFontSizeByWindow(HANDLE hConsole) { // ���ݴ��ڸ߶�����Ӧ�����С
    COORD size;
    getConsoleSize(hConsole, size);
    // �Ը߶�Ϊ��׼����Ӧ�����С����С12�����32
    SHORT fontSize = max(12, min(32, size.Y / 30));
    SetConsoleFontSize(hConsole, fontSize);
}
/*
// ��ÿ���̨��С
void getConsoleSize(HANDLE hStdout, COORD& setwindowsize) {
   if (GetConsoleScreenBufferInfo(hStdout, &csbi)) { // ��ȡ����̨��Ļ��������Ϣ
       setwindowsize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;  // ���
       setwindowsize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; // �߶�
   } else {
       setwindowsize.Y = 0;
       setwindowsize.X = 0; // �����ȡʧ�ܣ�����0
   }
}
*/
// ���ÿ���̨��С�����أ�# �����С�������� #������ win11 �޷�����
void setsize(_COORD set) {

	if (owner == NULL) {
		// Windows 10
		SetWindowPos(hwnd, nullptr, 0, 0, set.X, set.Y, SWP_NOZORDER | SWP_NOMOVE);
	}
	else {
		// Windows 11
		SetWindowPos(owner, nullptr, 0, 0, set.X, set.Y, SWP_NOZORDER | SWP_NOMOVE);
	}
    // ���������С
    adjustFontSizeByWindow(hStdout);
}//���ô��ڴ�С


// ȫ��
void full_screen()
{
    HWND hwnd = GetForegroundWindow();
    int cx = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
    int cy = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */

    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* ��ȡ������Ϣ */
    /* ���ô�����Ϣ ��� ȡ�����������߿� */
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

    SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}//ȫ��