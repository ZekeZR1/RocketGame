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
	//頂点バッファを設定。
	//IASetVertexBuffer(m_vertexBuffer);
	//IASetIndexBuffer(m_indexBuffer);
	//プリミティブのトポロジーを設定。
	//IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//描画。
	//DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
}
