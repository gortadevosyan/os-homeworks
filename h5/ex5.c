#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
 int n;
 printf("Enter the number of students: ");
 scanf("%d", &n);

 int *grades = malloc(n * sizeof(int));
 printf("Enter the grades: ");

 int maxGrade = INT_MIN, minGrade = INT_MAX;
 for(int i=0; i<n; i++){
  scanf("%d", &grades[i]);
  maxGrade = (grades[i] > maxGrade) ? grades[i] : maxGrade;
  minGrade = (grades[i] < minGrade) ? grades[i] : minGrade;
 }
 printf("Highest grade: %d \n", maxGrade);
 printf("Lowest grade: %d \n", minGrade);

}
