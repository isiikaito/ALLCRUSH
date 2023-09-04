/*!
@file TitleStage.cpp
@brief タイトルステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr float LOUDNESS = 0.5f;//!サウンドの大きさ

	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス実体
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {

		auto ptrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto ptrCamera = ObjectFactory::Create<Camera>();
		ptrView->SetCamera(ptrCamera);

		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}
	//!テクスチャの(スケール,ローテーション,ポジション)の構造体
	struct TextureTransformCreateDate
	{
		//!構造体テンプレート
		Vec2 scale = Vec2(0.0f);	//!大きさ
		Vec3 position = Vec3(0.0f);	//!位置

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
	std::vector<TextureTransformCreateDate>TitleTextureTransformDate(const wstring& keyName)
	{
		std::vector<TextureTransformCreateDate>result;	//!トランスフォームのデータを保存する配列
		vector<wstring>LineVec;							//!変数名
		auto& app = App::GetApp();						//!アプリの取得
		wstring DateDir;								//!データ
		App::GetApp()->GetDataDirectory(DateDir);		//!データを取得する
		auto fullPass = DateDir + L"csvFolder\\" + L"TexturecsvFolder\\" + L"TitleStageTextureTransform.csv";//!特定のcsvの取得
		CsvFile csvFile;						//!csvの保存
		csvFile.SetFileName(fullPass);			//!ファイルの名前を保存する
		csvFile.ReadCsv();						//!csvを読みこっむ
		csvFile.GetSelect(LineVec, 0, keyName);	//!1行めが指定の文字か判別

		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;						//!トークン(カラム)の配置
			Util::WStrToTokenVector(Tokens, v, L',');	//!トークン(カラム)単位で文字列を抽出(',')

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
		return result;//!構造体の中身を配列に入れて返す
	}
	
	//初期化
	void TitleStage::OnCreate() {
		ShowCursor(false);
		CreateViewLight();

		auto datas = TitleTextureTransformDate( L"TitleTextureTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			AddGameObject<TitleSprite>(
				L"TITLE_TX", 
				false,
				data.scale,
 Vec2(data.position.x, data.position.y));
		}
	
		
	}

	//更新
	void TitleStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
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
			//フェードアウトの作成
			AddGameObject<FadeOut>( true,
				Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f,0.0f));
			PostEvent(XM_PI / 2, GetThis<TitleStage>(), App::GetApp()->GetScene<Scene>(), L"ToMenuStage");
			m_OnPushB = false;
		}
	
			OnPushBCheck = true;
	}
	
}

//end namespace basecross