#ifndef __BMPLOADER_H__
#define __BMPLOADER_H__

#include <PlatformUtils.h>

#include <Texture\TextureResource.h>
#include <FileSystem\File.h>

#include <Parsers\bitmap\BmpParser.h>

#define SE_EDITOR_LOAD_BMP_TEXTURE(bmpFileHandle) SE::editor::loader::image::BmpLoader::loadBmpTexture(bmpFileHandle);

namespace SE {
	namespace editor {
		namespace loader {
			namespace image {
				class BmpLoader
				{
					typedef SE::resource::Texture							TextureResource;
					typedef SE::core::parser::binary::bitmap::BmpParser		BmpParser;
					typedef SE::core::parser::binary::bitmap::BmpImage		BmpImage;

				public:
					BmpLoader() {}
					~BmpLoader() {}

				public:
					static const TextureResource&	loadBmpTexture(SPARK_INOUT_P(SE::platform::filesystem::OsFile) bmpFileHandle) {
						TextureResource result = TextureResource();

						BmpParser parser = BmpParser();
						BmpImage image = BmpImage();

						parser.readBitmap(image, bmpFileHandle);

						result.
					};
				};
			}
		}
	}
}
#endif // !__BMPLOADER_H__