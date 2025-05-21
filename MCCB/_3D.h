#include <math.h>


// 二维点结构体
struct _2D {
    double x;
    double y;
    bool operator==(const _2D& other) const {
        return round(x) == round(other.x) && round(y) == round(other.y);
    }
};

// 三维点结构体
struct _3D {
    double D[3];
    _3D operator+(const _3D& other) const {
        return { D[0] + other.D[0], D[1] + other.D[1], D[2] + other.D[2] };
    }
    bool operator==(const _3D& other) const {
        return D[0] == other.D[0] && D[1] == other.D[1] && D[2] == other.D[2];
    }
};

// 线结构体
union Line{
    _3D print3D[2];
	_2D print2D[2];
};

// 正方平面结构体
struct Plane{
    Line line[2];   //下线段
};

// 投影平面方程结构体（单位法向量形式）
struct Plane0{
    _3D center;   // 投影中心O  
    double a, b, c; // 单位法向量的分量  
    double A, B; // 视角的角度  
    int h;         // 平面到O的距离  

    Plane0(_3D o, double A, double B, int h)
        : center(o), A(A), B(B), h(h) {
        updateNormalVector();
    }

    void setAngles(double newA, double newB) {
        A = newA;
        B = newB;
        updateNormalVector();
    }

private:
    void updateNormalVector() {
        a = (-cos(A) * sin(B));
        b = (-sin(A) * sin(B));
        c = (-cos(B));
    }
};

// 正方体结构体
struct block {
    Plane plane[2]; // 两个面  
    bool operator==(const block& other) const {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    if (!(plane[i].line[j].print3D[k] == other.plane[i].line[j].print3D[k])) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};

// 正方体在平面上的投影
struct Box_Plane{
    Plane plane[2];
    bool operator==(const Box_Plane& other) const {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    if (!(plane[i].line[j].print2D[k] == other.plane[i].line[j].print2D[k])) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};

// 空间内方块的集合的链表
struct setofblock {
    block box;
	setofblock* next;
	setofblock* pre;
	setofblock(block s) : box(s), next(nullptr), pre(nullptr) {}
};

// 投影集合链表
struct setofprojection {
    int count;
	Box_Plane Pbox;
	setofprojection* next;
	setofprojection* pre;
	setofprojection(Box_Plane s) :count(0), Pbox(s), next(nullptr), pre(nullptr) {}
};

struct count {
    int n;
    count* next;
    count* pre;
    count(int val) : n(val), next(nullptr), pre(nullptr) {}
};

struct setofprint {
    int c;
    count* n;
    _2D P;
    setofprint* next;
    setofprint* pre;
    setofprint(_2D s) : c(0), n(nullptr), P(s), next(nullptr), pre(nullptr) {}
};

//包围盒结构体（未使用）
struct BBox
{
    _3D min; // 最小坐标
    _3D max; // 最大坐标
};

