#include <stdio.h>
#include <stdlib.h>

typedef void* Data;
typedef struct Node Node;

typedef enum{
	DATA_INT,
	DATA_DOUBLE
}DataType;

void print(Node *list, DataType t);
void push(Node **plist, Data d, DataType t);
Data pop(Node **plist);
int is_empty(Node *list);

struct Node {
	DataType type;
	Data data;
	Node *next;
};

void print(Node *list, DataType t){
	switch(t){
	case DATA_INT:
		for(Node *p = list; p != NULL; p = p->next){
			printf("%d\t", *(int*)p->data);
		}
		printf("\n");
		break;
	case DATA_DOUBLE:
		for(Node *p = list; p != NULL; p = p->next){
			printf("%f\t", *(double*)p->data);
		}
		printf("\n");
		break;
	default:
		fprintf(stdout, "invalid type\n");
		break;
	}
}

void push(Node **plist, Data d, DataType t){
	Node *p = malloc(sizeof(Node));
	p->type = t;
	p->data = d;
	p->next = *plist;
	*plist = p;
}
Data pop(Node **plist){
	Node *p = *plist;
	Data buff = p->data;
	*plist = p->next;
	free(p);
	return buff;
}

int is_empty(Node *list){
	return list == NULL;
}

int main(){
	fprintf(stdout, "test for int type\n");

	Node *list = NULL;
	int test[] = {1, 2, 3};
	printf("Empty? %s\n", is_empty(list) ? "yes" : "no");

	for(size_t i = 0; i < sizeof(test)/sizeof(test[0]); i++){
		push(&list, &test[i], DATA_INT);
		print(list, DATA_INT);
	}
	printf("Empty? %s\n", is_empty(list) ? "yes" : "no");

	while(!is_empty(list)){
		Data d = pop(&list);
		printf("pop %d: ", *(int*)d);
		print(list, DATA_INT);
	}
	printf("Empty? %s\n", is_empty(list) ? "yes" : "no");

	fprintf(stdout, "test for double type\n");
	double test2[] = {0.1, 0.2, 0.3};

	for(size_t i = 0; i < sizeof(test2)/sizeof(test2[0]); i++){
		push(&list, &test2[i], DATA_DOUBLE);
		print(list, DATA_DOUBLE);
	}
	while(!is_empty(list)){
			Data d = pop(&list);
			printf("pop %f: ", *(double*)d);
			print(list, DATA_DOUBLE);
	}
	return 0;
}

/*
 * Необходимо сделать данные типа void* чтобы была возможность создавать 
 * односвязный список для разных типов данных.
 *
 * Напишем простейший список, в котором будет возможность добавлять узел,
 * удалять узел, проверять пуст ли список и печатать список в определенном формате.
 * 
 *  К сожалению реализация каждой функции должна быть своя для каждого типа, поэтому
 *  код может быть довольно большой, если реализовывать каждый тип. В функции main 
 *  прописанной пару тестов с реализацией различных типов.
 *  
 *  На основе списков можно создавать такие структуры, как очереди, а они уже
 *  могут использоваться как средства работы с операционной системой. В частности 
 *  FreeRtos обладает Queues как средство взаимодействия между Tasks
*/


