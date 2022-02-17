#ifndef _garbage_scenecomponent
#define _garbage_scenecomponent

#include "GarbageSDK.h"
#include "Object.h"
#include "Transform.h"

namespace garbage
{

	class GSDK SceneComponent : public Object
	{
	public:

		inline Transform* GetTransform() { return &m_transform; }

		const Vector3& GetLocation() const { return m_transform.Location; }
		//const Quaternion& GetRotation() const { return m_transform.Rotation; }
		const Vector3& GetScale() const { return m_transform.Scale; }

	private:

		Transform m_transform;

	};

}

#endif