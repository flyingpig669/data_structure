#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_numbers(int N, int choice, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return;
    }

    for (int i = 0; i < N; i++) {
        if (choice == 1) { // 整数
            int random_int = rand()%100 ; // 生成0到99之间的随机整数
            fprintf(file, "%d\n", random_int);
        } else if (choice == 2) { // 浮点数
            float random_float = (float)rand() / RAND_MAX * 100.0; // 生成0到100之间的随机浮点数
            fprintf(file, "%.2f\n", random_float);
        }
    }

    fclose(file);
}



float find_min_in_file(const char *filename);


int main(){
    int N, choice;

    srand(time(NULL)); // 初始化随机数种子

    printf("*************************************\n");
    printf("project1\n");
    printf("*************************************\n");
    printf("请输入需要产生的随机数个数N=");
    scanf("%d", &N);
    printf("*************************************\n");
    printf("请选择随机数的类型：\n");
    printf("1：整数\n");
    printf("2：浮点数\n");
    printf("3：退出\n");
    printf("*************************************\n");
    printf("请输入（1，2或3）：");
    scanf("%d", &choice);
    if (choice == 3) {
        printf("程序已退出。\n");
        return 0;
    } else if (choice != 1 && choice != 2) {
        printf("无效的选择，请输入1、2或3。\n");
        return 1;
    }
    printf("***************************************\n");
    printf("请输入存储的文件名：");
    char filename[100];
    scanf("%s", filename);
    generate_random_numbers(N, choice, filename);
    printf("***************************************\n");
    printf("请输入读取的文件名：");
    char read_filename[100];
    scanf("%s", read_filename);
    printf("***************************************\n");
    printf("文件中最小值是：");
    float min = find_min_in_file(read_filename);
    if (min == (long long)min) {
        printf("%lld\n", (long long)min);
    } else {
        printf("%.2f\n", min);
    }


    return 0;
}

float find_min_in_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return 0;
    }

    float min_value;
    int first_value = 1; // 标记是否是第一个值

    while (!feof(file)) {
        float value;
        if (fscanf(file, "%f", &value) == 1) {
            if (first_value) {
                min_value = value;
                first_value = 0;
            } else if (value < min_value) {
                min_value = value;
            }
        }
    }

    fclose(file);

    if (!first_value) {
        return min_value;
    } else {
        printf("文件中没有有效的数字。\n");
        return 0;
    }
}
