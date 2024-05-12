#include "SaveManager.h"
#include <iostream>
#include <filesystem>
#include <chrono>


bool SaveHandler::confirmFile(const char* filepath)
{
	this->filepath = std::filesystem::current_path().generic_string() + "/" + filepath;
	return (filepath && std::filesystem::exists(this->filepath));
}

void SaveHandler::write(const char* dataPtr, size_t dataSize, SaveDataType type)
{
	file.open(filepath, std::ios::out | std::ios::binary);
	if (!file)
	{
		return;
	}

	file.write(dataPtr, dataSize);

	file.close();
}

void SaveHandler::read(char* dataPtr, size_t dataSize, SaveDataType type)
{
	file.open(filepath, std::ios::in | std::ios::binary);
	if (!file)
	{
		return;
	}

	file.read(dataPtr, dataSize);

	file.close();
}

bool SaveHandler::saveFileExists(const char* filepath)
{
	return std::filesystem::exists(std::filesystem::current_path().generic_string() + "/data/" + filepath);
}

bool SaveHandler::isDirectoryEmpty(const char* folderpath)
{
	std::filesystem::path path(std::filesystem::current_path().generic_string() + "/data/" + folderpath);

	if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
		std::cerr << "ERROR: The folder is sus!" << std::endl;
		return false;
	}

	return std::filesystem::is_empty(path);
}

const std::filesystem::path SaveHandler::recentlyEditedDirectory(const char* folderpath)
{
	const std::filesystem::path path(std::filesystem::current_path().generic_string() + "/data/" + folderpath);

	std::time_t lastEditedTime = 0;
	std::filesystem::path lastEditedDirectory;
	
	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path))
	{
		if (!std::filesystem::is_directory(entry))
		{
			continue;
		}
		const std::filesystem::file_time_type editTime = std::filesystem::last_write_time(entry);
		const std::chrono::system_clock::time_point systemTime = std::chrono::clock_cast<std::chrono::system_clock>(editTime);
		const std::time_t time = std::chrono::system_clock::to_time_t(systemTime);

		if (time > lastEditedTime)
		{
			lastEditedTime = time;
			lastEditedDirectory = entry.path();
		}
	}

	return lastEditedDirectory;
}
