#include <stdio.h>

int main() {
 int i;
 char c;
 double d;
 short s;
 printf("sizeof int: %lu, address: %p \n", sizeof(i), &i);
 printf("sizeof char: %lu, address: %p \n", sizeof(c), &c);
 printf("sizeof double: %lu, address: %p \n", sizeof(d), &d);
 printf("sizeof short: %lu, address: %p \n", sizeof(s), &s);
}
