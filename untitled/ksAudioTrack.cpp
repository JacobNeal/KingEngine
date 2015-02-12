#include "ksAudioTrack.h"

#define MIN_VOLUME 0 
#define MAX_VOLUME 30

ksAudioTrack::ksAudioTrack( std::string track_filename )
	: m_track_transition( false ), m_track_volume( MAX_VOLUME )
{
	if ( ! m_track.openFromFile( track_filename ) )
		throw "ERROR (ksAudioTrack): Couldn't load track";

	m_track.setLoop( true );
	m_track.play();
}

ksAudioTrack::~ksAudioTrack()
{
	m_track.stop();
}

void ksAudioTrack::transitionTrack( std::string new_track )
{
	m_transition_file = new_track;
	m_track_transition = true;
}

void ksAudioTrack::update()
{
	if ( m_track_transition )
	{
		if ( m_track_volume > MIN_VOLUME )
		{
			m_track_volume--;
			m_track.setVolume( m_track_volume );
		}
		else
		{
			m_track.stop();

			if ( ! m_track.openFromFile( m_transition_file ) )
				throw "ERROR (ksAudioTrack): Couldn't load transition track";

			m_track.play();
			m_track_transition = false;
		}
	}
	else
	{
		if ( m_track_volume < MAX_VOLUME )
		{
			m_track_volume++;
			m_track.setVolume( m_track_volume );
		}
	}
}