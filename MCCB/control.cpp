// ��������Ŀ����߼�

#include <stdio.h>
#include <windows.h>
#include <math.h>
#include "functions.h"
#define PI 3.14159265358979323846

extern Plane0 pi; //��ȡȫ�ֱ���OP����ʾͶӰ����
extern HANDLE hStdin;// ����̨������
extern HANDLE hStdout;// ����̨������
extern DWORD mode;// ����̨����ģʽ
extern CONSOLE_SCREEN_BUFFER_INFO csbi;// ����̨��Ļ��������Ϣ
extern int _mode;// ����̨����ģʽ
extern int width, height;// ����̨���ڿ�Ⱥ͸߶�

// ���ÿ���̨ģʽ1
void InitializeConsole() {
    GetConsoleMode(hStdin, &mode);// ��ȡ��ǰ����̨����ģʽ
    SetConsoleMode(hStdin, mode & ~ENABLE_LINE_INPUT & ~ENABLE_ECHO_INPUT);// ���ÿ���̨����ģʽΪ�����ԺͲ�������
    _mode = 1; // ����ģʽΪ1
}

// ģʽ2������浵��
void loading() {  
   char address[64];  
   int chose = 0;  
   while (1) {  
       SetConsoleMode(hStdin, mode); // �ָ�����̨����ģʽ  
       system("cls");  
       printf("������break(�˳�)�ļ���ַ(��ʽ:..\\\\save\\\\filename):");  
       scanf("%63s", address); // ��ȡ�û�����
       if (strcmp(address, "break") == 0) break;
       if (load(address)) break;
   }  
}

//ģʽ1�µĿ���
int control() {
    InitializeConsole();
    INPUT_RECORD ir0; // �����¼
    DWORD eventsRead; // ��ȡ���¼�
    ReadConsoleInput(hStdin, &ir0, 1, &eventsRead); // ��ȡ����̨�����¼�
    if (ir0.EventType == KEY_EVENT && ir0.Event.KeyEvent.bKeyDown) { // ����ǰ����¼�
        int n=0;
        switch (ir0.Event.KeyEvent.wVirtualKeyCode) { 
        case VK_ESCAPE:
            SetConsoleMode(hStdin, mode); // �ָ�����̨����ģʽ
            return 0;
        case VK_CONTROL:
            append(CCB());
            appendPl(convert(CCB()));
            n = 1;
            break;
        }
        if (n == 1) return 1; // �ı�setofblock������
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
            return 3;// �޹�����
        }
        return 2; // �ӽ�����仯����
    }
    return 3;// �޹�����
}
