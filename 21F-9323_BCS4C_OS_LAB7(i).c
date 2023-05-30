#include<stdio.h>
#include<pthread.h>

struct range 
{ 
int start;
int end;
};


int prime(int n)
{
if(n<=1)
{
return 0;
}
for(int i=2; i*i<n,i++)
{
if (n%i==0)
{
return 0;
}
}
return 1;
}


void worker()
{
for(int i=start; i<end; i++)
{
printf("Prime numbers are: ");
if (prime(i))
{
printf(",%d", i);
}
pthread_exit(NULL);
}


int main()
{
pthread_t t;
struct range obj;
printf("Enter start and end point: ");
scanf("%d %d", &obj.start, &obj.end);
pthread_create(&t, NULL, worker, &obj);

pthread_join(t, NULL); 
}
