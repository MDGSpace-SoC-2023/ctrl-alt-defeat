   // cam.h

#ifndef CAM_H
#define CAM_H

#include <SDL2/SDL.h>
#include "objects.h"

using namespace std;

int CAM = 0;

void process_cam_input(keypress key){
    switch(key)
    {
        case(KEY_W):
        CAM+=12;
        break;

        case(KEY_S):
        CAM-=12;
        break;
    }     
}

void limit_cam(){
    if(CAM>2160) CAM = 2160;
    else if(CAM<0) CAM = 0;
}
#endif