#pragma once
#include <bitset>

constexpr int MAX_COMPONENTS = 8*14;
constexpr int MAX_ENTITIES = 64;

typedef uint32_t EntityIndex;
typedef uint32_t EntityVersion;
typedef uint64_t EntityID;
typedef std::bitset<MAX_COMPONENTS> ComponentMask;

namespace util
{
	extern int componentCounter;
	template <class T>
	int generateNewID()
	{
		static int componentId = componentCounter++;
		return componentId;
	}
}

