#include <stdio.h>

struct Person {
  char name[50];
  int age;
  float height;
};

int main() {
  struct Person person1 = {"Alice", 30, 5.4};
  struct Person person2 = {"Ben", 25, 6.10};

  printf("Name 1: %s\n", person1.name);
  printf("Age 1: %d\n", person1.age);
  printf("Height 1: %.1f\n", person1.height);

  int *pAge = &person1.age;

  printf("Age 1: %d\n", *pAge);

  return 0;
}
