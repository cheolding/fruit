#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* element;

typedef struct DlistNode {
    element data;
    struct DlistNode* llink;
    struct DlistNode* rlink;
} DlistNode;

// ���� ������ ���� ���õ� ������ ����ų �����͸� �����մϴ�.
DlistNode* currentFruit = NULL;

// ���� ���� ����Ʈ�� �Ӹ� ���� ���� ��带 ����ų �����͸� �����մϴ�.
DlistNode* head = NULL;
DlistNode* tail = NULL;

// ���ο� ������ ����Ʈ�� �߰��ϴ� �Լ��Դϴ�.
void addFruit(element fruit) {
    DlistNode* newNode = (DlistNode*)malloc(sizeof(DlistNode));
    newNode->data = (element)malloc(strlen(fruit) + 1);
    strcpy(newNode->data, fruit);
    newNode->llink = NULL;
    newNode->rlink = NULL;

    if (head == NULL) {  // ����Ʈ�� ����ִ� ���
        head = newNode;
        tail = newNode;
    }
    else {  // ����Ʈ�� ������� ���� ���
        newNode->llink = tail;
        tail->rlink = newNode;
        tail = newNode;
    }

    currentFruit = newNode;  // ���� �߰��� ������ �����մϴ�.
}

// ���� ���õ� ������ �����ϴ� �Լ��Դϴ�.
void deleteCurrentFruit() {
    if (currentFruit == NULL) {
        printf("���� ���õ� ������ �����ϴ�.\n");
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

// ���� ���õ� ������ ���� ���Ϸ� �̵��ϴ� �Լ��Դϴ�.
void moveToNextFruit() {
    if (currentFruit != NULL) {
        currentFruit = currentFruit->rlink;
    }
}

// ���� ���õ� ������ ���� ���Ϸ� �̵��ϴ� �Լ��Դϴ�.
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
            printf("�߰��� ���� �̸��� �Է��ϼ���: ");
            scanf("%s", fruitName);
            addFruit(fruitName);
            break;
        case 'o':
            printFruitList();
            break;
        case 'e':
            // �޸𸮸� �����ϰ� ���α׷��� �����մϴ�.
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