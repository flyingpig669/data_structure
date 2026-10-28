#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

void generateRandomNumbers(int N, int choice, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) { printf("无法创建文件 %s\n", filename); return; }

    for (int i = 0; i < N; i++) {
        if (choice == 1) { // 整数
            int random_int = rand()%100000 ;
            fprintf(file, "%d\n", random_int);
        } else if (choice == 2) { // 浮点数
            float random_float = (float)rand() / RAND_MAX * 100.0; // 生成0到100之间的随机浮点数
            fprintf(file, "%.2f\n", random_float);
        }
    }

    fclose(file);
}

double* readFile(const char *filename,const int N ){
    FILE *file = fopen(filename,"r");
    if (file == NULL){
        printf("无法打开文件 %s \n",filename);
        return NULL;
    }
    double* array = malloc(N * sizeof(double));
    double value;int i=0;
    while(i<N && fscanf(file,"%lf",&value)==1){
        array[i++] = value;
    }
    fclose(file);
    return array;
}

// define node struct
typedef struct Node {
    double data;
    struct Node* next;
} Node;

// define linked list struct
typedef struct {
    Node* head;
    size_t count;
} LinkedList;

// define stack struct
typedef struct {
    Node* top;
} Stack;

//define queue struct
typedef struct {
    Node* front;
    Node* rear;
    size_t count;
} Queue;


bool isEqual(double a, double b) {
    return fabs(a - b) < 1e-4;
}


Node * createNode(double data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf( "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


// linked list functions
Node* initLinkedList(LinkedList* list) {
    list->head = NULL;
    list->count = 0;
    return list->head;
}

Node* insertListAt(LinkedList* list, double data, int position) {
    /*
    return the pointer of the new node, if insert failed return NULL
    */

    if (position < 0 || position > list->count) {
        printf("Invalid position\n");
        return NULL;
    }

    Node* newNode = createNode(data);
    //1.insert Head
    if (position == 0) {
        newNode ->next = list ->head;
        list ->head =newNode;
        list->count++;
        return newNode;
    }
    //2.normal insert
    Node* current = list->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    list->count++;
    return newNode;

}

Node* deleteListAt(LinkedList* list, int position) {
    /*
    return the pointer of the deleted node, if delete failed return NULL
    */

    if (list->head == NULL) {
        printf("List is empty\n");
        return NULL;
    }

    if (position < 0 || position >= list->count) {
        printf("Invalid position\n");
        return NULL;
    }

    // delete head
    if (position == 0) {
        Node* temp = list->head;
        list->head = list->head->next;
        list->count--;
        return temp;
    }

    Node* current = list->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    Node* temp = current->next;
    current->next = current->next->next;
    list->count--;
    return temp;

}

Node* getListAt(LinkedList* list, double data) {
    Node* current = list->head;
    while (current != NULL){
        if (isEqual(current->data, data)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void displayList(LinkedList *list,int numType) {
    Node *current = list->head;

    if (current == NULL) {
        printf("链表为空！\n");
        return;
    }

    while (current != NULL) {
        printf("\n");
        if (numType == 1) { // 整数
            printf("%lld ", (long long)current->data);
        } else if (numType == 2) { // 浮点数
            printf("%.2f ", current->data);
        }
        current = current->next;
    }

    printf("\nDisplay Over!\n");
}


void linkedListMenu(LinkedList* list,int numType) {
    int choice;

    while(1){
        printf("1.插入\n2.删除\n3.查询\n4.display\n5.返回上级菜单\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                printf("输入插入的位置以及数据，用空格分开：\n");
                double data;int pos;
                scanf("%d %lf",&pos,&data);
                if(insertListAt(list,data,pos)!= NULL){
                    printf("插入成功");
                    break;
                }
                else{
                    printf("插入失败");
                    break;
                    }
            }
            case 2:{
                printf("删除数据的位置\n");
                int pos;
                scanf("%d",&pos);
                Node* deleted = deleteListAt(list,pos);
                if (deleted!=NULL){
                    printf("删除成功");
                    free(deleted);
                    break;
                }
                else{
                    printf("删除失败");
                    break;
                }
            }
            case 3:{
                printf("请输入要查询的数据\n");
                double data;
                scanf("%lf",&data);
                if (getListAt(list,data)!=NULL){
                    printf("数据存在");
                    break;
                }
                else{
                    printf("数据不存在");
                    break;
                }
            }
            case 4:{
                printf("\n===============LinkedList================\n");
                displayList(list,numType);
                printf("\n===============LinkedList================\n");
                break;
            }
            case 5:
                return;

            default:{
                printf("无效的选择！\n");
                break;

            }
        }


    }
}

void operateList(double* arr,const int N,int numType){
    // 1. make linked-list
    LinkedList list;
    initLinkedList(&list);
    for(int i=0;i<N;i++){
        insertListAt(&list,arr[i],i);
    }

    linkedListMenu(&list,numType);

}




int main(){
    int N, choice;

    srand(time(NULL)); // 初始化随机数种子

    printf("*************************************\n");
    printf("project2\n");
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
    generateRandomNumbers(N, choice, filename);
    printf("***************************************\n");
    printf("请输入读取的文件名：");
    char read_filename[100];
    scanf("%s", read_filename);
    double* data = readFile(read_filename,N);
    printf("***************************************\n");
    while(1){

        printf("请选择数据结构的类型：\n");
        printf("1：linked-list\n");
        printf("2：queue\n");
        printf("3：stack\n");
        printf("4：返回上一级菜单\n");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                operateList(data,N,choice);
                break;
            case 4: free(data); return 0;
            default:break;

        }
    }
    printf("*************************************");

    return 0;
}


