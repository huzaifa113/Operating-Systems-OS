#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int arr[100];
int num;
int found = 0;


void* search(void* arg) 
{
    int thread_num = *((int*)arg);
    int start = thread_num * (100 / 4);
    int end = (thread_num + 1) * (100 / 4) - 1;

    for (int i = start; i <= end; i++) 
    {
        if (arr[i] == num) 
        {
            found = 1;
            printf("Thread ID: TID%d - Found number %d at index %d\n", thread_num+1, num, i);
            for (int j = 0; j < 4; j++) 
            {
                if (j != thread_num) 
                {
                    pthread_cancel(j+1);
                }
            }
            break;
        }
    }

    pthread_exit(NULL);
}


int main() 
{
    
    for (int i = 0; i < 100; i++) 
    {
        arr[i] = i+1;
    }

    
    printf("Enter number to search: ");
    scanf("%d", &num);

    
    pthread_t tid[4];
    int thread_nums[4];
    for (int i = 0; i < 4; i++) 
    {
        thread_nums[i] = i;
        pthread_create(&tid[i], NULL, search, &thread_nums[i]);
    }

    
    for (int i = 0; i < 4; i++) 
    {
        pthread_join(tid[i], NULL);
    }

    
    if (!found) 
    {
        printf("Number %d not found in the given range.\n", num);
    }

    return 0;
}
