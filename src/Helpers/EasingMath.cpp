#include "EasingMath.h"
#include <cmath>

const float mUtils::easeInOutExpo(float x)
{
    return x < 0.5f ? std::pow(2.0f, 20.0f * x - 10.0f) / 2.0f : (2.0f - std::pow(2.0f, -20.0f * x + 10.0f)) / 2.0f; 
}
