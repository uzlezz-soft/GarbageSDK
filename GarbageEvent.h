#ifndef _garbage_event
#define _garbage_event

#include "GarbageSDK.h"
#include <vector>

namespace garbage
{

	class GSDK GarbageEvent
	{
	public:

		void Bind(void(*ev));
		void Unbind(void(*ev));

		void Invoke();

	private:

		std::vector<void(*)> m_events;

	};

}

#endif