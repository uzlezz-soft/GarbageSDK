#include "GString.h"

garbage::GString::GString(const char* text)
{
	SetBuffer(text, strlen(text));
}

garbage::GString::GString(const char c)
{
	m_buffer.Add(c);
}

garbage::GString::GString(std::string& str)
{
	SetBuffer(str.c_str(), str.size());
}

garbage::GString::~GString()
{
	m_buffer.Clear();
}

inline int garbage::GString::GetLength() const
{
	return m_buffer.GetLength();
}

void garbage::GString::operator=(const char* text)
{
	m_buffer.Clear();

	SetBuffer(text, strlen(text));
}

char* garbage::GString::operator[](int index)
{
	return nullptr;
}

garbage::GString::operator const char* () const
{
	return nullptr;
}

bool garbage::GString::Empty() const
{
	return m_buffer.GetLength() == 0;
}

garbage::GString garbage::GString::Replace(const GString& source, const GString& from, const GString& to)
{
	std::string _source = source.ToString();
	std::string _from = from.ToString();
	std::string _to = to.ToString();

	std::string newString;
	newString.reserve(_source.length());

	std::string::size_type lastPos = 0;
	std::string::size_type findPos;

	while (std::string::npos != (findPos = _source.find(_from, lastPos)))
	{
		newString.append(source, lastPos, findPos - lastPos);
		newString += _to;
		lastPos = findPos + _from.length();
	}

	// Care for the rest after last occurrence
	newString += _source.substr(lastPos);

	return newString;
}

std::string garbage::GString::ToString() const
{
	std::stringstream ss;

	for (int i = 0; i < m_buffer.GetLength(); i++)
	{
		ss << m_buffer.GetElement(i);
	}

	return ss.str();
}

void garbage::GString::SetBuffer(const char* text, int length)
{
	for (int i = 0; i < length; i++)
	{
		m_buffer.Add(text[i]);
	}
}
