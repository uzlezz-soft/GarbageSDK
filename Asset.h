#ifndef _garbage_asset
#define _garbage_asset

#include "GarbageSDK.h"
#include <string>
#include <fstream>
#include "Utils.h"
#include <iostream>

#define AH_Version (int)1
#define AH_Text (const char*)"GARBAGE_{$asset_type}_FILE"
#define AH_Date (const char*)"02.01.22"
#define ASSET_XOR (int)123

namespace garbage
{

	enum GSDK AssetLoadResult
	{
		ALR_None, ALR_Success, ALR_HeadersMismatch, ALR_UnknownError, ALR_FileNotFound, ALR_HeadersOk, ALR_SyntaxError, ALR_UnexceptedEndOfFile
	};

	GSDK AssetLoadResult ENUM_StringToALR(std::string& str);
	GSDK const std::string ENUM_ALRToString(AssetLoadResult alr);

	class GSDK Asset
	{
	public:

		virtual const AssetLoadResult LoadFromFile(std::string filename);

	protected:

		std::string m_originalFile;

		const AssetLoadResult LoadFileHeaders(std::ifstream& in, const char* assetType);

	};

}

#endif