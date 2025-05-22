// ת����ά�㵽��ά��

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <cstdlib>
#include "functions.h"


extern Plane0 pi; // ��ȡȫ�ֱ��� pi����ʾͶӰƽ��

// ����� P ��ƽ���ϵ�ͶӰ��
_3D project_point(const _3D& P) {
    double dx = P.D[0] - pi.center.D[0];
    double dy = P.D[1] - pi.center.D[1];
    double dz = P.D[2] - pi.center.D[2];
    double denominator = pi.a * dx + pi.b * dy + pi.c * dz;

    // �����ĸΪ��������P �� O ����ƽ����ƽ�棩
    if (fabs(denominator) < 1e-9 || denominator > 0) {//c++; 
    return {pi.center.D[0],pi.center.D[1],pi.center.D[2]}; // ������Ч��
    }

    double t = -pi.h / denominator;
    return { pi.center.D[0] + t * dx, pi.center.D[1] + t * dy, pi.center.D[2] + t * dz };
}

// ������PL��ƽ���ϵ�ͶӰ��PL'
Plane project_Plane(const Plane& PL) {
    // ͶӰ�߶� line0  
    _3D projected_start0 = project_point(PL.line[0].print3D[0]);
    _3D projected_end0 = project_point(PL.line[0].print3D[1]);
    Line projected_line0 = { projected_start0, projected_end0 };

    // ͶӰ�߶� line1  
    _3D projected_start1 = project_point(PL.line[1].print3D[0]);
    _3D projected_end1 = project_point(PL.line[1].print3D[1]);
    Line projected_line1 = { projected_start1, projected_end1 };
    // ����ͶӰ���ƽ��  
    return { projected_line0, projected_line1 };
}

// ������������ƽ���ϵ�ͶӰ
Box_Plane project_box(const block& box) {
    return { project_Plane(box.plane[0]), project_Plane(box.plane[1]) };
}

// ����ά��ת��Ϊ��ά��
_2D convertTo2D(const _3D& point) {
    double dx = point.D[0] - pi.center.D[0] + pi.h * pi.a;
    double dy = point.D[1] - pi.center.D[1] + pi.h * pi.b;
    double dz = point.D[2] - pi.center.D[2] + pi.h * pi.c;

    return {
        dx * sin(pi.A) + dy * (-cos(pi.A)),
		dx * (-cos(pi.A) * cos(pi.B)) + dy * (-sin(pi.A) * cos(pi.B)) + dz * sin(pi.B)
    };
}

// ��������δʹ�ã�
double cross(const _2D* a, const _2D* b, const _2D* c) {
    return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
}

// ����ȽϺ�����δʹ�ã�
int compare(const void* a, const void* b) {
    const _2D* p1 = static_cast<const _2D*>(a);
    const _2D* p2 = static_cast<const _2D*>(b);
    return (p1->x != p2->x) ? (p1->x - p2->x) : (p1->y - p2->y);
}

// ����͹��������͹������������δʹ�ã�
int convex_hull(_2D* points, int n, _2D* hull) {
    if (n == 0) return 0;
    qsort(points, n, sizeof(_2D), compare);

    int k = 0;
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(&hull[k - 2], &hull[k - 1], &points[i]) <= 0) k--;
        hull[k++] = points[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(&hull[k - 2], &hull[k - 1], &points[i]) <= 0) k--;
        hull[k++] = points[i];
    }
    return (k > 1) ? k - 1 : k;
}

// �жϵ��Ƿ���͹���ڣ�δʹ�ã�
int is_inside(const _2D& p, const _2D* hull, int hull_size) {
    for (int i = 0; i < hull_size; i++) {
        if (cross(&hull[i], &hull[(i + 1) % hull_size], &p) < 0) return 0;
    }
    return 1;
}

// ����ͶӰ
Box_Plane convert(const block& UB) {
    Box_Plane projectedPlane = project_box(UB);
    _3D v[8] = {
        projectedPlane.plane[0].line[0].print3D[0], projectedPlane.plane[0].line[0].print3D[1],
        projectedPlane.plane[0].line[1].print3D[0], projectedPlane.plane[0].line[1].print3D[1],
        projectedPlane.plane[1].line[0].print3D[0], projectedPlane.plane[1].line[0].print3D[1],
        projectedPlane.plane[1].line[1].print3D[0], projectedPlane.plane[1].line[1].print3D[1]
    };

    _2D Vertices[8];
    for (int i = 0; i < 8; ++i) {
        Vertices[i] = convertTo2D(v[i]);
    }
    return _2DtoBP(Vertices);

   // 
     //   printf("%.1f,%.1f",Vertices[i].x,Vertices[i].y);
    //}
/*
    _2D* points = static_cast<_2D*>(malloc(8 * sizeof(_2D)));
    _2D* hull = static_cast<_2D*>(malloc(16 * sizeof(_2D)));
    if (!points || !hull) {
        free(points);
        free(hull);
        return;
    }

    for (int i = 0; i < 8; i++) points[i] = Vertices[i];
    int k = convex_hull(points, 8, hull);


//��ӡ����ͼ�Σ��о������ӡ��ܣ�

    // ��ӡ͹����������
    printf("͹����������: %d\n", k);

    // ��ӡ͹�����������
    printf("͹����������:\n");
    for (int i = 0; i < k; i++) {
        printf("hull[%d]: (%.2f, %.2f)\n", i, hull[i].x, hull[i].y);
    }
*/
/*
    int min_x = points[0].x, max_x = points[0].x;
    int min_y = points[0].y, max_y = points[0].y;
    for (int i = 1; i < 8; i++) {
        if (points[i].x < min_x) min_x = points[i].x;
        if (points[i].x > max_x) max_x = points[i].x;
        if (points[i].y < min_y) min_y = points[i].y;
        if (points[i].y > max_y) max_y = points[i].y;
    }

    for (int y = max_y; y >= min_y; y--) {
        for (int x = min_x; x <= max_x; x++) {
            _2D p = { x, y };
            if (is_inside(p, hull,k)) gotoxy(static_cast<int>(p.x), static_cast<int>(p.y));
        }
    
    free(points);
    free(hull);}*/
}