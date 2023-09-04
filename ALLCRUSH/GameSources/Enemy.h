/*!
@file Enemy.h
@brief 敵など
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	追いかける敵オブジェクト
	//--------------------------------------------------------------------------------------

	class EnemyObject : public GameObject {
		//ステートマシーン
		unique_ptr< StateMachine<EnemyObject> >  m_StateMachine;
		Vec3 m_StartPos;              //位置
		float m_StateChangeSize;	  //ステートを切り替える距離感
	    Vec3 m_Force;	              //フォース
		Vec3 m_Velocity;              //速度
		float m_Speed = 35.0f;         //スピード
		float EnemyTime;              //鳴き声
		float StopTime;               //ボスの止めている時間
		int StopCount;                //ボスが動きを止めているかどうか
		int PillarCount;              //柱が消えているかどうか
		int m_EnemySetDrawActiveCount;//ボスの表示カウント
		float m_Telop2Time;           //テロップ2
		bool m_Event;				  //イベントの判断	

	public:
		//構築と破棄
		EnemyObject(const shared_ptr<Stage>& StagePtr); // , const Vec3& StartPos);
		virtual ~EnemyObject();
		//初期化
		virtual void OnCreate() override;
		//アクセサ
		const unique_ptr<StateMachine<EnemyObject>>& GetStateMachine() {
			return m_StateMachine;
		}
		float GetStateChangeSize() const {
			return m_StateChangeSize;
		}
		const Vec3& GetForce()const {
			return m_Force;
		}
		void SetForce(const Vec3& f) {
			m_Force = f;
		}
		void AddForce(const Vec3& f) {
			m_Force += f;
		}
		const Vec3& GetVelocity()const {
			return m_Velocity;
		}
		void SetVelocity(const Vec3& v) {
			m_Velocity = v;
		}
		void ApplyForce();
		Vec3 GetTargetPos()const;
		//更新
		virtual void OnUpdate() override;
		//衝突判定
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		int GetEnemySetDrawActiveCount()const {
			return m_EnemySetDrawActiveCount;
		}
		void SetEnemySetDrawActiveCount(int m_EnemySetDrawActiveCount) {
			m_EnemySetDrawActiveCount = m_EnemySetDrawActiveCount;
		}
		
	};

	//--------------------------------------------------------------------------------------
	//	用途: プレイヤーから遠いときの移動
	//--------------------------------------------------------------------------------------
	class SeekFarState : public ObjState<EnemyObject>
	{
		SeekFarState() {}
	public:
		static shared_ptr<SeekFarState> Instance();
		virtual void Enter(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Execute(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Exit(const shared_ptr<EnemyObject>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	用途: プレイヤーから近いときの移動
	//--------------------------------------------------------------------------------------
	class SeekNearState : public ObjState<EnemyObject>
	{
		SeekNearState() {}
	public:
		static shared_ptr<SeekNearState> Instance();
		virtual void Enter(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Execute(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Exit(const shared_ptr<EnemyObject>& Obj)override;
	};
	
}

