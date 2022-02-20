#include "Updatable.h"

void garbage::Updatable::Engine_Update(float deltaTime)
{
	if (m_bUpdateEnabled) Update(deltaTime);
}