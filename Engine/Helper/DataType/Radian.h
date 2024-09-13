#pragma once

class Degree;

class Radian
{
private:
    float angle;
public:
    Radian() = default;
    Radian(float _angle) : angle(_angle) {}
    operator Degree() const;
    operator float() const;
    void operator=(const float& _angle) { angle = _angle; }
};