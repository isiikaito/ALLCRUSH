/*!
@file XSprite.h
@brief �A�C�e���{�^��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class XSprite : public GameObject {
		bool m_Trace;        //����
		Vec2 m_StartScale;   //�傫��
		Vec3 m_StartPos;     //�ʒu
		wstring m_TextureKey;//�e�N�X�`��
		float m_TotalTime;   //���Ԃ̎擾
		vector<VertexPositionTexture> m_BackupVertices;//�o�b�N�A�b�v���_�f�[�^
		const Vec2 m_LeftUpperSummit;	//!����̒��_
		const Vec2 m_LeftLowerSummit;	//!�����̒��_
		const Vec2 m_RightUpperSummit;	//!�E��̒��_
		const Vec2 m_RightLowerSummit;	//!�E���̒��_
	public:

		XSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		//�f�X�g���N�^
		virtual ~XSprite();
		//������
		virtual void OnCreate() override;

	};
}