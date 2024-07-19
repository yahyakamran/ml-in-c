#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    float n1w1;
    float n1w2;
    float n1b;

    float n2w1;
    float n2w2;
    float n2b;

    float n3w1;
    float n3w2;
    float n3b;

}Model;

typedef float sample[3];

sample xor_data[] = {
    { 0 , 0 , 0 },
    { 0 , 1 , 1 },
    { 1 , 0 , 1 },
    { 1 , 1 , 0 },
};

sample nor_data[] = {
    { 0 , 0 , 1 },
    { 0 , 1 , 0 },
    { 1 , 0 , 0 },
    { 1 , 1 , 0 },
};

int n = 4;
sample *data = nor_data;

float sigmodf(float x){
    return 1/(1.0f + expf(-x));
}

float float_rand(){
    return (float) random()/ RAND_MAX;
}

float forward(Model m , float x1 , float x2){
    float a = sigmodf(x1*m.n1w1 + x2*m.n1w2 + m.n1b);
    float b = sigmodf(x1*m.n2w1 + x2*m.n2w2 + m.n2b);
    float y = sigmodf(a*m.n3w1 + b*m.n3w2 + m.n3b);
    return y;
}

float cost(Model m){
    float cost = 0.0f;
    for(int i = 0 ; i < n ; ++i){
	float x1 = data[i][0];
	float x2 = data[i][1];
	float y = forward(m , x1 , x2);
	float d = y - data[i][2];
	cost += d*d;
    }
    return cost/n;
}

Model finite_distance(Model m){
    Model g;
    float c = cost(m);
    float eps = 1e-1;
    float saved;

    saved = m.n1w1;
    m.n1w1 += eps;
    g.n1w1 = (cost(m) - c)/eps;
    m.n1w1 = saved;

    saved = m.n1w2;
    m.n1w2 += eps;
    g.n1w2 = (cost(m) - c)/eps;
    m.n1w2 = saved;

    saved = m.n1b;
    m.n1b += eps;
    g.n1b = (cost(m) - c)/eps;
    m.n1b = saved;

    saved = m.n2w1;
    m.n2w1 += eps;
    g.n2w1 = (cost(m) - c)/eps;
    m.n2w1 = saved;

    saved = m.n2w2;
    m.n2w2 += eps;
    g.n2w2 = (cost(m) - c)/eps;
    m.n2w2 = saved;

    saved = m.n2b;
    m.n2b += eps;
    g.n2b = (cost(m) - c)/eps;
    m.n2b = saved;

    saved = m.n3w1;
    m.n3w1 += eps;
    g.n3w1 = (cost(m) - c)/eps;
    m.n3w1 = saved;

    saved = m.n3w2;
    m.n3w2 += eps;
    g.n3w2 = (cost(m) - c)/eps;
    m.n3w2 = saved;

    saved = m.n3b;
    m.n3b += eps;
    g.n3b = (cost(m) - c)/eps;
    m.n3b = saved;

    return g;
}

Model train(Model m , Model g , float rate){

    m.n1w1 -= rate*g.n1w1;
    m.n1w2 -= rate*g.n1w2;
    m.n1b -= rate*g.n1b;

    m.n2w1 -= rate*g.n2w1;
    m.n2w2 -= rate*g.n2w2;
    m.n2b -= rate*g.n2b;

    m.n3w1 -= rate*g.n3w1;
    m.n3w2 -= rate*g.n3w2;
    m.n3b -= rate*g.n3b;

    return m;
}

Model random_model(){
    Model m;

    m.n1w1 = float_rand();
    m.n1w2 = float_rand();
    m.n1b = float_rand();

    m.n2w1 = float_rand();
    m.n2w2 = float_rand();
    m.n2b = float_rand();

    m.n3w1 = float_rand();
    m.n3w2 = float_rand();
    m.n3b = float_rand();

    return m;
}

void print_model(Model m){
    printf("n1w1 = %f\n",m.n1w1);
    printf("n1w2 = %f\n",m.n1w2);
    printf("n1b = %f\n",m.n1b);

    printf("n1w1 = %f\n",m.n1w1);
    printf("n1w2 = %f\n",m.n1w2);
    printf("n1b = %f\n",m.n1b);

    printf("n3w1 = %f\n",m.n3w1);
    printf("n3w2 = %f\n",m.n3w2);
    printf("n3b = %f\n",m.n3b);
}

int main(void){
    srand(69);
    Model m = random_model();
    float rate = 1e-1;

    for(int i = 0 ; i < 1000 * 1000 ; ++i){
	printf("Cost = %f\n",cost(m));
    	Model g = finite_distance(m);
    	m = train( m , g , rate);
    }

    for(int i = 0 ; i < 2 ; ++i ){
	for(int j = 0 ; j < 2 ; ++j ){
	    printf("%d , %d = %f\n", i , j , forward(m, i , j));
	}
    }

    return 0;
}
