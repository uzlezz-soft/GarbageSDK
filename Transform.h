#ifndef _garbage_transform
#define _garbage_transform

#include "GarbageSDK.h"
#include "Vector3.h"

namespace garbage
{

	class GSDK Transform
	{
	public:

		Vector3 Location = Vector3::Zero();
		// Quaternion Rotation;
		Vector3 Scale = Vector3::One();

		inline Transform* GetParent() const { return m_parent; }
		void SetParent(Transform* parent);

	private:

		Transform* m_parent = nullptr;

	};

}

#endif