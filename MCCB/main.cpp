#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <cmath>
#include "functions.h"
#define PI 3.14159265358979323846

using namespace std;

_3D OP = { 1 , -1, 0.5 }; // ����һ��ȫ�ֱ���OP����ʾ��Դ
Plane0 pi = { OP, PI, PI/2, 20}; // ����һ��ȫ�ֱ���pi����ʾͶӰƽ��
int c = 0;// ����
COORD setwindowsize ; // ���ÿ���̨���ڴ�С
setofblock* Bhead = nullptr; // ��ʼ������ͷָ��Ϊ nullptr
setofprojection* Plhead = nullptr; // ��ʼ������ͷָ��Ϊ nullptr
setofprint* Prhead = nullptr;
HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);// ����̨������
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);// ����̨������
HWND hwnd = GetConsoleWindow();// ��ȡ����̨���ھ��
HWND owner = GetWindow(hwnd, GW_OWNER);// ��ȡ���������߾��(�ж��ǲ���win10)
DWORD mode;// ����̨����ģʽ
CONSOLE_SCREEN_BUFFER_INFO csbi;// ����̨��Ļ��������Ϣ
int _mode;// ����̨����ģʽ


// ���ݴ��ڴ�С�����ű���������λ�ã�����ӡ��ɫ�Ǻ�    
void gotoxy(int x, int y, int c) {
    double scaledX = setwindowsize.X / 2;
    double scaledY = setwindowsize.Y;

    if (x < scaledX && -x < scaledX && y < scaledY && -y < scaledY) {    // �ж��Ƿ��ڿɻ�������
        COORD pos;
        pos.X = static_cast<SHORT>(scaledX + x);
        pos.Y = static_cast<SHORT>((scaledY - y) / 2);
        SetConsoleCursorPosition(hStdout, pos);
        int color = 31 + (c % 6);         // ����c�仯���ò�ͬ��ɫ��ѭ��ʹ��6����ɫ
        printf("\033[%dm*\033[0m", color);
    }
}

// ��ӡ�˵�
void printMenu() {
    COORD pos = { setwindowsize.X / 4 ,setwindowsize.Y / 4};
    SetConsoleCursorPosition(hStdout, pos);
    printf("\033[0m\033[1;32m%s\033[0m", "ͼ����Ⱦ����ţ�");
    SetConsoleCursorPosition(hStdout, { short(pos.X / 4 + 5) , short(pos.Y + 3) });
    printf("\033[0m\033[1;36m%s\033[0m", "�����������㷨��150*35���廭�ʣ����伫�����֣�");
    SetConsoleCursorPosition(hStdout, { short(pos.X / 4) , short(pos.Y + 8) });
	printf("1.ctrl��ʼ");
    SetConsoleCursorPosition(hStdout, { short(pos.X / 4) , short(pos.Y + 11) });
	printf("2.esc�˳�");
	SetConsoleCursorPosition(hStdout, { short(pos.X / 4 - 5) , short(pos.Y + 14) });
	printf("\033[0m\033[1;34m%s\033[0m","#���ƹ���:ctrl�����·��飬back�������ɵķ��飬wasd����xoy�ƶ����ӽǷ���Ϊ��)\n�������ҿ����ӽǣ��ո�shift����z�ᣬesc�˳�����\n����ʵʱ��ȡ���ں������С���ı���ʾ��Χ�������������Ż�ˢ�£�");
}
// ��ʼ
void _continue(){
    HideCursor(); // ���ع��
    SetConsoleCursorPosition(hStdout, { static_cast<short>(setwindowsize.X/2), static_cast<short>(setwindowsize.Y /2) });
    printf("+");
    cout << "\x1B[2J\x1B[H" << flush; // ��������
    print();
    _mode = 1; // ����ģʽΪ1����ʼѭ�����㣩
    while (_mode == 1) {
        int n = control();
        switch (n) {
        case 2:
            getConsoleSize(hStdout, setwindowsize); // ��ȡ����̨��С
            cout << "\x1B[2J\x1B[H"  << flush;
            shift();
            print();
        case 1:
            SetConsoleCursorPosition(hStdout, { static_cast<short>(setwindowsize.X/2), static_cast<short>(setwindowsize.Y/2) });
            printf("+");
            break;
        case 0:
            _mode = 0; // ����ģʽΪ0(����ѭ��)
        default:
            break;
        }
        Sleep(1000 / 120); // ����֡��
    }
}

int main(int argc, char** argv)  
{
    Sleep(10); // ����
    SetConsoleTitleA("MCCB"); // ���ÿ���̨���ڱ���
    getConsoleSize(hStdout, setwindowsize); // ��ȡ����̨��С
    adjustFontSizeByWindow(hStdout); // ����ʱ����Ӧ����
    //setwindowsize = { 1440, 720 }; // ���ÿ���̨���ڴ�С
    //setsize(setwindowsize);
    block box; // ����������
    // �����������8������  
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

    // ��������䵽������������  
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
    Sleep(10); // ����(��Ȼ���ӡ̫�쵼��ƫ��)
    print();
    printMenu(); // ��ӡ�˵�
    while (1) {
        INPUT_RECORD ir; // �����¼
        DWORD eventsRead; // ��ȡ���¼���
        if (hStdin == INVALID_HANDLE_VALUE || hStdout == INVALID_HANDLE_VALUE) {
            std::cerr << "Failed to get console handle." << std::endl;
            return -1;
        }
        ReadConsoleInput(hStdin, &ir, 1, &eventsRead); // ��ȡ����̨�����¼�

        // �������������ڻ�������С����¼�����̬��������
        if (ir.EventType == WINDOW_BUFFER_SIZE_EVENT) {
            getConsoleSize(hStdout, setwindowsize);
            adjustFontSizeByWindow(hStdout);
            print();
            printMenu();
            continue;
        }

        if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown) { // ����ǰ����¼�
            switch (ir.Event.KeyEvent.wVirtualKeyCode) { // ���ݰ��������ж�
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
