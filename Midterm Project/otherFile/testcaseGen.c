//
//  testcaseGen.c
//  
//
//  Created by Alan Lin on 12/11/12.
//
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SIZE 100000
int main(int argc, char *argv[])
{
    FILE *testcase;
    testcase = fopen(argv[1],"w");
    int i;
    srand(time(NULL));
    fprintf(testcase,"%d\n",SIZE);
    i = 0;
    while (i < SIZE) {
        int gen = rand();
        fprintf(testcase,"%d %d\n",i,(gen % 2000) + 800);
        i++;
    }
    return 0;
}