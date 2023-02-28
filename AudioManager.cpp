#include "main.h"
#include "manager.h"
#include "AudioManager.h"

std::unordered_map<std::string, class Audio*> AudioManager::m_BGMAudio;
std::unordered_map<std::string, class Audio*> AudioManager::m_SEAudio;
// BGMの音量
float AudioManager::m_BGMVolume;
// SEの音量
float AudioManager::m_SEVolume;

// Audioのファイル読み込みを事前にロードするための関数
// unordered_mapを使って各Audioクラスの情報を入れています
void AudioManager::Load()
{
	m_BGMAudio["BGMTitleSea"] = new Audio();
	m_BGMAudio["BGMTitleSea"]->Load("asset\\Sounds\\BGM\\BGM_TitleSea.wav");

	m_BGMAudio["BGMBoss"] = new Audio();
	m_BGMAudio["BGMBoss"]->Load("asset\\Sounds\\BGM\\BGM_Boss.wav");

	m_BGMAudio["BGMMinion"] = new Audio();
	m_BGMAudio["BGMMinion"]->Load("asset\\Sounds\\BGM\\BGM_Minion.wav");

	m_BGMAudio["BGMResult"] = new Audio();
	m_BGMAudio["BGMResult"]->Load("asset\\Sounds\\BGM\\BGM_Result.wav");

	m_SEAudio["SEClickButton"] = new Audio();
	m_SEAudio["SEClickButton"]->Load("asset\\Sounds\\SE\\SE_ClickButton.wav");

	m_SEAudio["SEClick"] = new Audio();
	m_SEAudio["SEClick"]->Load("asset\\Sounds\\SE\\SE_Click.wav");

	m_SEAudio["SECursor"] = new Audio();
	m_SEAudio["SECursor"]->Load("asset\\Sounds\\SE\\SE_ChangeCursor.wav");

	m_SEAudio["SEAttack01"] = new Audio();
	m_SEAudio["SEAttack01"]->Load("asset\\Sounds\\SE\\SE_SwordAttack01.wav");

	m_SEAudio["SEAttack02"] = new Audio();
	m_SEAudio["SEAttack02"]->Load("asset\\Sounds\\SE\\SE_SwordAttack02.wav");

	m_SEAudio["SEAttack03"] = new Audio();
	m_SEAudio["SEAttack03"]->Load("asset\\Sounds\\SE\\SE_SwordAttack03.wav");

	m_SEAudio["SEActivateFail"] = new Audio();
	m_SEAudio["SEActivateFail"]->Load("asset\\Sounds\\SE\\SE_ActivateFail.wav");

	m_SEAudio["SEActivateUlt"] = new Audio();
	m_SEAudio["SEActivateUlt"]->Load("asset\\Sounds\\SE\\SE_ActivateUlt.wav");

	m_SEAudio["SEBlock"] = new Audio();
	m_SEAudio["SEBlock"]->Load("asset\\Sounds\\SE\\SE_Block.wav");

	m_SEAudio["SEHitEnemy"] = new Audio();
	m_SEAudio["SEHitEnemy"]->Load("asset\\Sounds\\SE\\SE_HitEnemy.wav");

	m_SEAudio["SEPauseButton"] = new Audio();
	m_SEAudio["SEPauseButton"]->Load("asset\\Sounds\\SE\\SE_PauseButton.wav");

	m_SEAudio["SEShootSword"] = new Audio();
	m_SEAudio["SEShootSword"]->Load("asset\\Sounds\\SE\\SE_ShootSword.wav");

	m_SEAudio["SEUltLastAtk"] = new Audio();
	m_SEAudio["SEUltLastAtk"]->Load("asset\\Sounds\\SE\\SE_UltLastAtk.wav");

	m_SEAudio["SEZombie"] = new Audio();
	m_SEAudio["SEZombie"]->Load("asset\\Sounds\\SE\\SE_ZombieSound.wav");

	m_SEAudio["SEBossLand"] = new Audio();
	m_SEAudio["SEBossLand"]->Load("asset\\Sounds\\SE\\SE_BossLandGround.wav");

	m_SEAudio["SEBossRage01"] = new Audio();
	m_SEAudio["SEBossRage01"]->Load("asset\\Sounds\\SE\\SE_BossRageAtk01.wav");

	m_SEAudio["SEBossRage02"] = new Audio();
	m_SEAudio["SEBossRage02"]->Load("asset\\Sounds\\SE\\SE_BossRageAtk02.wav");

	m_SEAudio["SEBossScream"] = new Audio();
	m_SEAudio["SEBossScream"]->Load("asset\\Sounds\\SE\\SE_BossScream.wav");

	m_SEAudio["SEMeteorExplode"] = new Audio();
	m_SEAudio["SEMeteorExplode"]->Load("asset\\Sounds\\SE\\SE_MeteorExplode.wav");


	// BGMの音量初期化
	SetVolumeBGM(0.3f);
	// SEの音量初期化
	SetVolumeSE(0.4f);
}

// Audioのファイルを最後に解放するための関数
void AudioManager::Unload()
{
	// for文でunordered_mapの中のAudioクラスを全部終了処理します
	for (auto P : m_BGMAudio)
	{
		P.second->Uninit();
		delete P.second;
	}
	// unordered_mapの中のデータを解放します
	m_BGMAudio.clear();

	// for文でunordered_mapの中のAudioクラスを全部終了処理します
	for (auto P : m_SEAudio)
	{
		P.second->Uninit();
		delete P.second;
	}
	// unordered_mapの中のデータを解放します
	m_SEAudio.clear();
}

// Audioをプレイします
// _NameはプレイするAudioの名前、_Loopはループするかどうか
void AudioManager::PlayBGM(std::string _Name, bool _Loop)
{
	m_BGMAudio[_Name]->Play(_Loop);
}
// _NameはプレイするAudioの名前、_Loopはループするかどうか
void AudioManager::PlaySE(std::string _Name)
{
	m_SEAudio[_Name]->Play();
}

// Audioを止めます
// _NameはどのAudioを止める
void AudioManager::StopBGM(std::string _Name)
{
	m_BGMAudio[_Name]->Stop();
}
// _NameはどのAudioを止める
void AudioManager::StopSE(std::string _Name)
{
	m_SEAudio[_Name]->Stop();
}
void AudioManager::SetVolumeBGM(float _Vol)
{
	// for文で回す
	for (auto B : m_BGMAudio)
	{
		B.second->SetVolume(_Vol);
	}

	// BGMの音量を記録します
	m_BGMVolume = _Vol;
}
void AudioManager::SetVolumeSE(float _Vol)
{
	// for文で全部を調整する
	for (auto S : m_SEAudio)
	{
		S.second->SetVolume(_Vol);
	}

	// SEの音量を記録します
	m_SEVolume = _Vol;
}
// Audioを一時的に止める
// _NameはどのAudioを止める
//// （まだ調整中）
//void AudioManager::Pause(std::string _Name)
//{
//	m_Audio[_Name]->Pause();
//}
//
//// Audioを再開します
//// _NameはどのAudioを再開する、_LoopはそのAudioをループしますか
//// （まだ調整中）
//void AudioManager::Resume(std::string _Name, bool _Loop)
//{
//	m_Audio[_Name]->Play(_Loop);
//}
