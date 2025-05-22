//��Դ�ļ�����ļ��������弯�������Ķ�д

#include <string.h>
#include <stdio.h>
#include "functions.h"
#include <sys/stat.h>

extern setofblock* Bhead;

// ����ļ��Ƿ����
bool file_exists(const char* filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

// ��ȡ��һ�����õ������ļ���
void get_next_filename(char* out, size_t out_size) {
    int idx = 1;
    do {
        snprintf(out, out_size, "..\\save\\%d", idx);
        idx++;
    } while (file_exists(out));
}

// �洢��ǰ���з���
void save() {
    setofblock* temp = Bhead;
    FILE* fp;
    char filename[64];
    get_next_filename(filename, sizeof(filename));
    
    // ʹ�� fopen_s ��� fopen
    if (fopen_s(&fp, filename, "w") != 0 || !fp) {      // IDE����������ʦ�̵ģ�����ȫ.jpg����(��o��)
        return;
    }

    while (temp) {                                      // ��������д��ÿ���ڵ������
        fwrite(&(temp->box), sizeof(block), 1, fp);
        temp = temp->next;
    }
    fclose(fp);
}

// ��ȡָ���ļ��ķ��鵽block�������ͷŵ�ǰblock����
void load(char* in) {
    block box;
    FILE* fp;
    char filename[64];    
    strcpy_s(filename, sizeof(filename), in);           // IDE����������ʦ�̵ģ�����ȫ.jpg����(��o��)��

    if (fopen_s(&fp, filename, "r") != 0 || !fp) {      // IDE����������ʦ�̵ģ�����ȫ.jpg����(��o��)��
        return;
    }
    if (!fp) {
        return; 
    }

    while (!feof(fp)) {                                  // �����ļ������������ڵ�
        fread(&box, sizeof(block), 1, fp);
        append(CCB());
        appendPl(convert(CCB()));
    }
    fclose(fp);
}