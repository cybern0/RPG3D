#ifndef MUSIC_H
#define MUSIC_H

#include <Godot.hpp>
#include <AudioStreamPlayer3D.hpp>

namespace godot
{
	class Music : public AudioStreamPlayer3D
	{
		GODOT_CLASS(Music, AudioStreamPlayer3D)
		public:
			Music();
			~Music();
			static void _register_methods();
			void _init();
			void _process(float);
	};
}

#endif
