#include "main.h"
#include "manager.h"
#include "AudioManager.h"

std::unordered_map<std::string, class Audio*> AudioManager::m_BGMAudio;
std::unordered_map<std::string, class Audio*> AudioManager::m_SEAudio;
// BGM�̉���
float AudioManager::m_BGMVolume;
// SE�̉���
float AudioManager::m_SEVolume;

// Audio�̃t�@�C���ǂݍ��݂����O�Ƀ��[�h���邽�߂̊֐�
// unordered_map���g���ĊeAudio�N���X�̏������Ă��܂�
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


	// BGM�̉��ʏ�����
	SetVolumeBGM(0.3f);
	// SE�̉��ʏ�����
	SetVolumeSE(0.4f);
}

// Audio�̃t�@�C�����Ō�ɉ�����邽�߂̊֐�
void AudioManager::Unload()
{
	// for����unordered_map�̒���Audio�N���X��S���I���������܂�
	for (auto P : m_BGMAudio)
	{
		P.second->Uninit();
		delete P.second;
	}
	// unordered_map�̒��̃f�[�^��������܂�
	m_BGMAudio.clear();

	// for����unordered_map�̒���Audio�N���X��S���I���������܂�
	for (auto P : m_SEAudio)
	{
		P.second->Uninit();
		delete P.second;
	}
	// unordered_map�̒��̃f�[�^��������܂�
	m_SEAudio.clear();
}

// Audio���v���C���܂�
// _Name�̓v���C����Audio�̖��O�A_Loop�̓��[�v���邩�ǂ���
void AudioManager::PlayBGM(std::string _Name, bool _Loop)
{
	m_BGMAudio[_Name]->Play(_Loop);
}
// _Name�̓v���C����Audio�̖��O�A_Loop�̓��[�v���邩�ǂ���
void AudioManager::PlaySE(std::string _Name)
{
	m_SEAudio[_Name]->Play();
}

// Audio���~�߂܂�
// _Name�͂ǂ�Audio���~�߂�
void AudioManager::StopBGM(std::string _Name)
{
	m_BGMAudio[_Name]->Stop();
}
// _Name�͂ǂ�Audio���~�߂�
void AudioManager::StopSE(std::string _Name)
{
	m_SEAudio[_Name]->Stop();
}
void AudioManager::SetVolumeBGM(float _Vol)
{
	// for���ŉ�
	for (auto B : m_BGMAudio)
	{
		B.second->SetVolume(_Vol);
	}

	// BGM�̉��ʂ��L�^���܂�
	m_BGMVolume = _Vol;
}
void AudioManager::SetVolumeSE(float _Vol)
{
	// for���őS���𒲐�����
	for (auto S : m_SEAudio)
	{
		S.second->SetVolume(_Vol);
	}

	// SE�̉��ʂ��L�^���܂�
	m_SEVolume = _Vol;
}
// Audio���ꎞ�I�Ɏ~�߂�
// _Name�͂ǂ�Audio���~�߂�
//// �i�܂��������j
//void AudioManager::Pause(std::string _Name)
//{
//	m_Audio[_Name]->Pause();
//}
//
//// Audio���ĊJ���܂�
//// _Name�͂ǂ�Audio���ĊJ����A_Loop�͂���Audio�����[�v���܂���
//// �i�܂��������j
//void AudioManager::Resume(std::string _Name, bool _Loop)
//{
//	m_Audio[_Name]->Play(_Loop);
//}
