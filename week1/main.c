#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	struct node *next;
	int value;
} NODE;

struct STACK {
    int size;
    struct node * first;

};

struct STACK stack;

void create() {
	stack.first = NULL;
	stack.size = 0;
}

void display() {
	NODE *node = stack.first;
	for (int i = 0; i < stack.size; i++) {
		printf("%d ", node->value);
		node = node->next;
	}
	printf("\n");
}
void push(int value) {
	NODE *node = (NODE*)malloc(sizeof(NODE));
	node->value = value;
	if (stack.size == 0) {
		stack.first = node;
		node->next = NULL;
	} else {
		node->next = stack.first;
		stack.first = node;
	}
	stack.size++;
	printf("Pushed\n");
}

void pop() {
	if (stack.size == 0) {
		printf("Empty stack\n");
		return;
	} else if (stack.size == 1) {
		printf("Popped %d\n", stack.first->value);
		stack.first = NULL;
	}else {
		printf("Popped %d\n", stack.first->value);
		stack.first = stack.first->next;
	}
	stack.size--;
}

int peek() {
	if (stack.first == NULL) {
		printf("Empty stack\n");
	} else {
		printf("%d\n", stack.first->value);
		return stack.first->value;
		}
}

void stack_size() {
	printf("%d\n", stack.size);
}

int empty() {
	if (stack.size == 0)
		printf("Stack is empty\n");
	else
		printf("Stack is not empty\n");
	return (stack.size == 0);
}

int main() {
	int fd[2];
	pipe(fd);
	
	pid_t pid = fork();
	if (pid > 0) {
		//client();
		while(1) {
			char buf[64];
			scanf("%s", buf);
			write(fd[1], buf, 64);
			}
	}
	else if (pid == 0){
		create();
		while(1) {
			char buf[64];
			read(fd[0], buf, 64);
			char* second_part;
			for (int i = 0; i < 64; i++) {
				if (buf[i] == ':'){
					buf[i] = '\0';
					second_part = buf+i+1;
					break;
				}
			}
			if (strcmp(buf,"push")==0){
				printf("TEST: %d\n", atoi(second_part));
				push(atoi(second_part));
			}
			else if (strcmp(buf,"pop")==0){
				pop();
			}
			else if (strcmp(buf,"peek")==0){
				peek();
			}
			else if (strcmp(buf,"display")==0){
				display();
			}
			else if (strcmp(buf,"stack_size")==0){
				stack_size();
			}
			else if (strcmp(buf,"empty")==0){
				empty();
			}
			else if (strcmp(buf,"create")==0){
				create();
			}
			else {
				printf("Not valid command.<command>:<argument>\n");
			}
		}
	}
	else
		return -1;
}
