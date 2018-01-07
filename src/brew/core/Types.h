/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Feb 11, 2016
 */

/**
 * \file
 * \brief This header file contains elemental type definitions used by BREW.
 */

#ifndef BREW_TYPES_H
#define BREW_TYPES_H

#include "BuildInfo.h"

#include <stddef.h>
#include <stdint.h>
#include <limits>
#include <typeinfo>
#include <string>
#include <sstream>

namespace brew {

typedef size_t SizeT;

typedef int8_t s8;
typedef uint8_t u8;

typedef int16_t s16;
typedef uint16_t u16;

typedef int32_t s32;
typedef uint32_t u32;

typedef int64_t s64;
typedef uint64_t u64;

typedef float f32;
typedef double f64;
typedef f32 Real;

typedef u8 Byte;

typedef std::string String;
typedef std::stringstream StringStream;
typedef char Char;

typedef std::wstring WideString;
typedef std::wstringstream WideStringStream;
typedef wchar_t WideChar;

} /* namespace brew */

#endif /* BREW_TYPES_H */
