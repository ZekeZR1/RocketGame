#pragma once
namespace ZekeEngine {
	class CConstantBuffer : public CGPUBuffer {
	public:
		CConstantBuffer();
		~CConstantBuffer();
		bool Create(const void* pInitData, int bufferSize);
	};
}