#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct Rect 
{
    double length;
    double width;
};

double area;
double perimeter;

void* calcArea(void* arg) 
{
    struct Rect* r = (struct Rect*)arg;
    area = r->length * r->width;
    pthread_exit(NULL);
}

void* calcPerimeter(void* arg) 
{
    struct Rect* r = (struct Rect*)arg;
    perimeter = 2 * (r->length + r->width);
    pthread_exit(NULL);
}

int main() 
{
    struct Rect r;

    printf("Enter length and width of rectangle: ");
    scanf("%lf %lf", &r.length, &r.width);

    pthread_t t1,t2;
    pthread_create(&t1, NULL, calcArea, &r);
    pthread_create(&t2, NULL, calcPerimeter, &r);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Area = %lf\n", area);
    printf("Perimeter = %lf\n", perimeter);

    return 0;
}

