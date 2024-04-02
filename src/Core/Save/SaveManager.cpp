#include "SaveManager.h"
#include <filesystem>


bool SaveManager::confirmFile(const char* filepath)
{
	this->filepath = std::filesystem::current_path().generic_string() + "/" + filepath;
	return (filepath && std::filesystem::exists(this->filepath));
}

void SaveManager::write(const char* dataPtr, size_t dataSize, SaveDataType type)
{
	file.open(filepath, std::ios::out | std::ios::binary);
	if (!file)
	{
		return;
	}

	file.write(dataPtr, dataSize);

	file.close();
}

void SaveManager::read(char* dataPtr, size_t dataSize, SaveDataType type)
{
	file.open(filepath, std::ios::in | std::ios::binary);
	if (!file)
	{
		return;
	}

	file.read(dataPtr, dataSize);

	file.close();
}
