//
//  PoemTrack.cpp
//  InteractivePoetry
//
//  Created by Baptiste Bohelay on 09/10/2016.
//
//

#include "PoemTrack.hpp"
#include "cinder/Utilities.h"


using namespace ci;
using namespace std;
using namespace FMOD;

PoemTrack::PoemTrack(int aIndexPoem, int aIndexTrack, FMOD::System	*aSystem)
{
    string lNameFiles = "P" + std::to_string(aIndexPoem) + "E" + std::to_string(aIndexTrack);
    std::string lTrackName = lNameFiles + ".wav";
    std::string lCSVName = lNameFiles + ".csv";
    aSystem->createSound( app::getAssetPath(lTrackName ).string().c_str(), FMOD_SOFTWARE, NULL, &mSound );
    mSound->setMode( FMOD_LOOP_NORMAL );
    parseCSV(app::getAssetPath(lCSVName).string().c_str());
    aSystem->playSound( FMOD_CHANNEL_FREE, mSound, false, &mChannel );
    mSystem = aSystem;
    mIndex = 0;
}

void PoemTrack::parseCSV(std::string aPath)
{
    //LOAD JOINT DATA FROM CSV
    vector< string > entries = split( loadString( loadFile( aPath ) ), "\r\n" );
    
    for (int i = 0; i < entries.size(); i++)
    {
        vector< string > values = split( entries[i] , "," );
        if(!values[0].length())
        {
            continue;
        }
        string indexStr = values[0].substr(1,values[0].length() - 1);
        if(!indexStr.length())
        {
            continue;
        }
        
        // we take the last value.
        string timeStr = values[values.size() - 1];
        vector< string > timeStrVec = split( timeStr , "." );
        
        float add1 = (std::stof(timeStrVec[0]) - 1.f) * 2.f;
        float add2 = (std::stof(timeStrVec[1]) - 1.f + std::stof(timeStrVec[2]) * 0.01f) * 0.5f;
        
        float lSeconds = add1 + add2;
        mMarkers.push_back(lSeconds);
    }
}

bool PoemTrack::isFinished()
{
    unsigned int lPos = 0;
    mChannel->getPosition(&lPos, FMOD_TIMEUNIT_MS);
    if(mIndex < mMarkers.size() - 1)
    {
        return lPos >= int(mMarkers[mIndex + 1] * 1000.f);
    }
    else
    {
        bool lIsPlaying = false;
        mChannel->isPlaying(&lIsPlaying);
        return lIsPlaying;
    }
}

void PoemTrack::play()
{
    mChannel->setPaused(false);
}

void PoemTrack::pause()
{
    mChannel->setPaused(true);
}

void PoemTrack::setPositionIndex(int aIndex)
{
    mIndex = aIndex;
    mChannel->setPosition((unsigned int)floor(mMarkers[mIndex] * 1000.f), FMOD_TIMEUNIT_MS);
}

FMOD_RESULT fModCallback(FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACKTYPE type, void *commanddata1, void *commanddata2)
{
//    if (type == FMOD_CHANNEL_CALLBACKTYPE_END)
//    {
//        FMOD::Channel *channel = (FMOD::Channel *)chanControl;
//        // Channel specific functions here...
//    }
//    else
//    {
//        FMOD::ChannelGroup *group = (FMOD::ChannelGroup *)chanControl;
//        // ChannelGroup specific functions here...
//    }
    
    // ChannelControl generic functions here...
    
    return FMOD_OK;
}