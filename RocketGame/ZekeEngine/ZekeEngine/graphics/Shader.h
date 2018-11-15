#pragma once
namespace ZekeEngine {
	class Shader
	{
	public:
		enum class EnType {
			VS,			//!<���_�V�F�[�_�[
			PS,			//!<�s�N�Z���V�F�[�_�[
			CS,			//!<�R���s���[�g�V�F�[�_�[
		};
		Shader();
		~Shader();
	
		void Release();

		bool Load(const char* filePath, const char* entryFuncName, EnType shaderType);

		void* GetBody()
		{
			return m_shader;
		}
		ID3D11InputLayout* GetInputLayout()
		{
			return m_inputLayout;
		}
		void* GetByteCode()
		{
			return m_blobOut->GetBufferPointer();
		}
		size_t GetByteCodeSize()
		{
			return m_blobOut->GetBufferSize();
		}
	private:
		void*				m_shader = nullptr;					
		ID3D11InputLayout*	m_inputLayout = nullptr;			
		ID3DBlob*			m_blobOut = nullptr;
	};
}