#include <stdio.h>

#pragma pack(1)
struct my_struct {
 char a;
 int b;
 double c;
};

int main() {
 struct my_struct A;
 printf("size of my_struct: %lu\n", sizeof(A));
 printf("address of char: %p \n", &A.a);
 printf("address of int: %p \n", &A.b);
 printf("address of double: %p \n", &A.c);
}
