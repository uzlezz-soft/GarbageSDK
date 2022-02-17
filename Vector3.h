#ifndef _garbage_vector
#define _garbage_vector

#include "GarbageSDK.h"
#include <glm/glm.hpp>
#include <glm/gtx/functions.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "IString.h"

namespace garbage
{

	class GSDK Vector3 : public IString
	{
	public:

		Vector3() { m_v3 = glm::vec3(0.f); }
		Vector3(float x, float y, float z) { SetX(x); SetY(y); SetZ(z); }
		Vector3(float xyz) { SetX(xyz); SetY(xyz); SetZ(xyz); }
		Vector3(glm::vec3 v3) { m_v3 = v3; }

		inline float GetX() const { return m_v3.x; }
		inline float GetY() const { return m_v3.y; }
		inline float GetZ() const { return m_v3.z; }

		void SetX(float x) { m_v3.x = x; }
		void SetY(float y) { m_v3.y = y; }
		void SetZ(float z) { m_v3.z = z; }

		inline float Length() const { return glm::length(m_v3); }
		inline float SqrLength() const { float l = Length(); return l * l; }
		inline float Distance(Vector3& other) const { return glm::distance(m_v3, other.m_v3); }
		inline Vector3 Normalized() const { return Vector3(glm::normalize(m_v3)); }

		inline float Angle(Vector3& other) const { return glm::angle(m_v3, other.m_v3); }
		inline Vector3 Cross(Vector3& other) const { return glm::cross(m_v3, other.m_v3); }
		inline float Dot(Vector3& other) const { return glm::dot(m_v3, other.m_v3); }

		inline Vector3 Max(Vector3& other) const { return glm::max(m_v3, other.m_v3); }
		inline Vector3 Min(Vector3& other) const { return glm::min(m_v3, other.m_v3); }

		Vector3 MoveTowards(Vector3& other, float deltaDistance) const;
		Vector3 Lerp(Vector3& other, float time) const;

		static inline Vector3 Zero() { return Vector3(); }
		static inline Vector3 One() { return Vector3(1.f, 1.f, 1.f); }
		static inline Vector3 Forward() { return Vector3(0.f, 0.f, -1.f); }
		static inline Vector3 Right() { return Vector3(1.f, 0.f, 0.f); }
		static inline Vector3 Up() { return Vector3(0.f, 1.f, 0.f); }

		Vector3 operator+(Vector3& other);
		Vector3 operator-(Vector3& other);
		Vector3 operator*(float other);
		Vector3 operator/(float other);
		bool operator!=(Vector3& other);
		bool operator==(Vector3& other);

		operator glm::vec3() const { return m_v3; }

	protected:

		virtual std::string ToString() const override;

	private:

		glm::vec3 m_v3;

	};

}

#endif