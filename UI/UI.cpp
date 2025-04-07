#include "UI.h"

using namespace godot;

UI::UI(){}

void UI::_init(){}

void UI::_register_methods()
{
	register_method("_ready", &UI::_ready);
	register_method("update_health_bar", &UI::update_health_bar);
	register_method("update_gold_text", &UI::update_gold_text);
}

void UI::update_health_bar(int curHp, int maxHp)
{
	healthBar->set_value((100 * curHp) / maxHp); 
}

void UI::update_gold_text(int gold)
{
	goldText->set_text("Gold : " + String::num(gold));
}

void UI::_ready()
{
	healthBar = Object::cast_to<TextureProgress>(get_node("HealthBar"));
	goldText = Object::cast_to<Label>(get_node("GoldText"));
	goldText->set_text("Gold : " + String::num(0));
	healthBar->set_value(100); 
}

UI::~UI(){}
