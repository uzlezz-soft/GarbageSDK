#include "GarbageEvent.h"

void garbage::GarbageEvent::Bind(void (*ev)())
{
	m_events.push_back(ev);
}

void garbage::GarbageEvent::Unbind(void (*ev)())
{
	remove(m_events.begin(), m_events.end(), ev);
}

void garbage::GarbageEvent::Invoke()
{
	for (auto it = m_events.begin(); it != m_events.end(); it++)
	{
		try
		{
			(*it)();
		}
		catch (...)
		{
			m_events.erase(it);
		}
	}
}



/*template <class T>
void garbage::GarbageEventP<T>::Bind(void (*ev)(T))
{
	
}

template <class T>
void garbage::GarbageEventP<T>::Unbind(void (*ev)(T))
{
	
}*/

/*template<class T>
void garbage::GarbageEventP<T>::Invoke(T t)
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
}*/

/*template <class T>
void garbage::GarbageEventP<T>::Invoke(T t)
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
}*/
