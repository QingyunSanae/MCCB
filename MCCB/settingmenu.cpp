// ���ò˵���controlʱF3��������save,load,delete,color_on_off,back��
// load->�����ַ������BadApple!! check��,back
// delete->�����ַ,back
// color->on,off,back
// back(break)
// ��strcmpʵ��

#include <stdio.h>
#include <windows.h>
#include "functions.h"

extern HANDLE hStdin;// ����̨������
extern HANDLE hStdout;// ����̨������
extern DWORD mode;// ����̨����ģʽ
extern COORD setwindowsize; // ���ÿ���̨���ڴ�С


bool loading() {
    char address[64];
    while (1) {
        system("cls");
        printf("������back(�˳�)���ļ���ַ(��ʽ:..\\\\save\\\\filename):");
        scanf("%63s", address); // ��ȡ�û�����
        if (strcmp(address, "back") == 0) return 1;
        if (load(address)) return 0;
    }
}

bool deleting() { // (��ûд)
    char address[64];
    while (1) {
        system("cls");
        printf("������break(�˳�)���ļ���ַ(��ʽ:..\\\\save\\\\filename):");
        scanf("%63s", address); // ��ȡ�û�����
        if (strcmp(address, "break") == 0) return 1;
        if (load(address)) return 0;
    }
}

bool color_control() { // (��ûд)
    char address[64];
    while (1) {
        system("cls");
        printf("������break(�˳�)���ļ���ַ(��ʽ:..\\\\save\\\\filename):");
        scanf("%63s", address); // ��ȡ�û�����
        if (strcmp(address, "break") == 0) return 1;
        if (load(address)) return 1;
    }

}

void setting() {
    char chose[64];
    SetConsoleMode(hStdin, mode); // �ָ�����̨����ģʽ  
    while (1) {
        getConsoleSize(hStdout, setwindowsize); // ��ȡ����̨��С
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
        printf("��������һ������(����������ʽ����������Сд���������ַ���Ӣ��):");
        scanf("%63s", &chose);
        if (strcmp(chose, "save") == 0) save(nullptr);
        else if (strcmp(chose, "load") == 0) { if (loading()) continue; }
        else if (strcmp(chose, "delete") == 0) { if (deleting()) continue; }
        else if (strcmp(chose, "color_control") == 0) { if (color_control()) continue; }
        else if (strcmp(chose, "back") == 0) break;
    }
}

