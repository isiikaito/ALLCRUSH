/*!
@file GageSprite.cpp
@brief �Q�[�W�̎���a
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	constexpr float HELFSIZE = 0.5f;//!�|���S���T�C�Y
	constexpr float STARTSCALEZ = 1.0f;//!z�̑傫��

	//�Q�[�W

	GageSpriteWhite::GageSpriteWhite(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0),
		m_TextureColor(Col4(1.0f, 1.0f, 1.0f, 1.0f))
	{}

	GageSpriteWhite::~GageSpriteWhite() {}
	void GageSpriteWhite::OnCreate() {
		//���_�z��
		m_BackupVertices = {
			//�J���[�@�����x
           { VertexPositionColor(Vec3(-HELFSIZE, HELFSIZE, 0),m_TextureColor) },
           { VertexPositionColor(Vec3(HELFSIZE, HELFSIZE, 0), m_TextureColor) },
           { VertexPositionColor(Vec3(-HELFSIZE, -HELFSIZE, 0), m_TextureColor) },
           { VertexPositionColor(Vec3(HELFSIZE, -HELFSIZE, 0), m_TextureColor) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//��������
		SetAlphaActive(m_Trace);
		//������
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, STARTSCALEZ);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);
	}
}