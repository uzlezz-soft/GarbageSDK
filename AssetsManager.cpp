#include "AssetsManager.h"

garbage::AssetsManager* garbage::AssetsManager::Instance()
{
	static garbage::AssetsManager instance;

	return &instance;
}