#pragma once
#include <filesystem>
#include <string>



namespace strUtil
{
	std::string firstNameFromString(const std::string& original);

	std::string fileNameFromPath(const std::filesystem::path& path);

	std::string firstNameFromPath(const std::filesystem::path& path);

}
