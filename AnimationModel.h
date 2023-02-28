#pragma once

#include <unordered_map>

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#pragma comment (lib, "assimp.lib")

// 変形後頂点構造体
struct DEFORM_VERTEX
{
	aiVector3D		Position;
	aiVector3D		Normal;
	int				BoneNum;
	std::string		BoneName[4];	// 本来はボーンインデックスで管理するべき
	float			BoneWeight[4];
};

// ボーン構造体
struct BONE
{
	aiMatrix4x4		Matrix;
	aiMatrix4x4		AnimationMatrix;
	aiMatrix4x4		OffsetMatrix;
};

class AnimationModel
{
private:
	bool m_isBlending = false;

	const aiScene* m_AiScene = NULL;
	std::unordered_map<std::string, const aiScene*> m_Animation;

	ID3D11Buffer** m_VertexBuffer;
	ID3D11Buffer** m_IndexBuffer;
	
	D3DXVECTOR3 m_Size;	// サイズ

	std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture;

	std::vector<DEFORM_VERTEX>* m_DeformVertex;	// 変形後頂点データ
	std::unordered_map<std::string, BONE>m_Bone;	// ボーンデータ（名前で参照）

	std::unordered_map<std::string, float>m_Duration; // アニメーションの長さ

	// モデルの全ての頂点座標
	std::vector<D3DXVECTOR3> m_VertexPosition;
	
	void CreateBone(aiNode* node);
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);

public:
	void Load(const char* FileName);
	void LoadAnimation(	const char *FileName,
						const char *AnimationName);
	void Unload();
	void Update(const char *AnimationName1, const char *AnimationName2, float BlendRate, int Frame1, int Frame2);
	void Draw();
	bool GetBlend() { return m_isBlending; }
	float GetDuration(const char* AnimationName)
	{
		return m_Duration[AnimationName];
	}
	D3DXVECTOR3 GetModelSize()
	{
		return m_Size;
	}
	
	void CopyInformation(AnimationModel* AM)
	{
		m_Animation = AM->m_Animation;
		m_AiScene = AM->m_AiScene;
		m_VertexBuffer = AM->m_VertexBuffer;
		m_IndexBuffer = AM->m_IndexBuffer;
		m_Size = AM->m_Size;
		m_Texture = AM->m_Texture;
		m_DeformVertex = AM->m_DeformVertex;
		m_Bone = AM->m_Bone;
		m_Duration = AM->m_Duration;
	}
};

