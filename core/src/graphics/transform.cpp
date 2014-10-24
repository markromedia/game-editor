#include "graphics/transform.hpp"

glm::vec3 graphics::Transform::UNIT_X = glm::vec3(1,0,0);
glm::vec3 graphics::Transform::UNIT_Y = glm::vec3(0,1,0);
glm::vec3 graphics::Transform::UNIT_Z = glm::vec3(0,0,1);

graphics::Transform::Transform() : _dirty_bits(kTransformDirty | kRotationDirty | kScaleDirty | kTranslationDirty),
                                   _translation(glm::vec3(0.0f, 0.0f, 0.0f)),
                                   _scale(glm::vec3(1.0f,1.0f,1.0f)),
                                   _x_rot(0), _y_rot(0), _z_rot(0),
                                   _orientation(glm::quat(glm::vec3(0.0f,0.0f,0.0f)))
{
}

glm::mat4 graphics::Transform::getMatrix() {
    if (_dirty_bits & kTransformDirty) {
        if (_dirty_bits & kTranslationDirty) {
            _translation_matrix = glm::translate(glm::mat4(1.0f), _translation);
        }

        if (_dirty_bits & kRotationDirty) {
            _orientation = _orientation * glm::angleAxis(glm::radians(_x_rot), UNIT_X);
            _orientation = _orientation * glm::angleAxis(glm::radians(_y_rot), UNIT_Y);
            _orientation = _orientation * glm::angleAxis(glm::radians(_z_rot), UNIT_Z);
        }

        if (_dirty_bits & kScaleDirty) {
            _scale_matrix = glm::scale(glm::mat4(1.0f), _scale);
        }

        _transform = _translation_matrix * glm::mat4_cast(_orientation) * _scale_matrix;
        _dirty_bits = 0;
    }

    return _transform;
}

void graphics::Transform::translate(float x, float y, float z) {
    if (x != _translation.x || y != _translation.y || z != _translation.z) {
        _translation.x = x;
        _translation.y = y;
        _translation.z = z;
        _dirty_bits |= (kTransformDirty | kTranslationDirty);
    }
}

void graphics::Transform::rotate(float x_rot, float y_rot, float z_rot) {
    if (x_rot != _x_rot || y_rot != _y_rot || z_rot != _z_rot) {
        _x_rot = x_rot;
        _y_rot = y_rot;
        _z_rot = z_rot;
        _dirty_bits |= (kTransformDirty | kRotationDirty);
    }
}

void graphics::Transform::scale(float scale_x, float scale_y, float scale_z) {
    if (scale_x != _scale.x || scale_y != _scale.y  || scale_z != _scale.z) {
        _scale.x = scale_x;
        _scale.y = scale_y;
        _scale.z = scale_z;
        _dirty_bits |= (kTransformDirty | kScaleDirty);
    }
}

void graphics::Transform::uniform_scale(float scale) {
    this->scale(scale, scale, scale);
}
