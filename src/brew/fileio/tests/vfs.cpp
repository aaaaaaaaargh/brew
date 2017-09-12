#include <gtest/gtest.h>

#include <fstream>

#include <brew/core/Types.h>

#include <brew/fileio/FileStream.h>
#include <brew/fileio/VirtualFileSystem.h>
#include <brew/fileio/LocalFileSystem.h>
#include <brew/fileio/HeapFileSystem.h>

using namespace brew;

TEST(FileIO, OpenReadFileStreams)
{
	std::filebuf* buf = new std::filebuf();
	FileStream fs(buf);

	char cbuf[1024];
	fs.read(cbuf, 100);

	EXPECT_FALSE(fs.good());
	EXPECT_TRUE(fs.eof());
}

TEST(FileIO, NormalizePaths)
{
	String path = VirtualFileSystem::normalizePath("/already/normalized/path");
	EXPECT_EQ(path, "/already/normalized/path");

	path = VirtualFileSystem::normalizePath("/././/this//is/./ /messed/../cleaned///up//");
	EXPECT_EQ(path, "/this/is/cleaned/up/");

	path = VirtualFileSystem::normalizePath("                     ");
	EXPECT_EQ(path, "");

	path = VirtualFileSystem::normalizePath("       /             ");
	EXPECT_EQ(path, "/");

	path = VirtualFileSystem::normalizePath("         test / a / b / c / d            ");
	EXPECT_EQ(path, "test/a/b/c/d");

	path = VirtualFileSystem::normalizePath(" ../hello/../good/day/../../hello/world   ");
	EXPECT_EQ(path, "../hello/world");
}

TEST(FileIO, GetDirectory)
{
	VirtualFileSystem vfs;
	EXPECT_THROW(vfs.getDirectory("/"), IOException);
}

TEST(FileIO, LocalFileSystem)
{
	VirtualFileSystem vfs;
	vfs.mount("/", std::make_unique<LocalDirectory>("."));
	auto dir = vfs.getDirectory("/");
	for (auto filename : dir->getEntries())
	{
		EXPECT_TRUE(dir->exists(filename));
		if (!dir->isDirectory(filename))
		{
			auto file = dir->getFile(filename);
			auto stream = file->open();
		}
	}

	EXPECT_THROW(dir->getFile("this_file_does_not_exist"), IOException);
}

TEST(FileIO, HeapFileSystem)
{
	VirtualFileSystem vfs;
	std::map<brew::String, std::vector<brew::Byte> > heapData;

	brew::String file_contents = "Contents of /a.txt";
	heapData["a.txt"] = std::vector<brew::Byte>(file_contents.begin(), file_contents.end());

	file_contents = "Contents of /first/b.txt";
	heapData["first/b.txt"] = std::vector<brew::Byte>(file_contents.begin(), file_contents.end());

	file_contents = "Contents of /first/c.txt";
	heapData["first/something/illegal/../../c.txt"] = std::vector<brew::Byte>(file_contents.begin(), file_contents.end());

	file_contents = "Contents of /first/second/d.txt";
	heapData["first/third/../second/third/and/many/more/d.txt"] = std::vector<brew::Byte>(file_contents.begin(), file_contents.end());

	vfs.mount("/", std::make_unique<HeapDirectory>(heapData));
	auto dir = vfs.getDirectory("/first");

	dir = vfs.getDirectory("/first/second/third/and/many/more");
	EXPECT_TRUE(dir->exists("d.txt"));
}

TEST(FileIO, RootMountPoint) {
	VirtualFileSystem vfs;
	std::map<brew::String, std::vector<brew::Byte> > heapData;

	brew::String file_contents = "Contents of /a.txt";
	heapData["a.txt"] = std::vector<brew::Byte>(file_contents.begin(), file_contents.end());

	vfs.mount("/", std::make_unique<HeapDirectory>(heapData));

	EXPECT_NO_THROW(vfs.getFile("/a.txt"));
}

