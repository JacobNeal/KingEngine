/********************************************************
* Class:            ksAudioTrack
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksAudioTrack.cpp
********************************************************/

#include "ksAudioTrack.h"

#define MIN_VOLUME 0

/********************************************************
*   ksAudioTrack
*
*   Initializes the audio track to the passed OGG Vorbis
*   audio file and set to the passed volume.
********************************************************/
ksAudioTrack::ksAudioTrack(std::string track_filename, int duration, int volume)
    : m_track_volume(0), m_track_transition(false), m_muted(false),
    m_max_volume(volume), m_transition(&m_track_volume, (double) volume, duration),
    m_duration(duration)
{
    if (!m_track.openFromFile(track_filename))
        throw "ERROR (ksAudioTrack): Couldn't load audio file.";
    
    m_track.setLoop(true);
    m_track.setVolume(m_track_volume);
    m_track.play();
}

/********************************************************
*   ~ksAudioTrack
*
*   Stop the audio upon the destruction of the audio track.
********************************************************/
ksAudioTrack::~ksAudioTrack()
{
    m_track.stop();
}

/********************************************************
*   mute
*
*   Mute the playback of the audio track.
********************************************************/
void ksAudioTrack::mute()
{
    m_track_volume = 0;
    m_track.setVolume((int) m_track_volume);
    m_muted = true;
}

/********************************************************
*   transitionTrack
*
*   Transition to a different audio file.
********************************************************/
void ksAudioTrack::transitionTrack(std::string new_track)
{
    m_transition_file = new_track;
    m_track_transition = true;
    m_transition = ksTransition<double>(&m_track_volume, 0, m_duration);
}

/********************************************************
*   update
*
*   Update the playback of the audio track to create
*   transition between tracks if transitioning.
********************************************************/
void ksAudioTrack::update()
{
    if (m_track_transition && m_transition.isDone())
    {
        if (!m_track.openFromFile(m_transition_file))
            throw "ERROR (ksAudioTrack): Couldn't load audio file.";
            
        m_transition = ksTransition<double>(&m_track_volume, m_max_volume, m_duration / 2);
        
        m_track.play();
        m_track_transition = false;
    }
    
    m_track.setVolume((int) m_track_volume);
    m_transition.update();
}