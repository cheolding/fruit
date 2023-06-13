#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* element;

typedef struct DlistNode {
    element data;
    struct DlistNode* llink;
    struct DlistNode* rlink;
} DlistNode;

// 전역 변수로 현재 선택된 과일을 가리킬 포인터를 선언합니다.
DlistNode* currentFruit = NULL;

// 이중 연결 리스트의 머리 노드와 꼬리 노드를 가리킬 포인터를 선언합니다.
DlistNode* head = NULL;
DlistNode* tail = NULL;

// 새로운 과일을 리스트에 추가하는 함수입니다.
void addFruit(element fruit) {
    DlistNode* newNode = (DlistNode*)malloc(sizeof(DlistNode));
    newNode->data = (element)malloc(strlen(fruit) + 1);
    strcpy(newNode->data, fruit);
    newNode->llink = NULL;
    newNode->rlink = NULL;

    if (head == NULL) {  // 리스트가 비어있는 경우
        head = newNode;
        tail = newNode;
    }
    else {  // 리스트가 비어있지 않은 경우
        newNode->llink = tail;
        tail->rlink = newNode;
        tail = newNode;
    }

    currentFruit = newNode;  // 새로 추가된 과일을 선택합니다.
}

// 현재 선택된 과일을 삭제하는 함수입니다.
void deleteCurrentFruit() {
    if (currentFruit == NULL) {
        printf("현재 선택된 과일이 없습니다.\n");
        return;
    }

    DlistNode* prevNode = currentFruit->llink;
    DlistNode* nextNode = currentFruit->rlink;

    if (prevNode != NULL) {
        prevNode->rlink = nextNode;
    }
    else {
        head = nextNode;
    }

    if (nextNode != NULL) {
        nextNode->llink = prevNode;
    }
    else {
        tail = prevNode;
    }

    free(currentFruit);
    currentFruit = NULL;
}

// 현재 선택된 과일의 다음 과일로 이동하는 함수입니다.
void moveToNextFruit() {
    if (currentFruit != NULL) {
        currentFruit = currentFruit->rlink;
    }
}

// 현재 선택된 과일의 이전 과일로 이동하는 함수입니다.
void moveToPrevFruit() {
    if (currentFruit != NULL) {
        currentFruit = currentFruit->llink;
    }
}

void printFruitList() {
    DlistNode* temp = head;

    while (temp != NULL) {
        if (temp == currentFruit) {
            printf("%s [O]\n", temp->data);
        }
        else {
            printf("%s\n", temp->data);
        }
        temp = temp->rlink;
    }
}

int main(void) {
    char option;
    char fruitName[100];

    while (1) {
        
        printf("n) next fruit\n");
        printf("p) previous fruit\n");
        printf("d) delete the current fruit\n");
        printf("i) insert fruit after current fruint\n");
        printf("o) output the fruit list(Output [0] at the and of the currently selected fruit)\n");
        printf("e) exit the program\n");
        printf("select a menu:");

        printf(">> ");
        scanf(" %c", &option);

        switch (option) {
        case 'n':
            moveToNextFruit();
            break;
        case 'p':
            moveToPrevFruit();
            break;
        case 'd':
            deleteCurrentFruit();
            break;
        case 'i':
            printf("추가할 과일 이름을 입력하세요: ");
            scanf("%s", fruitName);
            addFruit(fruitName);
            break;
        case 'o':
            printFruitList();
            break;
        case 'e':
            // 메모리를 해제하고 프로그램을 종료합니다.
            while (head != NULL) {
                deleteCurrentFruit();
            }
            return 0;
        default:
            printf("Invalid menu.\n");
            break;
        }

        printf("\n");
    }

    return 0;
}