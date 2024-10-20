#pragma once
#include "Core/ECS/ECData/EntityManager.hpp"
#include "Entities/BasicComponentData.h"
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <cstdint>
#include "Resources/TextureHandler.h"

namespace loaders
{
	struct HeaderBlock
	{
		uint16_t animationType;
		uint16_t size;
	};

	struct AnimationRawDataHeader
	{
		// Header
		sf::Vector2<uint16_t> spriteSize;
		uint16_t duration;
		uint16_t animationAmounts;

		//Fixed sized array animaatioiden koosta eli kuinka monta framea yhessa animaatio tyypissä on.
		//uint16_t animations[animationAmounts];

		//std::vector<sf::Vector2<uint16_t>> texCoords;
	};



	void loadAnimationFromSpriteSheet(EntityManager& eManager,uint64_t entityID, std::filesystem::path& filepath);
}
