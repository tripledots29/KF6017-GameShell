#pragma once
#include "mysoundengine.h"

class SoundFX
{
private:
	static const int NUMEXPLOSIONSOUNDS = 5;
	SoundIndex m_Explosions[NUMEXPLOSIONSOUNDS];
	SoundIndex m_Engine;
	SoundIndex m_Shot;
	bool m_isEnginePlaying;

public:
	SoundFX();
	~SoundFX();
	void LoadSounds();
	void PlayShot();
	void PlayExplosion();
	void StartPlayingEngineSound();
	void StopPlayingEngineSound();
	void SetEngineVolume(int volume);
};