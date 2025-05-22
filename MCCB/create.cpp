// ����������߼�

#include <stdio.h>
#include <math.h>
#include "functions.h"

extern Plane0 pi; // ��ȡȫ�ֱ��� pi����ʾͶӰƽ��
extern setofblock* Bhead; // ��������ͷָ��
extern setofprojection* Plhead; // ͶӰ����ͷָ��
extern setofprint* Prhead; // �����ͶӰ������ͷָ��

// ѹ��8��_2D�㵽Box_Plane
Box_Plane _2DtoBP(const _2D points[8]) {
    Box_Plane boxPlane;
    for (int i = 0; i < 4; i++) {
        boxPlane.plane[0].line[i / 2].print2D[i % 2] = points[i];
        boxPlane.plane[1].line[i / 2].print2D[i % 2] = points[i + 4];
    }
    return boxPlane;
}

// ��ѹBox_Plane��8��_2D��
void BPto_2D(const Box_Plane& boxPlane, _2D points[8]) {
    for (int i = 0; i < 4; i++) {
        points[i] = boxPlane.plane[0].line[i / 2].print2D[i % 2];
        points[i + 4] = boxPlane.plane[1].line[i / 2].print2D[i % 2];
    }
}

// ������Ұ���ľ���Ϊ3�ĵ������
inline _3D point1() {
    _3D dP;
    dP.D[0] = floor(pi.center.D[0] + 3 * (cos(pi.A) * sin(pi.B)));
    dP.D[1] = floor(pi.center.D[1] + 3 * (sin(pi.A) * sin(pi.B)));
    dP.D[2] = floor(pi.center.D[2] + 3 * (cos(pi.B)));
    return dP;
}

// ���Ӿ���������������
block CCB() {//code compilation block ȷ��
    block UB;
    // �����������8������  
    _3D vertices[8] = {
        (point1() + _3D{  1,  0,  0 }),
        (point1() + _3D{  0,  0,  0 }),
        (point1() + _3D{  1,  1,  0 }),
        (point1() + _3D{  0,  1,  0 }),
        (point1() + _3D{  1,  0,  1 }),
        (point1() + _3D{  0,  0,  1 }),
        (point1() + _3D{  1,  1,  1 }),
        (point1() + _3D{  0,  1,  1 }),
    };
    // ��������䵽������������  
    for (int p = 0; p < 2; p++) {
        for (int l = 0; l < 2; l++) {
            for (int i = 0; i < 2; i++) {
                if (p * 4 + l * 2 + i < 8) {
                    UB.plane[p].line[l].print3D[i] = vertices[p * 4 + l * 2 + i];
                }
            }
        }
    }
    return UB;
}

// ���ͶӰ�Ƿ��Ѿ�����
inline int checkPl(Box_Plane NUB) {
    setofprojection* temp = Plhead;
    while (temp) {
        if (temp->Pbox == NUB) return 1;
        temp = temp->next;
    }
    return 0;
}

// ���ͶӰ�ڵ㵽����ĩβ
void appendPl(Box_Plane NUB) {
    if (!checkPl(NUB)) {
        setofprojection* newNode = new setofprojection(NUB);
        if (!Plhead) {
            Plhead = newNode;
            Plhead->count = 1;
            Plhead->pre = nullptr;
            appendPr(newNode->Pbox, 1);
        }
        else {
            setofprojection* temp = Plhead;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->pre = temp;
            newNode->count = temp->count + 1;
            appendPr(newNode->Pbox, newNode->count);
        }
        return;
    }
}

// ��鷽���Ƿ��Ѿ�����
inline int check(block NUB) {
    setofblock* temp = Bhead;
    while (temp) {
        if (temp->box == NUB) return 1;
        temp = temp->next;
    }
    return 0;
}

// ��ӷ���ڵ㵽����ĩβ
void append(block NUB) {
    if (!check(NUB)) {
        setofblock* newNode = new setofblock(NUB);
        if (!Bhead) {
            Bhead = newNode;
            Bhead->pre = nullptr;
        }
        else {
            setofblock* temp = Bhead;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->pre = temp;
        }
        return;
    }
}

// ɾ��ѡ���ڵ�(��ֺ�ɾ��)
int deleteblock0(block B) {
    setofblock* Btemp = Bhead;
    int c = 1;
    while (Btemp && !(Btemp->box == B)) {      // ����Ŀ��ڵ�
        Btemp = Btemp->next;
        c++;
    }
    if (Btemp) {
        if (Btemp->pre) {
            Btemp->pre->next = Btemp->next;
        } else {
            Bhead = Btemp->next;
            if (Bhead) Bhead->pre = nullptr;
        }
        if (Btemp->next) Btemp->next->pre = Btemp->pre;
        delete Btemp;
        return c;
    }
    return 0;
}
void deleteprojection(int c) {
    setofprojection* Pltemp = Plhead;
    for (int i = 1; i < c; i++)    Pltemp = Pltemp->next;
    if (Pltemp->pre) {
        Pltemp->pre->next = Pltemp->next;
    } else {
        Plhead = Pltemp->next;
        if (Plhead) Plhead->pre = nullptr;
    }
    if (Pltemp->next) Pltemp->next->pre = Pltemp->pre;
    delete Pltemp;
    return;
}
void deleteprint(int c) {
    setofprint* Prtemp = Prhead;
    while (Prtemp) {
        count* ntemp = Prtemp->n;
        while (ntemp && ntemp->n != c) ntemp = ntemp->next;
        if (ntemp) {
            if (Prtemp->n->n != c) {
                if (ntemp->pre) ntemp->pre->next = ntemp->next;
                else Prtemp->n = ntemp->next;
                if (ntemp->next) ntemp->next->pre = ntemp->pre;
                delete ntemp;
            } else {
                setofprint* toDelete = Prtemp;
                if (Prtemp->pre) {
                    Prtemp->pre->next = Prtemp->next;
                } else {
                    Prhead = Prtemp->next;
                    if (Prhead) Prhead->pre = nullptr;
                }
                if (Prtemp->next) Prtemp->next->pre = Prtemp->pre;
                Prtemp = Prtemp->next;
                delete toDelete;
                continue;
            }
        }
        Prtemp = Prtemp->next;
    }
}
void deleteblock() {
    block target = CCB();
    int c = deleteblock0(target);
    if (c) {
        deleteprojection(c);
        deleteprint(c);
    }
}

// ת������setofblock�е����нڵ�
void shift() {
    freePrList();
    setofblock* Btemp = Bhead;
    setofprojection* Ptemp = Plhead;
    while (Btemp) {
        Ptemp->Pbox = convert(Btemp->box);
        Btemp = Btemp->next;
        Ptemp = Ptemp->next;
    }
    shifttoPr();
}

// ��ӡ����setofprint�����е�
void print() {
    setofprint* temp = Prhead;
    while (temp) {
        count* c = temp->n;
        while (c->next) c = c->next;
        gotoxy(static_cast<int>(round(temp->P.x)), static_cast<int>(round(temp->P.y)), c->n);
        temp = temp->next;
    }
}


void freeB() {
    setofblock* curr = Bhead;
    while (curr) {
        setofblock* next = curr->next;
        delete curr;
        curr = next;
    }
    Bhead = nullptr;
}

void freePl() {
    setofprojection* curr = Plhead;
    while (curr) {
        setofprojection* next = curr->next;
        delete curr;
        curr = next;
    }
    Plhead = nullptr;
}