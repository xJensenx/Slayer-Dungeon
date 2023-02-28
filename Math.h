#pragma once
#include "main.h"
#include <random>
#include <math.h>

class Math
{
public:
	static D3DXQUATERNION QuaternionLookAt(D3DXVECTOR3 TargetPos, D3DXVECTOR3 SelfPos)
	{
		// 方向を計算します
		D3DXVECTOR3 TarDir = TargetPos - SelfPos;
		// 方向を標準化します
		D3DXVec3Normalize(&TarDir, &TarDir);
		// 上方向を設置します
		D3DXVECTOR3 Norm = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// 外積を求めます
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &Norm, &TarDir);
		// 外積の標準化
		D3DXVec3Normalize(&Cross, &Cross);
		// 内積を求めます
		float Dot = D3DXVec3Dot(&Norm, &TarDir);
		// Quaternionに代入する
		D3DXQUATERNION Q;
		// 角度計算します
		float Rad = acosf(Dot);
		D3DXQuaternionRotationAxis(&Q, &Cross, Rad);
		return Q;
	}

	static float FloatRandBetween(float Range1, float Range2)
	{
		std::random_device rnd;
		std::mt19937 mt(rnd());
		std::normal_distribution<> Rand(Range1, Range2);
		return (float)Rand(mt);
	}
	static int IntRandBetween(int Range1, int Range2)
	{
		std::random_device rnd;
		std::mt19937 mt(rnd());
		std::uniform_int_distribution<> Rand(Range1, Range2);
		return Rand(mt);
	}
	static float Distance(D3DXVECTOR3 V1, D3DXVECTOR3 V2)
	{
		D3DXVECTOR3 V3 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		V3.x = (V1.x - V2.x) * (V1.x - V2.x);
		V3.y = (V1.y - V2.y) * (V1.y - V2.y);
		V3.z = (V1.z - V2.z) * (V1.z - V2.z);

		float Length = sqrtf(V3.x + V3.y + V3.z);

		return Length;
	}

	static float PI()
	{
		return D3DX_PI;
	}

	static float RadToDeg()
	{
		return PI() / 180.0f;
	}

	static float RotateTowards(D3DXVECTOR3 TargetPos, D3DXVECTOR3 SelfPos)
	{
		D3DXVECTOR3 DirOfPlayer = TargetPos - SelfPos;
		D3DXVECTOR3 DirNormalize;
		D3DXVec3Normalize(&DirNormalize, &DirOfPlayer);
		float RotateAngle = atan2f(DirNormalize.x, DirNormalize.z);

		return RotateAngle;
	}

	static float RandNorma()
	{
		return (float)rand() / (float)RAND_MAX;
	}

	static D3DXVECTOR2 GetVectorXZ(D3DXVECTOR3 Vec3)
	{
		D3DXVECTOR2 ReturnVal;
		ReturnVal.x = Vec3.x;
		ReturnVal.y = Vec3.z;

		return ReturnVal;
	}

	static float FloatLerp(float From, float To, float T)
	{
		return From + T * (To - From);
	}

	static float GetLerpTime(float From, float To, float Cur)
	{
		return ((Cur - From) / (To - From));
	}

	static float GetAngle(float Y, float X)
	{
		float RotateAngle = atan2f(Y, X);
		return RotateAngle;
	}

	static D3DXVECTOR2 Vector2RotateAngle(D3DXVECTOR2 V1, float Angle)
	{
		float s, c, rad;
		rad = Angle * 6.28f / 360;
		s = sinf(rad);
		c = cosf(rad);

		D3DXVECTOR2 v_ret = { V1.x * c - V1.y * s, V1.x * s + V1.y * c };
		return v_ret;
	}

	static float NpExp(float Val)
	{
		return powf(2.71828182845904523536028747135266249775724709369995f, Val);
	}

	static float Sigmoid(float X)
	{
		return 1.0f / (1.0f + NpExp(-X));
	}

	static D3DXVECTOR3 CalculateTowardsRotation(D3DXVECTOR3 V1, D3DXVECTOR3 V2)
	{
		D3DXVECTOR3 Dir = V2 - V1;
		D3DXVec3Normalize(&Dir, &Dir);

		float ValX, ValY, ValZ;
		float X, Y, Z;
		X = Dir.z;
		Y = Dir.x;
		Z = Dir.y;

		ValY = Sigmoid(Y) * (acosf(X / (sqrtf(powf(X, 2) + powf(Y, 2)))));
		ValZ = acosf((Z) / (sqrtf(powf(X, 2) + powf(Y, 2) + powf(Z, 2))));

		//ValX = sqrtf(powf(X, 2) + powf(Y, 2) + powf(Z, 2));

		ValX = atan2f(Dir.y, Dir.z);

		return D3DXVECTOR3(ValX, ValY, ValZ);

	}
};