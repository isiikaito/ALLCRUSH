/*!
@file Wall.h
@brief �ǂ̎���
*@author Kaito Isii
*/

#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"
namespace basecross {

	class Wall : public GameObject {
		
		int m_HP;										//�ǂ�HP
		StaticModelDeta m_wallModelData;				//!�ǂ̃��f���f�[�^
		Vec3 m_playerPos;								//�v���C���[�̍��W
		Vec3 m_cameraPos;								//�J�����̍��W
		Vec3 modelScale;								//!���b�V���̑傫��
		Vec3 modelRotOrigin;							//!��]�̋N��
		Vec3 modelRotation;								//!���b�V���̉�]
		Vec3 modelPosition;								//!���b�V���̈ʒu
		weak_ptr<Transform> m_palyerTransform;			//�v���C���\�̃g�����X�t�H�[��
		weak_ptr<PNTStaticModelDraw> m_wallModelDraw;	//�ǂ̃��f���̕`��f�[�^
		InputHandler2<Wall> m_InputHandler;				//���̓n���h���[

		void WallChangeMesh(wstring meshName);					//!�ǂ̃��b�V���̕ύX
	public:
		//�\�z�Ɣj��
		Wall(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const int HP
		);
		
		//������
		virtual void OnCreate() override;

		//�R���g���[���[�̃{�^������X
		void OnPushX(){}
		//�R���g���[���[�̃{�^������A
		void OnPushA() {}   
		//�R���g���[���[�̃{�^������\���L�[��
		void OnPushUP() {}  
		//�R���g���[���[�̃{�^������\���L�[��
		void OnPushDOWN() {} 
		//�R���g���[���[�̃{�^������Y
		void OnPushY(){}     
		//�R���g���[���[�̃{�^������B
		void OnPushB(){}     
		//�X�V
		void OnUpdate();

		//HP�̎擾
		int GetHP()const {
			return m_HP;
		}
		//HP�̊Ǘ�
		void SetHP(int HP) {
			m_HP = HP;
		}
	};

}
// namespace basecross
