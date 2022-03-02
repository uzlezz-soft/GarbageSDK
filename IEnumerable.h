#ifndef _garbage_ienumerable
#define _garbage_ienumerable

#include "GarbageSDK.h"
//#include "IString.h"

namespace garbage
{

	template <class T>
	class GSDK IEnumerable// : public IString
	{
	public:

		IEnumerable<T>(){}
		~IEnumerable<T>(){}

		virtual void Add(T element) {}
		virtual void Remove(T element) {}
		virtual void RemoveByIndex(int index) {}

		virtual void Clear() {}
		virtual inline int GetLength() const { return 0; }

		virtual T GetElement(int index) const { T t = T(); return t; }

		virtual T operator[](int index) { return GetElement(index); }
		virtual void operator+=(T element) { Add(element); }
		virtual void operator-=(T element) { Remove(element); }

	/*protected:

		virtual std::string ToString() const override { return "IEnumerable"; }*/

	};

}

#endif