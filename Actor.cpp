#include "Actor.h"

garbage::Actor::Actor() : SceneComponent()
{
	
}

const garbage::Vector3 garbage::Actor::GetWorldLocation() const
{
	return ((Transform)m_transform).GetWorldLocation();
}

const garbage::Quaternion garbage::Actor::GetWorldRotation() const
{
	return ((Transform)m_transform).GetWorldRotation();
}

const garbage::Vector3 garbage::Actor::GetWorldScale() const
{
	return ((Transform)m_transform).GetWorldScale();
}
