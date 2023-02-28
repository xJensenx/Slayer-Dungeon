#pragma once

#include <xaudio2.h>
#include <unordered_map>
#include "gameObject.h"

#define SOUND_SOURCE_MAX (10)

class Audio
{
private:

	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	
	IXAudio2SourceVoice*	m_SourceVoice[SOUND_SOURCE_MAX];
	BYTE*					m_SoundData;

	int						m_Length;
	int						m_PlayLength;


public:
	static void InitMaster();
	static void UninitMaster();

	void Uninit();

	void Load(const char *FileName);
	int Play(bool Loop = false);
	void Stop();
	void Resume();
	void Pause();
	void SetVolume(float _Vol) {
		for (int j = 0; j < SOUND_SOURCE_MAX; j++)
		{
			m_SourceVoice[j]->SetVolume(_Vol);
		}
	}
};

