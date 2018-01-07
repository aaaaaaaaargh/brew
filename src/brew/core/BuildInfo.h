/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: Aug 18 2016
 *
 */

/**
 *\file compile-time environment information. Most of this are macro definitions.
 */

#ifndef BREW_BUILDINFO_H
#define BREW_BUILDINFO_H

#ifndef BREW_DEBUG
#ifdef DEBUG
#define BREW_DEBUG 1
#else
#define BREW_DEBUG 0
#endif
#endif // BREW_DEBUG

// Architectures. Query with BREW_ARCH.
#define BREW_ARCH_ARM   0x2
#define BREW_ARCH_ARM64 0x3
#define BREW_ARCH_X86   0x4

// Architecture detection
#if defined(__amd64__) || defined(_M_X64)
#define BREW_ARCH BREW_ARCH_AMD64
#endif

#if defined(__arm__) || defined(__thumb__) || defined(_M_ARM)
#define BREW_ARCH BREW_ARCH_ARM
#endif

#if defined(__aarch64__)
#define BREW_ARCH BREW_ARCH_ARM64
#endif

#if defined(__i386) || defined(_M_IX86) || defined(__X86__) || defined(_X86_)
#define BREW_ARCH BREW_ARCH_X86
#endif

#ifndef BREW_ARCH
#error Target architecture is not supported.
#endif

// Platforms. Query with BREW_PLATFORM
#define BREW_PLATFORM_LINUX 0x1
#define BREW_PLATFORM_WINDOWS 0x2
#define BREW_PLATFORM_ANDROID 0x3
#define BREW_PLATFORM_MACOS 0x4
#define BREW_PLATFORM_IOS 0x5

// Platform detection
#if defined(__linux__)
#define BREW_PLATFORM BREW_PLATFORM_LINUX
#endif

#if defined(__MINGW32__ ) or defined (MSW)
#define BREW_PLATFORM BREW_PLATFORM_WINDOWS
#endif

#if defined(__APPLE__)
#include <TargetConditionals.h>
#if __APPLE__ == TARGET_OS_IPHONE
#define BREW_PLATFORM BREW_PLATFORM_IOS
#else
#define BREW_PLATFORM BREW_PLATFORM_MACOS
#endif
#endif

#ifndef BREW_PLATFORM
#error Target platform is not supported.
#endif

// Compiler. Query with BREW_COMPILER
#define BREW_COMPILER_GCC 0x1

#ifdef __GNUC__
#define BREW_COMPILER BREW_COMPILER_GCC
#endif

#ifndef BREW_COMPILER
#error Target compiler is not supported.
#endif

#endif //BREW_BUILDINFO_H
