#ifndef KS_AUDIO_TRACK_H
#define KS_AUDIO_TRACK_H

#include <SFML/Audio.hpp>

class ksAudioTrack
{
	public:
		ksAudioTrack( std::string track_filename );
		~ksAudioTrack();

		void transitionTrack( std::string new_track );
		void update();

	private:
		sf::Music m_track;
		std::string m_transition_file;

		int m_track_volume;
		bool m_track_transition;
};

#endif