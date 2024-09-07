#pragma once
#include <string>
#include <SFML/Graphics/Font.hpp>


/*
* -- HARD CODED WAY TO STORE FONTS --
* yah it's stupid but we only need few fonts duh.
*/


namespace Global
{
	constexpr int MAX_FONT_AMOUNT = 2;

	class FontHandler
	{
	public:
		enum FontType : int
		{
			NORMAL_FONT,
			SPECIAL_FONT
		};

		FontHandler(const FontHandler&) = delete;
		FontHandler& operator=(const FontHandler&) = delete;

		static void load();
		static void shutDown();

		static void addFont(std::string& filepath, FontType type);
		static sf::Font& getFont(FontType type);
	private:
		FontHandler();
		~FontHandler();

		void addFontFromInstance(std::string& filepath, FontType type);
		sf::Font& getFontFromInstance(FontType type);

		sf::Font fonts[MAX_FONT_AMOUNT];
	};
}


