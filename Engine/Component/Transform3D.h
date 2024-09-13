#pragma once
#include "Base/Component.h"

class Transform3D
	: public Component
{
public:
	using Component::Component;
	virtual ~Transform3D();

	virtual void FixedUpdate() override;
	virtual void PreUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Vector3 GetWorldPosition();
	Vector3 GetWorldRotation();
	Vector3 GetWorldScale();
private:
	Matrix4X4F m_localTransform;
	Matrix4X4F m_worldTransform;
};

