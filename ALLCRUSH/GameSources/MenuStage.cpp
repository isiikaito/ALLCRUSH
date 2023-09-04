/*!
@file MenuStage.cpp
@brief メニューステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr float LOUDNESS = 0.5f;//!サウンドの大きさ
	constexpr float OFIDLETIME = 1.0f;//!描画オフの時間
	constexpr float ONIDLETIME = 1.5f;//!描画オンの時間
	//--------------------------------------------------------------------------------------
	//	メニューステージクラス実体
	//--------------------------------------------------------------------------------------
	void MenuStage::CreateViewLight() {

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
	std::vector<TextureTransformCreateDate>StageSelectTextureTransformDate(const wstring& keyName)
	{
		std::vector<TextureTransformCreateDate>result;	//!トランスフォームのデータを保存する配列
		vector<wstring>LineVec;							//!変数名
		auto& app = App::GetApp();						//!アプリの取得
		wstring DateDir;								//!データ
		App::GetApp()->GetDataDirectory(DateDir);		//!データを取得する
		auto fullPass = DateDir + L"csvFolder\\" + L"TexturecsvFolder\\" + L"MenuStageTextureTransform.csv";//!特定のcsvの取得	
		CsvFile csvFile;						//!csvの保存
		csvFile.SetFileName(fullPass);			//!ファイルの名前を保存する
		csvFile.ReadCsv();						//!csvを読みこっむ
		csvFile.GetSelect(LineVec, 0, keyName);	//!1行めが指定の文字か判別

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



			result.push_back(TextureTransformCreateDate(Scale, Vec3(Pos.x, Pos.y , Pos.z)));

		}
		return result;//!構造体の中身を配列に入れて返す
	}

    //アイテムスプライト作成
	void MenuStage::CreateMenuSprite1() {
		auto datas = StageSelectTextureTransformDate(L"MenuSprite1Texture");//!指定のキーの行を取得

		for (auto& data : datas)
		{
			AddGameObject<MenuSprite1>(L"Stage1_TX", true,
				data.scale, data.position);
		}
	}

	//アイテムスプライト作成
	void MenuStage::CreateMenuSprite2() {
		auto datas = StageSelectTextureTransformDate(L"MenuSprite2Texture");//!指定のキーの行を取得
		for (auto& data : datas)
		{
			AddGameObject<MenuSprite2>(L"Stage2_TX", true,
				data.scale, data.position);
		}
	}
	
	
	//初期化
	void MenuStage::OnCreate() {
		CreateViewLight();
		auto datas = StageSelectTextureTransformDate(L"MenuSelectTexture");//!指定のキーの行を取得
		for (auto& data : datas)
		{
			AddGameObject<TitleSprite>(L"MenuSelect_TX", false,
				data.scale, Vec2(data.position.x, data.position.y));
		}
		CreateMenuSprite1();//Stage1スプライト
		CreateMenuSprite2();//Stage2スプライト
	}
	
	void MenuStage::SelectStage()
	{
		//sceneの取得
		auto scene = App::GetApp()->GetScene<Scene>();
		//ステージ番号の取得
		auto Select = scene->GetStageSelect();
		//今選んでいるステージ番号を渡す
		Select = StageNum;
		scene->SetStageSelect(Select);
	}

	//十字キー上
	void MenuStage:: OnPushUP() {

		StageNum--;
		if (StageNum <= m_UPlimit)
		{
			StageNum = m_UPlimit;
		}
	}
	//十字キー下
	void MenuStage::OnPushDOWN() {
		StageNum++;
		if (StageNum >= m_DOWNlimit)
		{
			StageNum = m_DOWNlimit;
		}
	}

	
	void MenuStage::StageSprite1()
	{
	    //menuSprite1を取得する
		auto ptrStage1 = GetSharedGameObject<MenuSprite1>(L"MenuSprite1");
		//elapsedTimeを取得することにより時間を使える
		float elapsedTime = App::GetApp()->GetElapsedTime();
		if (OnPushBCheck) {
			if (!OnPushBCheck1)
			{
				auto WalkSound = App::GetApp()->GetXAudio2Manager();
				WalkSound->Start(L"WalkSound", 0, LOUDNESS);
				OnPushBCheck1 = true;
			}
		}
		//時間を変数に足す
		m_idleTime += elapsedTime;
		//十字キーを利用してnumが０の時
		 if (StageNum == m_UPlimit)
		    {   //時間が1秒後に表示がオフになる
				if (m_idleTime >= OFIDLETIME)
				  {
                     ptrStage1->SetDrawActive(false);
					  //時間が1.5秒後にオンになる
					  if (m_idleTime >= ONIDLETIME)
					   {
						 ptrStage1->SetDrawActive(true);
						 //m_idleTimeを0にすることにより元に戻ってループする。
						 m_idleTime = 0;
					   }
						return;
				  }
		 }
		 //選択されてないときは表示されたまま
		else{ ptrStage1->SetDrawActive(true); }

	}

	//ステージスプライト２の処理
	void MenuStage::StageSprite2()
	{
         //menuSprite1を取得する
		 auto ptrStage2 = GetSharedGameObject<MenuSprite2>(L"MenuSprite2");
		
		 //時間を変数に足す
		
		 //十字キーを利用してnumが０の時
		 if (StageNum == m_DOWNlimit)
		 {   //時間が1秒後に表示がオフになる
			 if (m_idleTime >= OFIDLETIME)
			 {
				 ptrStage2->SetDrawActive(false);
				 //時間が1.5秒後にオンになる
				 if (m_idleTime >= ONIDLETIME)
				 {
					 ptrStage2->SetDrawActive(true);
					 //m_idleTimeを0にすることにより元に戻ってループする。
					 m_idleTime = 0;
				 }
				 return;
			 }
		 }
		 //選択されてないときは表示されたまま
		 else { ptrStage2->SetDrawActive(true); }
				
				
	}
	//更新
	void MenuStage::OnUpdate() {
		SelectStage();
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<MenuStage>());

		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];
        //コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		StageSprite1();
		StageSprite2();	
		
	}

	
	//Bボタンが押されていたら
	void MenuStage::OnPushB() {
		
		wstring stagename[]
		{  
			L"ToMovieStage",
			L"ToGameStage"
		};
		if (m_OnPushB==true)
		{
			auto datas = StageSelectTextureTransformDate(L"FadeOutTexture");//!指定のキーの行を取得

			for (auto& data : datas)
			{
				//フェードアウトの作成
				AddGameObject<FadeOut>(true,
					data.scale, data.position);
			}
		SelectStage();
		//次のステージへ移行
		PostEvent(XM_PI / 2, GetThis<MenuStage>(), App::GetApp()->GetScene<Scene>(), stagename[StageNum]);
		m_OnPushB = false;
		}
		
		OnPushBCheck = true;
	}
}

//end namespace basecross