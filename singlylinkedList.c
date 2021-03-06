 
#include <stdio.h>
#include <string.h>

/*단일 연결리스트*/

typedef struct { //노드에 담을 자료 멤버
	int num;
	char *name;
}Member;

//노드
typedef struct __node {
	//Member data; -> 데이터 여러개 담을 수도 있음
    char *data;
	struct __node *next;
}Node;

//연결리스트
typedef struct _list{
	Node *head;  //머리 노드에 대한 포인터 -> 데이터 값이 바로 들어감
    int size; //리스트 크기
}List;

//단순 연결 리스트를 초기화 & 할당하는 함수
List *listInit() {
    // 리스트를 선언
    List *newList;
    newList = (List *)malloc(sizeof(List));
    // 새로운 리스트의 head 초기화
    newList->head = NULL;
    newList->size = 0;
    return newList;
}

//노드를 주어진 문자열로 초기화하는 함수
Node *nodeInit(char *str) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data.name = (char *)malloc(strlen(str) + 1);
    strcpy(newNode->data, str);

    newNode->next = NULL;

    return newNode;
}


/*추가*/

//리스트의 끝에 노드를 추가하는 함수
void addLast(List *list, char *str) {
    Node *newNode = nodeInit(str);
    Node *selectNode = list->head;

    // 리스트에 노드가 없는 경우
    if (list->head == NULL) {
        list->head = newNode;
    }
    // 리스트에 노드가 있는 경우
    else {
        while (selectNode->next != NULL) {
            selectNode = selectNode->next;
        }
        selectNode->next = newNode;
    }
    list->size++;
}

//리스트의 처음에 노드 추가
void addFirst(List *list, char *str) {
    Node *newNode = nodeInit(str);

    if (list->head == NULL) {
        list->head = newNode;
    }
    else {
        newNode->next = list->head;
        list->head = newNode;
    }
    list->size++;
}

//리스트의 head로부터 n번째 위치에 노드를 추가
void addNodeAt(List *list, char *str, int n) {
    Node *newNode;
    Node *selectNode = list->head;
    int i;

    if (list->size == 0 || n < 0 || list->size - 1 < n) {
        addLast(list, str);
        return 0;
    }

    newNode = nodeInit(str);

    if (n == 0) {
        newNode->next = list->head;
        list->head = newNode;
    }
    else {
        for (int i = 0; i < n - 1; i++) {
            selectNode = selectNode->next;
        }
        newNode->next = selectNode->next;
        selectNode->next = newNode;
    }
    list->size++;
}



/*삭제*/


//마지막 노드 삭제
void removeLast(List *list) {
    // prvNode : 현재 마지막에서 두번째 노드를 담을 변수
    Node *prvNode;
    Node *selectNode = list->head;

    if (list->head == NULL) return;

    // 리스트에 노드가 하나인 경우 head로 지정된 노드를 제거
    if (list->head->next == NULL) {
        free(list->head->data);
        free(list->head);
        list->head = NULL;
    }
    // 리스트에 노드가 하나 이상인 경우
    else {
        while (selectNode->next != NULL) {
            prvNode = selectNode;
            selectNode = selectNode->next;
        }
        
        free(selectNode->data);
        free(selectNode);
        // prvNode를 마지막 노드로 설정
        prvNode->next = NULL;
    }
    
    list->size--;
}

//첫번째 노드 삭제
void removeLast(List *list) {
    Node *nextNode; //head 다음노드
    Node *selectNode = list->head;

    // 리스트에 노드가 없는경우 함수를 종료
    if (list->head == NULL) return;

    // 리스트에 노드가 하나인 경우 head로 지정된 노드를 제거
    if (list->head->next == NULL) {
        free(list->head->data);
        free(list->head);
        list->head = NULL;
    }
    // 리스트에 노드가 하나 이상인 경우
    else {
        nextNode = list->head->next;

        free(selectNode->data);
        free(selectNode);
        
        list->head = nextNode;
    }
    list->size--;
}

// 리스트의 head로부터 n번째 위치의 노드를 삭제
void removeNodeAt(List *list, int n) {
    Node *selectNode = list->head;
    Node *deleteNode;
    int i;

    // 리스트에 노드가 없거나 인수 n의 값이 올바르지 않을 경우
    if (list->head == NULL || n < 0 || list->size - 1 < n) {
        return;
    }

    if (n == 0) {
        list->head = list->head->next;
        free(selectNode->data);
        free(selectNode);
        list->size--;
    }
    
    else {
        // 리스트의 head부터 시작해서 제거할 n번째 위치의 이전 노드로 이동
        for (int i = 0; i < n - 1; i++) {
            selectNode = selectNode->next;
        }
        
        deleteNode = selectNode->next;        
        selectNode->next = selectNode->next->next;
        // 노드 삭제
        free(deleteNode->data);
        free(deleteNode);
        list->size--;
    }
}

/*탐색*/

// searchNodes : 문자열 str이 head로부터 몇번째 위치에 있는지 확인 -> 참고
void searchArrNodes(List *list, char *str) {
    // access[] : 위치를 저장할 배열을 생성 (같은 내용의 데이터가 있을수도 있으니)
    int access[100] = { -1 };
    int accessCount = 0;
    // selectNode : 리스트의 노드를 선택하기 위한 변수. 리스트의 head부터 시작
    Node *selectNode = list->head;
    int i;

    // 리스트의 head부터 마지막 노드까지 루프
    for (i = 0; i < list->size; i++) {
        if (!strcmp(selectNode->data, str)) {
            // 만약 같은 문자열이 있다면 access 배열에 위치를 저장
            access[accessCount] = i;
            // 끝을 표시하기위해 배열의 마지막 원소의 값을 -1로 지정
            access[accessCount + 1] = -1;
            accessCount++;
        }
        selectNode = selectNode->next;
    }

    // 검색 결과를 출력
    // access에 값이 들어가지 않았을시 해당 데이터가 없음을 출력
    if (access[0] == -1) {
        printf("%s Not Found!\n\n", str);
    }
    // 해당 데이터가 있을시에 위치를 출력
    else {
        for (int i = 0; i < 100; i++) {
            if (access[i] == -1) {
                break;
            }
            else {
                printf("%d ", access[i]);
            }
        }
        printf("\n\n");
    }
}

//모든 데이터 출력
void printList(List *list) {
    Node *selectNode = list->head;

    // 출력
    while (selectNode != NULL) {
        printf("%s", selectNode->data);
        selectNode = selectNode->next;
        if (selectNode != NULL) {
            printf("\n");
        }
    }
}