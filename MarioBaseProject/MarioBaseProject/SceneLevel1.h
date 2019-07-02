#pragma once

#include "Commons.h"
#include "SDL.h"
#include "Scene.h"
#include <vector>


class Texture2D; // promise to compiler
class Character;
class CharacterMario;
class LevelMap;
class PowBlock;
class CharacterKoopa;
class CharacterAnimated;
// what if we dont

class SceneLevel1 : Scene
{
public:
	SceneLevel1();
	SceneLevel1(SDL_Renderer* renderer);
	~SceneLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdatePowBlock(float deltaTime);
	void DoScreenShake();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D pos, DIRECTION direction, float speed);
	void CreateCharacterAnimated(Vector2D pos);

private:
	Texture2D* m_BackgroundTex;
	bool SetLevel();
	CharacterMario* m_Mario;
	CharacterAnimated* m_Animated;
	void SetLevelMap();
	LevelMap* m_LevelMap;
	PowBlock* m_PowBlock;
	std::vector<CharacterKoopa*> m_Enemies;
};
