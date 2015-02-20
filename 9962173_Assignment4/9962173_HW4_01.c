//  Created by Alan Lin on 12/10/20.
#include <pthread.h>
#include <stdio.h>

void *runner(void *param);                            //The thread!
int IsPrime(int);

int main(int argc, char *argv[])
{    
    int chkValue = atoi(argv[1]);
    if (chkValue >= 1) {                              //Argument checking
        pthread_t tid;                                //Create a thread
        pthread_attr_t attr;    
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, runner, argv[1]); //Arg3 must be void*
        pthread_join(tid, NULL);
    }    
    return 0;
}

void *runner(void *param)
{
    int k, upperBound = atoi(param);
    for (k = 2; k <= upperBound; k++)
    {
        if (IsPrime(k))
            printf("%d ", k);        
        else
            continue;        
    }
    printf("\n");
    pthread_exit(0);
}

int IsPrime(int number)
{
    int i;
    for (i = 2; i*i <= number; i++)
        if (number % i == 0)
            return 0;    
    return 1;
}
