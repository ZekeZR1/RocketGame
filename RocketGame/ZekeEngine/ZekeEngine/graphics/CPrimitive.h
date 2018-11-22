#pragma once
namespace ZekeEngine {
	class CPrimitive
	{
	public:
		CPrimitive();
		~CPrimitive();
		/*!
		*@brief	�v���~�e�B�u�쐬�B
		*@param[in]	topology			�g�|���W�[�B
		*@param[in]	numVertex			���_�̐��B
		*@param[in]	vertexStride		���_�X�g���C�h�B
		*@param[in]	pSrcVertexBuffer	�\�[�X�ƂȂ钸�_�o�b�t�@�B
		*@param[in]	numIndex			�C���f�b�N�X�̐��B
		*@param[in]	indexType			�C���f�b�N�X�̌^�B
		*@param[in]	pSrcIndexBuffer		�\�[�X�ƂȂ�C���f�b�N�X�o�b�t�@�B
		*@retval	true	�쐬����
		*@retval	false	�쐬���s�B
		*/
		bool Create(
			D3D_PRIMITIVE_TOPOLOGY topology,
			int numVertex,
			int vertexStride,
			void* pSrcVertexBuffer,
			int numIndex,
			CIndexBuffer::EnIndexType indexType,
			void* pSrcIndexBuffer
		);
		/*!
		*@brief	�����I�Ƀ����[�X�B
		*/
		void Release();
		/*!
		*@brief	�`��B
		*/
		void Draw();
	private:
		CVertexBuffer			m_vertexBuffer;		//!<���_�o�b�t�@�B
		CIndexBuffer			m_indexBuffer;		//!<�C���f�b�N�X�o�b�t�@�B
		D3D_PRIMITIVE_TOPOLOGY	m_topology;			//!<�g�|���W�[�B
	};
}