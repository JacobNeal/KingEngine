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

#ifndef KS_AUDIO_TRACK_H
#define KS_AUDIO_TRACK_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Audio.hpp>
#include "ksTransition.h"

////////////////////////////////////////////////////////////
/// \brief Plays an OGG Vorbis (.ogg) audio file and allows
/// transitions between audio files.
///
////////////////////////////////////////////////////////////
class ksAudioTrack
{
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Initializes the audio track to the passed OGG Vorbis
        /// audio file and set to the passed volume.
        ///
        /// \param track_filename  The filename of the audio track.
        /// \param duration        The duration to fade the music out/in.
        /// \param volume          The max volume of the audio track.
        ///
        ////////////////////////////////////////////////////////////
        ksAudioTrack(std::string track_filename, int duration = 30, int max_volume = 30);

        ////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        /// Stop the audio track from playing.
        ///
        ////////////////////////////////////////////////////////////
        ~ksAudioTrack();
        
        ////////////////////////////////////////////////////////////
        /// \brief Mute the audio track.
        ///
        ////////////////////////////////////////////////////////////
        void mute();

        ////////////////////////////////////////////////////////////
        /// \brief Transition the audio to a new track over the
        /// previous duration.
        ///
        /// \param new_track  The new audio track to transition into.
        ///
        ////////////////////////////////////////////////////////////
        void transitionTrack(std::string new_track);

        ////////////////////////////////////////////////////////////
        /// \brief Update the playback of the audio track to create
        /// transition between tracks if transitioning.
        ///
        ////////////////////////////////////////////////////////////
        void update();
        
    private:
        ////////////////////////////////////////////////////////////
        // Member Data
        ////////////////////////////////////////////////////////////
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