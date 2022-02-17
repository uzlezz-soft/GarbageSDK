#include "Updatable.h"

void garbage::Updatable::Engine_Update(float deltaTime)
{
	if (bUpdateEnabled) Update(deltaTime);
}