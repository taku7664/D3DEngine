#include "pch.h"
#include "Degree.h"

Degree::operator Radian() const
{
    Radian radian{ 3.141592f * angle / 180.f };
    return radian;
}
Degree::operator float() const
{
    return angle;
}
