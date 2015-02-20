//  Created by Alan Lin on 12/11/10.
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#define SIZE (500000)

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
typedef struct Data{
    int id;
    int rankValue;
} Data;

Data playersData[SIZE];
int i = 0;
long numberOfPlayers;
int quick_sort(Data *array,int low,int high);
void compareID(Data *array,int low,int high);
void *readFunction(void *param);

int main(int argc, char *argv[])
{
    //time_t t1,t2;
    //t1 = time(NULL);
    FILE *inputFile;
    inputFile = fopen ( argv[1], "r" );
    if (!inputFile) {
        printf("Read File Fail...\n");
        exit(1);
    }
    fscanf(inputFile, "%ld", &numberOfPlayers); // numberOfPlayers - 1 is the end of the array
    
    //t1 = time(NULL);
    pthread_t thread1;
    pthread_create(&thread1, NULL, (void *)readFunction, inputFile);
    pthread_join(thread1, NULL);
    
    
    
    
    quick_sort(playersData, 0, numberOfPlayers - 1);
    compareID (playersData, 0, numberOfPlayers - 1);
    
    FILE *outputFile;
    outputFile = fopen(argv[2],"w");
    long k;
    for (k = 0; k < numberOfPlayers; k++) {
        fprintf(outputFile ,"%d %d\n", playersData[k].id, playersData[k].rankValue);
    }
    //t2 = time(NULL);
    //printf("This program reads data for: %f seconds.\n",difftime(t2,t1));
    
    
    return 0;
}

void *readFunction(void *param)
{
    while(i < numberOfPlayers){
        fscanf(param, "%d", &playersData[i].id);
        fscanf(param, "%d", &playersData[i].rankValue);
        i++;
    }
    pthread_exit(0);
    
}
void compareID(Data *array,int low,int high)//  Comparing players' ID with the same rankValue, which can tolerate 100000 the same rankValue
{
    int tempID, times = 10000,i;
    while (times){
        for (tempID = -1,i = low; i <= high; i++) {
            if (array[i].rankValue == array[i + 1].rankValue) {
                if(array[i].id > array[i+1].id){
                    tempID = array[i].id;
                    array[i].id = array[i + 1].id;
                    array[i + 1].id = tempID;
                }
            }
        }
        times--;
    }
}
int quick_sort(Data *array,int low,int high) {
    int pivot_point,pivot_item,i,j;
    Data temp;
    // 指標交界結束排序
    if(high<=low){return 1;}
    
    // 紀錄樞紐值
    pivot_item = array[low].rankValue;
    j=low;
    
    // 尋找比樞紐小的數
    for(i =low+1; i<=high; i++) {
        // 跳過等於或大於的數
        if(array[i].rankValue>=pivot_item){continue;}
        
        j++;
        // 交換 array[i] , array[j]
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    
    // 將樞紐位址移到中間
    pivot_point=j;
    // 交換 array[low] , array[pivot_point]
    temp = array[low];
    array[low] = array[pivot_point];
    array[pivot_point] = temp;
    
    // 遞迴處理左側區段
    quick_sort(array,low,pivot_point-1);
    // 遞迴處理右側區段
    quick_sort(array,pivot_point+1,high);
    
    return 1;
}




