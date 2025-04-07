#include "Camera.h"

using namespace godot;

Camera::Camera(){}
Camera::~Camera(){}

void Camera::_init() {
	lookSensitivity = 15;
	minLookAngle = -20;
	maxLookAngle = 75;
	player = nullptr;
	mouseDelta = Vector2();
}

void Camera::_register_methods() {
    register_method("_ready", &Camera::_ready);
    register_method("_process", &Camera::_process);
    register_method("_input", &Camera::_input);
}

void Camera::_ready() {
   player = Object::cast_to<KinematicBody>(get_parent());
     Input* input = Input::get_singleton();
     input->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
}

void Camera::_process(float delta) {
	Vector3 rot = Vector3(mouseDelta.y ,mouseDelta.x , 0) * lookSensitivity * delta, rotation_deg = get_rotation_degrees(), playerRotDeg = player->get_rotation_degrees();
	rotation_deg.x +=  rot.x;
	rotation_deg.x = Math::clamp(rotation_deg.x ,minLookAngle ,maxLookAngle );
	playerRotDeg.y -= rot.y;
	set_rotation_degrees(rotation_deg);
	player->set_rotation_degrees(playerRotDeg);
	mouseDelta = Vector2();
}

void Camera::_input(Ref<InputEvent> event) {
        if (event->is_class("InputEventMouseMotion")) {
        Ref<InputEventMouseMotion> mouse_motion = event;
        	mouseDelta = mouse_motion->get_relative();
        }
}
