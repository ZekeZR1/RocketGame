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
void CPrimitive::Draw(int numVertex ,Shader& vsShader, Shader& psShader)
{
	UINT stride = m_vertexBuffer.GetStride();
	GraphicsEngine().GetD3DDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer.GetBody(), &stride, 0);
	GraphicsEngine().GetD3DDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
	GraphicsEngine().GetD3DDeviceContext()->Draw(numVertex, 0);
}
