#pragma once
#include "Skelton.h"

namespace ZekeEngine {
	//TODO : インスタンシング描画できるようにする

	enum EnFbxUpAxis {
		enFbxUpAxisY,		//Y-up
		enFbxUpAxisZ,		//Z-up
	};

	class SkinModel : Noncopyable
	{
	public:
		//メッシュが見つかったときのコールバック関数。
		using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
		/*!
		*@brief	デストラクタ。
		*/
		~SkinModel();

		/*!
		*@brief	初期化。
		*@param[in]	filePath		ロードするcmoファイルのファイルパス。
		*@param[in] enFbxUpAxis		fbxの上軸。デフォルトはenFbxUpAxisZ。
		*/
		void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);

		CMatrix GetWorldMatrix() {
			return m_worldMatrix;
		}
		/*!
		*@brief	モデルをワールド座標系に変換するためのワールド行列を更新する。
		*@param[in]	position	モデルの座標。
		*@param[in]	rotation	モデルの回転。
		*@param[in]	scale		モデルの拡大率。
		*/
		void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
		/*!
		*@brief	ボーンを検索。
		*@param[in]		boneName	ボーンの名前。
		*@return	見つかったボーン。見つからなかった場合はnullptrを返します。
		*/
		Bone* FindBone(const wchar_t* boneName)
		{
			int boneId = m_skeleton.FindBoneID(boneName);
			return m_skeleton.GetBone(boneId);
		}
		void FindVertexPosition(std::function<void(CVector3* pos)>func);
		/*!
		*@brief	モデルを描画。
		*@param[in]	viewMatrix		カメラ行列。
		*  ワールド座標系の3Dモデルをカメラ座標系に変換する行列です。
		*@param[in]	projMatrix		プロジェクション行列。
		*  カメラ座標系の3Dモデルをスクリーン座標系に変換する行列です。
		*/
		void Draw(CMatrix viewMatrix, CMatrix projMatrix);
		void Draw();
		/*!
		*@brief	スケルトンの取得。
		*/
		Skeleton& GetSkeleton()
		{
			return m_skeleton;
		}
		/*!
		*@brief	メッシュを検索する。
		*@param[in] onFindMesh		メッシュが見つかったときのコールバック関数
		*/
		void FindMesh(OnFindMesh onFindMesh) const
		{
			for (auto& modelMeshs : m_modelDx->meshes) {
				for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
					onFindMesh(mesh);
				}
			}
		}
		/*!
		*@brief	SRVのレジスタ番号。
		*/
		enum EnSkinModelSRVReg {
			enSkinModelSRVReg_DiffuseTexture = 0,		//!<ディフューズテクスチャ。
			enSkinModelSRVReg_BoneMatrix,				//!<ボーン行列。
		};

		void SetDirColor(CVector4 col) {
			m_DirCol = col;
		}

		void SetDirLight(CVector4 dir) {
			m_DirLight = dir;
		}
	private:
		/*!
		*@brief	サンプラステートの初期化。
		*/
		void InitSamplerState();
		/*!
		*@brief	定数バッファの作成。
		*/
		void InitConstantBuffer();
		/*!
		*@brief	スケルトンの初期化。
		*@param[in]	filePath		ロードするcmoファイルのファイルパス。
		*/
		void InitSkeleton(const wchar_t* filePath);

	private:
		//定数バッファ。
		struct SVSConstantBuffer {
			CMatrix mWorld;
			CMatrix mView;
			CMatrix mProj;
			CVector4 mCol;
			CVector4 mDir;
		};
		EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBXの上方向。
		ID3D11Buffer*		m_cb = nullptr;					//!<定数バッファ。
		Skeleton			m_skeleton;						//!<スケルトン。
		CMatrix				m_worldMatrix;					//!<ワールド行列。
		DirectX::Model*		m_modelDx;						//!<DirectXTKが提供するモデルクラス。
		ID3D11SamplerState* m_samplerState = nullptr;		//!<サンプラステート。
		CVector4 m_DirLight = { 0.707,-0.707,0.0f,0.0f };
		CVector4 m_DirCol = { 1.0f,1.0f,1.0f,1.0f };
	};
}
