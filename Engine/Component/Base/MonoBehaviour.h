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
		//==============Render메소드삭제==============
		virtual void Render() final {};
		//============MonoBehaviour메소드=============
		void DestroyObject(Object* _object);
		//================CallBack함수================
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