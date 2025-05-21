#include <math.h>


// ��ά��ṹ��
struct _2D {
    double x;
    double y;
    bool operator==(const _2D& other) const {
        return round(x) == round(other.x) && round(y) == round(other.y);
    }
};

// ��ά��ṹ��
struct _3D {
    double D[3];
    _3D operator+(const _3D& other) const {
        return { D[0] + other.D[0], D[1] + other.D[1], D[2] + other.D[2] };
    }
    bool operator==(const _3D& other) const {
        return D[0] == other.D[0] && D[1] == other.D[1] && D[2] == other.D[2];
    }
};

// �߽ṹ��
union Line{
    _3D print3D[2];
	_2D print2D[2];
};

// ����ƽ��ṹ��
struct Plane{
    Line line[2];   //���߶�
};

// ͶӰƽ�淽�̽ṹ�壨��λ��������ʽ��
struct Plane0{
    _3D center;   // ͶӰ����O  
    double a, b, c; // ��λ�������ķ���  
    double A, B; // �ӽǵĽǶ�  
    int h;         // ƽ�浽O�ľ���  

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

// ������ṹ��
struct block {
    Plane plane[2]; // ������  
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

// ��������ƽ���ϵ�ͶӰ
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

// �ռ��ڷ���ļ��ϵ�����
struct setofblock {
    block box;
	setofblock* next;
	setofblock* pre;
	setofblock(block s) : box(s), next(nullptr), pre(nullptr) {}
};

// ͶӰ��������
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

//��Χ�нṹ�壨δʹ�ã�
struct BBox
{
    _3D min; // ��С����
    _3D max; // �������
};

