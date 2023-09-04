/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr float CHANGETIME = 1.0f;//!�ύX���鎞��
	constexpr float MAXIDLETIME = 2.0f;//!�e���b�v����������
	constexpr float MAXTOTALTIME = 1000.0f;//!�X�e�[�W����
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();

		//OpeningCameraView�p�̃r���[
		m_OpeningCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_OpeningCameraView->SetCamera(ptrOpeningCamera);
		//MyCamera�p�̃r���[
		m_MyCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_MyCameraView->SetCamera(ptrMyCamera);
		//������Ԃł�m_OpeningCameraView���g��
		SetView(m_OpeningCameraView);
		m_CameraSelect = CameraSelect::openingCamera;
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();

		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateMultiSpark() {
		auto MultiSparkPtr = AddGameObject<InsertEffect>();
		//���L�I�u�W�F�N�g�ɃX�p�[�N��o�^
		SetSharedGameObject(L"MultiEffect", MultiSparkPtr);
	}

	void GameStage::CreateMultiSpark1() {
		auto MultiSparkPtr = AddGameObject<InsertEffect>();
		//���L�I�u�W�F�N�g�ɃX�p�[�N��o�^
		SetSharedGameObject(L"MultiEffect1", MultiSparkPtr);
	}


	//����ǂ̍쐬
	void GameStage::CreateWall() {
		//�O���[�v�̎擾
		auto group = CreateSharedObjectGroup(L"Wall_Group");
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"BreakWall"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"Wall");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z�u
			vector<wstring>Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o�iL','�j
			Util::WStrToTokenVector(Tokens, v, L',');
			//�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//��]�́uXM_PLDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//HP�̎擾
			int HP(
				(int)_wtof(Tokens[10].c_str())
			);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			AddGameObject<Wall>(Scale, Rot, Pos, HP);
		}
	}
	//�g���b�v�̍쐬
	void GameStage::CreateTrap()
	{
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"Trap");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z�u
			vector<wstring>Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o�iL','�j
			Util::WStrToTokenVector(Tokens, v, L',');
			//�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//��]�́uXM_PLDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			AddGameObject<Trap>(Scale, Rot, Pos);
		}
	}
	//�X�e�[�W�̕ǂ̍쐬
	void GameStage::CreateStageWall() {
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"StageWall");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z�u
			vector<wstring>Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o�iL','�j
			Util::WStrToTokenVector(Tokens, v, L',');
			//�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//��]�́uXM_PLDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			AddGameObject<StageWall>(Scale, Rot, Pos);


		}

	}

	//�}���̕ǂ̍쐬
	void GameStage::CreateExitWall() {
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"ExitWall");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z�u
			vector<wstring>Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o�iL','�j
			Util::WStrToTokenVector(Tokens, v, L',');
			//�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//��]�́uXM_PLDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			AddGameObject<ExitWall>(Scale, Rot, Pos);


		}

	}

	//�}���̏��̍쐬
	void GameStage::CreateStageFloor() {
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"StageFloor");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z�u
			vector<wstring>Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o�iL','�j
			Util::WStrToTokenVector(Tokens, v, L',');
			//�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//��]�́uXM_PLDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			AddGameObject<StageFloor>(Scale, Rot, Pos);
		}



	}
	//��Q���P�쐬
	void GameStage::CreateObstacle1() {
		
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"Obstacle1");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z�u
			vector<wstring>Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o�iL','�j
			Util::WStrToTokenVector(Tokens, v, L',');
			//�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//��]�́uXM_PLDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			AddGameObject<Obstacle1>(Scale, Rot, Pos);
		}
	}

	//��Q��2�쐬
	void GameStage::CreateObstacle2() {
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"Obstacle2");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z�u
			vector<wstring>Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o�iL','�j
			Util::WStrToTokenVector(Tokens, v, L',');
			//�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//��]�́uXM_PLDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			AddGameObject<Obstacle2>(Scale, Rot, Pos);
		}
	}

	//���̍쐬
	void GameStage::CreatePillar() {
		//auto group2 = CreateSharedObjectGroup(L"Pillar_Group1");
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"Pillar");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z�u
			vector<wstring>Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o�iL','�j
			Util::WStrToTokenVector(Tokens, v, L',');
			//�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//��]�́uXM_PLDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			AddGameObject<Pillar>(Scale, Rot, Pos);
		}
	}

	//���΂̍쐬
	void GameStage::CreateFallingRock() {

		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		auto group3 = CreateSharedObjectGroup(L"FallingRock_Group1");
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"FallingRock");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z�u
			vector<wstring>Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o�iL','�j
			Util::WStrToTokenVector(Tokens, v, L',');
			//�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//��]�́uXM_PLDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			AddGameObject<FallingRock>(Scale, Rot, Pos);
		}
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
	std::vector<TextureTransformCreateDate>GameStageTextureTransformDate(const wstring& FolderName, const wstring& csvName, const wstring& keyName)
	{
		std::vector<TextureTransformCreateDate>result;//!�g�����X�t�H�[���̃f�[�^��ۑ�����z��
		vector<wstring>LineVec;//!�ϐ���

		auto& app = App::GetApp();//!�A�v���̎擾
		wstring DateDir;
		App::GetApp()->GetDataDirectory(DateDir);
		auto fullPass = DateDir + L"csvFolder\\" + FolderName + csvName;

		CsvFile csvFile;
		csvFile.SetFileName(fullPass);
		csvFile.ReadCsv();

		csvFile.GetSelect(LineVec, 0, keyName);

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

			result.push_back(TextureTransformCreateDate(Scale, Vec3(Pos.x, Pos.y, Pos.z)));

		}
		return result;
	}


	//�^�C���X�v���C�g�쐬
	void GameStage::CreateTime() {
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"TimeTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			AddGameObject<MyTime>(
				4,
				L"NUMBER_TX",
				true,
				data.scale,
				data.position
				);
		}
	}

	//�A�C�e���X�v���C�g�쐬
	void GameStage::CreateMyitem1() {
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"Myitem1Texture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			AddGameObject<Myitem1>(
				L"SPEED_TX", 
				true,
				data.scale,
				data.position
				);
		}
	}
	//X�{�^���X�v���C�g
	void GameStage::CreateXSprite() {
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"XSpriteTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			AddGameObject<XSprite>(
				L"XButton_TX",
				true,
				data.scale, 
				data.position
				);
		}
	}
	//Y�{�^���X�v���C�g
	void GameStage::CreateYSprite() {
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"YSpriteTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			AddGameObject<YSprite>(
				L"YButton_TX", 
				true,
				data.scale,
				data.position
				);
		}
	}

	//�Q�[�W�̘g�쐬
	void GameStage::CreateMygage() {
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"MygageTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			AddGameObject<Mygage>(L"GAGE_TX", true,
				data.scale, data.position);
		}
	}
	//�Q�[�W�̃o�[�̍쐬
	void GameStage::CreateGageSprite()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"GageSpriteTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			AddGameObject<GageSprite>(true,
				data.scale, data.position);
		}
	}


	void GameStage::CreateGageWhite()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"GageWhiteTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			AddGameObject<GageSpriteWhite>(true,
				data.scale, data.position);
		}
	}


	//�v���C���[�̍쐬
	void GameStage::CreatePlayer() {
		//�v���[���[�̍쐬
		auto PlayerPtr = AddGameObject<Player>();
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", PlayerPtr);
	}



	// ������e���b�v
	void GameStage::CreateTickerSprite()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"TickerSpriteTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			AddGameObject<TickerSprite>(L"FLEE_TX", true,
				data.scale, Vec2(data.position.x, data.position.y));
		}
	}

	// �����󂷃e���b�v
	void GameStage::CreateTelop()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"TelopTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			AddGameObject<Telop>(L"PillarBrake_TX", true,
				data.scale, Vec2(data.position.x, data.position.y));
		}
	}

	// �����󂷃^�C�~���O�e���b�v
	void GameStage::CreateTelop2()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"Telop2Texture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			AddGameObject<Telop2>(L"JustTiming_TX", true,
				data.scale, Vec2(data.position.x, data.position.y));
		}
	}

	// �o���O�e���b�v
	void GameStage::CreateTelop3()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"Telop3Texture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			AddGameObject<Telop3>(L"ClearNear_TX", true,
				data.scale, Vec2(data.position.x, data.position.y));
		}
	}

	// �ǂ��󂹁I�I�e���b�v
	void GameStage::CreateTelop4()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"Telop4Texture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			AddGameObject<Telop4>(L"WallBrake_TX", true,
				data.scale, Vec2(data.position.x, data.position.y));
		}
	}



	void GameStage::BGM() {
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"BGM", XAUDIO2_LOOP_INFINITE, 0.4f);
	}

	//�J�����}���̍쐬
	void GameStage::CreateCameraman() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto ptrCameraman = AddGameObject<Cameraman>(2.0f);
		//�V�F�A�z���Cameraman��ǉ�
		SetSharedGameObject(L"Cameraman", ptrCameraman);
		//�V�F�A�z���OpeningCameraman��ǉ�
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraman>();
		SetSharedGameObject(L"OpeningCameraman", ptrOpeningCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_OpeningCameraView->GetCamera());
		if (ptrOpeningCamera) {
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);
			SetView(m_OpeningCameraView);
			m_CameraSelect = CameraSelect::openingCamera;
		}

	}

	void GameStage::OnCreate() {
		try {

			auto  Select = App::GetApp()->GetScene<Scene>()->GetStageSelect();

			SetPhysicsActive(true);//�����v�Z�L��

			// �u�A�v���v�I�u�W�F�N�g�̃C���X�^���X���擾����i�C���X�^���X�F�N���X�̎��ԁA�I�u�W�F�N�g�w���̃I�u�W�F�N�g�̂��Ɓj
			auto& app = App::GetApp();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//CSV�t�@�C�����̓ǂݍ���
			m_CsvC.SetFileName(DataDir + L"stage" + Util::IntToWStr(Select) + L".csv");
			m_CsvC.ReadCsv();


			CreateViewLight();           //�r���[�ƃ��C�g�̍쐬
			CreateMultiSpark();          //�G�t�F�N�g0�̍쐬
			CreateMultiSpark1();         //�G�t�F�N�g1�̍쐬
			CreatePlayer();              //�v���[���[�̍쐬
			BGM();                       //BGM�̍Đ�
			CreatePillar();              //���̍쐬
			AddGameObject<EnemyObject>();//�G�̍쐬
			CreateStageWall();           //�X�e�[�W�̕ǂ̒ǉ�	
			CreateStageFloor();          //���̒ǉ�
			CreateObstacle1();           //��Q���P�̒ǉ�
			CreateFallingRock();         //����
			CreateTrap();                //�g���b�v�̍쐬
			CreateExitWall();            //�}���ł������o��
			CreateTime();                //�^�C���X�v���C�g�쐬
			CreateWall();                //����ǂ̍쐬
			CreateMyitem1();             //�A�C�e���X�v���C�g
			CreateXSprite();             //X�{�^���̃X�v���C�g�̍쐬
			CreateYSprite();             //Y�{�^���̃X�v���C�g�̍쐬
			CreateMygage();              //�Q�[�W�̘g�̍쐬
			CreateGageSprite();          //�Q�[�W�̃X�v���C�g1�̍쐬
			CreateGageWhite();           //�Q�[�W�̔w�i�̍쐬
			CreateTickerSprite();        //�e���b�v0�̍쐬
			CreateTelop();               //�e���b�v1�̍쐬
			CreateTelop2();              //�e���b�v2�̍쐬
			CreateTelop3();              //�e���b�v3�̍쐬             
			CreateCameraman();           //�J�����}���̍쐬
			CreateTelop4();              //�e���b�v4�̍쐬

		}
		catch (...) {
			throw;
		}
	}

	void GameStage::ToMyCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//MyCamera�ɕύX
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_MyCameraView->GetCamera());
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);
			//m_MyCameraView���g��
			SetView(m_MyCameraView);
			m_CameraSelect = CameraSelect::myCamera;
		}
	}

	void GameStage::OnUpdate() {

		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<GameStage>());
		ResetHandler.ResetHandle(GetThis<GameStage>());
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;
		if (m_TotalTime >= MAXTOTALTIME) {
			m_TotalTime = 0.0f;
		}
		//�^�C�����X�V����
		auto ptrScor = GetSharedGameObject<MyTime>(L"Time");
		ptrScor->SetScore(m_TotalTime);

		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto Exit = ptrPlayer->GetExitCount();
		auto GameOver = ptrPlayer->GetGameOver();
		auto state = ptrPlayer->GetGameState();
		static shared_ptr<FadeOut> fadeOut = nullptr;
		static float FadeTime = 0.0f;
		switch (state)
		{
			//!�X�e�[�g�̑J��
		case GameState::Game://!�������Ă��Ȃ��������
			break;
		case GameState::Down://!�{�X�ɒǂ����ꂽ���
			ptrPlayer->SetGameState(GameState::FadeStart);
			break;
		case GameState::FadeStart://!�t�F�[�h�A�E�g���n�܂������

			fadeOut = AddGameObject<FadeOut>(true,
				Vec2(1290.0f, 960.0f), Vec3(0.0f));//!
			ptrPlayer->SetGameState(GameState::FadeOut);
		case GameState::FadeOut:
			FadeTime += elapsedTime;
			if (FadeTime >= CHANGETIME)
			{
				AddGameObject<GameOverSprite>(L"GAMEOVER_TX", true,
					Vec2(500.0f, 500.0f), Vec3(0.0f));
				AddGameObject<PushButtonXTelop>(L"PushButtonX_TX", true,
					Vec2(500.0f, 500.0f), Vec3(0.0f, -250.0f, 0.0f));
				ptrPlayer->SetGameState(GameState::ChangeStage);
			}
			break;
		case GameState::ChangeStage:
			break;

			//!�Q�[���I�[�o�[�̎���GameOver�̕����̍쐬
			AddGameObject<GameOverSprite>(L"GAMEOVERTELOP_TX", true,
				Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.0f));

			m_createGameOverObjectFlg = true;
		case GameState::GameExit:
			//�t�F�[�h�A�E�g�̍쐬
			AddGameObject<FadeOut>(true,
				Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.0f));
			float elapsedTime1 = App::GetApp()->GetElapsedTime();
			m_ExitTime += elapsedTime1;
			if (m_ExitTime >= CHANGETIME)
			{
				PostEvent(0.0, GetThis<GameStage>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
			}
		}
		ptrPlayer->SetExitCount(Exit);
		ptrPlayer->SetGameOver(GameOver);
		// �e���b�v�̎���
		auto ptrStage = GetSharedGameObject<TickerSprite>(L"TickerSprite");
		// ���Ԃ̕ϐ��ɑ���
		m_idleTime += elapsedTime;
		if (m_idleTime >= MAXIDLETIME)
		{
			// 1�b��ɕ\�����I�t�ɂȂ�
			ptrStage->SetDrawActive(false);
		}

		
	}
	void GameStage::OnPushReset()
	{
		GameReset();
	}

	void GameStage::GameReset()
	{
		PostEvent(0.0f, GetThis<GameStage>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
	}

	void GameStage::OnDestroy() {
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

}
//end basecross
