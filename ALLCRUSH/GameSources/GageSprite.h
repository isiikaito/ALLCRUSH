/*!
@file GageSprite.h
@brief �Q�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum PowerGage {
		notpower,
		first,
		second,
		treed
	};
	//�Q�[�W
	class GageSprite : public GameObject
	{
		bool m_Trace;		//����
		Vec2 m_StartScale;	//�傫��
		Vec3 m_StartPos;	//�ʒu
		float m_TotalTime;	//���Ԃ̎擾
		int m_BreakCount;   //�ǂ��󂵂���
		int m_PowerON;      //�p���[�A�b�v��
		int m_PowerOFF;     //�p���[�A�b�v���ĂȂ�
		Vec3 firstScale;	//�ǈ�ڂ̑傫��
		Vec3 firstpos;		//�ǈ�ڂ̈ʒu
		Vec3 secondScale;	//�Ǔ�ڂ̑傫��
		Vec3 secondpos;		//�Ǔ�ڂ̈ʒu
		Vec3 treedScale;	//�ǎO�ڂ̑傫��
		Vec3 treedpos;		//�ǎO�ڂ̈ʒu
		Col4 m_TextureColor;//!�e�N�X�`���̐F
		Col4 m_gageTextureColor;//!�Q�[�W�̐F
		vector<VertexPositionColor>m_BackupVertices;//�o�b�N�A�b�v���_�f�[�^

		
	public:
		GageSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~GageSprite();
		virtual void OnCreate() override;//������
		virtual void OnUpdate()override; //�X�V

	};
}