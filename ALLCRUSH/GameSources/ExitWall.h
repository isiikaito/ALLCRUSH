/**
*@file ExitWall.h
*@brief �o���̕ǂ̎�������`����Ă���w�b�_�[�t�@�C��
*@author Kaito Isii
*@details �o���̕ǂ̎���
*/

#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {

	class ExitWall : public GameObject {
		StaticModelDeta m_exitWallModelData;//!�o���̃��f���f�[�^

	public:

		/**
		* �R���X�g���N�^
		*/
		ExitWall(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
�@�@�@�@* �f�X�g���N�^
�@�@�@�@*/
		virtual ~ExitWall() {}

		/**
		* �o���̕ǂ̏����p�����[�^������������֐�
		*/
		virtual void OnCreate() override;

	};
}
