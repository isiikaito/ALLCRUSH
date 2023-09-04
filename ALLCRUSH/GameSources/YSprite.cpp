/*!
@file YSprite.cpp
@brief�@�p���[�{�^��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr float HELFSIZE = 0.5f;//!�|���S���T�C�Y
	constexpr int POWERMAX = 3;//!�Q�[�W�̍ő�
	constexpr int GAGEFLASHTRUE = 1;//!�Q�[�W�̓_��
	constexpr float STARTSCALEZ = 1.0f;//!z�̑傫��
	YSprite::YSprite(const shared_ptr<Stage>& StagePtr,
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

	YSprite::~YSprite() {}
	void YSprite::OnCreate() {
		//���_�z��
		m_BackupVertices={
			{ VertexPositionTexture(Vec3(-HELFSIZE, HELFSIZE, 0),m_LeftUpperSummit) },
			{ VertexPositionTexture(Vec3(HELFSIZE, HELFSIZE, 0), m_RightUpperSummit) },
			{ VertexPositionTexture(Vec3(-HELFSIZE, -HELFSIZE, 0), m_LeftLowerSummit) },
			{ VertexPositionTexture(Vec3(HELFSIZE, -HELFSIZE, 0),m_RightLowerSummit) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

		//��������
		SetAlphaActive(m_Trace);

		//�����ʒu�̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, STARTSCALEZ);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

		//�e�N�X�`���̓ǂݍ���
		ptrDraw->SetTextureResource(m_TextureKey);

		//�e�N�X�`���̕\�������Ȃ�
		SetDrawActive(false);

		//�ǂݍ��݂̐ݒ������
		GetStage()->SetSharedGameObject(L"YSprite", GetThis<YSprite>());
	}

	void YSprite::OnUpdate() 
	{
		//�v���C���[�̎擾
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");

		//�ǂ��󂵂���
		auto PowerCount = ptrPlayer->GetPowerCount();
		ptrPlayer->SetPowerCount(PowerCount);

		//�g���I����Ă邩�ǂ���
		auto Gageflash = ptrPlayer->GetGageflash();
		ptrPlayer->SetGageflash(Gageflash);
		if (PowerCount == POWERMAX)
		{
			//�e�N�X�`����\������
			SetDrawActive(true);
		}
		//�Q�[�W���g���I�������
		if (Gageflash == GAGEFLASHTRUE)
		{
			//�e�N�X�`���̕\�������Ȃ�
			SetDrawActive(false);
			Gageflash = 0;
		}
	}
}