#include "Quaternion.h"

std::string garbage::Quaternion::ToString() const
{
	std::stringstream ss;
	ss << "X: " << GetX() << " Y: " << GetY() << " Z: " << GetZ() << " W: " << GetW();
	return ss.str();
}