#include <FileSystem\FileSystem.h>
#include <FileSystem\File.h>
#include <Parsers\bitmap\BmpParser.h>

int main() {
	SE::platform::filesystem::OsFileSystem* fileSystem = new SE::platform::filesystem::OsFileSystem("C:/Users/rugge/Documents/Visual Studio 2015/Projects/sparkengine_desktop/assets");
	SE::platform::filesystem::OsFile* textureFile = fileSystem->openExplicitFileRead("C:/Users/rugge/Documents/Visual Studio 2015/Projects/sparkengine_desktop/assets/textures/barbara.bmp");

	SE::core::parser::binary::bitmap::BmpParser bmpParser = SE::core::parser::binary::bitmap::BmpParser();
	SE::core::parser::binary::bitmap::BmpImage bmpResult = SE::core::parser::binary::bitmap::BmpImage();

	bmpParser.readBitmap(bmpResult, textureFile);

	return 0;
}