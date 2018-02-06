/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 17.05.17
 *
 */

#include <brew/core/SystemInfo.h>
#include <brew/core/BuildInfo.h>

#if BREW_PLATFORM == BREW_PLATFORM_LINUX
#include <brew/core/linux/LinuxSystemInfo.h>
#define BREW_SYSTEMQUERY_CLASS ::brew::detail::LinuxSystemQuery
#elif BREW_PLATFORM == BREW_PLATFORM_WINDOWS
#include <brew/core/windows/WindowsSystemInfo.h>
#define BREW_SYSTEMQUERY_CLASS ::brew::detail::WindowsSystemQuery
#elif BREW_PLATFORM == BREW_PLATFORM_ANDROID
#include <brew/core/android/AndroidSystemInfo.h>
#define BREW_SYSTEMQUERY_CLASS ::brew::detail::AndroidSystemQuery
#elif BREW_PLATFORM == BREW_PLATFORM_MACOS
#include <brew/core/macos/MacOSSystemInfo.h>
#define BREW_SYSTEMQUERY_CLASS ::brew::detail::MacOSSystemQuery
#elif BREW_PLATFORM == BREW_PLATFORM_IOS
#include <brew/core/ios/IOSSystemInfo.h>
#define BREW_SYSTEMQUERY_CLASS ::brew::detail::IOSSystemQuery
#endif // BREW_PLATFORM

namespace brew {

BREW_SYSTEMQUERY_CLASS systemQuery;

SizeT SystemInfo::getNumLogicalProcessors() {
    return systemQuery.getNumLogicalProcessors();
}

SizeT SystemInfo::getNumPhysicalProcessors() {
    return systemQuery.getNumPhysicalProcessors();
}

SizeT SystemInfo::getPhysicalMemory() {
    return systemQuery.getPhysicalMemory();
}

SizeT SystemInfo::getPhysicalMemoryAvailable() {
    return systemQuery.getPhysicalMemoryAvailable();
}

SizeT SystemInfo::getVirtualMemory() {
    return systemQuery.getVirtualMemory();
}

const String &SystemInfo::getPlatformName() {
    return systemQuery.getPlatformName();
}

SizeT SystemInfo::getTotalMemory() {
    return getVirtualMemory() + getPhysicalMemory();
}

const String& SystemInfo::getCWD() {
    return systemQuery.getCWD();
}

} /* namespace brew */
