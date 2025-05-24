// 跨文件调用的函数声明

#include "_3D.h"
#include <windows.h>


int control(); // 控制函数
void setsize(_COORD set); // 设置控制台大小
void getConsoleSize(HANDLE hStdout, COORD& setwindowsize); // 获取控制台大小
inline void adjustFontSizeByWindow(HANDLE hConsole); // 根据窗口高度自适应字体大小
void full_screen(); // 全屏
void HideCursor(); // 隐藏光标
void gotoxy(int x, int y, int c); // 移动光标（附带颜色标记）
block CCB(); // 创建正方体                                                         #最重要的函数（并非）
Box_Plane convert(const block& UB); // 转换为投影函数
void append(block NUB); // 添加方块到链表
void appendPl(Box_Plane NUB); // 添加投影到链表
void appendPr(const Box_Plane& NUB, int n);// 优化（会显示的点）
void freeB();
void freePl();
void freePrList(); // 清空点链表
void shifttoPr(); //转换到点链表 
void shift(); // 根据方块链表改变投影链表
void print(); // 打印投影链表
void deleteblock(); // 删除添加的节点
void BPto_2D(const Box_Plane& boxPlane, _2D points[8]); // 解压Box_Plane到8个_2D点
Box_Plane _2DtoBP(const _2D points[8]); // 压缩8个_2D点到Box_Plane
void save(char* QS); // 存档（大概）
bool load(char* in); // 读取（文件名自己输入）
void setting();


