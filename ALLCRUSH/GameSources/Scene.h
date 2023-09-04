/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase {
		//--------------------------------------------------------------------------------------
		/*!
		@brief テクスチャの読み込み
		*/
		//--------------------------------------------------------------------------------------
		void RoadTexture(const wstring& TextureName, const wstring& UseTextureName);

		//--------------------------------------------------------------------------------------
		/*!
		@brief スタティックモデルの読み込み
		*/
		//--------------------------------------------------------------------------------------
		void RoadStaticModelMesh(const wstring& staticModelbmfName, const wstring& staticModelMeshName);

		//--------------------------------------------------------------------------------------
		/*!
		@brief ボーンモデルのの読み込み
		*/
		//--------------------------------------------------------------------------------------
		void RoadBoneModel(const wstring& BoneModelbmfName, const wstring& BoneModelMeshName, const wstring& BomeModelMeshTangentName);

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		void CreateResourses();
		bool m_MovieActive;
		int m_StageSelect;
		Scene() :SceneBase() , m_MovieActive(false),m_StageSelect(1){}
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief イベント取得
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;
		bool IsMovieActive() const {
			return m_MovieActive;
		}
		//ステージの選択の取得
		int GetStageSelect()const {
			return m_StageSelect;
		}
		void SetStageSelect(int StageSelect) {
			m_StageSelect = StageSelect;
		}

		
	};

}

//end basecross

