#pragma once
#include <unordered_map>
#include "audio.h"

class AudioManager : public Audio
{
private:
	// BGMのAudio
	static std::unordered_map<std::string, class Audio*> m_BGMAudio;
	// SEのAudio
	static std::unordered_map<std::string, class Audio*> m_SEAudio;
	// BGMの音量
	static float m_BGMVolume;
	// SEの音量
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

	// BGMの音量を取得
	static float GetVolumeBGM() { return m_BGMVolume; }
	// SEの音量を取得
	static float GetVolumeSE() { return m_SEVolume; }
};