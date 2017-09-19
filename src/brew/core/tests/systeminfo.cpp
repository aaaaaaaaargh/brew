#include <gtest/gtest.h>

#include <brew/core/SystemInfo.h>

using namespace brew;

#if BREW_PLATFORM == BREW_PLATFORM_LINUX
TEST(SystemInfo, DetectsLinux) {
	EXPECT_EQ("Linux", SystemInfo::getPlatformName());
}
#endif // BREW_PLATFORM_LINUX

TEST(SystemInfo, DetectsCPU) {
	EXPECT_LT(0, SystemInfo::getNumLogicalProcessors());
	EXPECT_LT(0, SystemInfo::getNumPhysicalProcessors());
	EXPECT_LE(SystemInfo::getNumPhysicalProcessors(), SystemInfo::getNumLogicalProcessors());
}

TEST(SystemInfo, DetectsMemory) {
	EXPECT_LT(0, SystemInfo::getPhysicalMemory());
	EXPECT_LT(0, SystemInfo::getVirtualMemory());
	EXPECT_LT(0, SystemInfo::getTotalMemory());
}