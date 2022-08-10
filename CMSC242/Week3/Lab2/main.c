#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct data {
  int top;
};

struct node {
  struct data input;
  struct node *next;
};

void push(struct node **top, int x) {
  struct node* node = NULL;
  node = (struct node*)malloc(sizeof(struct node));
  node->input.top = x;
  node->next = *top;
  *top = node;
  printf("ok\n");
}

void pop(struct node** top) {
  struct node* node = NULL;
  node = *top;
  printf("%d\n", node->input.top);
  *top = (*top)->next;
  free(node);
}

int main() {
  struct node* b = malloc(sizeof(struct node));
  char command[5];
  int i = 1;
  int scan;
  while(i > 0) {
  scanf("%5s", command);
  if(strcmp("end", command) == 0) {
    while(b != NULL) {
      if(b->input.top == 0) {
	break;
      }
      printf("%d\n", b->input.top);
      b = b->next;
    }
    break;
  }
  else if(strcmp("push", command) == 0) {
    scanf("%d", &scan);
    push(&b, scan);
  }
  else if(strcmp("pop", command) == 0) {
    pop(&b);
    //printf("%d\n", b->input.top);
  }
  else {
    printf("error\n");
  }
  }
  free(b);

}


