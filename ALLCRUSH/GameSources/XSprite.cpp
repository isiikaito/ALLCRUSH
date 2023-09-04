/*!
@file XSprite.cpp
@brief �A�C�e���{�^��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	constexpr float m_STARTSCALEZ = 1.0f;//!z�̑傫��

	XSprite::XSprite(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0),
		m_LeftUpperSummit(Vec2(0.0f, 0.0f)),
		m_LeftLowerSummit(Vec2(0.0f, 1.0f)),
		m_RightUpperSummit(Vec2(1.0f, 0.0f)),
		m_RightLowerSummit(Vec2(1.0f, 1.0f))
	{}

	XSprite::~XSprite() {}
	void XSprite::OnCreate() {
		float helfSize = 0.5f;
		//���_�z��
		m_BackupVertices = {
			{ VertexPositionTexture(Vec3(-helfSize, helfSize, 0), m_LeftUpperSummit) },
			{ VertexPositionTexture(Vec3(helfSize, helfSize, 0), m_RightUpperSummit) },
			{ VertexPositionTexture(Vec3(-helfSize, -helfSize, 0),m_LeftLowerSummit) },
			{ VertexPositionTexture(Vec3(helfSize, -helfSize, 0),m_RightLowerSummit) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//��������
		SetAlphaActive(m_Trace);

		//�����ʒu�̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, m_STARTSCALEZ);
		ptrTrans->SetPosition(m_StartPos);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

		//�e�N�X�`���̓ǂݍ���
		ptrDraw->SetTextureResource(m_TextureKey);

		//�e�N�X�`���̕\�����I�t�ɂ���
		SetDrawActive(false);

		//�ǂݍ��݂̐ݒ������
		GetStage()->SetSharedGameObject(L"XSprite", GetThis<XSprite>());
	}
}