#include "Utils.h"
#include <fstream>

std::string garbage::utils::Replace(const std::string& source, const std::string& from, const std::string& to)
{
    std::string newString;
    newString.reserve(source.length());  // avoids a few memory allocations

    std::string::size_type lastPos = 0;
    std::string::size_type findPos;

    while (std::string::npos != (findPos = source.find(from, lastPos)))
    {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString += source.substr(lastPos);

    return newString;
}

std::string garbage::utils::GetFileContents(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);

    if (in)
    {
        std::string contents;

        in.seekg(0, std::ios::end);

        contents.resize(in.tellg());

        in.seekg(0, std::ios::beg);

        in.read(&contents[0], contents.size());

        in.close();

        return(contents);
    }

    throw(errno);
}