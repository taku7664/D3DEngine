#pragma once

enum class GameState
{
	Create,
	Active,
	Passive,
	Destroy,
};

enum class ComponentType
{
	BoxCollider3D,
	CircleCollider3D,
	SpriteRenderer,
	Animator,
	RectRenderer,
	CircleRenderer,
	LineRenderer,
	TextRenderer,
	Button,
	Script,
	FiniteStateMachine,
	Transform,
	Camera,
	SIZE,
};

enum class ResourceType
{
	NONE,
	Texture,
	Sprite,
	Animation,
	AudioClip,
	Font,
	SIZE,
};