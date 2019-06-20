#pragma once

#include <SDL_mixer.h>
#include <string>

class SoundManager
{
public:	
	~SoundManager();
	static SoundManager* GetInstance();
	void Init();
	void PlaySound(Mix_Music* sound, int loops);
	bool LoadSound(std::string path);
	void PlayBackgroundMusic();
	bool LoadBackgroundMusic();

private:
	SoundManager();

	Mix_Music* m_Sound;
	bool m_IsInitSuccess;

	static SoundManager* m_Instance;
};