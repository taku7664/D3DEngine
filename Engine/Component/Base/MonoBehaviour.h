#pragma once
class Collider;
class Object;
class WorldManager;

namespace Engine
{
	_ABSTRACT MonoBehaviour
	{
	public:
		MonoBehaviour();
		virtual ~MonoBehaviour();
		//==============Render�޼ҵ����==============
		virtual void Render() final {};
		//============MonoBehaviour�޼ҵ�=============
		void DestroyObject(Object* _object);
		//================CallBack�Լ�================
		virtual _CALLBACK OnEnable() {};
		virtual _CALLBACK OnDisable() {};
		virtual _CALLBACK OnDestroy() {};

		virtual _CALLBACK OnCollisionEnter(Collider* _origin, Collider* _destination) {};
		virtual _CALLBACK OnCollisionStay(Collider* _origin, Collider* _destination) {};
		virtual _CALLBACK OnCollisionExit(Collider* _origin, Collider* _destination) {};

		virtual _CALLBACK OnMouseEnter() {};
		virtual _CALLBACK OnMouseStay() {};
		virtual _CALLBACK OnMouseExit() {};

		virtual _CALLBACK OnAnimationPlay() {};
		virtual _CALLBACK OnAnimationStop() {};
		virtual _CALLBACK OnAnimationStart() {};
		virtual _CALLBACK OnAnimationEnd() {};
	};
}