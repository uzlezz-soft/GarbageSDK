#include "Quaternion.h"

std::string garbage::Quaternion::ToString() const
{
	std::stringstream ss;
	ss << "X: " << GetX() << " Y: " << GetY() << " Z: " << GetZ() << " W: " << GetW();
	return ss.str();
}

garbage::Quaternion garbage::Quaternion::operator+(Quaternion other) const
{
	return m_q + other.m_q;
}

garbage::Quaternion garbage::Quaternion::operator-(Quaternion other) const
{
	return m_q - other.m_q;
}

void garbage::Quaternion::operator+=(Quaternion other)
{
	m_q += other.m_q;
}

void garbage::Quaternion::operator-=(Quaternion other)
{
	m_q -= other.m_q;
}

void garbage::Quaternion::operator*=(float other)
{
	m_q *= other;
}

void garbage::Quaternion::operator/=(float other)
{
	m_q /= other;
}

garbage::Quaternion garbage::Quaternion::operator*(float other) const
{
	return m_q * other;
}

garbage::Quaternion garbage::Quaternion::operator/(float other) const
{
	return m_q / other;
}

bool garbage::Quaternion::operator==(Quaternion& other) const
{
	return m_q == other.m_q;
}

bool garbage::Quaternion::operator!=(Quaternion& other) const
{
	return m_q != other.m_q;
}
