/**
*@file StageFloor.cpp
*@brief �X�e�[�W�̏����̂���������Ă���\�[�X�t�@�C��
*@author Kaito Isii
*@details �X�e�[�W�̏����̂̎���
*/

#include "stdafx.h"
#include "Project.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {
	//!�p�����[�^�̏�����
	StageFloor::StageFloor(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_floorModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(0.045f, 1.0f, 0.13f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),   
				Vec3(0.0f, 0.0f, -0.05f),  
				L"STAGEFLOOR_MESH"

			}
		)

	{}

	void StageFloor::OnCreate()
	{
		AddComponent<StaticModelComponent>(m_floorModelData);//!���f���f�[�^����

	}

}