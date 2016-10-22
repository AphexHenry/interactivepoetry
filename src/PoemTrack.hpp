//
//  PoemTrack.hpp
//  InteractivePoetry
//
//  Created by Baptiste Bohelay on 09/10/2016.
//
//

#ifndef PoemTrack_hpp
#define PoemTrack_hpp

#include <stdio.h>
#include "cinder/app/App.h"

#include "FMOD.hpp"

class PoemTrack
{
public:
    PoemTrack(int aIndexPoem, int aIndexTrack, FMOD::System	*aSystem);
    bool isFinished();
    void play();
    void pause();
    void setPositionIndex(int aIndex);    
    
private:
    
    void parseCSV(std::string aPath);
    
    int mIndex;
    
    FMOD::System * mSystem;
    FMOD::Channel	*mChannel;
    FMOD::Sound    	*mSound;
    std::vector<float> mMarkers;
};

#endif /* PoemTrack_hpp */
