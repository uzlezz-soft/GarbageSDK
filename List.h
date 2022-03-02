#ifndef _garbage_listimplementation
#define _garbage_listimplementation

#include "GarbageSDK.h"
#include "IEnumerable.h"
#include <vector>
#include <stdexcept>

namespace garbage
{

	template <class T>
	class GSDK List : public IEnumerable<T>
	{
	public:

		List() : IEnumerable<T>() {}
		~List() {}

		virtual void Add(T element) override
		{
			m_vector.push_back(element);
		}
		virtual void Remove(T element) override
		{
			for (auto it = m_vector.begin(); it != m_vector.end(); it++)
			{
				if (*it == element)
				{
					m_vector.erase(it);
					return;
				}
			}
		}
		virtual void RemoveByIndex(int index) override
		{
			if (index >= GetLength())
			{
				throw std::runtime_error("Cannot remove element by index: out of bounds!");
			}

			m_vector.erase(m_vector.begin() + index);
		}

		virtual void Clear() override
		{
			m_vector.clear();
		}
		virtual inline int GetLength() const
		{
			return m_vector.size();
		}

		virtual T GetElement(int index) const override
		{
			if (index >= GetLength())
			{
				throw std::runtime_error("Cannot get element by index: out of bounds!");
			}

			return m_vector.at(index);
		}

		virtual T operator[](int index) override
		{
			return GetElement(index);
		}

	/*protected:

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "List{";

			for (int i = 0; i < GetLength(); i++)
			{
				try {
					ss << ' ' << i << ':' << m_vector.at(i);
				}
				catch (...)
				{
					return "Can't convert list to string";
				}
			}

			ss << " }";

			return ss.str();
		}*/

	private:

		std::vector<T> m_vector;

	};

}

#endif