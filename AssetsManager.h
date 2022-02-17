#ifndef _garbage_assetsmanager
#define _garbage_assetsmanager

#include "GarbageSDK.h"
#include "Asset.h"
#include "Texture.h"

namespace garbage
{

	class GSDK AssetsManager
	{
	public:

		static AssetsManager* Instance();

	private:

		AssetsManager() = default;

	};

}

#endif