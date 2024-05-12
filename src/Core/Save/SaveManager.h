#pragma once
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

enum class SaveDataType
{
	SETTINGS,
	GAME_PROGRESS,
	PLAYER_DATA,
	ENEMIES_DATA,
	WORLD_DATA,

};

/*
Oisko j‰rkev‰‰ pist‰‰ kaikki yhteen tiedostoon vai jokanen omaan tiedostoon?
esim world data ja settings eri hommaan?
*/


class SaveHandler
{
public:
	bool confirmFile(const char* filepath);

	//write data
	void write(const char* dataPtr, size_t dataSize, SaveDataType type);

	//return data
	void read(char* dataPtr, size_t dataSize, SaveDataType type);

	static bool saveFileExists(const char* filepath);

	static bool isDirectoryEmpty(const char* folderpath);
	
	static const std::filesystem::path recentlyEditedDirectory(const char* folderpath);

	//void createWorldFile(const char* folderpath);

private:
	std::string filepath;
	std::fstream file;
};

