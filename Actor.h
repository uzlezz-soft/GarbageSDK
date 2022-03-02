#ifndef _garbage_actor
#define _garbage_actor

#include "SceneComponent.h"
#include "Transform.h"

namespace garbage
{

	class GSDK Actor : public SceneComponent
	{
	public:

		Actor();

		inline Transform* GetTransform() { return &m_transform; }

		const Vector3 GetLocation() const { return m_transform.Location; }
		const Quaternion GetRotation() const { return m_transform.Rotation; }
		const Vector3 GetScale() const { return m_transform.Scale; }

		const Vector3 GetWorldLocation() const;
		const Quaternion GetWorldRotation() const;
		const Vector3 GetWorldScale() const;

	private:

		Transform m_transform;

	};

}

#endif