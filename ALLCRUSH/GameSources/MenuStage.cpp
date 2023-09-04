/*!
@file MenuStage.cpp
@brief ���j���[�X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr float LOUDNESS = 0.5f;//!�T�E���h�̑傫��
	constexpr float OFIDLETIME = 1.0f;//!�`��I�t�̎���
	constexpr float ONIDLETIME = 1.5f;//!�`��I���̎���
	//--------------------------------------------------------------------------------------
	//	���j���[�X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void MenuStage::CreateViewLight() {

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
		Vec2 scale = Vec2(0.0f);//!�傫��
		Vec3 position = Vec3(0.0f);//!�ʒu

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
	std::vector<TextureTransformCreateDate>StageSelectTextureTransformDate(const wstring& keyName)
	{
		std::vector<TextureTransformCreateDate>result;	//!�g�����X�t�H�[���̃f�[�^��ۑ�����z��
		vector<wstring>LineVec;							//!�ϐ���
		auto& app = App::GetApp();						//!�A�v���̎擾
		wstring DateDir;								//!�f�[�^
		App::GetApp()->GetDataDirectory(DateDir);		//!�f�[�^���擾����
		auto fullPass = DateDir + L"csvFolder\\" + L"TexturecsvFolder\\" + L"MenuStageTextureTransform.csv";//!�����csv�̎擾	
		CsvFile csvFile;						//!csv�̕ۑ�
		csvFile.SetFileName(fullPass);			//!�t�@�C���̖��O��ۑ�����
		csvFile.ReadCsv();						//!csv��ǂ݂�����
		csvFile.GetSelect(LineVec, 0, keyName);	//!1�s�߂��w��̕���������

		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;//!�g�[�N��(�J����)�̔z�u
			Util::WStrToTokenVector(Tokens, v, L',');//!�g�[�N��(�J����)�P�ʂŕ�����𒊏o(',')

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



			result.push_back(TextureTransformCreateDate(Scale, Vec3(Pos.x, Pos.y , Pos.z)));

		}
		return result;//!�\���̂̒��g��z��ɓ���ĕԂ�
	}

    //�A�C�e���X�v���C�g�쐬
	void MenuStage::CreateMenuSprite1() {
		auto datas = StageSelectTextureTransformDate(L"MenuSprite1Texture");//!�w��̃L�[�̍s���擾

		for (auto& data : datas)
		{
			AddGameObject<MenuSprite1>(L"Stage1_TX", true,
				data.scale, data.position);
		}
	}

	//�A�C�e���X�v���C�g�쐬
	void MenuStage::CreateMenuSprite2() {
		auto datas = StageSelectTextureTransformDate(L"MenuSprite2Texture");//!�w��̃L�[�̍s���擾
		for (auto& data : datas)
		{
			AddGameObject<MenuSprite2>(L"Stage2_TX", true,
				data.scale, data.position);
		}
	}
	
	
	//������
	void MenuStage::OnCreate() {
		CreateViewLight();
		auto datas = StageSelectTextureTransformDate(L"MenuSelectTexture");//!�w��̃L�[�̍s���擾
		for (auto& data : datas)
		{
			AddGameObject<TitleSprite>(L"MenuSelect_TX", false,
				data.scale, Vec2(data.position.x, data.position.y));
		}
		CreateMenuSprite1();//Stage1�X�v���C�g
		CreateMenuSprite2();//Stage2�X�v���C�g
	}
	
	void MenuStage::SelectStage()
	{
		//scene�̎擾
		auto scene = App::GetApp()->GetScene<Scene>();
		//�X�e�[�W�ԍ��̎擾
		auto Select = scene->GetStageSelect();
		//���I��ł���X�e�[�W�ԍ���n��
		Select = StageNum;
		scene->SetStageSelect(Select);
	}

	//�\���L�[��
	void MenuStage:: OnPushUP() {

		StageNum--;
		if (StageNum <= m_UPlimit)
		{
			StageNum = m_UPlimit;
		}
	}
	//�\���L�[��
	void MenuStage::OnPushDOWN() {
		StageNum++;
		if (StageNum >= m_DOWNlimit)
		{
			StageNum = m_DOWNlimit;
		}
	}

	
	void MenuStage::StageSprite1()
	{
	    //menuSprite1���擾����
		auto ptrStage1 = GetSharedGameObject<MenuSprite1>(L"MenuSprite1");
		//elapsedTime���擾���邱�Ƃɂ�莞�Ԃ��g����
		float elapsedTime = App::GetApp()->GetElapsedTime();
		if (OnPushBCheck) {
			if (!OnPushBCheck1)
			{
				auto WalkSound = App::GetApp()->GetXAudio2Manager();
				WalkSound->Start(L"WalkSound", 0, LOUDNESS);
				OnPushBCheck1 = true;
			}
		}
		//���Ԃ�ϐ��ɑ���
		m_idleTime += elapsedTime;
		//�\���L�[�𗘗p����num���O�̎�
		 if (StageNum == m_UPlimit)
		    {   //���Ԃ�1�b��ɕ\�����I�t�ɂȂ�
				if (m_idleTime >= OFIDLETIME)
				  {
                     ptrStage1->SetDrawActive(false);
					  //���Ԃ�1.5�b��ɃI���ɂȂ�
					  if (m_idleTime >= ONIDLETIME)
					   {
						 ptrStage1->SetDrawActive(true);
						 //m_idleTime��0�ɂ��邱�Ƃɂ�茳�ɖ߂��ă��[�v����B
						 m_idleTime = 0;
					   }
						return;
				  }
		 }
		 //�I������ĂȂ��Ƃ��͕\�����ꂽ�܂�
		else{ ptrStage1->SetDrawActive(true); }

	}

	//�X�e�[�W�X�v���C�g�Q�̏���
	void MenuStage::StageSprite2()
	{
         //menuSprite1���擾����
		 auto ptrStage2 = GetSharedGameObject<MenuSprite2>(L"MenuSprite2");
		
		 //���Ԃ�ϐ��ɑ���
		
		 //�\���L�[�𗘗p����num���O�̎�
		 if (StageNum == m_DOWNlimit)
		 {   //���Ԃ�1�b��ɕ\�����I�t�ɂȂ�
			 if (m_idleTime >= OFIDLETIME)
			 {
				 ptrStage2->SetDrawActive(false);
				 //���Ԃ�1.5�b��ɃI���ɂȂ�
				 if (m_idleTime >= ONIDLETIME)
				 {
					 ptrStage2->SetDrawActive(true);
					 //m_idleTime��0�ɂ��邱�Ƃɂ�茳�ɖ߂��ă��[�v����B
					 m_idleTime = 0;
				 }
				 return;
			 }
		 }
		 //�I������ĂȂ��Ƃ��͕\�����ꂽ�܂�
		 else { ptrStage2->SetDrawActive(true); }
				
				
	}
	//�X�V
	void MenuStage::OnUpdate() {
		SelectStage();
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<MenuStage>());

		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];
        //�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		StageSprite1();
		StageSprite2();	
		
	}

	
	//B�{�^����������Ă�����
	void MenuStage::OnPushB() {
		
		wstring stagename[]
		{  
			L"ToMovieStage",
			L"ToGameStage"
		};
		if (m_OnPushB==true)
		{
			auto datas = StageSelectTextureTransformDate(L"FadeOutTexture");//!�w��̃L�[�̍s���擾

			for (auto& data : datas)
			{
				//�t�F�[�h�A�E�g�̍쐬
				AddGameObject<FadeOut>(true,
					data.scale, data.position);
			}
		SelectStage();
		//���̃X�e�[�W�ֈڍs
		PostEvent(XM_PI / 2, GetThis<MenuStage>(), App::GetApp()->GetScene<Scene>(), stagename[StageNum]);
		m_OnPushB = false;
		}
		
		OnPushBCheck = true;
	}
}

//end namespace basecross