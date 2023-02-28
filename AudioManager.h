#pragma once
#include <unordered_map>
#include "audio.h"

class AudioManager : public Audio
{
private:
	// BGM��Audio
	static std::unordered_map<std::string, class Audio*> m_BGMAudio;
	// SE��Audio
	static std::unordered_map<std::string, class Audio*> m_SEAudio;
	// BGM�̉���
	static float m_BGMVolume;
	// SE�̉���
	static float m_SEVolume;
public:
	static void Load();
	static void Unload();
	static void PlayBGM(std::string _Name,bool _Loop);
	static void PlaySE(std::string _Name);
	static void StopBGM(std::string _Name);
	static void StopSE(std::string _Name);
	static void SetVolumeBGM(float _Vol);
	static void SetVolumeSE(float _Vol);
	//static void Pause(std::string _Name);
	//static void Resume(std::string _Name,bool _Loop);

	// BGM�̉��ʂ��擾
	static float GetVolumeBGM() { return m_BGMVolume; }
	// SE�̉��ʂ��擾
	static float GetVolumeSE() { return m_SEVolume; }
};