#ifndef _garbage_string
#define _garbage_string

#include "GarbageSDK.h"
#include "List.h"
#include "IString.h"

namespace garbage
{

	class GSDK GString : public IString
	{
	public:

		GString(){}
		GString(const char* text);
		GString(const char c);
		GString(std::string& str);
		~GString();

		inline int GetLength() const;
		bool Empty() const;

		GString Replace(const GString& source, const GString& from, const GString& to);

		void operator=(const char* text);
		char* operator[](int index);

		operator const char*() const;

	protected:

		virtual std::string ToString() const;

	private:

		List<char> m_buffer;

		void SetBuffer(const char* text, int length);

	};

}

#endif