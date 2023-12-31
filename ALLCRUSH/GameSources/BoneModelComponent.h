/*!
@file BoneModelComponent.h
@author Kaito Isii
@brief  ボーン付きモデルの実装
*/
#pragma once
#include "stdafx.h"

/**basecross共通のネームペース*/
namespace basecross
{

	struct BoneModelDeta
	{
		Vec3 scale;					//!大きさ
		Vec3 rotation;				//!回転
		Vec3 position;				//!位置
		Vec3 modelScale;			//!メッシュの大きさ
		Vec3 modelRotOrigin;		//!回転の起源
		Vec3 modelRotation;			//!メッシュの回転
		Vec3 modelPosition;			//!メッシュの位置
		wstring meshName;			//!メッシュの名前
		wstring tnaMeshName;		//!タンジェント付きメッシュの名前
		wstring nomalMapTex;		//!法線マップテクスチャ
	
	};

	class BoneModelComponent :public Component
	{

		BoneModelDeta m_modelData;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	このコンポーネントを所持するゲームオブジェクト
		*/
		explicit BoneModelComponent(const shared_ptr<GameObject>& GameObjectPtr, BoneModelDeta& modelData) :
			Component(GameObjectPtr),
			m_modelData(modelData) {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~BoneModelComponent() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		*/
		virtual void OnCreate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新処理
		*/
		virtual void OnUpdate()override{}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	};
}
