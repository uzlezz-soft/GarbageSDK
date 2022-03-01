#ifndef _garbage_object
#define _garbage_object

#include <string>
#include "Updatable.h"

namespace garbage
{

	class GSDK Object : public Updatable
	{
	public:

		std::string Name = "New Object";

		Object() {}
		Object(std::string name) { Name = name; }

		virtual ~Object() {}

	};

	template <class T>
	GSDK T* Cast(Object* source)
	{
		try {
			T* object = static_cast<T*>(source);

			return object;
		}
		catch (...)
		{
			return nullptr;
		}
	}

}

#endif