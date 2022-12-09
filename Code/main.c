#include <stdio.h> 

int main()
{
    char name[20];
    int age;
    float height;
    
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter your age: ");
    scanf("%d", &age);
    printf("Enter your height: ");
    scanf("%f", &height);

    printf("Your name is %s, you are %d years old and you are %f meters tall", name, age, height);
    return 0;
}