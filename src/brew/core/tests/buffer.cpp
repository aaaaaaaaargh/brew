#include <gtest/gtest.h>

#include <brew/core/HeapBuffer.h>
#include <brew/core/StringBuffer.h>

using namespace brew;

TEST(Buffer, StringBufferCopy) {
	String str("Hello world!");
	String str2("------------");
	StringBuffer a(str);
	StringBuffer b(str2);
	EXPECT_EQ(a.getSize(), str.size()+1);
	EXPECT_EQ(a.getString(), str);

	HeapBuffer buf(a.getSize());
	a.copyTo(buf);
	buf.copyTo(b);
	EXPECT_EQ(b.getString(), str);
}
