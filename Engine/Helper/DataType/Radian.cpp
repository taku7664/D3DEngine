#include "pch.h"
#include "Radian.h"

Radian::operator Degree() const
{
    Degree degree = Degree(180.f * angle / 3.141592f);
    return degree;
}
Radian::operator float() const
{
    return angle;
}
