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
	void MyClearStage::OnCreate() {
		MovieStage::OnCreate();
		wstring dataDir;
		//サンプルのためアセットディレクトリを取得
		App::GetApp()->GetAssetsDirectory(dataDir);
		wstring strMovie = dataDir + L"GameClear1.mp4";
		SetMovieFileName(strMovie);
		//再生
		Play();
	}

	void MyClearStage::OnUpdate() {
		auto elps = App::GetApp()->GetElapsedTime();
		m_Time += elps;
		//動画の時間調整
		if ( m_Time>= MovieTime) {
			SetAutoRepeat(true);
			//シーンの切り替え
			PostEvent(0.0f, GetThis<ObjectInterface>(),
				App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			return;
		}

	}


	
}
//end basecross
