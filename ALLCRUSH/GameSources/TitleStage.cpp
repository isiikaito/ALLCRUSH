/*!
@file TitleStage.cpp
@brief �^�C�g���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr float LOUDNESS = 0.5f;//!�T�E���h�̑傫��

	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {

		auto ptrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto ptrCamera = ObjectFactory::Create<Camera>();
		ptrView->SetCamera(ptrCamera);

		//�}���`���C�g�̍쐬
		auto ptrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		ptrMultiLight->SetDefaultLighting();
	}
	//!�e�N�X�`����(�X�P�[��,���[�e�[�V����,�|�W�V����)�̍\����
	struct TextureTransformCreateDate
	{
		//!�\���̃e���v���[�g
		Vec2 scale = Vec2(0.0f);	//!�傫��
		Vec3 position = Vec3(0.0f);	//!�ʒu

		TextureTransformCreateDate() :
			TextureTransformCreateDate(Vec2(0.0f), Vec3(0.0f))
		{}
		//!�\���̂̏�����
		TextureTransformCreateDate(
			const Vec2& scale,
			const Vec3& position
		) :
			scale(scale),
			position(position)
		{}
	};

	//!csv����f�[�^�̎��o��
	std::vector<TextureTransformCreateDate>TitleTextureTransformDate(const wstring& keyName)
	{
		std::vector<TextureTransformCreateDate>result;	//!�g�����X�t�H�[���̃f�[�^��ۑ�����z��
		vector<wstring>LineVec;							//!�ϐ���
		auto& app = App::GetApp();						//!�A�v���̎擾
		wstring DateDir;								//!�f�[�^
		App::GetApp()->GetDataDirectory(DateDir);		//!�f�[�^���擾����
		auto fullPass = DateDir + L"csvFolder\\" + L"TexturecsvFolder\\" + L"TitleStageTextureTransform.csv";//!�����csv�̎擾
		CsvFile csvFile;						//!csv�̕ۑ�
		csvFile.SetFileName(fullPass);			//!�t�@�C���̖��O��ۑ�����
		csvFile.ReadCsv();						//!csv��ǂ݂�����
		csvFile.GetSelect(LineVec, 0, keyName);	//!1�s�߂��w��̕���������

		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;						//!�g�[�N��(�J����)�̔z�u
			Util::WStrToTokenVector(Tokens, v, L',');	//!�g�[�N��(�J����)�P�ʂŕ�����𒊏o(',')

			//!�g�[�N��(�J����)���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec2 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str())
			);

			//!�ʒu
			Vec3 Pos(
				(float)_wtof(Tokens[3].c_str()),
				(float)_wtof(Tokens[4].c_str()),
				(float)_wtof(Tokens[5].c_str())
			);



			result.push_back(TextureTransformCreateDate(Scale, Vec3(Pos.x, Pos.y, Pos.z)));

		}
		return result;//!�\���̂̒��g��z��ɓ���ĕԂ�
	}
	
	//������
	void TitleStage::OnCreate() {
		ShowCursor(false);
		CreateViewLight();

		auto datas = TitleTextureTransformDate( L"TitleTextureTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			AddGameObject<TitleSprite>(
				L"TITLE_TX", 
				false,
				data.scale,
 Vec2(data.position.x, data.position.y));
		}
	
		
	}

	//�X�V
	void TitleStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<TitleStage>());
		if (OnPushBCheck) {
			if (!OnPushBCheck1)
			{
			auto WalkSound = App::GetApp()->GetXAudio2Manager();
			WalkSound->Start(L"WalkSound", 0, LOUDNESS);
			OnPushBCheck1 = true;
			}			
		}
		
	}
	void TitleStage::OnPushB() {	

		if (m_OnPushB)
		{
			//�t�F�[�h�A�E�g�̍쐬
			AddGameObject<FadeOut>( true,
				Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f,0.0f));
			PostEvent(XM_PI / 2, GetThis<TitleStage>(), App::GetApp()->GetScene<Scene>(), L"ToMenuStage");
			m_OnPushB = false;
		}
	
			OnPushBCheck = true;
	}
	
}

//end namespace basecross