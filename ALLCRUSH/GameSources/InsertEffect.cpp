/*!
@file ImpactSmoke.cpp
@brief　エフェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// 複数のスパーククラス
	//--------------------------------------------------------------------------------------
	//構築と破棄
	InsertEffect::InsertEffect(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	InsertEffect::~InsertEffect() {}

	//初期化
	void InsertEffect::OnCreate() {
		SetAddType(true);
	}

	void InsertEffect::OnUpdate() {
		for (auto ptrParticle : GetParticleVec()) {
			for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
				if (rParticleSprite.m_Active) {
					rParticleSprite.m_Color.z += 0.05f;
					if (rParticleSprite.m_Color.z >= 1.0f) {
						rParticleSprite.m_Color.z = 1.0f;
					}
				}
			}
		}
		//親クラスのOnUpdate()を呼ぶ
		MultiParticle::OnUpdate();
	}



	void InsertEffect::InsertSplash(const Vec3& Pos) {
		auto ptrParticle = InsertParticle(25);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"Splash_TX");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {	
			//エフェクトの可動域指定
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.3f - 0.1f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.3f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.3f - 0.1f;
			//エフェクトサイズの調整
			rParticleSprite.m_LocalScale.x = 5.0f;
			rParticleSprite.m_LocalScale.y = 5.0f;
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Color = Col4(0.8f, 0.8f, 0.0f, 0.4f);

			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 18.0f,
				rParticleSprite.m_LocalPos.y * 18.0f,
				rParticleSprite.m_LocalPos.z * 18.0f
			);
			//色の指定
		}
	}

	void InsertEffect::InsertSpark(const Vec3& Pos) {
		auto ptrParticle = InsertParticle(18);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"Spark_TX");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
			//エフェクトの可動域指定
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.3f - 0.1f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.3f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.3f - 0.1f;
			//エフェクトサイズの調整
			rParticleSprite.m_LocalScale.x = 5.0f;
			rParticleSprite.m_LocalScale.y = 5.0f;
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 28.0f,
				rParticleSprite.m_LocalPos.y * 28.0f,
				rParticleSprite.m_LocalPos.z * 28.0f
			);
			//色の指定
			rParticleSprite.m_Color = Col4(0.4f,0.4f,0.4f,0.8f);
		}
	}

	void InsertEffect::InsertSpeedUp(const Vec3& Pos) {
		auto ptrParticle = InsertParticle(16);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"SpeedUp_TX");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
			//エフェクトの可動域指定
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.2f - 0.1f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.2f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.2f - 0.1f;
			//エフェクトサイズの調整
			rParticleSprite.m_LocalScale.x = 5.0f;
			rParticleSprite.m_LocalScale.y = 5.0f;
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 25.0f,
				rParticleSprite.m_LocalPos.y * 25.0f,
				rParticleSprite.m_LocalPos.z * 25.0f
			);
			//色の指定
			rParticleSprite.m_Color = Col4(0.4f, 0.4f, 0.4f, 0.8f);
		}
	}

	void InsertEffect::InsertImpact(const Vec3& Pos) {
		auto ptrParticle = InsertParticle(10);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"Impact_TX");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
			//エフェクトの可動域指定
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.2f - 0.1f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.2f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.2f - 0.1f;
			//エフェクトサイズの調整
			rParticleSprite.m_LocalScale.x = 5.0f;
			rParticleSprite.m_LocalScale.y = 5.0f;
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 20.0f,
				rParticleSprite.m_LocalPos.y * 20.0f,
				rParticleSprite.m_LocalPos.z * 20.0f
			);
			//色の指定
			rParticleSprite.m_Color = Col4(0.4f, 0.4f, 0.4f, 0.8f);
		}
	}

	void InsertEffect::InsertPowerUp(const Vec3& Pos) {
		auto ptrParticle = InsertParticle(14);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"PowerUp_TX");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
			//エフェクトの可動域指定
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.2f - 0.1f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.2f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.2f - 0.1f;
			//エフェクトサイズの調整
			rParticleSprite.m_LocalScale.x = 5.0f;
			rParticleSprite.m_LocalScale.y = 5.0f;
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 18.0f,
				rParticleSprite.m_LocalPos.y * 18.0f,
				rParticleSprite.m_LocalPos.z * 18.0f
			);
			//色の指定
			rParticleSprite.m_Color = Col4(0.4f, 0.4f, 0.4f, 0.8f);
		}
	}
}
// end namespace basecross
