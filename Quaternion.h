#ifndef _garbage_quaternion
#define _garbage_quaternion

#include "GarbageSDK.h"
#include <glm/glm.hpp>
#include <glm/gtx/functions.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Vector3.h"
#include "Mathf.h"

namespace garbage
{

	class GSDK Quaternion : public IString
	{
	public:

		Quaternion() { m_q = glm::quat(); }
		Quaternion(float x, float y, float z, float w) { SetX(x); SetY(y); SetZ(z); SetW(w); }
		Quaternion(float xyzw) { SetX(xyzw); SetY(xyzw); SetZ(xyzw); SetW(xyzw); }
		Quaternion(glm::quat q) { m_q = q; }
		Quaternion(glm::vec3 eulerAngles) { m_q = glm::quat(eulerAngles) * Mathf::Rad2Deg(); }

		inline float GetX() const { return m_q.x; }
		inline float GetY() const { return m_q.y; }
		inline float GetZ() const { return m_q.z; }
		inline float GetW() const { return m_q.z; }

		void SetX(float x) { m_q.x = x; }
		void SetY(float y) { m_q.y = y; }
		void SetZ(float z) { m_q.z = z; }
		void SetW(float w) { m_q.w = w; }

		inline Vector3 GetEulerAngles() const { return glm::eulerAngles(m_q); }
		void SetEulerAngles(Vector3 eulerAngles) { m_q = Quaternion(eulerAngles); }

		inline Quaternion Normalized() const { return glm::normalize(m_q); }

		static Quaternion LookAt(Vector3 from, Vector3 to) 
		{ return glm::conjugate(glm::toQuat(glm::lookAt((glm::vec3)from, (glm::vec3)to, (glm::vec3)Vector3::Up()))); }

		static inline Quaternion Identity() { return Quaternion(); }

		operator glm::quat() const { return m_q; }

	protected:

		virtual std::string ToString() const override;

	private:

		glm::quat m_q;

	};

}

#endif