#include <stddef.h>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] = {
    {0, 0},
    {1, 5}, 
    {2, 10},
    {3, 15}, 
    {4, 20}, 
};

#define train_count (sizeof(train)/sizeof(train[0]))

float rand_float(void)
{
    return (float) rand()/ (float)RAND_MAX;
}

float cost(float w) 
{
    float result = 0.0f;
    for(size_t i = 0; i < train_count; i++){
        float x = train[i][0];
        float y = x*w;
        float d = y - train[i][1];
        result += d*d;
    }
    result /= train_count;
    return result;
}

void demonstrate_gradient_direction() {
    float w1 = 0.5, w2 = 3.5;

    float cost_at_w1 = cost(w1);  
    printf("cost at 0.5 -> %f\n", cost_at_w1);
    // So we subtract negative slope = add to w = move right toward w=2
    printf("slope for w = 0.5 -> %f\n", (cost(w1 + 1e-3) - cost_at_w1) / 1e-3);  

    float cost_at_w2 = cost(w2);      
    printf("cost at 3.5 -> %f\n", cost_at_w1);

    printf("slope for w = 3.5 -> %f\n", (cost(w2 + 1e-3)- cost_at_w2) / 1e-3);  
    // slope2 is POSITIVE because cost increases as w increases
    // So we subtract positive slope = decrease w = move left toward w=2
}

void compare_forward_and_backward_differences() {
    printf("Comparing Forward and Backward Difference Methods\n");
    printf("================================================\n\n");
    
    float w = 1.5;  // A point on our parabola
    float h = 0.001;  // Small step size
    
    // Forward difference: f(x+h) - f(x) / h
    float forward_diff = (cost(w + h) - cost(w)) / h;
    
    // Backward difference: f(x) - f(x-h) / h  
    float backward_diff = (cost(w) - cost(w - h)) / h;
    
    // Central difference (most accurate): f(x+h) - f(x-h) / 2h
    float central_diff = (cost(w + h) - cost(w - h)) / (2 * h);
    
    printf("At w = %.2f:\n", w);
    printf("Forward difference:  %.6f\n", forward_diff);
    printf("Backward difference: %.6f\n", backward_diff);
    printf("Central difference:  %.6f\n", central_diff);
    printf("\nNotice they're all approximately the same!\n");
    printf("They all measure the SAME slope at w = %.2f\n", w);
}

int main(void){
    // srand(time(NULL));
    srand(69);
    // y = x*w;
    float w = rand_float()*10.0f;
    printf("%f\n", w);

    float eps = 1e-3;
    float rate = 1e-3;
    printf("%f\n", cost(w));

    for (size_t i = 0; i < 2100; i++){
        float dcost = (cost(w + eps) - cost(w)) / eps;
        w -= rate*dcost;
        printf("%f\n", cost(w));
    }

    printf("%f\n", w);
    return 0;
}
