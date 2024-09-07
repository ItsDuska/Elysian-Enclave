#include "AnimationCache.h"
#include <fstream>


void AnimationCache::awake(const sf::Vector2i frameSize, const sf::Vector2i textureSize,std::string& filepath)
{
    if (built)
    {
        return;
    }

    //frameCounts = { 0,6,2 }; // the fist value is NULL
    frameCounts = { 0 };
    this->frameSize = frameSize;
    this->textureSize = textureSize;
    widthInTiles = textureSize.x / frameSize.x;
    built = true;


    //const char* filepath = "data/texture/animationFrames.data";
    std::string fullFilePath = filepath + ".data";


    std::ifstream file(fullFilePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << fullFilePath << std::endl;
        return;
    }

    int frameCount;
    while (file >> frameCount)
    {
        frameCounts.push_back(frameCount);
    }

    file.close();


    precomputeStartPositions();
}

sf::Vector2i AnimationCache::getAnimationFrame(int animationIndex, int frame) const
{
    if (animationIndex == 0)
    {
        return sf::Vector2i(0, 0);
    }

    if (animationIndex >= startPositions.size())
    {
        std::cerr << "INFO: AnimationIndex to frames is too big... Your index is: " << animationIndex << "\n";
        animationIndex = 0;
    }

    sf::Vector2i startPos = startPositions[animationIndex];
    int frameCount = frameCounts[animationIndex]-1;

    if (frame == frameCount)
    {
        startPos.x += 1;

        if (startPos.x * frameSize.x > textureSize.x)
        {
            // Move to the next row
            startPos.x = 0;
            startPos.y += 1;
        }
    }

    return startPos;
}

std::vector<sf::Vector2i>* AnimationCache::getStartPositionsPtr()
{
    return &startPositions;
}

int AnimationCache::getStartPosition(int index)
{
    if (index >= startPositions.size()) {
        //std::cerr << "guh? in animation buh\n";
        return 0;
    }
    sf::Vector2i position = startPositions[index];
    return position.y * widthInTiles + position.x;
}

int AnimationCache::getMaxSprites()
{
    return frameCounts.size();
}

int AnimationCache::getAnimationFrameCount(int animationIndex)
{
    if (animationIndex <= 0 || animationIndex >= frameCounts.size()) {
        //std::cerr << "sussy Animation number: returning 0. Your number is " << animationIndex << "\n";
        return 0;
    }
    return frameCounts[animationIndex];
}

void AnimationCache::precomputeStartPositions()
{
    startPositions.push_back(sf::Vector2i(NULL, NULL)); // NULL Value.

    int x = 16; 
    int y = 0;

    for (int i = 1; i < frameCounts.size(); ++i)
    {
        if (x + frameCounts[i] * frameSize.x > textureSize.x)
        {
            x = 1; // Aloita seuraavalta rivilt�
            y += frameSize.y;
        }

        startPositions.push_back(sf::Vector2i(x/16, y/16));
        std::cout << i << " : values are |" << x/16 << "x " << y/16 << "y\n";
        x += frameCounts[i] * frameSize.x;
    }
}
