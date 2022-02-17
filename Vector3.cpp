#include "Vector3.h"
#include "Mathf.h"

garbage::Vector3 garbage::Vector3::MoveTowards(Vector3& other, float deltaDistance) const
{
	if (Distance(other) < deltaDistance) return other;

	Vector3 result = m_v3 + (Vector3(other.m_v3 - m_v3).Normalized() * deltaDistance).m_v3;
	if (result.Distance(other) < deltaDistance) return other;
	
	return result;
}

garbage::Vector3 garbage::Vector3::Lerp(Vector3& other, float time) const
{
	return Vector3(Mathf::Lerp(GetX(), other.GetX(), time), Mathf::Lerp(GetY(), other.GetY(), time), Mathf::Lerp(GetZ(), other.GetZ(), time));
}

garbage::Vector3 garbage::Vector3::operator+(Vector3& other)
{
	return m_v3 + other.m_v3;
}

garbage::Vector3 garbage::Vector3::operator-(Vector3& other)
{
	return m_v3 - other.m_v3;
}

garbage::Vector3 garbage::Vector3::operator*(float other)
{
	return m_v3 * other;
}

garbage::Vector3 garbage::Vector3::operator/(float other)
{
	return m_v3 / other;
}

bool garbage::Vector3::operator!=(Vector3& other)
{
	return m_v3 != other.m_v3;
}

bool garbage::Vector3::operator==(Vector3& other)
{
	return m_v3 == other.m_v3;
}

std::string garbage::Vector3::ToString() const
{
	std::stringstream ss;
	ss << "X: " << GetX() << " Y: " << GetY() << " Z: " << GetZ();
	return ss.str();
}