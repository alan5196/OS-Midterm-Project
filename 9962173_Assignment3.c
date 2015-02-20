#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
    
    int fib_0 = 0, fib_1 = 1, i, j, fib, n;
    pid_t pid;    
    pid = fork();    
    if(pid == 0)
    {        
        n = atoi(argv[1]);
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
        printf("%d ", fib);
     }
        printf("\n");
    }
    else if(pid < 0)
    {
         printf("Error!!!"); 
         return 1;    
    }
    else
    {
         wait(NULL);
    }
    return 0;
}


