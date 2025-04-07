#ifndef COINGOLD_H
#define COINGOLD_H

#include <Godot.hpp>
#include <Area.hpp>
#include <Math.hpp>
#include <Node.hpp>

namespace godot
{
	class CoinGold : public Area
	{
		GODOT_CLASS(CoinGold, Area)
	private:
		int goldToGive;
		float rotateSpeed;
	public:
		static void _register_methods();
		CoinGold();
		~CoinGold();
		void _init();
		void _process(float);
		void _ready();
		void OnBodyEntered(Node*);
	};
}

#endif
