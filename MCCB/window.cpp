#include "functions.h"
#include <iostream>
#include <windows.h>


extern _3D OP; //读取全局变量OP，表示投影中心
extern HANDLE hStdin;// 控制台输入句柄
extern HANDLE hStdout;
extern HWND owner;
extern DWORD mode;// 控制台输入模式
extern HWND hwnd;
extern CONSOLE_SCREEN_BUFFER_INFO csbi;// 控制台屏幕缓冲区信息
extern int _mode;// 控制台输入模式
extern COORD setwindowsize; // 设置控制台窗口大小


// 影藏光标
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(hStdout, &cursor_info);
}

inline void getConsoleSize(HANDLE hConsole, COORD& size) { // 获取控制台窗口大小
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    size = csbi.dwSize;
}

inline void SetConsoleFontSize(HANDLE hConsole, SHORT fontSize) {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    if (!GetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
        std::cerr << "无法获取当前控制台字体信息。" << std::endl;
        return;
    }
    cfi.dwFontSize.Y = fontSize; // 设置字体大小
    if (!SetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
        std::cerr << "无法设置控制台字体大小。" << std::endl;
    }
}

inline void adjustFontSizeByWindow(HANDLE hConsole) { // 根据窗口高度自适应字体大小
    COORD size;
    getConsoleSize(hConsole, size);
    // 以高度为基准自适应字体大小，最小12，最大32
    SHORT fontSize = max(12, min(32, size.Y / 30));
    SetConsoleFontSize(hConsole, fontSize);
}
/*
// 获得控制台大小
void getConsoleSize(HANDLE hStdout, COORD& setwindowsize) {
   if (GetConsoleScreenBufferInfo(hStdout, &csbi)) { // 获取控制台屏幕缓冲区信息
       setwindowsize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;  // 宽度
       setwindowsize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; // 高度
   } else {
       setwindowsize.Y = 0;
       setwindowsize.X = 0; // 如果获取失败，返回0
   }
}
*/
// 设置控制台大小（像素）# 字体大小不会设置 #行列在 win11 无法设置
void setsize(_COORD set) {

	if (owner == NULL) {
		// Windows 10
		SetWindowPos(hwnd, nullptr, 0, 0, set.X, set.Y, SWP_NOZORDER | SWP_NOMOVE);
	}
	else {
		// Windows 11
		SetWindowPos(owner, nullptr, 0, 0, set.X, set.Y, SWP_NOZORDER | SWP_NOMOVE);
	}
    // 调整字体大小
    adjustFontSizeByWindow(hStdout);
}//设置窗口大小


// 全屏
void full_screen()
{
    HWND hwnd = GetForegroundWindow();
    int cx = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
    int cy = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */

    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* 获取窗口信息 */
    /* 设置窗口信息 最大化 取消标题栏及边框 */
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

    SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}//全屏