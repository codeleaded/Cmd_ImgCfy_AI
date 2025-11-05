#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
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
    NeuralNetwork nn = NeuralNetwork_Make(
        (NeuralLayerBuilder[]){ 
            NeuralLayerBuilder_Make(784,"relu"),
            NeuralLayerBuilder_Make(128,"relu"),
            NeuralLayerBuilder_Make(10,"softmax"),
            NeuralLayerBuilder_End()
        }
    );

    for(int i = 0;i<10;i++){
        for(int j = 0;j<SPRITE_COUNT;j++){
            CStr ntraining_s = CStr_Format("./assets/" SPRITE_TRAINING "/%d/%d.sprg",i,j);
            GSprite sp = GSprite_Load(ntraining_s);
            CStr_Free(&ntraining_s);
            
            NeuralType outs[10];
            memset(outs,0,sizeof(outs));
            outs[i] = 1.0f;

            NeuralDataMap ndm = NeuralDataMap_Make_GSprite(DATA_PATH SPRITE_TRAINING);
            NeuralNetwork_Learn(&nn,&ndm,NN_LEARNRATE);
            NeuralDataMap_Free(&ndm);

            ndm = NeuralDataMap_Make_GSprite(DATA_PATH SPRITE_TEST);
            NeuralType loss = NeuralNetwork_Test_C(&nn,&ndm);
            NeuralDataMap_Free(&ndm);

            GSprite_Free(&sp);
        }
    }
    for(int i = 0;i<10;i++){
        for(int j = 0;j<SPRITE_COUNT;j++){
            CStr ntraining_s = CStr_Format("./assets/" SPRITE_TEST "/%d/%d.sprg",i,j);
            GSprite sp = GSprite_Load(ntraining_s);
            CStr_Free(&ntraining_s);

            NeuralNetwork_Test(&nn,sp.img);
            NeuralLayer* lastnl = (NeuralLayer*)Vector_Get(&nn.layers,nn.layers.size - 1);
            NeuralLayer_Print_G(lastnl);

            int d = NeuralNetwork_Decision(&nn);
            printf("%c -> Guess: %d | Correct: %d\n",(d == i ? '!' : 'X'),d,i);

            GSprite_Free(&sp);
        }
    }

    //NeuralNetwork_Print_G(&nn);

    NeuralNetwork_Free(&nn);
    return 0;
}