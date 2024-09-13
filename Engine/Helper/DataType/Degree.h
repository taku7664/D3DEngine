#pragma once

class Radian;

class Degree
{
private:
    float angle = 0.f;
public:
    Degree() = default;
    Degree(float _angle) : angle(_angle) {}
    operator Radian() const;
    operator float() const;
    void operator=(const float& _angle) { angle = _angle; }
};