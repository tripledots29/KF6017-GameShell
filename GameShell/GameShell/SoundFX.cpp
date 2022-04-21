#include "SoundFX.h"
#include "GameObject.h"

SoundFX::SoundFX() 
{
	GameObject::SetSoundFX(this);
}

SoundFX::~SoundFX()
{
	GameObject::SetSoundFX(nullptr);
}

void SoundFX::LoadSounds()
{
	MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();
	m_Shot = pSoundEngine->LoadWav(L"shoot.wav");
	m_Engine = pSoundEngine->LoadWav(L"thrustloop2.wav");
	m_Explosions[0] = pSoundEngine->LoadWav(L"explosion.wav");
	m_Explosions[1] = pSoundEngine->LoadWav(L"explosion1.wav");
	m_Explosions[2] = pSoundEngine->LoadWav(L"explosion2.wav");
	m_Explosions[3] = pSoundEngine->LoadWav(L"explosion3.wav");
	m_Explosions[4] = pSoundEngine->LoadWav(L"explosion4.wav");

}

void SoundFX::PlayShot()
{
	MySoundEngine::GetInstance()->Play(m_Shot);
}

void SoundFX::PlayExplosion()
{
	int choice = rand() % NUMEXPLOSIONSOUNDS;
	MySoundEngine::GetInstance()->Play(m_Explosions[choice]);
}

void SoundFX::StartPlayingEngineSound()
{
	if (!m_isEnginePlaying)
	{
		MySoundEngine::GetInstance()->Play(m_Engine, true);
	}
	m_isEnginePlaying = true;
}

void SoundFX::StopPlayingEngineSound()
{
	if (m_isEnginePlaying)
	{
		MySoundEngine::GetInstance()->Stop(m_Engine);
	}
	m_isEnginePlaying = false;
}

void SoundFX::SetEngineVolume(int volume)
{
	volume = (volume - 100) * 35;
	MySoundEngine::GetInstance()->SetVolume(m_Engine, volume);
}


