#include "Transform.h"

void garbage::Transform::SetParent(Transform* parent)
{
	if (parent != nullptr)
	{
		Location = GetWorldLocation() - parent->GetWorldLocation();
		Rotation = GetWorldRotation() - parent->GetWorldRotation();

		Vector3 worldScale = GetWorldScale();
		Scale = Vector3(worldScale.GetX() / parent->Scale.GetX(),
			worldScale.GetY() / parent->Scale.GetY(),
			worldScale.GetZ() / parent->Scale.GetZ());

		m_parent = parent;
	}
	else
	{
		Location = GetWorldLocation();
		Rotation = GetWorldRotation();
		Scale = GetWorldScale();

		m_parent = nullptr;
	}
}

garbage::Vector3 garbage::Transform::GetWorldLocation()
{
	if (m_parent)
	{
		return Location + m_parent->GetWorldLocation();
	}
	else
	{
		return Location;
	}
}

garbage::Quaternion garbage::Transform::GetWorldRotation()
{
	if (m_parent)
	{
		return Rotation + m_parent->GetWorldRotation();
	}
	else
	{
		return Rotation;
	}
}

garbage::Vector3 garbage::Transform::GetWorldScale()
{
	if (m_parent)
	{
		return Vector3(Scale.GetX() * m_parent->Scale.GetX(),
			Scale.GetY() * m_parent->Scale.GetY(),
			Scale.GetZ() * m_parent->Scale.GetZ());
	}
	else
	{
		return Scale;
	}
}

void garbage::Transform::SetWorldLocation(Vector3 worldLocation)
{
	Location = m_parent->GetWorldLocation() - worldLocation;
}

void garbage::Transform::SetWorldRotation(Quaternion worldRotation)
{
	Rotation = m_parent->GetWorldRotation() - worldRotation;
}

void garbage::Transform::SetWorldScale(Vector3 worldScale)
{
	Vector3 worldScaleParent = m_parent->GetWorldScale();
	Scale = Vector3(worldScale.GetX() / worldScaleParent.GetX(),
		worldScale.GetY() / worldScaleParent.GetY(),
		worldScale.GetZ() / worldScaleParent.GetZ());
}
