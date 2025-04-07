#ifndef CAMERA_H
#define CAMERA_H

#include <Godot.hpp>
#include <Spatial.hpp>
#include <InputEvent.hpp>
#include <InputEventMouseMotion.hpp>
#include <Math.hpp>
#include <KinematicBody.hpp>
#include <Input.hpp>
#include <Vector2.hpp>

namespace godot {

    class Camera : public Spatial {
        GODOT_CLASS(Camera, Spatial)

    private:
        float lookSensitivity;
        float minLookAngle;
        float maxLookAngle;
        Vector2 mouseDelta;
        KinematicBody* player;

    public:
        static void _register_methods();

        Camera();
        ~Camera();
        void _init();
        void _ready();

        void _process(float delta);
        void _input(Ref<InputEvent> event);
    };

}

#endif
