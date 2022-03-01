#ifndef _garbage_transform
#define _garbage_transform

#include "GarbageSDK.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace garbage
{

	class GSDK Transform
	{
	public:

		Vector3 Location = Vector3::Zero();
		Quaternion Rotation = Quaternion::Identity();
		Vector3 Scale = Vector3::One();

		inline Transform* GetParent() const { return m_parent; }
		void SetParent(Transform* parent);

		Vector3 GetWorldLocation();
		Quaternion GetWorldRotation();
		Vector3 GetWorldScale();

		void SetWorldLocation(Vector3 worldLocation);
		void SetWorldRotation(Quaternion worldRotation);
		void SetWorldScale(Vector3 worldScale);

	private:

		Transform* m_parent = nullptr;

	};

}

#endif