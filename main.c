#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#define THREAD_COUNT 16
#define ARR_SIZE 10

int sorted[ARR_SIZE] = {0, 15, 25, 27, 28, 30, 32, 34, 35, 37};
int sortedDec[ARR_SIZE] = {30, 28, 25, 23, 21, 15, 13, 12, 11, 8};
int unsorted[ARR_SIZE] = {0, 27, 2, 5, 54, 1, 7, 3, 24, 22};

bool isSorted[THREAD_COUNT];

void *checkSorted(void *arg);
void *checkSortedDec(void *arg);

bool checkDecreasing(int a[]);

int main()
{
    pthread_t th[THREAD_COUNT];
    
    for(int i=0; i<THREAD_COUNT; i++){
        isSorted[i] = true;
    }
    
    if(checkDecreasing(sorted) == false){
        printf("array is increasing\n");
        for(long i=0; i<THREAD_COUNT; i++){
            int created = pthread_create(&th[i], NULL, checkSorted, (void*)i);
        }
    }else{
        printf("array is decreasing\n");
        for(long i=0; i<THREAD_COUNT; i++){
            int created = pthread_create(&th[i], NULL, checkSortedDec, (void*)i);
        }
    }
    
       
    for(long i=0; i<THREAD_COUNT; i++){
        pthread_join(th[i], NULL);
    }
    
    bool flag = true;
    
    for(int i=0; i<THREAD_COUNT; i++){
        if(isSorted[i] == false){
            flag = false;
            break;
        }
        
    }
    
    if(flag == true){
        printf("Array sorted!");
    }else{
        printf("Array is not sorted!");
    }
    
    
    

    return 0;
}

void *checkSorted(void *arg){
    long myRank = (long) arg;
    int startPoint = myRank * ARR_SIZE / THREAD_COUNT;
    int endPoint = (myRank+1) * ARR_SIZE / THREAD_COUNT;
    
    for(int i=startPoint; i<endPoint; i++){
        if(sorted[i] < sorted[i-1]){
            isSorted[myRank] = false;
            break;
        }
    }
    
}

void *checkSortedDec(void *arg){
    long myRank = (long) arg;
    int startPoint = myRank * ARR_SIZE / THREAD_COUNT;
    int endPoint = (myRank+1) * ARR_SIZE / THREAD_COUNT;
    
    for(int i=startPoint; i<endPoint; i++){
        if(sorted[i+1] > sorted[i]){
            isSorted[myRank] = false;
            printf("rank : %ld",myRank);
            break;
        }
    }
    
}

bool checkDecreasing(int a[]){
    if(a[0] < a[1]){
        return false;
        
    }else{
        return true;
    }
}
