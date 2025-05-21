#include <math.h>
#include <stdio.h>
#include "functions.h"

int _count = 0;
extern setofprojection* Plhead; // 投影链表头指针
extern setofprint* Prhead;      // 处理后投影点链表头指针
extern COORD setwindowsize;     // 设置控制台窗口大小

// 检查投影点是否已经存在
inline setofprint* checkPr(const _2D& Pr) {
    setofprint* temp = Prhead;
    while (temp) {
        if (temp->P == Pr) return temp;
        temp = temp->next;
    }
    return nullptr;
}

// 添加点节点到链表末尾(重叠点则记录)
void appendPr(const Box_Plane& NUB, int n) {
    printf("%d", n);
    _2D V[8];
    BPto_2D(NUB, V);
    for (int i = 0; i < 8; i++) {
        setofprint* temp0 = checkPr(V[i]);                      // 检查是否是重复点
        if (!temp0) {                                           // 如果是新点，则在点链表尾添加
            setofprint* newNode = new setofprint(V[i]);
            count* newCount = new count(n);
            newCount->next = nullptr;
            newCount->pre = nullptr;
            newNode->n = newCount;
            newNode->c = 1;
            newNode->next = nullptr;
            newNode->pre = nullptr;
            if (!Prhead) {
                Prhead = newNode;
            }
            else {
                setofprint* temp = Prhead;
                while (temp->next) temp = temp->next;
                temp->next = newNode;
                newNode->pre = temp;
            }
            gotoxy(static_cast<int>(round(newNode->P.x)), static_cast<int>(round(newNode->P.y)), n);
        }
        else {                                                  // 如果点已存在，则记录编号链到count链表尾
            count* newN = new count(n);
            newN->next = nullptr;
            newN->pre = nullptr;
            count* last = temp0->n;
            if (!last) {
                temp0->n = newN;
            }
            else {
                while (last->next) last = last->next;
                last->next = newN;
                newN->pre = last;
            }
            temp0->c++;
            gotoxy(static_cast<int>(round(temp0->P.x)), static_cast<int>(round(temp0->P.y)), n);
        }
    }
}

// 释放setofprint链表的所有节点
void freePrList() {
    setofprint* curr = Prhead;
    while (curr) {
        setofprint* next = curr->next;
        count* cnode = curr->n;
        while (cnode) {
            count* cnext = cnode->next;
            delete cnode;
            cnode = cnext;
        }
        delete curr;
        curr = next;
    }
    Prhead = nullptr;
}

// 转换为投影点链表
void shifttoPr() {
    freePrList();
    setofprojection* Pltemp = Plhead;
    _count = 0;
    while (Pltemp) {
        _2D V[8];
        BPto_2D(Pltemp->Pbox, V);
        for (int i = 0; i < 8; i++) {
            if (V[i].x >= -setwindowsize.X / 2 && V[i].x <= setwindowsize.X / 2 && V[i].y >= -setwindowsize.Y / 2 && V[i].y <= setwindowsize.Y / 2) {       // 判断点是否在窗口内
                setofprint* temp0 = checkPr(V[i]);                      // 检查是否是重复点
                if (!temp0) {                                           // 如果是新点，则在点链表尾添加
                    _count++;
                    setofprint* newNode = new setofprint(V[i]);
                    count* newCount = new count(Pltemp->count);
                    newCount->next = nullptr;
                    newCount->pre = nullptr;
                    newNode->n = newCount;
                    newNode->c = 1;
                    newNode->next = nullptr;
                    newNode->pre = nullptr;
                    if (!Prhead) {
                        Prhead = newNode;
                    }
                    else {
                        setofprint* temp = Prhead;
                        while (temp->next) temp = temp->next;
                        temp->next = newNode;
                        newNode->pre = temp;
                    }
                }
                else {                                                  // 如果点已存在，则记录编号链到count链表尾
                    count* newN = new count(Pltemp->count);
                    newN->next = nullptr;
                    newN->pre = nullptr;
                    count* last = temp0->n;
                    if (!last) {
                        temp0->n = newN;
                    }
                    else {
                        while (last->next) last = last->next;
                        last->next = newN;
                        newN->pre = last;
                    }
                    temp0->c++;
                }
            }
        }
        Pltemp = Pltemp->next;
    }
    printf("%d", _count); // 记录点的数量
}