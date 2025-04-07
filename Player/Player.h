#ifndef PLAYER_H
#define PLAYER_H

#include <Godot.hpp>
#include <KinematicBody.hpp>
#include <Vector3.hpp>
#include <Spatial.hpp>
#include <RayCast.hpp>
#include <Input.hpp>
#include <SceneTree.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <Node.hpp>
#include <OS.hpp>
#include <AnimationPlayer.hpp>
#include <Control.hpp>
#include <AudioStreamPlayer3D.hpp>

namespace godot
{
	class Player : public KinematicBody
	{
		GODOT_CLASS(Player, KinematicBody)
	private:
		int curHp;
		int maxHp;
		int damage;
		int gold;
		float attackRate;
		int lastAttackTime;
		float moveSpeed;
		float jumpForce;
		float gravity;
		Vector3 vel;
		Spatial* camera;
		RayCast* attackCast;
		AnimationPlayer* swordAnim;
		Control* ui;
		AudioStreamPlayer3D* music;
		AudioStreamPlayer3D* coin;
		AudioStreamPlayer3D* kaSound;
	public:
		Player();
		~Player();
		static void _register_methods();
		void _init();
		void _ready();
		void _process(float);
		void _physics_process(float);
		void give_gold(int);
		void take_damage(int);
		void die();
		void try_attack();
	};
}
#endif
