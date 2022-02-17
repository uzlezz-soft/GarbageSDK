#include "GarbageEvent.h"

void garbage::GarbageEvent::Bind(void(*ev))
{
	m_events.push_back(ev);
}

void garbage::GarbageEvent::Unbind(void(*ev))
{
	remove(m_events.begin(), m_events.end(), ev);
}

void garbage::GarbageEvent::Invoke()
{
	for (auto it = m_events.begin(); it != m_events.end(); it++)
	{
		//it();
	}
}