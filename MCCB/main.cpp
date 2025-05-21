#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <cmath>
#include "functions.h"
#define PI 3.14159265358979323846

using namespace std;

_3D OP = { 1 , -1, 0.5 }; // 定义一个全局变量OP，表示光源
Plane0 pi = { OP, PI, PI/2, 20}; // 定义一个全局变量pi，表示投影平面
int c = 0;// 计数
COORD setwindowsize ; // 设置控制台窗口大小
setofblock* Bhead = nullptr; // 初始化链表头指针为 nullptr
setofprojection* Plhead = nullptr; // 初始化链表头指针为 nullptr
setofprint* Prhead = nullptr;
HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);// 控制台输入句柄
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);// 控制台输出句柄
HWND hwnd = GetConsoleWindow();// 获取控制台窗口句柄
HWND owner = GetWindow(hwnd, GW_OWNER);// 获取窗口所有者句柄(判断是不是win10)
DWORD mode;// 控制台输入模式
CONSOLE_SCREEN_BUFFER_INFO csbi;// 控制台屏幕缓冲区信息
int _mode;// 控制台输入模式


// 根据窗口大小和缩放比例计算光标位置，并打印彩色星号    
void gotoxy(int x, int y, int c) {
    double scaledX = setwindowsize.X / 2;
    double scaledY = setwindowsize.Y;

    if (x < scaledX && -x < scaledX && y < scaledY && -y < scaledY) {    // 判断是否在可绘制区域
        COORD pos;
        pos.X = static_cast<SHORT>(scaledX + x);
        pos.Y = static_cast<SHORT>((scaledY - y) / 2);
        SetConsoleCursorPosition(hStdout, pos);
        int color = 31 + (c % 6);         // 根据c变化设置不同颜色，循环使用6种颜色
        printf("\033[%dm*\033[0m", color);
    }
}

// 打印菜单
void printMenu() {
    COORD pos = { setwindowsize.X / 4 ,setwindowsize.Y / 4};
    SetConsoleCursorPosition(hStdout, pos);
    printf("\033[0m\033[1;32m%s\033[0m", "图形渲染（大概）");
    SetConsoleCursorPosition(hStdout, { short(pos.X / 4 + 5) , short(pos.Y + 3) });
    printf("\033[0m\033[1;36m%s\033[0m", "（四舍五入算法，150*35高清画质，搭配极致脑渲）");
    SetConsoleCursorPosition(hStdout, { short(pos.X / 4) , short(pos.Y + 8) });
	printf("1.ctrl开始");
    SetConsoleCursorPosition(hStdout, { short(pos.X / 4) , short(pos.Y + 11) });
	printf("2.esc退出");
	SetConsoleCursorPosition(hStdout, { short(pos.X / 4 - 5) , short(pos.Y + 14) });
	printf("\033[0m\033[1;34m%s\033[0m","#控制规则:ctrl生成新方块，back销毁生成的方块，wasd控制xoy移动（视角方向为正)\n上下左右控制视角，空格、shift控制z轴，esc退出控制\n新增实时获取窗口和字体大小，改变显示范围（但按键输入后才会刷新）");
}
// 开始
void _continue(){
    HideCursor(); // 隐藏光标
    SetConsoleCursorPosition(hStdout, { static_cast<short>(setwindowsize.X/2), static_cast<short>(setwindowsize.Y /2) });
    printf("+");
    cout << "\x1B[2J\x1B[H" << flush; // 立即清屏
    print();
    _mode = 1; // 设置模式为1（开始循环计算）
    while (_mode == 1) {
        int n = control();
        switch (n) {
        case 2:
            getConsoleSize(hStdout, setwindowsize); // 获取控制台大小
            cout << "\x1B[2J\x1B[H"  << flush;
            shift();
            print();
        case 1:
            SetConsoleCursorPosition(hStdout, { static_cast<short>(setwindowsize.X/2), static_cast<short>(setwindowsize.Y/2) });
            printf("+");
            break;
        case 0:
            _mode = 0; // 设置模式为0(结束循环)
        default:
            break;
        }
        Sleep(1000 / 120); // 控制帧率
    }
}

int main(int argc, char** argv)  
{
    Sleep(10); // 缓冲
    SetConsoleTitleA("MCCB"); // 设置控制台窗口标题
    getConsoleSize(hStdout, setwindowsize); // 获取控制台大小
    adjustFontSizeByWindow(hStdout); // 启动时自适应字体
    //setwindowsize = { 1440, 720 }; // 设置控制台窗口大小
    //setsize(setwindowsize);
    block box; // 正方体生成
    // 定义正方体的8个顶点  
    _3D vertices[8] = {
           {0, 0, 0},
           {-1, 0, 0},
           {0, 1, 0},
           {-1, 1, 0},
           {0, 0, 1},
           {-1, 0, 1},
           {0, 1, 1},
           {-1, 1, 1}
    };

    // 将顶点分配到正方体的面和线  
    for (int p = 0; p < 2; p++) {
        for (int l = 0; l < 2; l++) {
            for (int i = 0; i < 2; i++) {
                if (p * 4 + l * 2 + i < 8) {
                    box.plane[p].line[l].print3D[i] = vertices[p * 4 + l * 2 + i];
                }
            }
        }
    }
    append(box);
    appendPl(convert(box));
    Sleep(10); // 缓冲(不然会打印太快导致偏移)
    print();
    printMenu(); // 打印菜单
    while (1) {
        INPUT_RECORD ir; // 输入记录
        DWORD eventsRead; // 读取的事件数
        if (hStdin == INVALID_HANDLE_VALUE || hStdout == INVALID_HANDLE_VALUE) {
            std::cerr << "Failed to get console handle." << std::endl;
            return -1;
        }
        ReadConsoleInput(hStdin, &ir, 1, &eventsRead); // 读取控制台输入事件

        // 新增：监听窗口缓冲区大小变更事件，动态调整字体
        if (ir.EventType == WINDOW_BUFFER_SIZE_EVENT) {
            getConsoleSize(hStdout, setwindowsize);
            adjustFontSizeByWindow(hStdout);
            print();
            printMenu();
            continue;
        }

        if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown) { // 如果是按键事件
            switch (ir.Event.KeyEvent.wVirtualKeyCode) { // 根据按键代码判断
            case VK_CONTROL:
                _continue();
                printf("%.1lf %.1lf %.1lf\n", pi.center.D[0], pi.center.D[1], pi.center.D[2]);
                break;
            case VK_ESCAPE:
                deleteblock();
                delete Bhead;
                delete Plhead;
                delete Prhead;
                Sleep(100);
                return 0;
            default:
                break;
            }
        }
    }
}
