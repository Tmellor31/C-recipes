#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "linked_list.h"

void clear_cons(Cons *cons) {
  Cons *cdr = NULL;
  for (; cons != NULL; cons = cdr) {
    cdr = cons->cdr;
    free(cons);
  }
}

Cons *cons(char car, Cons *cdr) {
  Cons *cons = (Cons*) malloc(sizeof(Cons));
  cons->car = car;
  cons->cdr = cdr;
  return cons;
}

Cons *copy_cons(Cons *existing) {
  if (existing == NULL) {
    return NULL;
  }
  return cons(existing->car, copy_cons(existing->cdr));
}

Cons *last(Cons* cons) {
    for (; cons != NULL; cons = cons->cdr) {
      if (cons->cdr == NULL) {
	return cons;
      }
    }
    return NULL;
}

Cons *append(Cons *first, Cons *second) {
  Cons *first_copy = copy_cons(first);
  Cons *last_cons = last(first_copy);
  if (last_cons == NULL) {
    return second;
  }
  last_cons->cdr = second;
  return first_copy;
}

bool insert_after(Cons* current, char new_value) {
  if (current == NULL) {
    return false;
  }
  
  Cons *new_cons = cons(new_value, current->cdr);
  current->cdr = new_cons;
  return true;
}

void print_cons(Cons *cons) {
  for (; cons != NULL; cons = cons->cdr) {
    putchar(cons->car);
    if (cons->cdr != NULL) {
      printf("->");
    }
  }
  printf("\n");
}

void test(void) {
  Cons *single = cons('A', NULL);
  assert(single->car == 'A');
  assert(single->cdr == NULL);

  Cons *pair = cons('B', single);
  assert(pair->car == 'B');
  assert(pair->cdr == single);

  Cons *copy = copy_cons(pair);
  assert(copy != pair);
  assert(copy->car == 'B');
  assert(copy->cdr != single);
  assert(copy->cdr->car == 'A');
  assert(copy->cdr->cdr == NULL);

  Cons *joined = append(single, pair);
  assert(joined->car == 'A');
  assert(joined->cdr->car == 'B');
  assert(joined->cdr->cdr->car == 'A');
  assert(joined->cdr->cdr->cdr == NULL);

  Cons *my_list = cons('A', cons('Z', cons('Q', cons('X', NULL))));
  Cons *q_cons = my_list->cdr->cdr;
  insert_after(q_cons, 'Y');
  assert(q_cons->cdr->car == 'Y');
  assert(q_cons->cdr->cdr->car == 'X');

  clear_cons(my_list);
  clear_cons(copy);
  clear_cons(joined);
}

int main() {
  test();
  return 0;
}
