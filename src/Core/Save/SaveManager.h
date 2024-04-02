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


class SaveManager
{
public:
	bool confirmFile(const char* filepath);

	//write data
	void write(const char* dataPtr, size_t dataSize, SaveDataType type);

	//return data
	void read(char* dataPtr, size_t dataSize, SaveDataType type);

private:
	std::string filepath;
	std::fstream file;
};

