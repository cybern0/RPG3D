#include "CoinGold.h"

using namespace godot;

CoinGold::CoinGold(){}

void CoinGold::_init()
{
	goldToGive = 1;
	rotateSpeed = 5.0f;
}

void CoinGold::_register_methods()
{
	register_method("_ready", &CoinGold::_ready);
	register_method("_process", &CoinGold::_process);
	register_method("OnBodyEntered", &CoinGold::OnBodyEntered);
}

void CoinGold::_process(float delta)
{
	rotate_y(rotateSpeed * delta);
}

void CoinGold::_ready()
{
	connect("body_entered", this, "OnBodyEntered");
}

void CoinGold::OnBodyEntered(Node* body)
{
	if (body && body->get_name() == "Player")
	{
		body->call("give_gold", goldToGive);
		queue_free();
	}
}

CoinGold::~CoinGold(){}
