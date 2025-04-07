#include "Music.h"

using namespace godot;

Music::Music(){}
Music::~Music(){}

void Music::_init(){}

void Music::_register_methods()
{
	register_method("_process", &Music::_process);
}

void Music::_process(float delta)
{
	if(!this->is_playing())
		this->play();
}
