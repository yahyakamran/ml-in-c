#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float data[][2] = {
    { 0 , 0 },
    { 1 , 2 },
    { 2 , 4 },
    { 3 , 6 },
    { 4 , 8 },
};

#define DATA_LEN (sizeof(data)/sizeof(data[0]));

float float_rand(){
    return (float) random()/ RAND_MAX;
}

float dcost(float w){
    float cost = 0.0f;
    int n = DATA_LEN;
    for(int i = 0 ; i < n ; ++i){
	float x = data[i][0];
	float y = data[i][1];
	float temp = x*w - y;
    }
    return cost/n;
}
float cost(float w){
    float cost = 0.0f;
    int n = DATA_LEN;
    for(int i = 0 ; i < n ; ++i){
	float x = data[i][0];
	float y = x*w;
	float d = y - data[i][1];
	cost += d*d;
    }
    return cost/n;
}

void dump_data(float w){
    int n = DATA_LEN;
    for(int i = 0 ; i < n ; ++i){
	float x = data[i][0];
	float y = x*w;
	printf("X : %f , Y : %f , OurY : %f\n",x , data[i][1] , y);
    }
}

int main(void){
    srand(time(0));
    float w = float_rand()*10.0f;
    float eps = 1e-3;
    float rate = 1e-3;

    for(int i = 0 ; i < 300 ; ++i){
	float c = cost(w);
	float dw = (cost(w + eps) - c)/eps;
	w -= rate*dw;
	printf("The cost of your model is %f\n",c);
    }

    dump_data(w);

    return 0;
}
