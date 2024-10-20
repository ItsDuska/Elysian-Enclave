#include "StringUtils.h"

std::string strUtil::firstNameFromString(const std::string& original)
{
    const size_t underscore_pos = original.find('_');
    return (underscore_pos != std::string::npos) ? original.substr(0, underscore_pos) : original;
}

std::string strUtil::fileNameFromPath(const std::filesystem::path& path)
{
    return path.filename().string();
}

std::string strUtil::firstNameFromPath(const std::filesystem::path& path)
{
    return firstNameFromString(fileNameFromPath(path));
}


