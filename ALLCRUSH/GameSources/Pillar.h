/**
*@file Pillar.h
*@brief 柱オブジェクトの実装が定義されているヘッダーファイル
*@author Kaito Isii
*@details 柱オブジェクトの実装
*/
#pragma once
#include "stdafx.h"

/** basecross共通のネームスペース */
namespace basecross {

	class Pillar : public GameObject {
		Vec3 m_Scale;    //!大きさ
		Vec3 m_Rotation; //!回転
		Vec3 m_Position; //!位置
		StaticModelDeta m_pillarModelData;			//!家のモデルデータ
	public:
		/**
		* コンストラクタ
		*/
		Pillar(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
　　　　* デストラクタ
　　　　*/
		virtual ~Pillar() {}

		/**
		* 柱オブジェクトの初期パラメータを初期化する関数
		*/
		virtual void OnCreate() override;

		/**
		* 柱オブジェクトの更新をする関数
		*/
		virtual void OnUpdate() override;

		
	};
}
