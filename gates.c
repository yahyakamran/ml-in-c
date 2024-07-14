#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <stdio.h>

typedef float sample[3];

//The gates that can be trained by Perceptron

sample or_data[] = {
    {1 , 1 , 1},
    {1 , 0 , 1},
    {0 , 1 , 1},
    {0 , 0 , 0},
};

sample and_data[] = {
    {1 , 1 , 1},
    {1 , 0 , 0},
    {0 , 1 , 0},
    {0 , 0 , 0},
};

sample nor_data[] = {
    {1 , 1 , 0},
    {1 , 0 , 0},
    {0 , 1 , 0},
    {0 , 0 , 1},
};

int n = 4;
sample *data = nor_data;

float sigmodf(float x){
    return 1/(1.0f + expf(-x));
}

float cost(float w1 , float w2 , float b){
    float cost = 0.0f;
    for(int i = 0 ; i < n ; ++i){
	float x1 = data[i][0];
	float x2 = data[i][1];
	float y = sigmodf(x1*w1 + x2*w2 + b);
	float d = y - data[i][2];
	cost += d*d;
    }
    return cost/n;
}

float float_rand(){
    return (float) random()/ RAND_MAX;
}

int main(void){
    srand(69);
    float w1 = float_rand();
    float w2 = float_rand();
    float eps = 1e-3;
    float rate = 1e-1;
    float b = float_rand();


    for(int i = 0 ; i < 1000 * 1000 ; ++i){
	float c = cost(w1 , w2 , b);
	float dw1 = (cost(w1 + eps , w2 , b) - c)/eps;
	float dw2 = (cost(w1 , w2 + eps , b) - c)/eps;
	float db = (cost(w1 , w2 , b + eps) - c)/eps;

	printf("The cost is %f\n", c);
	//printf("w1(%f/%f), w2(%f/%f), b(%f/%f)\n",
	//    w1,dw1,w2,dw2,b,db);

	w1 -= rate*dw1;
	w2 -= rate*dw2;
	b  -= rate*db;
    }

    for(int i = 0 ; i < n ; ++i){
	float x1 = data[i][0];
	float x2 = data[i][1];
	float y = sigmodf(x1*w1 + x2*w2 + b);
	printf("%f && %f = %f(%f)\n", x1 , x2 , data[i][2], y);
    }
    return 0;
}
