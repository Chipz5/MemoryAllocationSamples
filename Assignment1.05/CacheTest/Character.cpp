#include "Vector3.h"
#include "Utilities.h"
#include "Vector4.h"
#include "Timing/Timing.h"
#include "Component.cpp"

using namespace Engine;

const size_t numChar = 8192;

struct character
{
	Engine::Vector4 position;
	Engine::Vector4 velocity;

	unsigned int health;
	unsigned int lives;
	unsigned int strength;
	unsigned int mana;

	double mass;
	double drag;

	char name[64];
	Component* components[16];

	void processVelocity(const Engine::Vector4& newVelocity) {
		velocity = newVelocity;
		position += newVelocity;
	}
	
};

struct characterData 
{
	unsigned int health;
	unsigned int lives;
	unsigned int strength;
	unsigned int mana;

	double mass;
	double drag;

	char name[64];
	Component* components[16];
};

struct fastCharacter
{
	Engine::Vector4 position;
	Engine::Vector4 velocity;
	characterData* charData;

	void processVelocity(const Engine::Vector4& newVelocity) {
		velocity = newVelocity;
		position += newVelocity;
	}
};

struct hotData
{
	Engine::Vector4 position;
	Engine::Vector4 velocity;
	void processVelocity(const Engine::Vector4& newVelocity) {
		velocity = newVelocity;
		position += newVelocity;
	}
};

struct SoACharacterData
{
	hotData hotDatas[numChar];
	characterData charDatas[numChar];
};