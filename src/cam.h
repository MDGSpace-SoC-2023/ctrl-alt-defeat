   // cam.h

#ifndef CAM_H
#define CAM_H

#include <SDL2/SDL.h>
#include "objects.h"
#include "level.hpp"

using namespace std;

int CAMX = 0;
int CAMY = 0;

void process_cam_input(keypress key, Sigma &player){
    switch(key)
    {
        case(KEY_W):
        CAMY-=2;
        break;

        case(KEY_S):
        CAMY+=2;
        break;

        case(KEY_A):
        CAMX-=2;
        break;

        case(KEY_D):
        CAMX+=2;
        break;

        case(KEY_I):
                    cout<<player.rectangle.x<<" "<<player.rectangle.y<<" cam"<<endl;
                    cout<<player.rectangle.x-CAMX<<" "<<player.rectangle.y - CAMY<<" actual"<<endl;
        break;
    }     
}

void reverse_cam_input(keypress key){
    switch(key)
    {
        case(KEY_W):
        CAMY+=2;
        break;

        case(KEY_S):
        CAMY-=2;
        break;

        case(KEY_A):
        CAMX+=2;
        break;

        case(KEY_D):
        CAMX-=2;
        break;
    }  
}

void limit_cam(){
    if(CAMY>960) CAMY = 960;
    else if(CAMY<0) CAMY = 0;
    if(CAMX>1024) CAMX = 1024;
    else if(CAMX<0) CAMX = 0;
    
}
#endif