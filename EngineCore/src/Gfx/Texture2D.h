#pragma once

#include <GL/glew.h>
#include "../Types.h"
#include "../Resources/Image.h"
#include "GraphicsResource.h"

namespace Shard
{
	namespace Gfx
	{
		enum class TextureWrap
		{
			Repeat = GL_REPEAT,
			Clamp = GL_CLAMP,
			MirroredRepeat = GL_MIRRORED_REPEAT,
			ClampToEdge = GL_CLAMP_TO_EDGE,
			ClampToBorder = GL_CLAMP_TO_BORDER
		};

		enum class TextureFilter
		{
			Linear = GL_LINEAR,
			Nearest = GL_NEAREST
		};

		class Texture2D : public GraphicsResource
		{
		private:
			static TextureWrap s_WrapMode;
			static TextureFilter s_FilterMode;

		protected:
			GLuint m_TextureID;
			uint m_Width;
			uint m_Height;

		protected:
			Texture2D();

		public:
			Texture2D(const Resources::Image& image);

			virtual ~Texture2D();

		public:
			inline void Bind() const { glBindTexture(GL_TEXTURE_2D, m_TextureID); }
			inline void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

			inline GLuint GetTextureID() const { return m_TextureID; }
			inline uint GetWidth() const { return m_Width; }
			inline uint GetHeight() const { return m_Height; }

			void Dispose() override;

		public:
			static inline void SetWrapMode(TextureWrap mode) { s_WrapMode = mode; }
			static inline void SetFilterMode(TextureFilter mode) { s_FilterMode = mode; }
		};
	}
}