#include "Enemy.h"

using namespace godot;

Enemy::Enemy(){}

void Enemy::_init()
{
	curHp = 3;
	maxHp = 3;
	damage = 1;
	attackDist = 1.5f;
	attackRate = 1.0f;
	moveSpeed = 2.0f;
	vel = Vector3();
	swordAnim = nullptr;
	timer = nullptr;
	player = nullptr;
	kaSound = nullptr;
}

void Enemy::_register_methods()
{
	register_method("_ready", &Enemy::_ready);
	register_method("_physics_process", &Enemy::_physics_process);
	register_method("OnTimerTimeout", &Enemy::OnTimerTimeout);
	register_method("take_damage", &Enemy::take_damage);
	register_method("die", &Enemy::die);
}

void Enemy::_ready()
{
	swordAnim = Object::cast_to<AnimationPlayer>(get_node("weaponHolder/SwordAnimator"));
	timer = Object::cast_to<Timer>(get_node("Timer"));
	player = Object::cast_to<KinematicBody>(get_node("/root/MainScene/Player"));
	kaSound = Object::cast_to<AudioStreamPlayer3D>(get_node("katana"));
	timer->connect("timeout", this, "OnTimerTimeout");
	timer->set_wait_time(attackRate);
	timer->start();
}

void Enemy::_physics_process(float delta)
{
	Vector3 pos = get_translation();
	float dist = pos.distance_to(player->get_translation());
	if (dist > attackDist)
	{
		Vector3 dir = (player->get_translation() - pos).normalized();
		float angle_to_player = Math::atan2(dir.x, dir.z);
		set_rotation(Vector3(0, angle_to_player, 0));
		vel.x = dir.x * moveSpeed;
		vel.y = 0;
		vel.z = dir.z * moveSpeed;
		vel = move_and_slide(vel, Vector3(0,1,0));
	}

}

void Enemy::take_damage(int damageToTake)
{
	curHp -= damageToTake;
	if (curHp <= 0)
		die();
}

void Enemy::die()
{
	queue_free();
}

void Enemy::OnTimerTimeout()
{
	Vector3 pos = get_translation();
	if (pos.distance_to(player->get_translation()) <= attackDist + 0.5f)
	{
		player->call("take_damage", damage);
		kaSound->play();
		swordAnim->stop();
		swordAnim->play("attack");
	}
}

Enemy::~Enemy(){}
