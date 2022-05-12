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
	m_Alert = pSoundEngine->LoadWav(L"alert.wav");
	m_Launch = pSoundEngine->LoadWav(L"launch.wav");
	m_Select = pSoundEngine->LoadWav(L"select.wav");
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

void SoundFX::PlayLaunch()
{
	MySoundEngine::GetInstance()->Play(m_Launch);
}

void SoundFX::PlaySelect()
{
	MySoundEngine::GetInstance()->Play(m_Select);

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

void SoundFX::StartPlayingAlertSound()
{
	if (!m_isAlertPlaying)
	{
		MySoundEngine::GetInstance()->Play(m_Alert, true);
	}
	m_isAlertPlaying = true;
}

void SoundFX::StopPlayingAlertSound()
{
	if (m_isAlertPlaying)
	{
		MySoundEngine::GetInstance()->Stop(m_Alert);
	}
	m_isAlertPlaying = false;
}

void SoundFX::SetEngineVolume(int volume)
{
	volume = (volume - 100) * 35;
	MySoundEngine::GetInstance()->SetVolume(m_Engine, volume);
}

void SoundFX::SetAlertVolume(int volume)
{
	volume = (volume - 100) * 35;
	MySoundEngine::GetInstance()->SetVolume(m_Alert, volume);
}


