#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <unordered_map>

namespace Global
{
	class TextureHandler
	{
	public:
		TextureHandler(const TextureHandler&) = delete;
		TextureHandler& operator=(const TextureHandler&) = delete;

		static void load();
		static void shutDown();

		static void add(std::string& filepath, const std::string name);
		static void add(const std::string& filepath, std::string name);
		static sf::Texture& get(std::string& name);
		static sf::Texture& get(std::string name);
	private:
		TextureHandler();
		~TextureHandler();

		void addTexctureFromInstance(const std::string& filepath,const std::string& name);
		sf::Texture& getTexctureFromInstance(std::string& name);

		std::unordered_map<std::string, sf::Texture> textures;
	};
}


