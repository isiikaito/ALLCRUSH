/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ムービーステージクラス
	//--------------------------------------------------------------------------------------
	//初期化
	void MyMovieStage::OnCreate() {
		MovieStage::OnCreate();
		wstring dataDir;
		//サンプルのためアセットディレクトリを取得
		App::GetApp()->GetAssetsDirectory(dataDir);
		wstring strMovie = dataDir + L"BOSU WALK TRUE.mp4";
		SetMovieFileName(strMovie);
		//再生
		Play();
	}

	void MyMovieStage::OnUpdate() {
		ResetHandler.ResetHandle(GetThis<MyMovieStage>());//コントローラーのチェック
		auto elps = App::GetApp()->GetElapsedTime();
		m_Time += elps;
		//動画時間の設定
		if (m_Time >= MovieTime) {
			SetAutoRepeat(false);
			//シーンの切り替え
			PostEvent(0.0f, GetThis<ObjectInterface>(),
				App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			return;
		}

	}
	void MyMovieStage::OnPushSkip()
	{
		MovieSkip();
	}
	void MyMovieStage::MovieSkip()
	{
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
	}
}
//end basecross
