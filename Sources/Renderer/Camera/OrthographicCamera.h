#pragma once

#include <Core/Mathematics.h>

class OrthographicCamera {
private:
    Vec3 mPosition;
    Mat4 mProjection;
    float mRotation;
    float mAspectRatio;

    bool changed = false;

public:
    explicit OrthographicCamera(int w, int h);

    inline const Mat4& getProjectionMatrix() {

        if (!changed) {
            return mProjection;
        }

        changed = false;
        recalcucateMatrix();
        return mProjection;
    };

    void setPosition(const Vec3& position);
    void setRotation(float rotation);
    void setWidthAndHeight(int width, int height);


private:
    void recalcucateMatrix();




};
