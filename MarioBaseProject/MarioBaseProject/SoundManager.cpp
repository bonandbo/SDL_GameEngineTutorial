#include "SoundManager.h"
#include "Constants.h"

SoundManager* SoundManager::m_Instance = nullptr;

SoundManager* SoundManager::GetInstance()
{
	if (!m_Instance)
		m_Instance = new SoundManager();
	return m_Instance;
}

SoundManager::SoundManager()
{
	m_IsInitSuccess = false;
	//Init();
	//LoadBackgroundMusic();
}

void SoundManager::Init() // why void => want to avoid stop game if sound is not loaded. Up to you btw
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("Failed to init sound. E:%s", Mix_GetError());
		m_IsInitSuccess = false;
	}
	else
	{
		m_IsInitSuccess = true;
	}
}

bool SoundManager::LoadSound(std::string path)
{
	if (m_IsInitSuccess && !m_Sound)
	{
		m_Sound = Mix_LoadMUS(path.c_str());
		if (!m_Sound)
		{
			LOG("Error when load file: %s, E:%s", path.c_str(), Mix_GetError());
			return false;
		}
		return true;
	}
	return false;
}

bool SoundManager::LoadBackgroundMusic()
{
	return LoadSound(std::string(FOLDER_MUSIC).append("/").append(BACKGROUND_VOX));
}

void SoundManager::PlayBackgroundMusic()
{
	PlaySound(m_Sound, -1);
}

void SoundManager::PlaySound(Mix_Music* sound, int loops)
{
	if (m_IsInitSuccess)
	{
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(sound, loops);
		}
	}
}

SoundManager::~SoundManager()
{
	if (m_Instance)
	{
		m_Instance = nullptr;
	}
	if (m_Sound)
	{
		Mix_FreeMusic(m_Sound);
		m_Sound = nullptr;
	}
}