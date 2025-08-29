#include "/home/codeleaded/System/Static/Library/NeuralNetwork.h"

int main(){
    NeuralNetwork neuralnet = NeuralNetwork_New();
    NeuralNetwork_Free(&neuralnet);
    return 0;
}