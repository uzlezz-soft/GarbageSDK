#ifndef _garbage_event
#define _garbage_event

#include "GarbageSDK.h"
#include <vector>

namespace garbage
{

	class GSDK GarbageEvent
	{
	public:

		void Bind(void (*ev)());
		void Unbind(void (*ev)());

		void Invoke();

	private:

		std::vector<void(*)()> m_events;

	};

	template <class T>
	class GSDK GarbageEventP
	{
	public:

		void Bind(void (*ev)(T))
		{
			m_events.push_back(ev);
		}

		void Unbind(void (*ev)(T))
		{
			remove(m_events.begin(), m_events.end(), ev);
		}

		void Invoke(T t)
		{
			for (auto it = m_events.begin(); it != m_events.end(); it++)
			{
				try
				{
					(*it)(t);
				}
				catch (...)
				{
					m_events.erase(it);
				}
			}
		}

	private:

		std::vector<void(*)(T)> m_events;

	};

}

#endif