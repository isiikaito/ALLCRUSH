/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------

	//!�e�N�X�`���̓ǂݍ���
	void Scene::RoadTexture(const wstring& TextureName, const wstring& UseTextureName)
	{
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);//!�T���v���̂��߃��f�B�A�f�B���N�g�����擾
		wstring strTexture = dataDir + L"Texture\\" + TextureName;//!�e�N�X�`���̃p�X�̎w��
		App::GetApp()->RegisterTexture(UseTextureName, strTexture);//!�e�N�X�`���̓ǂݍ���
	}

	//!�X�^�e�B�b�N���f���̓ǂݍ���
	void Scene::RoadStaticModelMesh(const wstring& staticModelbmfName, const wstring& staticModelMeshName)
	{
		wstring dataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		App::GetApp()->GetAssetsDirectory(dataDir);

		App::GetApp()->RegisterResource(
			staticModelMeshName,
			MeshResource::CreateStaticModelMesh(dataDir, L"MayaModels\\" + staticModelbmfName + L".bmf")
		);

	}

	//!�{�[���t�����f���̓ǂݍ���
	void Scene::RoadBoneModel(const wstring& BoneModelbmfName, const wstring& BoneModelMeshName, const wstring& BomeModelMeshTangentName)
	{
		wstring dataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		App::GetApp()->GetAssetsDirectory(dataDir);

		//!�{�[�����f���̒ʏ탊�\�[�X
		App::GetApp()->RegisterResource(BoneModelMeshName,
			MeshResource::CreateBoneModelMesh(dataDir, L"MayaModels\\" + BoneModelbmfName + L".bmf"));

		//! �{�[�����f���̃^���W�F���g�t�����\�[�X
		App::GetApp()->RegisterResource(BomeModelMeshTangentName,
			MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"MayaModels\\" + BoneModelbmfName + L".bmf")
		);

	}

	void Scene::CreateResourses() {

		RoadTexture(L"wall.jpg", L"WALL_TX");//!�ǂ̃e�N�X�`��
		RoadTexture(L"doukutu.png", L"DOUKUTU_TX");//!���A�̃e�N�X�`��
		RoadTexture(L"TITLE.png", L"TITLE_TX");//!�^�C�g���̃e�N�X�`��
		RoadTexture(L"GameOver.jpg", L"GAMEOVER_TX");//!�Q�[���I�[�o�[�̃e�N�X�`��
		RoadTexture(L"PushButtonX.png", L"PushButtonX_TX");//!X�{�^���̃e�N�X�`��
		RoadTexture(L"flee.png", L"FLEE_TX");//!�ŏ��̃R�����g�̃e�N�X�`��
		RoadTexture(L"PillarBrake.png", L"PillarBrake_TX");//!�����󂷎��̃R�����g�̃e�N�X�`��
		RoadTexture(L"JustTiming.png", L"JustTiming_TX");//!�����󂷃^�C�~���O�̃R�����g�̃e�N�X�`��
		RoadTexture(L"ClearNear.png", L"ClearNear_TX");//!�S�[���ɋ߂Â������̃R�����g�̃e�N�X�`��
		RoadTexture(L"WallBrake.png", L"WallBrake_TX");//!�ǂ��󂷕��@�̃R�����g�̃e�N�X�`��
		RoadTexture(L"number.png", L"NUMBER_TX");//!�����̃e�N�X�`��
		RoadTexture(L"SPEED.png", L"SPEED_TX");//!�X�s�[�h�A�b�v�̃e�N�X�`��
		RoadTexture(L"XButton.png", L"XButton_TX");//!X�{�^���̃e�N�X�`��
		RoadTexture(L"YButton.png", L"YButton_TX");//!X�{�^���̃e�N�X�`��
		RoadTexture(L"GAGE.png", L"GAGE_TX");//!X�{�^���̃e�N�X�`��
		RoadTexture(L"Stage1.png", L"Stage1_TX");//!X�{�^���̃e�N�X�`��
		RoadTexture(L"Stage2.png", L"Stage2_TX");//!X�{�^���̃e�N�X�`��
		RoadTexture(L"MenuSelect.png", L"MenuSelect_TX");//!X�{�^���̃e�N�X�`��
		RoadTexture(L"PlayerUV_Normal.png", L"OBJECT_NORMAL_TX");//!X�{�^���̃e�N�X�`��
		
		
		wstring dataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		App::GetApp()->GetAssetsDirectory(dataDir);
		//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
		
	    //�v���C���[�̃{�[���t�����f���̓ǂݍ���
		RoadBoneModel(L"player", L"Object_WalkAnimation_MESH", L"Object_WalkAnimation_MESH_WITH_TAN");

		//�G�̃{�[���t�����f��
		RoadBoneModel(L"EnemyBoss", L"EnemyRun_MESH", L"EnemyRun_MESH_WITH_TAN");

		//�ǂ̃��f���ǂݍ���
		RoadStaticModelMesh(L"StageWall", L"STAGEWALL_MESH");
		
		//���̃I�u�W�F�N�g
		RoadStaticModelMesh(L"Floor", L"STAGEFLOOR_MESH");

		//�o���̃��f���̓ǂݍ���
		RoadStaticModelMesh(L"ExitWall", L"EXITWALL_MESH");

		//��Q��1��ǂݍ���
		RoadStaticModelMesh(L"Obuject.KU2", L"OBSTACLE1_MESH");
        
		//��Q��2�̓ǂݍ���
		RoadStaticModelMesh(L"Obuject05", L"OBSTACLE2_MESH");
		
		//���̓ǂݍ���
		RoadStaticModelMesh(L"pillar", L"PILLAR_MESH");
		
		//���΂̓ǂݍ���
		RoadStaticModelMesh(L"Foring", L"IWA_MESH");
		
		//�󂷕ǂ̓ǂݍ���
		RoadStaticModelMesh(L"BreakWall1", L"UNBREAKWALL_MESH");
		RoadStaticModelMesh(L"BreakWall2", L"DAMAGEWALL1_MESH");
		RoadStaticModelMesh(L"BreakWall3", L"DAMAGEWALL2_MESH");
		RoadStaticModelMesh(L"BreakWall4", L"DAMAGEWALL3_MESH");
		RoadStaticModelMesh(L"kumonosu", L"KUMONOSU_MESH");


		
		//�G�t�F�N�g�֘A
		wstring strTexture = dataDir + L"Splash.png";
		App::GetApp()->RegisterTexture(L"Splash_TX", strTexture);
		strTexture = dataDir + L"Spark.png";
		App::GetApp()->RegisterTexture(L"Spark_TX", strTexture);
		strTexture = dataDir + L"SpeedUp.png";
		App::GetApp()->RegisterTexture(L"SpeedUp_TX", strTexture);
		strTexture = dataDir + L"Impact.png";
		App::GetApp()->RegisterTexture(L"Impact_TX", strTexture);
		strTexture = dataDir + L"PowerUp.png";
		App::GetApp()->RegisterTexture(L"PowerUp_TX", strTexture);

		//�T�E���h
		wstring CursorWav = dataDir + L"music.mp3";
		App::GetApp()->RegisterWav(L"BGM", CursorWav);
		//�G�̐�
		CursorWav = dataDir + L"WalkSound.wav";
		App::GetApp()->RegisterWav(L"WalkSound", CursorWav);
		//����T�E���h	
		CursorWav = dataDir + L"run.wav";
		App::GetApp()->RegisterWav(L"run", CursorWav);
		//�X�s�[�h�A�b�v�̃T�E���h
		CursorWav = dataDir + L"SpeedUp.wav";
		App::GetApp()->RegisterWav(L"SpeedUp", CursorWav);
		//�X�s�[�h�A�b�v�̃T�E���h
		CursorWav = dataDir + L"PowerUp.wav";
		App::GetApp()->RegisterWav(L"PowerUp", CursorWav);
		//�n���}�[��U��T�E���h
		CursorWav = dataDir + L"Hammer.wav";
		App::GetApp()->RegisterWav(L"Hammer", CursorWav);
		//�ǂ��U�����s�������̃T�E���h
		CursorWav = dataDir + L"AttackWall.wav";
		App::GetApp()->RegisterWav(L"AttackWall", CursorWav);
		//�ǂ���ꂽ�Ƃ��̃T�E���h
		CursorWav = dataDir + L"BrakeWall.wav";
		App::GetApp()->RegisterWav(L"BrakeWall", CursorWav);
		//�G�̐�
		CursorWav = dataDir + L"EnemyVoice.wav";
		App::GetApp()->RegisterWav(L"EnemyVoice", CursorWav);
		//�G�Ɋ₪�����鉹
		CursorWav = dataDir + L"RockAttack.wav";
		App::GetApp()->RegisterWav(L"RockAttack", CursorWav);


	}
	void Scene::OnCreate() {
		try {
			//���\�[�X�쐬
			CreateResourses();
			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//�ŏ��̃V�[���ɐݒ�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");

		}

		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToTitleStage") {
			//�^�C�g���X�e�[�W�̐ݒ�
			ResetActiveStage<TitleStage>();
		}

		else if (event->m_MsgStr == L"ToGameStage") {
			//�Q�[���X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}
	
		else if (event->m_MsgStr == L"ToMenuStage") {
			//���j���[�X�e�[�W�̐ݒ�
			ResetActiveStage<MenuStage>();
		}
		else if (event->m_MsgStr == L"ToClearStage") {
			//�N���A�X�e�[�W�̐ݒ�
			ResetActiveStage<MyClearStage>();
		}

		
		else if (event->m_MsgStr == L"ToMovieStage") {
			m_MovieActive = true;
			//�{�X�̓o��V�[���X�e�[�W�̐ݒ�
			ResetActiveStage<MyMovieStage>();
		}
	}

}
//end basecross
