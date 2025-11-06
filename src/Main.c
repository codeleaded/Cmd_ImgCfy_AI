#include "/home/codeleaded/System/Static/Library/GSprite.h"
#include "/home/codeleaded/System/Static/Library/NeuralNetwork.h"

#define SPRITE_PATH         "/home/codeleaded/Data/NN/Digits/"
#define DATA_PATH           "/home/codeleaded/Data/NN/DigitsGray/"
#define SPRITE_TEST         "testing"
#define SPRITE_TRAINING     "training"
#define SPRITE_COUNT        4
#define SPRITE_MAX          300

#define NN_PATH             "./data/Model.nnalx"
#define NN_COUNT            10
#define NN_LEARNRATE        0.1f

int main(){
    int epoch = 0;
    NeuralNetwork nn = NeuralNetwork_Make(
        (NeuralLayerBuilder[]){ 
            NeuralLayerBuilder_Make(784,"relu"),
            NeuralLayerBuilder_Make(128,"relu"),
            NeuralLayerBuilder_Make(10,"softmax"),
            NeuralLayerBuilder_End()
        }
    );

    NeuralDataMap ndm = NeuralDataMap_Make_GSprite(DATA_PATH SPRITE_TRAINING,&epoch,SPRITE_COUNT,SPRITE_MAX);
    NeuralNetwork_Learn(&nn,&ndm,NN_LEARNRATE);
    NeuralDataMap_Free(&ndm);

    ndm = NeuralDataMap_Make_GSprite(DATA_PATH SPRITE_TEST,&epoch,SPRITE_COUNT,SPRITE_MAX);
    NeuralType loss = NeuralNetwork_Test_C(&nn,&ndm);
    NeuralDataMap_Free(&ndm);

    printf("Loss: %f\n",loss);

    //NeuralNetwork_Print_G(&nn);

    NeuralNetwork_Free(&nn);
    return 0;
}