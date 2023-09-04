/**
*@file StageWall.cpp
*@brief�o���̕ǂ̎��̂���������Ă���\�[�X�t�@�C��
*@author Kaito Isii
*@details �o���̕ǂ̎��̂̎���
*/

#include "stdafx.h"
#include "Project.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {
	//!�p�����[�^�̏�����
	ExitWall::ExitWall(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_exitWallModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(1.0f, 0.15f, 0.08),
				Vec3(0.0f, 5.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f), 
				Vec3(0.0f, -0.8f, 0.0f),
				L"EXITWALL_MESH"
			}
		)
	{}


	
	void ExitWall::OnCreate() 
	{
		AddComponent<StaticModelComponent>(m_exitWallModelData);	//!���f���f�[�^����

	}

}