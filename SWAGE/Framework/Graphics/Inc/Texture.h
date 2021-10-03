#pragma once

namespace SWAGE::Graphics
{
	class Texture
	{
	public:
		static void UnbindPS(uint32_t slot);

	public:
		enum class Format
		{
			RGBA_U8,
			RGBA_F32
		};

		Texture() = default;
		virtual ~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		virtual void Initialize(const std::filesystem::path& fileName);
		virtual void Initialize(uint32_t width, uint32_t height, Format format = Format::RGBA_U8);
		virtual void Terminate();

		void BindVS(uint32_t slot) const;
		void BindPS(uint32_t slot) const;

		void* GetRawData() const { return mShaderResourceView; }

		uint32_t GetWidth() const { return mWidth; }
		uint32_t GetHeight() const { return mHeight; }

	protected:
		ID3D11ShaderResourceView* mShaderResourceView = nullptr;

	private:
		friend class SpriteRenderer;

		uint32_t mWidth;
		uint32_t mHeight;
	};
}