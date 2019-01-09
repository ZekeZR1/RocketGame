#include "stdafx.h"
#include "PhysicsDebugDraw.h"

namespace ZekeEngine {
	//CPhysicsDebugDraw::~CPhysicsDebugDraw() {
	//	if (m_CB != nullptr) {
	//		m_CB->Release();
	//	}
	//}

	//void CPhysicsDebugDraw::Init()
	//{
	//	InitConstantBuffer();
	//	//ラインストリップのテスト。
	//	m_primitive.Create(
	//		D3D_PRIMITIVE_TOPOLOGY_LINELIST,
	//		static_cast<int>(m_vertexBuffer.size()),
	//		sizeof(CVector4),
	//		&m_vertexBuffer[0],
	//		0,
	//		CIndexBuffer::enIndexType_32,
	//		nullptr
	//	);
	//	m_vs.Load("Assets/shader/linePrimitive.fx", "VSMain", Shader::EnType::VS);
	//	m_ps.Load("Assets/shader/linePrimitive.fx", "PSMain", Shader::EnType::PS);
	//	m_cb.Create(nullptr, sizeof(SConstantBuffer));
	//}
	//void CPhysicsDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	//{
	//	int baseIndex = m_numLine * 2;
	//	m_vertexBuffer[baseIndex].Set(CVector3(from.x(), from.y(), from.z()));
	//	m_vertexBuffer[baseIndex + 1].Set(CVector3(to.x(), to.y(), to.z()));
	//	m_numLine++;

	//}

	//void CPhysicsDebugDraw::InitConstantBuffer(){
	//	D3D11_BUFFER_DESC desc;

	//	ZeroMemory(&desc, sizeof(desc));
	//	desc.Usage = D3D11_USAGE_DEFAULT;
	//	desc.ByteWidth = (((sizeof(SConstantBuffer) - 1) / 16) + 1) * 16;	//16バイトアライメントに切りあげる。
	//	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//	desc.CPUAccessFlags = 0;
	//	GraphicsEngine().GetD3DDevice()->CreateBuffer(&desc, NULL, &m_CB);
	//}

	//void CPhysicsDebugDraw::EndDraw()
	//{
	//	//定数バッファの更新。
	//	SConstantBuffer cb;
	//	cb.mView = MainCamera().GetViewMatrix();
	//	cb.mProj = MainCamera().GetProjectionMatrix();
	//	//Engine().GetGraphicsEngine().GetD3DDeviceContext()->UpdateSubresource(m_CB, 0, nullptr, &cb, 0, 0);
	//	GraphicsEngine().GetD3DDeviceContext()->VSSetConstantBuffers(0, 1, &m_CB);
	//	GraphicsEngine().GetD3DDeviceContext()->IASetInputLayout(m_vs.GetInputLayout());
	//	GraphicsEngine().GetD3DDeviceContext()->UpdateSubresource(m_CB, 0, nullptr, &cb, 0, 0);
	//	m_primitive.Draw(m_numLine * 2,m_vs,m_ps);
	//}
}