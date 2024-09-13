#pragma once

class Vector2 : public DirectX::SimpleMath::Vector2 
{
public:
	Vector2() : DirectX::SimpleMath::Vector2() {}
	Vector2(float x, float y) 
		: DirectX::SimpleMath::Vector2(x, y) {}
};
class Vector3 : public DirectX::SimpleMath::Vector3 
{
public:
	Vector3() : DirectX::SimpleMath::Vector3() {}
	Vector3(float x, float y, float z)
		: DirectX::SimpleMath::Vector3(x, y, z) {}
};
class Vector4 : public DirectX::SimpleMath::Vector4 
{
public:
	Vector4() : DirectX::SimpleMath::Vector4() {}
	Vector4(float x, float y, float z, float w)
		: DirectX::SimpleMath::Vector4(x, y, z, w) {}
};