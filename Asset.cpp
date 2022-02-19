#include "Asset.h"

garbage::AssetLoadResult garbage::ENUM_StringToALR(std::string& str)
{
	if (str == "ALR_FileNotFound") return ALR_FileNotFound;
	else if (str == "ALR_HeadersMismatch") return ALR_HeadersMismatch;
	else if (str == "ALR_HeadersOk") return ALR_HeadersOk;
	else if (str == "ALR_Success") return ALR_Success;
	else if (str == "ALR_SyntaxError") return ALR_SyntaxError;
	else if (str == "ALR_UnexceptedEndOfFile") return ALR_UnexceptedEndOfFile;
	else if (str == "ALR_UnknownError") return ALR_UnknownError;
	else return ALR_None;
}

const std::string garbage::ENUM_ALRToString(AssetLoadResult alr)
{
	if (alr == ALR_FileNotFound) return "ALR_FileNotFound";
	else if (alr == ALR_HeadersMismatch) return "ALR_HeadersMismatch";
	else if (alr == ALR_HeadersOk) return "ALR_HeadersOk";
	else if (alr == ALR_Success) return "ALR_Success";
	else if (alr == ALR_SyntaxError) return "ALR_SyntaxError";
	else if (alr == ALR_UnexceptedEndOfFile) return "ALR_UnexceptedEndOfFile";
	else if (alr == ALR_UnknownError) return "ALR_UnknownError";
	else return "ALR_None";
}

const garbage::AssetLoadResult garbage::Asset::LoadFromFile(std::string filename)
{
	m_originalFile = filename;

	return ALR_UnknownError;
}

const garbage::AssetLoadResult garbage::Asset::LoadFileHeaders(std::ifstream& in, const char* assetType)
{
	if (!in.is_open())
	{
		return ALR_FileNotFound;
	}

	int version;
	std::string text, date;

	char text_buffer[50], date_buffer[9];

	in >> version;

	std::string headerText = garbage::utils::Replace(AH_Text, "{$asset_type}", assetType);
	text_buffer[headerText.size()] = date_buffer[8] = '\0';

	in.read(text_buffer, headerText.size());
	text = text_buffer;

	in.read(date_buffer, 8);
	date = date_buffer;
	if (version != AH_Version || text != garbage::utils::Replace(AH_Text, "{$asset_type}", assetType) || date != AH_Date)
	{
		in.close();

		return ALR_HeadersMismatch;
	}

	if (text == garbage::utils::Replace(AH_Text, "{$asset_type}", "TEXTURE"))
	{

	}

	return ALR_HeadersOk;
}