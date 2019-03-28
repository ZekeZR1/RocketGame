#pragma once
namespace ZekeEngine {
	class CFont {
	public:
		enum TextType {
			en_Japanese,
			en_JapaneseBIG,
			en_Alphabet,
			en_numType
		};
		CFont();
		~CFont();
		/*!
		* @brief	�t�H���g��ݒ�B
		* @details	�f�t�H���g�t�H���g����ύX�������ꍇ��
		*  DirectX::SpriteFont���g�p���āA�t�H���g�����[�h���č����ւ����s���Ă��������B
		*/
		void SetFont(DirectX::SpriteFont* font)
		{
			m_spriteFont = font;
		}
		/*!
		 * @brief	�`��J�n�B
		 */
		void Begin();
		/*!
		 * @brief	�`��I���B
		 */
		void End();
		/*!
		 * @brief	�`��B
		 *@param[in]	text		�\���������e�L�X�g�B
		 *@param[in]	trans		���s�ړ��B
		 *@param[in]	color		�J���[�B
		 *@param[in]	rot			��]�B
		 *@param[in]	scale		�g��B
		 *@param[in]	pivot		��_�B
		 *						0.5, 0.5�ŉ摜�̒��S����_�B
		 *						0.0, 0.0�ŉ摜�̍����B
		 *						1.0, 1.0�ŉ摜�̉E��B
		 *						Unity��uGUI�ɏ����B
		 */
		void Draw(
			wchar_t const* text,
			const CVector2& position,
			const CVector4& color = CVector4::White,
			float rotation = 0.0f,
			float scale = 1.0f,
			CVector2 pivot = { 0.5f, 0.5f }
		);
		void SetTextType(TextType type) {
			m_type = type;
		}
	private:
		TextType m_type = en_Alphabet;
		DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//!<�X�v���C�g�o�b�`�B
		DirectX::SpriteFont*	m_spriteFont = nullptr;		//!<�X�v���C�g�t�H���g�B
		CMatrix m_scaleMat;
		ID3D11BlendState* m_blendState = nullptr;
		FLOAT m_BlendFactor[4];
		UINT m_SampleMask;
		ID3D11RasterizerState* m_rasterizerState;
		ID3D11DepthStencilState* m_depthStencilState;
		UINT m_StencilRef;
	};
}