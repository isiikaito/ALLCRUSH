/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------

	//!テクスチャの読み込み
	void Scene::RoadTexture(const wstring& TextureName, const wstring& UseTextureName)
	{
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);//!サンプルのためメディアディレクトリを取得
		wstring strTexture = dataDir + L"Texture\\" + TextureName;//!テクスチャのパスの指定
		App::GetApp()->RegisterTexture(UseTextureName, strTexture);//!テクスチャの読み込み
	}

	//!スタティックモデルの読み込み
	void Scene::RoadStaticModelMesh(const wstring& staticModelbmfName, const wstring& staticModelMeshName)
	{
		wstring dataDir;
		//サンプルのためアセットディレクトリを取得
		App::GetApp()->GetAssetsDirectory(dataDir);

		App::GetApp()->RegisterResource(
			staticModelMeshName,
			MeshResource::CreateStaticModelMesh(dataDir, L"MayaModels\\" + staticModelbmfName + L".bmf")
		);

	}

	//!ボーン付きモデルの読み込み
	void Scene::RoadBoneModel(const wstring& BoneModelbmfName, const wstring& BoneModelMeshName, const wstring& BomeModelMeshTangentName)
	{
		wstring dataDir;
		//サンプルのためアセットディレクトリを取得
		App::GetApp()->GetAssetsDirectory(dataDir);

		//!ボーンモデルの通常リソース
		App::GetApp()->RegisterResource(BoneModelMeshName,
			MeshResource::CreateBoneModelMesh(dataDir, L"MayaModels\\" + BoneModelbmfName + L".bmf"));

		//! ボーンモデルのタンジェント付きリソース
		App::GetApp()->RegisterResource(BomeModelMeshTangentName,
			MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"MayaModels\\" + BoneModelbmfName + L".bmf")
		);

	}

	void Scene::CreateResourses() {

		RoadTexture(L"wall.jpg", L"WALL_TX");//!壁のテクスチャ
		RoadTexture(L"doukutu.png", L"DOUKUTU_TX");//!洞窟のテクスチャ
		RoadTexture(L"TITLE.png", L"TITLE_TX");//!タイトルのテクスチャ
		RoadTexture(L"GameOver.jpg", L"GAMEOVER_TX");//!ゲームオーバーのテクスチャ
		RoadTexture(L"PushButtonX.png", L"PushButtonX_TX");//!Xボタンのテクスチャ
		RoadTexture(L"flee.png", L"FLEE_TX");//!最初のコメントのテクスチャ
		RoadTexture(L"PillarBrake.png", L"PillarBrake_TX");//!柱を壊す時のコメントのテクスチャ
		RoadTexture(L"JustTiming.png", L"JustTiming_TX");//!柱を壊すタイミングのコメントのテクスチャ
		RoadTexture(L"ClearNear.png", L"ClearNear_TX");//!ゴールに近づいた時のコメントのテクスチャ
		RoadTexture(L"WallBrake.png", L"WallBrake_TX");//!壁を壊す方法のコメントのテクスチャ
		RoadTexture(L"number.png", L"NUMBER_TX");//!数字のテクスチャ
		RoadTexture(L"SPEED.png", L"SPEED_TX");//!スピードアップのテクスチャ
		RoadTexture(L"XButton.png", L"XButton_TX");//!Xボタンのテクスチャ
		RoadTexture(L"YButton.png", L"YButton_TX");//!Xボタンのテクスチャ
		RoadTexture(L"GAGE.png", L"GAGE_TX");//!Xボタンのテクスチャ
		RoadTexture(L"Stage1.png", L"Stage1_TX");//!Xボタンのテクスチャ
		RoadTexture(L"Stage2.png", L"Stage2_TX");//!Xボタンのテクスチャ
		RoadTexture(L"MenuSelect.png", L"MenuSelect_TX");//!Xボタンのテクスチャ
		RoadTexture(L"PlayerUV_Normal.png", L"OBJECT_NORMAL_TX");//!Xボタンのテクスチャ
		
		
		wstring dataDir;
		//サンプルのためアセットディレクトリを取得
		App::GetApp()->GetAssetsDirectory(dataDir);
		//各ゲームは以下のようにデータディレクトリを取得すべき
		
	    //プレイヤーのボーン付きモデルの読み込み
		RoadBoneModel(L"player", L"Object_WalkAnimation_MESH", L"Object_WalkAnimation_MESH_WITH_TAN");

		//敵のボーン付きモデル
		RoadBoneModel(L"EnemyBoss", L"EnemyRun_MESH", L"EnemyRun_MESH_WITH_TAN");

		//壁のモデル読み込み
		RoadStaticModelMesh(L"StageWall", L"STAGEWALL_MESH");
		
		//床のオブジェクト
		RoadStaticModelMesh(L"Floor", L"STAGEFLOOR_MESH");

		//出口のモデルの読み込み
		RoadStaticModelMesh(L"ExitWall", L"EXITWALL_MESH");

		//障害物1を読み込む
		RoadStaticModelMesh(L"Obuject.KU2", L"OBSTACLE1_MESH");
        
		//障害物2の読み込む
		RoadStaticModelMesh(L"Obuject05", L"OBSTACLE2_MESH");
		
		//柱の読み込み
		RoadStaticModelMesh(L"pillar", L"PILLAR_MESH");
		
		//落石の読み込み
		RoadStaticModelMesh(L"Foring", L"IWA_MESH");
		
		//壊す壁の読み込み
		RoadStaticModelMesh(L"BreakWall1", L"UNBREAKWALL_MESH");
		RoadStaticModelMesh(L"BreakWall2", L"DAMAGEWALL1_MESH");
		RoadStaticModelMesh(L"BreakWall3", L"DAMAGEWALL2_MESH");
		RoadStaticModelMesh(L"BreakWall4", L"DAMAGEWALL3_MESH");
		RoadStaticModelMesh(L"kumonosu", L"KUMONOSU_MESH");


		
		//エフェクト関連
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

		//サウンド
		wstring CursorWav = dataDir + L"music.mp3";
		App::GetApp()->RegisterWav(L"BGM", CursorWav);
		//敵の声
		CursorWav = dataDir + L"WalkSound.wav";
		App::GetApp()->RegisterWav(L"WalkSound", CursorWav);
		//走るサウンド	
		CursorWav = dataDir + L"run.wav";
		App::GetApp()->RegisterWav(L"run", CursorWav);
		//スピードアップのサウンド
		CursorWav = dataDir + L"SpeedUp.wav";
		App::GetApp()->RegisterWav(L"SpeedUp", CursorWav);
		//スピードアップのサウンド
		CursorWav = dataDir + L"PowerUp.wav";
		App::GetApp()->RegisterWav(L"PowerUp", CursorWav);
		//ハンマーを振るサウンド
		CursorWav = dataDir + L"Hammer.wav";
		App::GetApp()->RegisterWav(L"Hammer", CursorWav);
		//壁を攻撃を行った時のサウンド
		CursorWav = dataDir + L"AttackWall.wav";
		App::GetApp()->RegisterWav(L"AttackWall", CursorWav);
		//壁が壊れたときのサウンド
		CursorWav = dataDir + L"BrakeWall.wav";
		App::GetApp()->RegisterWav(L"BrakeWall", CursorWav);
		//敵の声
		CursorWav = dataDir + L"EnemyVoice.wav";
		App::GetApp()->RegisterWav(L"EnemyVoice", CursorWav);
		//敵に岩が当たる音
		CursorWav = dataDir + L"RockAttack.wav";
		App::GetApp()->RegisterWav(L"RockAttack", CursorWav);


	}
	void Scene::OnCreate() {
		try {
			//リソース作成
			CreateResourses();
			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//最初のシーンに設定できる
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
			//タイトルステージの設定
			ResetActiveStage<TitleStage>();
		}

		else if (event->m_MsgStr == L"ToGameStage") {
			//ゲームステージの設定
			ResetActiveStage<GameStage>();
		}
	
		else if (event->m_MsgStr == L"ToMenuStage") {
			//メニューステージの設定
			ResetActiveStage<MenuStage>();
		}
		else if (event->m_MsgStr == L"ToClearStage") {
			//クリアステージの設定
			ResetActiveStage<MyClearStage>();
		}

		
		else if (event->m_MsgStr == L"ToMovieStage") {
			m_MovieActive = true;
			//ボスの登場シーンステージの設定
			ResetActiveStage<MyMovieStage>();
		}
	}

}
//end basecross
