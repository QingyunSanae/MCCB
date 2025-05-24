// 设置菜单（control时F3）（包含save,load,delete,color_on_off,back）
// load->输入地址（包含BadApple!! check）,back
// delete->输入地址,back
// color->on,off,back
// back(break)
// 由strcmp实现

#include <stdio.h>
#include <windows.h>
#include "functions.h"

extern HANDLE hStdin;// 控制台输入句柄
extern HANDLE hStdout;// 控制台输出句柄
extern DWORD mode;// 控制台输入模式
extern COORD setwindowsize; // 设置控制台窗口大小


bool loading() {
    char address[64];
    while (1) {
        system("cls");
        printf("请输入back(退出)或文件地址(格式:..\\\\save\\\\filename):");
        scanf("%63s", address); // 读取用户输入
        if (strcmp(address, "back") == 0) return 1;
        if (load(address)) return 0;
    }
}

bool deleting() { // (还没写)
    char address[64];
    while (1) {
        system("cls");
        printf("请输入break(退出)或文件地址(格式:..\\\\save\\\\filename):");
        scanf("%63s", address); // 读取用户输入
        if (strcmp(address, "break") == 0) return 1;
        if (load(address)) return 0;
    }
}

bool color_control() { // (还没写)
    char address[64];
    while (1) {
        system("cls");
        printf("请输入break(退出)或文件地址(格式:..\\\\save\\\\filename):");
        scanf("%63s", address); // 读取用户输入
        if (strcmp(address, "break") == 0) return 1;
        if (load(address)) return 1;
    }

}

void setting() {
    char chose[64];
    SetConsoleMode(hStdin, mode); // 恢复控制台输入模式  
    while (1) {
        getConsoleSize(hStdout, setwindowsize); // 获取控制台大小
        system("cls");
        COORD pos;
        pos.X = static_cast<SHORT>(setwindowsize.X / 10);
        pos.Y = static_cast<SHORT>(setwindowsize.Y / 10 * 9);
        SetConsoleCursorPosition(hStdout, pos);
        printf("save");
        SetConsoleCursorPosition(hStdout, { static_cast<SHORT>(pos.X * 2),pos.Y });
        printf("load");
        SetConsoleCursorPosition(hStdout, { static_cast<SHORT>(pos.X * 3),pos.Y });
        printf("delete");
        SetConsoleCursorPosition(hStdout, { static_cast<SHORT>(pos.X * 5),pos.Y });
        printf("color_control");
        SetConsoleCursorPosition(hStdout, { static_cast<SHORT>(pos.X * 8),pos.Y });
        printf("back");
        SetConsoleCursorPosition(hStdout, { 0,0 });
        printf("请输入下一步操作(不会正则表达式所以请输入小写不带其他字符的英文):");
        scanf("%63s", &chose);
        if (strcmp(chose, "save") == 0) save(nullptr);
        else if (strcmp(chose, "load") == 0) { if (loading()) continue; }
        else if (strcmp(chose, "delete") == 0) { if (deleting()) continue; }
        else if (strcmp(chose, "color_control") == 0) { if (color_control()) continue; }
        else if (strcmp(chose, "back") == 0) break;
    }
}

