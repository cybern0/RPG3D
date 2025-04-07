#include "Player.h"

using namespace godot;

Player::Player(){}

void Player::_register_methods()
{
	register_method("_ready", &Player::_ready);
	register_method("_physics_process", &Player::_physics_process);
	register_method("give_gold", &Player::give_gold);
	register_method("take_damage", &Player::take_damage);
	register_method("die", &Player::die);
	register_method("_process", &Player::_process);
	register_method("try_attack", &Player::try_attack);
}
void Player::_init()
{
	curHp = 10;
	maxHp = 10;
	damage = 1;
	gold = 0;
	attackRate = 0.3f;
	lastAttackTime = 0;
	moveSpeed = 5.0f;
	jumpForce = 10.0f;
	gravity = 15.0f;
	vel = Vector3();
	camera = nullptr;
	attackCast = nullptr;
	swordAnim = nullptr;
	ui = nullptr;
	music = nullptr;
	coin = nullptr;
	kaSound = nullptr;
}

void Player::_ready()
{
	camera = Object::cast_to<Spatial>(get_node("cameraOrbit"));
	attackCast = Object::cast_to<RayCast>(get_node("attackRayCast"));
	swordAnim = Object::cast_to<AnimationPlayer>(get_node("weaponHolder/SwordAnimator"));
	ui = Object::cast_to<Control>(get_node("/root/MainScene/CanvasLayer/UI"));
	music = Object::cast_to<AudioStreamPlayer3D>(get_node("Music"));
	coin = Object::cast_to<AudioStreamPlayer3D>(get_node("Coin"));
	kaSound = Object::cast_to<AudioStreamPlayer3D>(get_node("katana"));
}

void Player::_process(float delta)
{
	if (Input::get_singleton()->is_action_pressed("ui_accept"))
	{
		kaSound->play();
		try_attack();
	}
}

void Player::_physics_process(float delta)
{
	vel.x = 0;
	vel.z = 0;
	Vector3 rotation = get_rotation();
	Input* input = Input::get_singleton();
	if (input->is_action_pressed("ui_up"))
	{
		vel.x += Math::sin(rotation.y) * moveSpeed;
		vel.z += Math::cos(rotation.y) * moveSpeed;
	}
	if (input->is_action_pressed("ui_down"))
	{
		vel.x -= Math::sin(rotation.y) * moveSpeed;
		vel.z -= Math::cos(rotation.y) * moveSpeed;
	}
	vel.y -= gravity * delta;
	if (input->is_action_pressed("ui_page_up") && is_on_floor())
	{
		vel.y = jumpForce;
		music->play();
	}
	vel = move_and_slide(vel, Vector3(0,1,0));
}

void Player::try_attack()
{
	uint64_t ticks = OS::get_singleton()->get_ticks_msec();
	if (ticks - lastAttackTime < attackRate * 1000)
		return;
	lastAttackTime = ticks;
	swordAnim->stop();
	swordAnim->play("attack");
	if (attackCast->is_colliding())
	{
		Object* collider = attackCast->get_collider();
		if (collider && collider->has_method("take_damage"))
		        collider->call("take_damage", damage);
	}
}

void Player::take_damage(int damageToTake)
{
	curHp -= damageToTake;
	ui->call("update_health_bar", curHp, maxHp);
	if (curHp <= 0)
		die();
}

void Player::die()
{
	SceneTree *tree = get_tree();
	Node *current_scene = tree->get_current_scene();
	String scene_path = current_scene->get_filename();
	Ref<PackedScene> scene_resource = ResourceLoader::get_singleton()->load(scene_path);
	tree->change_scene_to(scene_resource);
}

void Player::give_gold(int amount)
{
	coin->play();
	gold += amount;
	ui->call("update_gold_text", gold);
}

Player::~Player(){}
