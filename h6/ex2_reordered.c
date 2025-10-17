#include <stdio.h>

struct my_struct {
 char a;
 double c;
 int b;
};

int main() {
 struct my_struct A;
 printf("size of my_struct: %lu\n", sizeof(struct my_struct));
 printf("address of char: %p \n", &A.a);
 printf("address of int: %p \n", &A.b);
 printf("address of double: %p \n", &A.c);
}
