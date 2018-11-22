#include "stdafx.h"
#include "CPrimitive.h"

CPrimitive::CPrimitive()
{
}


CPrimitive::~CPrimitive()
{
	Release();
}

void CPrimitive::Release()
{
	m_vertexBuffer.Release();
	m_indexBuffer.Release();
}
bool CPrimitive::Create(
	D3D_PRIMITIVE_TOPOLOGY topology,
	int numVertex,
	int vertexStride,
	void* pSrcVertexBuffer,
	int numIndex,
	CIndexBuffer::EnIndexType indexType,
	void* pSrcIndexBuffer)
{
	Release();
	bool result = m_vertexBuffer.Create(numVertex, vertexStride, pSrcVertexBuffer);
	if (!result) {
		return false;
	}
	result = m_indexBuffer.Create(numIndex, indexType, pSrcIndexBuffer);
	if (!result) {
		return false;
	}

	return true;
}
void CPrimitive::Draw()
{
	//���_�o�b�t�@��ݒ�B
	//IASetVertexBuffer(m_vertexBuffer);
	//IASetIndexBuffer(m_indexBuffer);
	//�v���~�e�B�u�̃g�|���W�[��ݒ�B
	//IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//�`��B
	//DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
}
