// ���ļ����õĺ�������

#include "_3D.h"
#include <windows.h>


int control(); // ���ƺ���
void setsize(_COORD set); // ���ÿ���̨��С
void getConsoleSize(HANDLE hStdout, COORD& setwindowsize); // ��ȡ����̨��С
inline void adjustFontSizeByWindow(HANDLE hConsole); // ���ݴ��ڸ߶�����Ӧ�����С
void full_screen(); // ȫ��
void HideCursor(); // ���ع��
void gotoxy(int x, int y, int c); // �ƶ���꣨������ɫ��ǣ�
block CCB(); // ����������                                                         #����Ҫ�ĺ��������ǣ�
Box_Plane convert(const block& UB); // ת��ΪͶӰ����
void append(block NUB); // ��ӷ��鵽����
void appendPl(Box_Plane NUB); // ���ͶӰ������
void appendPr(const Box_Plane& NUB, int n);// �Ż�������ʾ�ĵ㣩
void freeB();
void freePl();
void freePrList(); // ��յ�����
void shifttoPr(); //ת���������� 
void shift(); // ���ݷ�������ı�ͶӰ����
void print(); // ��ӡͶӰ����
void deleteblock(); // ɾ����ӵĽڵ�
void BPto_2D(const Box_Plane& boxPlane, _2D points[8]); // ��ѹBox_Plane��8��_2D��
Box_Plane _2DtoBP(const _2D points[8]); // ѹ��8��_2D�㵽Box_Plane
void save(char* QS); // �浵����ţ�
bool load(char* in); // ��ȡ���ļ����Լ����룩
void setting();


