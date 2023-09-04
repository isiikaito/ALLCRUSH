/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr float CHANGETIME = 1.0f;//!変更する時間
	constexpr float MAXIDLETIME = 2.0f;//!テロップを消す時間
	constexpr float MAXTOTALTIME = 1000.0f;//!ステージ時間
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();

		//OpeningCameraView用のビュー
		m_OpeningCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_OpeningCameraView->SetCamera(ptrOpeningCamera);
		//MyCamera用のビュー
		m_MyCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_MyCameraView->SetCamera(ptrMyCamera);
		//初期状態ではm_OpeningCameraViewを使う
		SetView(m_OpeningCameraView);
		m_CameraSelect = CameraSelect::openingCamera;
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();

		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateMultiSpark() {
		auto MultiSparkPtr = AddGameObject<InsertEffect>();
		//共有オブジェクトにスパークを登録
		SetSharedGameObject(L"MultiEffect", MultiSparkPtr);
	}

	void GameStage::CreateMultiSpark1() {
		auto MultiSparkPtr = AddGameObject<InsertEffect>();
		//共有オブジェクトにスパークを登録
		SetSharedGameObject(L"MultiEffect1", MultiSparkPtr);
	}


	//壊れる壁の作成
	void GameStage::CreateWall() {
		//グループの取得
		auto group = CreateSharedObjectGroup(L"Wall_Group");
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"BreakWall"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"Wall");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//HPの取得
			int HP(
				(int)_wtof(Tokens[10].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<Wall>(Scale, Rot, Pos, HP);
		}
	}
	//トラップの作成
	void GameStage::CreateTrap()
	{
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"Trap");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<Trap>(Scale, Rot, Pos);
		}
	}
	//ステージの壁の作成
	void GameStage::CreateStageWall() {
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"StageWall");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<StageWall>(Scale, Rot, Pos);


		}

	}

	//マヤの壁の作成
	void GameStage::CreateExitWall() {
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"ExitWall");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<ExitWall>(Scale, Rot, Pos);


		}

	}

	//マヤの床の作成
	void GameStage::CreateStageFloor() {
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"StageFloor");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<StageFloor>(Scale, Rot, Pos);
		}



	}
	//障害物１作成
	void GameStage::CreateObstacle1() {
		
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"Obstacle1");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<Obstacle1>(Scale, Rot, Pos);
		}
	}

	//障害物2作成
	void GameStage::CreateObstacle2() {
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"Obstacle2");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<Obstacle2>(Scale, Rot, Pos);
		}
	}

	//柱の作成
	void GameStage::CreatePillar() {
		//auto group2 = CreateSharedObjectGroup(L"Pillar_Group1");
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"Pillar");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<Pillar>(Scale, Rot, Pos);
		}
	}

	//落石の作成
	void GameStage::CreateFallingRock() {

		//CSVの行単位の配列
		vector<wstring>LineVec;
		auto group3 = CreateSharedObjectGroup(L"FallingRock_Group1");
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"FallingRock");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<FallingRock>(Scale, Rot, Pos);
		}
	}

	//!テクスチャの(スケール,ローテーション,ポジション)の構造体
	struct TextureTransformCreateDate
	{
		//!構造体テンプレート
		Vec2 scale = Vec2(0.0f);//!大きさ
		Vec3 position = Vec3(0.0f);//!位置

		TextureTransformCreateDate() :
			TextureTransformCreateDate(Vec2(0.0f), Vec3(0.0f))
		{}
		//!構造体の初期化
		TextureTransformCreateDate(
			const Vec2& scale,
			const Vec3& position
		) :
			scale(scale),
			position(position)
		{}
	};

	//!csvからデータの取り出し
	std::vector<TextureTransformCreateDate>GameStageTextureTransformDate(const wstring& FolderName, const wstring& csvName, const wstring& keyName)
	{
		std::vector<TextureTransformCreateDate>result;//!トランスフォームのデータを保存する配列
		vector<wstring>LineVec;//!変数名

		auto& app = App::GetApp();//!アプリの取得
		wstring DateDir;
		App::GetApp()->GetDataDirectory(DateDir);
		auto fullPass = DateDir + L"csvFolder\\" + FolderName + csvName;

		CsvFile csvFile;
		csvFile.SetFileName(fullPass);
		csvFile.ReadCsv();

		csvFile.GetSelect(LineVec, 0, keyName);

		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;//!トークン(カラム)の配置
			Util::WStrToTokenVector(Tokens, v, L',');//!トークン(カラム)単位で文字列を抽出(',')

			//!トークン(カラム)をスケール、回転、位置に読み込む
			Vec2 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str())
			);

			//!位置
			Vec3 Pos(
				(float)_wtof(Tokens[3].c_str()),
				(float)_wtof(Tokens[4].c_str()),
				(float)_wtof(Tokens[5].c_str())
			);

			result.push_back(TextureTransformCreateDate(Scale, Vec3(Pos.x, Pos.y, Pos.z)));

		}
		return result;
	}


	//タイムスプライト作成
	void GameStage::CreateTime() {
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"TimeTexture");//!csvの最初の行の文字の取得
		//!データ分回す
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

	//アイテムスプライト作成
	void GameStage::CreateMyitem1() {
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"Myitem1Texture");//!csvの最初の行の文字の取得
		//!データ分回す
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
	//Xボタンスプライト
	void GameStage::CreateXSprite() {
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"XSpriteTexture");//!csvの最初の行の文字の取得
		//!データ分回す
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
	//Yボタンスプライト
	void GameStage::CreateYSprite() {
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"YSpriteTexture");//!csvの最初の行の文字の取得
		//!データ分回す
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

	//ゲージの枠作成
	void GameStage::CreateMygage() {
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"MygageTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			AddGameObject<Mygage>(L"GAGE_TX", true,
				data.scale, data.position);
		}
	}
	//ゲージのバーの作成
	void GameStage::CreateGageSprite()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"GageSpriteTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			AddGameObject<GageSprite>(true,
				data.scale, data.position);
		}
	}


	void GameStage::CreateGageWhite()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"GageWhiteTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			AddGameObject<GageSpriteWhite>(true,
				data.scale, data.position);
		}
	}


	//プレイヤーの作成
	void GameStage::CreatePlayer() {
		//プレーヤーの作成
		auto PlayerPtr = AddGameObject<Player>();
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", PlayerPtr);
	}



	// 逃げるテロップ
	void GameStage::CreateTickerSprite()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"TickerSpriteTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			AddGameObject<TickerSprite>(L"FLEE_TX", true,
				data.scale, Vec2(data.position.x, data.position.y));
		}
	}

	// 柱を壊すテロップ
	void GameStage::CreateTelop()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"TelopTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			AddGameObject<Telop>(L"PillarBrake_TX", true,
				data.scale, Vec2(data.position.x, data.position.y));
		}
	}

	// 柱を壊すタイミングテロップ
	void GameStage::CreateTelop2()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"Telop2Texture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			AddGameObject<Telop2>(L"JustTiming_TX", true,
				data.scale, Vec2(data.position.x, data.position.y));
		}
	}

	// 出口前テロップ
	void GameStage::CreateTelop3()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"Telop3Texture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			AddGameObject<Telop3>(L"ClearNear_TX", true,
				data.scale, Vec2(data.position.x, data.position.y));
		}
	}

	// 壁を壊せ！！テロップ
	void GameStage::CreateTelop4()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"Telop4Texture");//!csvの最初の行の文字の取得
		//!データ分回す
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

	//カメラマンの作成
	void GameStage::CreateCameraman() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto ptrCameraman = AddGameObject<Cameraman>(2.0f);
		//シェア配列にCameramanを追加
		SetSharedGameObject(L"Cameraman", ptrCameraman);
		//シェア配列にOpeningCameramanを追加
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

			SetPhysicsActive(true);//物理計算有効

			// 「アプリ」オブジェクトのインスタンスを取得する（インスタンス：クラスの実態、オブジェクト指向のオブジェクトのこと）
			auto& app = App::GetApp();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//CSVファイルその読み込み
			m_CsvC.SetFileName(DataDir + L"stage" + Util::IntToWStr(Select) + L".csv");
			m_CsvC.ReadCsv();


			CreateViewLight();           //ビューとライトの作成
			CreateMultiSpark();          //エフェクト0の作成
			CreateMultiSpark1();         //エフェクト1の作成
			CreatePlayer();              //プレーヤーの作成
			BGM();                       //BGMの再生
			CreatePillar();              //柱の作成
			AddGameObject<EnemyObject>();//敵の作成
			CreateStageWall();           //ステージの壁の追加	
			CreateStageFloor();          //床の追加
			CreateObstacle1();           //障害物１の追加
			CreateFallingRock();         //落石
			CreateTrap();                //トラップの作成
			CreateExitWall();            //マヤでつくった出口
			CreateTime();                //タイムスプライト作成
			CreateWall();                //壊れる壁の作成
			CreateMyitem1();             //アイテムスプライト
			CreateXSprite();             //Xボタンのスプライトの作成
			CreateYSprite();             //Yボタンのスプライトの作成
			CreateMygage();              //ゲージの枠の作成
			CreateGageSprite();          //ゲージのスプライト1の作成
			CreateGageWhite();           //ゲージの背景の作成
			CreateTickerSprite();        //テロップ0の作成
			CreateTelop();               //テロップ1の作成
			CreateTelop2();              //テロップ2の作成
			CreateTelop3();              //テロップ3の作成             
			CreateCameraman();           //カメラマンの作成
			CreateTelop4();              //テロップ4の作成

		}
		catch (...) {
			throw;
		}
	}

	void GameStage::ToMyCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//MyCameraに変更
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_MyCameraView->GetCamera());
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);
			//m_MyCameraViewを使う
			SetView(m_MyCameraView);
			m_CameraSelect = CameraSelect::myCamera;
		}
	}

	void GameStage::OnUpdate() {

		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<GameStage>());
		ResetHandler.ResetHandle(GetThis<GameStage>());
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;
		if (m_TotalTime >= MAXTOTALTIME) {
			m_TotalTime = 0.0f;
		}
		//タイムを更新する
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
			//!ステートの遷移
		case GameState::Game://!何もしていない初期状態
			break;
		case GameState::Down://!ボスに追いつかれた状態
			ptrPlayer->SetGameState(GameState::FadeStart);
			break;
		case GameState::FadeStart://!フェードアウトが始まった状態

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

			//!ゲームオーバーの時にGameOverの文字の作成
			AddGameObject<GameOverSprite>(L"GAMEOVERTELOP_TX", true,
				Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.0f));

			m_createGameOverObjectFlg = true;
		case GameState::GameExit:
			//フェードアウトの作成
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
		// テロップの時間
		auto ptrStage = GetSharedGameObject<TickerSprite>(L"TickerSprite");
		// 時間の変数に足す
		m_idleTime += elapsedTime;
		if (m_idleTime >= MAXIDLETIME)
		{
			// 1秒後に表示がオフになる
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
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

}
//end basecross
