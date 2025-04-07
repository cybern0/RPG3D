#ifndef UI_H
#define UI_H

#include <Godot.hpp>
#include <Control.hpp>
#include <TextureProgress.hpp>
#include <Label.hpp>

namespace godot
{
	class UI : public Control
	{
		GODOT_CLASS(UI, Control)
	private:
		TextureProgress* healthBar;
		Label* goldText;
	public:
		UI();
		~UI();
		static void _register_methods();
		void update_health_bar(int, int);
		void update_gold_text(int);
		void _ready();
		void _init();
	};
}

#endif
