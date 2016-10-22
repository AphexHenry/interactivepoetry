//
//  SyphonSender.hpp
//  ThreeSixtyInteractive
//
//  Created by Baptiste Bohelay on 25/08/2016.
//
//

#ifndef SyphonSender_hpp
#define SyphonSender_hpp

#include <stdio.h>
#include "Syphon.h"
#include "cinder/app/App.h"

class SyphonSender
{
public:
    SyphonSender();
    ~SyphonSender(){};

    void SendScreen();
    
    void bind(int aIndex);
    void unbind();
    
private:
    int mServerIndex;
    reza::syphon::Server mServer[4];
};

#endif /* SyphonSender_hpp */
