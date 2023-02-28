
#include "main.h"
#include "audio.h"





IXAudio2*				Audio::m_Xaudio = NULL;
IXAudio2MasteringVoice*	Audio::m_MasteringVoice = NULL;

void Audio::InitMaster()
{
	// COM初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio生成
	XAudio2Create(&m_Xaudio, 0);

	// マスタリングボイス生成
	m_Xaudio->CreateMasteringVoice(&m_MasteringVoice);
}


void Audio::UninitMaster()
{
	m_MasteringVoice->DestroyVoice();
	m_Xaudio->Release();
	CoUninitialize();
}









void Audio::Load(const char *FileName)
{

	// サウンドデータ読込
	WAVEFORMATEX wfx = { 0 };

	{
		HMMIO hmmio = NULL;
		MMIOINFO mmioinfo = { 0 };
		MMCKINFO riffchunkinfo = { 0 };
		MMCKINFO datachunkinfo = { 0 };
		MMCKINFO mmckinfo = { 0 };
		UINT32 buflen;
		LONG readlen;


		hmmio = mmioOpen((LPSTR)FileName, &mmioinfo, MMIO_READ);
		assert(hmmio);

		riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

		mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(hmmio, (HPSTR)&wfx, sizeof(wfx));
		}
		else
		{
			PCMWAVEFORMAT pcmwf = { 0 };
			mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
			memset(&wfx, 0x00, sizeof(wfx));
			memcpy(&wfx, &pcmwf, sizeof(pcmwf));
			wfx.cbSize = 0;
		}
		mmioAscend(hmmio, &mmckinfo, 0);

		datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		

		buflen = datachunkinfo.cksize;
		m_SoundData = new unsigned char[buflen];
		readlen = mmioRead(hmmio, (HPSTR)m_SoundData, buflen);


		m_Length = readlen;
		m_PlayLength = readlen / wfx.nBlockAlign;


		mmioClose(hmmio, 0);
	}


	// サウンドソース生成
	for (int j = 0; j < SOUND_SOURCE_MAX; j++)
	{
		m_Xaudio->CreateSourceVoice(&m_SourceVoice[j], &wfx);
		assert(m_SourceVoice[j]);
	}
}


void Audio::Uninit()
{


	for (int i = 0; i < SOUND_SOURCE_MAX; i++)
	{
		m_SourceVoice[i]->Stop();
		m_SourceVoice[i]->DestroyVoice();
	}
	
	delete[] m_SoundData;
}





int Audio::Play(bool Loop)
{
	for (int i = 0; i < SOUND_SOURCE_MAX; i++)
	{
		XAUDIO2_VOICE_STATE state;
		m_SourceVoice[i]->GetState(&state);
		
		if (state.BuffersQueued == 0)
		{
			//m_SourceVoice[i]->Stop();
			//m_SourceVoice[i]->FlushSourceBuffers();


			// バッファ設定
			XAUDIO2_BUFFER bufinfo;

			memset(&bufinfo, 0x00, sizeof(bufinfo));
			bufinfo.AudioBytes = m_Length;
			bufinfo.pAudioData = m_SoundData;
			bufinfo.PlayBegin = 0;
			bufinfo.PlayLength = m_PlayLength;

			// ループ設定
			if (Loop)
			{
				bufinfo.LoopBegin = 0;
				bufinfo.LoopLength = m_PlayLength;
				bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
			}

			// 再生
			m_SourceVoice[i]->SubmitSourceBuffer(&bufinfo, NULL);

			/*
				float outputMatrix[4] = { 0.0f , 0.0f, 1.0f , 0.0f };
				m_SourceVoice->SetOutputMatrix(m_MasteringVoice, 2, 2, outputMatrix);
				m_SourceVoice->SetVolume(0.01f);
			*/
			m_SourceVoice[i]->Start();

			return i;
		}

	}
	return 0;
}

void Audio::Stop()
{
	for (int j = 0; j < SOUND_SOURCE_MAX; j++)
	{
		m_SourceVoice[j]->Stop();
	}
}

void Audio::Resume()
{
	for (int j = 0; j < SOUND_SOURCE_MAX; j++)
	{
		m_SourceVoice[j]->Start();
	}
}

void Audio::Pause()
{
	for (int j = 0; j < SOUND_SOURCE_MAX; j++)
	{
		m_SourceVoice[j]->Stop(XAUDIO2_PLAY_TAILS);
	}
}



