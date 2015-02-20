//  Created by Alan Lin on 12/10/20.
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define ARR_SIZE 10000


void *runner(void *param);
int array[ ARR_SIZE ];
int main(int argc, char* argv[])
{    
    int chkValue = atoi(argv[1]), i;
    if (chkValue > 0) {                              //Argument checking
        pthread_t tid;                               //Create a thread
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, runner, argv[1]); //Arg3 must be void*
        pthread_join(tid, NULL);                      //Waiting for child thread
        
        for (i = 0; (i < ARR_SIZE) && (array[i] != -1); i++)//Here is parent thread
            printf("%d ", array[i]);                  //Print the array until meet the ending value (-1)
        printf("\n");    
    }
    return 0;
}

void *runner(void *param)
{
    int n = atoi(param);
    int i, j, fib_0 = 0, fib_1 = 1, fib;
    
    for(i = 0; i < n; i++)
    {
        if (i == 0)
            fib = fib_0;
        else if (i == 1)
            fib = fib_1;
        else
        {
            for (j = 2; j <= i; j++)
            {
                fib = fib_1 + fib_0; //Iteration to generate Fib. sequence
                fib_0 = fib_1;
                fib_1 = fib;
            }
            fib_1 = 1;
            fib_0 = 0;               //Clear to the default value
        }
        array[ i ] = fib;
    }
    array[ i ] = -1;                 //Ending value
    pthread_exit(0);
}




