#include <Godot.hpp>
#include <KinematicBody.hpp>
#include <Timer.hpp>
#include <Vector3.hpp>
#include <Math.hpp>
#include <AnimationPlayer.hpp>
#include <AudioStreamPlayer3D.hpp>

namespace godot
{
	class Enemy : public KinematicBody
	{
		GODOT_CLASS(Enemy, KinematicBody)
	private:
		int curHp;
		int maxHp;
		int damage;
		float attackDist;
		float attackRate;
		float moveSpeed;
		Vector3 vel;
		Timer* timer;
		KinematicBody* player;
		AnimationPlayer* swordAnim;
		AudioStreamPlayer3D* kaSound;
	public:
		Enemy();
		~Enemy();
		static void _register_methods();
		void _init();
		void _ready();
		void _physics_process(float);
		void OnTimerTimeout();
		void take_damage(int);
		void die();
	};
}
