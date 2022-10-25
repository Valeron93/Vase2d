
#include "OrthographicCamera.h"

void OrthographicCamera::recalcucateMatrix() {

    auto transform = Mat4(1.0f);
    transform = glm::translate(transform, mPosition);
    transform = glm::rotate(transform, mRotation, Vec3(0, 0, 1));

    mProjection =
            glm::ortho(-mAspectRatio, mAspectRatio, -1.0f, 1.0f, 0.0f, 100.0f) *
            glm::inverse(transform);
}

OrthographicCamera::OrthographicCamera(int w, int h)
        : mRotation(0),
          mPosition(Vec3(0.0f)),
          mAspectRatio(float(w)/float(h)),
          mProjection()
{
    recalcucateMatrix();
}

void OrthographicCamera::setPosition(const Vec3& position) {
    mPosition = position;
    changed = true;
}

void OrthographicCamera::setRotation(float rotation) {
    mRotation = rotation;
    changed = true;
}

void OrthographicCamera::setWidthAndHeight(int width, int height) {
    mAspectRatio = float(width) / float(height);
    changed = true;
}
