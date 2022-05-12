#pragma once
#include "mysoundengine.h"


class SoundFX
{
protected:
	static const int NUMEXPLOSIONSOUNDS = 5;
	SoundIndex m_Explosions[NUMEXPLOSIONSOUNDS];
	SoundIndex m_Engine;
	SoundIndex m_Shot;
	SoundIndex m_Select;
	SoundIndex m_Launch;
	SoundIndex m_Alert;
	bool m_isEnginePlaying;
	bool m_isAlertPlaying;

public:
	SoundFX();
	~SoundFX();
	void LoadSounds();
	void PlayShot();
	void PlayExplosion();
	void PlayLaunch();
	void PlaySelect();
	void StartPlayingEngineSound();
	void StopPlayingEngineSound();
	void StartPlayingAlertSound();
	void StopPlayingAlertSound();
	void SetEngineVolume(int volume);
	void SetAlertVolume(int volume);

};