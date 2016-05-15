/********************************************************
* Class:            ksAudioTrack
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksAudioTrack.h
*
*   Overview:
*       Plays an OGG Vorbis (.ogg) audio file and allows
*       transitions between audio files.
*
********************************************************/

#ifndef KS_AUDIO_TRACK_H
#define KS_AUDIO_TRACK_H

#include <SFML/Audio.hpp>
#include "ksTransition.h"

class ksAudioTrack
{
    public:
        //                         Member functions
        ksAudioTrack(std::string track_filename, int duration = 30, int max_volume = 30);
        ~ksAudioTrack();
        
        //                         Methods
        void                       mute();
        void                       transitionTrack(std::string new_track);
        void                       update();
        
    private:
        //                         Members
        sf::Music                  m_track;
        std::string                m_transition_file;
        double                     m_track_volume;
        bool                       m_track_transition;
        bool                       m_muted;
        double                     m_max_volume;
        ksTransition<double>       m_transition;
        int                        m_duration;
};

#endif