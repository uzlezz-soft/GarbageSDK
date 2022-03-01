#ifndef _garbage_utils
#define _garbage_utils

#include "GarbageSDK.h"
#include <string>

namespace garbage
{

	namespace utils
	{

		std::string GSDK Replace(const std::string& source, const std::string& from, const std::string& to);

		std::string GSDK GetFileContents(const char* filename);

	}

}

#endif