/*!
@file MenuSprite1.h
*@author Kaito Isii
@brief ����
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	
	class MenuSprite1 : public GameObject {
		bool m_Trace;        //����
		Vec2 m_StartScale;   //�傫��
		Vec3 m_StartPos;     //�ʒu
		wstring m_TextureKey;//�e�N�X�`��
		float m_idleTime;    //���Ԃ̎擾
		
		//�o�b�N�A�b�v���_�f�[�^
		vector< VertexPositionColorTexture> m_BackupVertices;
	public:
		
		MenuSprite1(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		
		virtual ~MenuSprite1();
		
		virtual void OnCreate() override;
		
		
	
	};
}