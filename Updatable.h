#ifndef _garbage_updatable
#define _garbage_updatable

#include "GarbageSDK.h"

namespace garbage
{

	class GSDK Updatable
	{
	public:

		void Engine_Update(float deltaTime);

	protected:

		bool bUpdateEnabled = false;

		virtual void Update(float deltaTime) {}

	};

}

#endif