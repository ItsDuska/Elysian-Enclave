#include "WorldHandler.h"

TileWorldHandler::TileWorldHandler(EditorCreationInfo& info)
    : vboHandler(info.staticSpriteSheetTexturePath,info.spritePixelSize),
    animationHandler(info.animatedSpriteSheetTexturePath,info.spritePixelSize),
    layer(info.layeredSpriteSheetTexturePath, info.spritePixelSize),
    entity(info.objectSpriteSheetTexturePath,info.spritePixelSize)
{
    chunkHandler.setAssetSizes(
        info.tileSize,
        info.spritePixelSize,
        vboHandler.getSpriteSheetSizeInTiles().x
    );

    chunkHandler.loadFromFile("data/world/EpistePng.chunk");

}

void TileWorldHandler::update(sf::Vector2f& position)
{
	chunkHandler.update(position);

	if (chunkHandler.needsUpdate())
	{
		updateBuffers();
	}
}

void TileWorldHandler::render(sf::RenderTarget& window, bool shaderUniformShowVisibility)
{
    vboHandler.render(window, shaderUniformShowVisibility);
    animationHandler.render(window);
    entity.render(window);
    layer.render(window);
}

VBOHandler& TileWorldHandler::getVBOHandler()
{
    return vboHandler;
}

AnimationHandler& TileWorldHandler::getAnimationHandler()
{
    return animationHandler;
}

chunk::ChunkHandler& TileWorldHandler::getChunkHandler()
{
    return chunkHandler;
}

LayeredTileHandler& TileWorldHandler::getLayeredTileHandler()
{
    return layer;
}

EntityHandler& TileWorldHandler::getEntityHandler()
{
    return entity;
}

ChunkData* TileWorldHandler::getChunkData(const sf::Vector2i& position)
{
    return chunkHandler.getChunk(position);
}

sf::VertexBuffer* TileWorldHandler::getVBOPtr(const sf::Vector2i& position)
{
    const int chunkIndex = chunkHandler.chunkInActiveMemory(position);
    return vboHandler.getBufferPtr(chunkIndex);
}

void TileWorldHandler::updateBuffers()
{
    std::vector<chunk::ChunkCreationTask>& tasks = chunkHandler.getChunkCreationTasks();

    for (const chunk::ChunkCreationTask& task : tasks)
    {
        vboHandler.addVertexBuffer(
            task.chunkCoord,
            task.hasTileMap,
            task.chunkData,
            chunkHandler.getRenderSizes()
        );
    }

    tasks.clear();

    std::vector<uint16_t>& deletionQueue = chunkHandler.getDeletionQueue();
    for (int i = 0; i<deletionQueue.size(); i++)
    {
        const uint16_t fixedIndex = deletionQueue[i] - i;
        vboHandler.removeBuffer(fixedIndex);
    }

    deletionQueue.clear();
    
    animationHandler.constructTileBuffer(chunkHandler);
    entity.constructTileBuffer(chunkHandler);
    layer.constractBuffer(chunkHandler);

}
