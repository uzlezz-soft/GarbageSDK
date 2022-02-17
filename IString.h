#ifndef _garbage_istring
#define _garbage_istring

#include "GarbageSDK.h"
#include <string>
#include <sstream>

namespace garbage
{

	class GSDK IString
	{
	public:

		operator std::string() const { return ToString(); }

	protected:

		virtual std::string ToString() const { return ""; }

	};

}

#endif