////////////////////////////////////////////////////////////
//
// KingEngine
// The MIT License (MIT)
// Copyright (c) 2016 Beyond Parallel
//
// Permission is hereby granted, free of charge, to any person 
// obtaining a copy of this software and associated documentation 
// files (the "Software"), to deal in the Software without restriction, 
// including without limitation the rights to use, copy, modify, merge, 
// publish, distribute, sublicense, and/or sell copies of the Software, 
// and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be 
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ksAudioTrack.h"

#define MIN_VOLUME 0

////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////
ksAudioTrack::~ksAudioTrack()
{
    m_track.stop();
}

////////////////////////////////////////////////////////////
void ksAudioTrack::mute()
{
    m_track_volume = 0;
    m_track.setVolume((int) m_track_volume);
    m_muted = true;
}

////////////////////////////////////////////////////////////
void ksAudioTrack::transitionTrack(std::string new_track)
{
    m_transition_file = new_track;
    m_track_transition = true;
    m_transition = ksTransition<double>(&m_track_volume, 0, m_duration);
}

////////////////////////////////////////////////////////////
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