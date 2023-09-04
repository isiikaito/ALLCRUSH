/*!
@file GageSprite.h
@brief ゲージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum PowerGage {
		notpower,
		first,
		second,
		treed
	};
	//ゲージ
	class GageSprite : public GameObject
	{
		bool m_Trace;		//透明
		Vec2 m_StartScale;	//大きさ
		Vec3 m_StartPos;	//位置
		float m_TotalTime;	//時間の取得
		int m_BreakCount;   //壁を壊した回数
		int m_PowerON;      //パワーアップ中
		int m_PowerOFF;     //パワーアップしてない
		Vec3 firstScale;	//壁一つ目の大きさ
		Vec3 firstpos;		//壁一つ目の位置
		Vec3 secondScale;	//壁二つ目の大きさ
		Vec3 secondpos;		//壁二つ目の位置
		Vec3 treedScale;	//壁三つ目の大きさ
		Vec3 treedpos;		//壁三つ目の位置
		Col4 m_TextureColor;//!テクスチャの色
		Col4 m_gageTextureColor;//!ゲージの色
		vector<VertexPositionColor>m_BackupVertices;//バックアップ頂点データ

		
	public:
		GageSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~GageSprite();
		virtual void OnCreate() override;//初期化
		virtual void OnUpdate()override; //更新

	};
}