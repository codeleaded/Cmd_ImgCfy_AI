#include "/home/codeleaded/System/Static/Library/NeuralNetwork.h"
#include "/home/codeleaded/System/Static/Library/GSprite.h"
#include "/home/codeleaded/System/Static/Library/String_G.h"

#define SPRITE_PATH         "/home/codeleaded/Data/NN/Digits/"
#define SPRITE_TEST         "testing"
#define SPRITE_TRAINING     "training"
#define SPRITE_COUNT        10

#define NN_LEARNRATE        0.5f

int main(){
    NeuralNetwork nn = NeuralNetwork_Make(
        (NeuralLayerCount[]){ 784,128,10,NeuralLayerCount_End }
    );

    for(int i = 0;i<10;i++){
        for(int j = 0;j<SPRITE_COUNT;j++){
            CStr ntraining_s = CStr_Format("./assets/" SPRITE_TRAINING "/%d/%d.sprg",i,j);
            GSprite sp = GSprite_Load(ntraining_s);
            CStr_Free(&ntraining_s);
            
            NeuralType outs[10];
            memset(outs,0,sizeof(outs));
            outs[i] = 1.0f;

            NeuralNetwork_Training(&nn,sp.img,outs,NN_LEARNRATE);

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