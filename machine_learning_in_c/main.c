#include<stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] = {
    {0, 0},
    {1, 2}, 
    {2, 4},
    {3, 6}, 
    {4, 8}, 
};

#define train_count (sizeof(train)/sizeof(train[0]))

float rand_float(void){
    return (float) rand()/ (float)RAND_MAX;
}

int main(void)
{
    // srand(time(NULL));
    srand(69);
    // y = x*w;
    float w = rand_float()*10.0f;
    printf("Weight is -> %f\n", w);
    for(size_t i = 0; i < train_count; i++){
        float x = train[i][0];
        float y = x*w;
        printf("Actual: %f, Expected: %f\n", y, train[i][1]);
    }
    return 0;
}
