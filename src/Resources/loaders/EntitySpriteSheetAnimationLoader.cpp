#include "EntitySpriteSheetAnimationLoader.h"
#include "Helpers/Text/StringUtils.h"
#include <iostream>
#include <algorithm>


void loaders::loadAnimationFromSpriteSheet(EntityManager& eManager, uint64_t entityID, std::filesystem::path& filepath)
{
	EntityComponent::Animation* animation = eManager.addComponent<EntityComponent::Animation>(entityID);
	EntityComponent::Image* image = eManager.addComponent<EntityComponent::Image>(entityID);

	const std::string name = strUtil::firstNameFromPath(filepath);
	Global::TextureHandler::add(filepath.string(), name);
	image->sprite.setTexture(Global::TextureHandler::get(name));
	
	std::ifstream file(filepath.replace_extension(".bin"), std::ios::binary);

	if (!file)
	{
		std::cerr << "Unable to open sprite sheet's bin file!" << std::endl;
		return;
	}

	AnimationRawDataHeader header;
	file.read(reinterpret_cast<char*>(&header), sizeof(AnimationRawDataHeader));
	std::vector<HeaderBlock> headerBlocks(header.animationAmounts);
	file.read(reinterpret_cast<char*>(headerBlocks.data()), sizeof(HeaderBlock) * header.animationAmounts);

	for (HeaderBlock& block : headerBlocks)
	{
		std::vector<EntityComponent::Animation::AnimationArray::AnimationFrame> data(block.size);
		file.read(reinterpret_cast<char*>(data.data()), sizeof(EntityComponent::Animation::AnimationArray::AnimationFrame) * block.size);

		EntityComponent::Animation::AnimationArray animationBlock;
		animationBlock.animationType = block.animationType;
		animationBlock.duration = header.duration;
		animationBlock.loop = (!EntityComponent::Animation::AnimationArray::isTurnAnimation(block.animationType)
			&& !EntityComponent::Animation::AnimationArray::isFallingAnimation(block.animationType)); // TODO: FIX THIS MESS D:

		if (EntityComponent::Animation::AnimationArray::isTurnAnimation(block.animationType))
		{
			std::reverse(data.begin(), data.end());
		}

		animationBlock.frames = std::move(data);
		
		animation->animations[block.animationType] = std::move(animationBlock);
	}

	file.close();

	animation->spriteSize = sf::Vector2i(header.spriteSize.x, header.spriteSize.y);
	sf::IntRect rect(0, 0, header.spriteSize.x, header.spriteSize.y);
	image->sprite.setTextureRect(rect);
	image->sprite.setScale(6, 6);
}
