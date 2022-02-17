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

		~Object() {}

	};

}

#endif