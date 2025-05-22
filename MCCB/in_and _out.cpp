//文件（正方体集合链表）的读写

#include <string.h>
#include <stdio.h>
#include "functions.h"
#include <sys/stat.h>

extern setofblock* Bhead;

// 检查文件是否存在
bool file_exists(const char* filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

// 获取下一个可用的数字文件名
void get_next_filename(char* out, size_t out_size) {
    int idx = 1;
    do {
        snprintf(out, out_size, "..\\save\\%d", idx);
        idx++;
    } while (file_exists(out));
}

// 存储当前所有方块
void save() {
    setofblock* temp = Bhead;
    FILE* fp;
    char filename[64];
    get_next_filename(filename, sizeof(filename));
    
    // 使用 fopen_s 替代 fopen
    if (fopen_s(&fp, filename, "w") != 0 || !fp) {      // IDE不让我用老师教的（不安全.jpg）（(ㄒoㄒ)）（懒得管SDL检查了）
        return;
    }

    while (temp) {                                      // 遍历链表并写入每个节点的数据
        fwrite(&(temp->box), sizeof(block), 1, fp);
        temp = temp->next;
    }
    fclose(fp);
}

// 读取指定文件的方块到block链表（会释放当前block链表）
bool load(char* in) {
    freeB();
    freePl();
    block box;
    FILE* fp;
    char filename[64];    
    strcpy_s(filename, sizeof(filename), in);

    if (fopen_s(&fp, filename, "r") != 0 || !fp) {
        printf("无效地址");
        Sleep(500);
        return 0;
    }
    if (!fp) {
        return 0;
    }

    while (fread(&box, sizeof(block), 1, fp) == 1) { // 每次读取一个方块的数据
        append(box);
        appendPl(convert(box));
    }
    fclose(fp);
    return 1;
}