// 键盘输入的控制逻辑

#include <stdio.h>
#include <windows.h>
#include <math.h>
#include "functions.h"
#define PI 3.14159265358979323846

extern Plane0 pi; //读取全局变量OP，表示投影中心
extern HANDLE hStdin;// 控制台输入句柄
extern HANDLE hStdout;// 控制台输出句柄
extern DWORD mode;// 控制台输入模式
extern CONSOLE_SCREEN_BUFFER_INFO csbi;// 控制台屏幕缓冲区信息
extern int _mode;// 控制台输入模式
extern int width, height;// 控制台窗口宽度和高度

// 设置控制台模式1
void InitializeConsole() {
    GetConsoleMode(hStdin, &mode);// 获取当前控制台输入模式
    SetConsoleMode(hStdin, mode & ~ENABLE_LINE_INPUT & ~ENABLE_ECHO_INPUT);// 设置控制台输入模式为不回显和不行输入
    _mode = 1; // 设置模式为1
}

// 模式2（输入存档）
void loading() {  
   char address[64];  
   int chose = 0;  
   while (1) {  
       SetConsoleMode(hStdin, mode); // 恢复控制台输入模式  
       system("cls");  
       printf("请输入break(退出)文件地址(格式:..\\\\save\\\\filename):");  
       scanf("%63s", address); // 读取用户输入
       if (strcmp(address, "break") == 0) break;
       if (load(address)) break;
   }  
}

//模式1下的控制
int control() {
    InitializeConsole();
    INPUT_RECORD ir0; // 输入记录
    DWORD eventsRead; // 读取的事件
    ReadConsoleInput(hStdin, &ir0, 1, &eventsRead); // 读取控制台输入事件
    if (ir0.EventType == KEY_EVENT && ir0.Event.KeyEvent.bKeyDown) { // 如果是按键事件
        int n=0;
        switch (ir0.Event.KeyEvent.wVirtualKeyCode) { 
        case VK_ESCAPE:
            SetConsoleMode(hStdin, mode); // 恢复控制台输入模式
            return 0;
        case VK_CONTROL:
            append(CCB());
            appendPl(convert(CCB()));
            n = 1;
            break;
        }
        if (n == 1) return 1; // 改变setofblock的输入
        switch (ir0.Event.KeyEvent.wVirtualKeyCode) {
        case 87: // W 
            pi.center.D[0] += cos(pi.A) / 2;
            pi.center.D[1] += sin(pi.A) / 2;
            break;
        case 83: // S
            pi.center.D[0] -= cos(pi.A) / 2;
            pi.center.D[1] -= sin(pi.A) / 2;
            break;
        case 65: // A
            pi.center.D[0] -= sin(pi.A) / 2;
            pi.center.D[1] += cos(pi.A) / 2;
            break;
        case 68: // D
            pi.center.D[0] += sin(pi.A) / 2;
            pi.center.D[1] -= cos(pi.A) / 2;
            break;
        case VK_SHIFT:
            pi.center.D[2] -= 0.5;
            break;
        case VK_SPACE:
            pi.center.D[2] += 0.5;
            break;
        case VK_LEFT:
            pi.A += PI / 12;
            pi.setAngles(pi.A, pi.B);
            break;
        case VK_RIGHT:
            pi.A -= PI / 12;
            pi.setAngles(pi.A, pi.B);
            break;
        case VK_UP:
            pi.B -= PI / 12;
            pi.setAngles(pi.A, pi.B);
            break;
        case VK_DOWN:
            pi.B += PI / 12;
            pi.setAngles(pi.A, pi.B);
            break;
        case VK_BACK:
            deleteblock();
            break;
        case VK_F2:
            loading();
            break;
        case VK_F1:
            save();
            break;
        default:
            return 3;// 无关输入
        }
        return 2; // 视角坐标变化输入
    }
    return 3;// 无关输入
}
