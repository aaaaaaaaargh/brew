/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  Color.cpp
 *
 *  Created on: Dec 13, 2015
 *      Author: void
 */

#include <brew/video/Color.h>
#include <brew/math/Math.h>

namespace brew {

std::ostream& operator<<(std::ostream& s, const ColorFormat& fmt) {
    switch (fmt) {
        case ColorFormat::C8I:
            s << "C8I";
            break;
        case ColorFormat::C8U:
            s << "C8U";
            break;
        case ColorFormat::RGB8I:
            s << "RGB8I";
            break;
        case ColorFormat::RGBA8I:
            s << "RGBA8I";
            break;
        case ColorFormat::RGB8U:
            s << "RGB8U";
            break;
        case ColorFormat::RGBA8U:
            s << "RGBA8U";
            break;

        case ColorFormat::C16I:
            s << "C16I";
            break;
        case ColorFormat::C16U:
            s << "C16U";
            break;
        case ColorFormat::RGB16I:
            s << "RGB16I";
            break;
        case ColorFormat::RGBA16I:
            s << "RGBA16I";
            break;
        case ColorFormat::RGB16U:
            s << "RGB16U";
            break;
        case ColorFormat::RGBA16U:
            s << "RGBA16U";
            break;

        case ColorFormat::C32I:
            s << "C32I";
            break;
        case ColorFormat::C32U:
            s << "C32U";
            break;
        case ColorFormat::RGB32I:
            s << "RGB32I";
            break;
        case ColorFormat::RGBA32I:
            s << "RGBA32I";
            break;
        case ColorFormat::RGB32U:
            s << "RGB32U";
            break;
        case ColorFormat::RGBA32U:
            s << "RGBA32U";
            break;

        case ColorFormat::C32F:
            s << "C32F";
            break;
        case ColorFormat::RGB32F:
            s << "RGB32F";
            break;
        case ColorFormat::RGBA32F:
            s << "RGBA32F";
            break;
    }
    return s;
}

SizeT ColorFormatInfo::getChannelSize(const ColorFormat& fmt) {
    switch (fmt) {
        case ColorFormat::C8I:
        case ColorFormat::C8U:
        case ColorFormat::RGB8I:
        case ColorFormat::RGBA8I:
        case ColorFormat::RGB8U:
        case ColorFormat::RGBA8U:
            return 1;

        case ColorFormat::C16I:
        case ColorFormat::C16U:
        case ColorFormat::RGB16I:
        case ColorFormat::RGBA16I:
        case ColorFormat::RGB16U:
        case ColorFormat::RGBA16U:
            return 2;

        case ColorFormat::C32I:
        case ColorFormat::C32U:
        case ColorFormat::C32F:
        case ColorFormat::RGB32I:
        case ColorFormat::RGB32U:
        case ColorFormat::RGBA32I:
        case ColorFormat::RGBA32U:
        case ColorFormat::RGB32F:
        case ColorFormat::RGBA32F:
            return 4;
    }
    return 0;
}

SizeT ColorFormatInfo::getNumChannels(const ColorFormat& fmt) {
    switch (fmt) {

        case ColorFormat::C8I:
        case ColorFormat::C16I:
        case ColorFormat::C32I:

        case ColorFormat::C8U:
        case ColorFormat::C16U:
        case ColorFormat::C32U:

        case ColorFormat::C32F:
            return 1;

        case ColorFormat::RGB8I:
        case ColorFormat::RGB16I:
        case ColorFormat::RGB32I:

        case ColorFormat::RGB8U:
        case ColorFormat::RGB16U:
        case ColorFormat::RGB32U:

        case ColorFormat::RGB32F:
            return 3;

        case ColorFormat::RGBA8I:
        case ColorFormat::RGBA16I:
        case ColorFormat::RGBA32I:

        case ColorFormat::RGBA8U:
        case ColorFormat::RGBA16U:
        case ColorFormat::RGBA32U:

        case ColorFormat::RGBA32F:
            return 4;
    }
    return 0;
}

Real Color::rReal() const {
    return static_cast<Real>(r) / 255.0f;
}

Real Color::gReal() const {
    return static_cast<Real>(g) / 255.0f;
}

Real Color::bReal() const {
    return static_cast<Real>(b) / 255.0f;
}

Real Color::aReal() const {
    return static_cast<Real>(a) / 255.0f;
}

Color::Color(u8 r, u8 g, u8 b, u8 a) :
    r(r), g(g), b(b), a(a) {}

void Color::set(u8 _r, u8 _g, u8 _b, u8 _a) {
    r = _r;
    g = _g;
    b = _b;
    a = _a;
}

void Color::set(Real _r, Real _g, Real _b, Real _a) {
    r = static_cast<u8>(255.0 * _r);
    g = static_cast<u8>(255.0 * _g);
    b = static_cast<u8>(255.0 * _b);
    a = static_cast<u8>(255.0 * _a);
}

u8 Color::operator[](u8 n) const {
    return static_cast<const u8*>(&r)[n];
}

bool Color::operator==(const Color& other) const {
    return other.r == r && other.g == g && other.b == b && other.a == a;
}

Color Color::fromMemory(const Byte* data, const ColorFormat& fmt) {
    Color col;

    const s8 S16toS8 = 1;
    const s8 S32toS8 = 1;
    const s8 U16toU8 = 1;
    const s8 U32toU8 = 1;

    switch (fmt) {

        case ColorFormat::C8I: {
            const s8& c = *reinterpret_cast<const s8*>(data);
            col.set((u8) c, (u8) c, (u8) c, 255);
            break;
        }

        case ColorFormat::C16I: {
            const s8 c = *reinterpret_cast<const s16*>(data) * S16toS8;
            col.set((u8) c, (u8) c, (u8) c, 255);
            break;
        }

        case ColorFormat::C32I: {
            const s8 c = *reinterpret_cast<const s32*>(data) * S32toS8;
            col.set((u8) c, (u8) c, (u8) c, 255);
            break;
        }

        case ColorFormat::C8U: {
            const u8& c = *reinterpret_cast<const u8*>(data);
            col.set((u8) c, (u8) c, (u8) c, 255);
            break;
        }

        case ColorFormat::C16U: {
            const u8 c = *reinterpret_cast<const u16*>(data) * U16toU8;
            col.set(c, c, c, 255);
            break;
        }

        case ColorFormat::C32U: {
            const u8 c = *reinterpret_cast<const u32*>(data) * U32toU8;
            col.set(c, c, c, 255);
            break;
        }

        case ColorFormat::C32F: {
            const f32& c = *reinterpret_cast<const f32*>(data);
            col.set(c, c, c, 1.0);
            break;
        }

        case ColorFormat::RGB8I: {
            const s8* rgb = reinterpret_cast<const s8*>(data);
            col.set((u8) rgb[0], (u8) rgb[1], (u8) rgb[2], 255);
            break;
        }

        case ColorFormat::RGB16I: {
            const SizeT sz = sizeof(s16);
            const s8 r = *reinterpret_cast<const s16*>(data) * S16toS8;
            const s8 g = *reinterpret_cast<const s16*>(data + sz) * S16toS8;
            const s8 b = *reinterpret_cast<const s16*>(data + sz + sz) * S16toS8;
            col.set((u8) r, (u8) g, (u8) b, 255);
            break;
        }

        case ColorFormat::RGB32I: {
            const SizeT sz = sizeof(s32);
            const s8 r = *reinterpret_cast<const s32*>(data) * S32toS8;
            const s8 g = *reinterpret_cast<const s32*>(data + sz) * S32toS8;
            const s8 b = *reinterpret_cast<const s32*>(data + sz + sz) * S32toS8;
            col.set((u8) r, (u8) g, (u8) b, 255);
            break;
        }

        case ColorFormat::RGB8U: {
            const u8* rgb = reinterpret_cast<const u8*>(data);
            col.set(rgb[0], rgb[1], rgb[2], 255);
            break;
        }

        case ColorFormat::RGB16U: {
            const SizeT sz = sizeof(u16);
            const u8 r = *reinterpret_cast<const u16*>(data) * U16toU8;
            const u8 g = *reinterpret_cast<const u16*>(data + sz) * U16toU8;
            const u8 b = *reinterpret_cast<const u16*>(data + sz + sz) * U16toU8;
            col.set(r, g, b, 255);
            break;
        }

        case ColorFormat::RGB32U: {
            const SizeT sz = sizeof(u32);
            const u8 r = *reinterpret_cast<const u32*>(data) * U32toU8;
            const u8 g = *reinterpret_cast<const u32*>(data + sz) * U32toU8;
            const u8 b = *reinterpret_cast<const u32*>(data + sz + sz) * U32toU8;
            col.set(r, g, b, 255);
            break;
        }

        case ColorFormat::RGB32F: {
            const SizeT sz = sizeof(f32);
            const f32& r = *reinterpret_cast<const f32*>(data);
            const f32& g = *reinterpret_cast<const f32*>(data + sz);
            const f32& b = *reinterpret_cast<const f32*>(data + sz + sz);
            col.set(r, g, b, 1.0);
            break;
        }

        case ColorFormat::RGBA8I: {
            const s8* rgb = reinterpret_cast<const s8*>(data);
            col.set((u8) rgb[0], (u8) rgb[1], (u8) rgb[2], (u8) rgb[3]);
            break;
        }

        case ColorFormat::RGBA16I: {
            const SizeT sz = sizeof(s16);
            const s8 r = *reinterpret_cast<const s16*>(data) * S16toS8;
            const s8 g = *reinterpret_cast<const s16*>(data + sz) * S16toS8;
            const s8 b = *reinterpret_cast<const s16*>(data + sz + sz) * S16toS8;
            const s8 a = *reinterpret_cast<const s16*>(data + sz + sz + sz) * S16toS8;
            col.set((u8) r, (u8) g, (u8) b, (u8) a);
            break;
        }

        case ColorFormat::RGBA32I: {
            const SizeT sz = sizeof(s32);
            const s8 r = *reinterpret_cast<const s32*>(data) * S32toS8;
            const s8 g = *reinterpret_cast<const s32*>(data + sz) * S32toS8;
            const s8 b = *reinterpret_cast<const s32*>(data + sz + sz) * S32toS8;
            const s8 a = *reinterpret_cast<const s32*>(data + sz + sz + sz) * S32toS8;
            col.set((u8) r, (u8) g, (u8) b, (u8) a);
            break;
        }

        case ColorFormat::RGBA8U: {
            const u8* rgb = reinterpret_cast<const u8*>(data);
            col.set(rgb[0], rgb[1], rgb[2], rgb[3]);
            break;
        }

        case ColorFormat::RGBA16U: {
            const SizeT sz = sizeof(u16);
            const u16 r = *reinterpret_cast<const u16*>(data) * U16toU8;
            const u16 g = *reinterpret_cast<const u16*>(data + sz) * U16toU8;
            const u16 b = *reinterpret_cast<const u16*>(data + sz + sz) * U16toU8;
            const u16 a = *reinterpret_cast<const u16*>(data + sz + sz + sz) * U16toU8;
            col.set((u8) r, (u8) g, (u8) b, (u8) a);
            break;
        }

        case ColorFormat::RGBA32U: {
            const SizeT sz = sizeof(u32);
            const u32 r = *reinterpret_cast<const u32*>(data) * U32toU8;
            const u32 g = *reinterpret_cast<const u32*>(data + sz) * U32toU8;
            const u32 b = *reinterpret_cast<const u32*>(data + sz + sz) * U32toU8;
            const u32 a = *reinterpret_cast<const u32*>(data + sz + sz + sz) * U32toU8;
            col.set((u8) r, (u8) g, (u8) b, (u8) a);
            break;
        }

        case ColorFormat::RGBA32F: {
            const SizeT sz = sizeof(f32);
            const f32& r = *reinterpret_cast<const f32*>(data);
            const f32& g = *reinterpret_cast<const f32*>(data + sz);
            const f32& b = *reinterpret_cast<const f32*>(data + sz + sz);
            const f32& a = *reinterpret_cast<const f32*>(data + sz + sz + sz);
            col.set(r, g, b, a);
            break;
        }
    }

    return col;
}

void Color::toMemory(Byte* data, const ColorFormat& fmt) const {
    switch (fmt) {

        case ColorFormat::C8I: {
            typedef s8 t;
            auto* d = reinterpret_cast<t*>(data);
            t c = (r + g + b) / 3;
            d[0] = c;
            break;
        }

        case ColorFormat::C16I: {
            typedef s16 t;
            auto* d = reinterpret_cast<t*>(data);
            t c = (r + g + b) / 3;
            d[0] = c;
            break;
        }

        case ColorFormat::C32I: {
            typedef s32 t;
            auto* d = reinterpret_cast<t*>(data);
            t c = (r + g + b) / 3;
            d[0] = c;
            break;
        }

        case ColorFormat::C8U: {
            typedef u8 t;
            auto* d = reinterpret_cast<t*>(data);
            t c = (r + g + b) / 3;
            d[0] = c;
            break;
        }

        case ColorFormat::C16U: {
            typedef u16 t;
            auto* d = reinterpret_cast<t*>(data);
            t c = (r + g + b) / 3;
            d[0] = c;
            break;
        }

        case ColorFormat::C32U: {
            typedef u32 t;
            auto* d = reinterpret_cast<t*>(data);
            t c = (r + g + b) / 3;
            d[0] = c;
            break;
        }

        case ColorFormat::C32F: {
            typedef f32 t;
            auto* d = reinterpret_cast<t*>(data);
            t c = (rReal() + gReal() + bReal()) / 3.0;
            d[0] = c;
            break;
        }

        case ColorFormat::RGB8I: {
            typedef s8 t;
            auto* d = reinterpret_cast<t*>(data);
            d[0] = static_cast<t>(r);
            d[1] = static_cast<t>(g);
            d[2] = static_cast<t>(b);
            break;
        }

        case ColorFormat::RGB16I: {
            typedef s16 t;
            auto* d = reinterpret_cast<t*>(data);
            d[0] = static_cast<t>(r);
            d[1] = static_cast<t>(g);
            d[2] = static_cast<t>(b);
            break;
        }

        case ColorFormat::RGB32I: {
            typedef s32 t;
            auto* d = reinterpret_cast<t*>(data);
            d[0] = static_cast<t>(r);
            d[1] = static_cast<t>(g);
            d[2] = static_cast<t>(b);
            break;
        }

        case ColorFormat::RGB8U: {
            typedef u8 t;
            auto* d = reinterpret_cast<t*>(data);
            d[0] = static_cast<t>(r);
            d[1] = static_cast<t>(g);
            d[2] = static_cast<t>(b);
            break;
        }

        case ColorFormat::RGB16U: {
            typedef u16 t;
            auto* d = reinterpret_cast<t*>(data);
            d[0] = static_cast<t>(r);
            d[1] = static_cast<t>(g);
            d[2] = static_cast<t>(b);
            break;
        }

        case ColorFormat::RGB32U: {
            typedef u32 t;
            auto* d = reinterpret_cast<t*>(data);
            d[0] = static_cast<t>(r);
            d[1] = static_cast<t>(g);
            d[2] = static_cast<t>(b);
            break;
        }

        case ColorFormat::RGB32F: {
            typedef f32 t;
            auto* d = reinterpret_cast<t*>(data);
            d[0] = rReal();
            d[1] = gReal();
            d[2] = bReal();
            break;
        }

        case ColorFormat::RGBA8I: {
            typedef s8 t;
            auto* d = reinterpret_cast<t*>(data);
            d[0] = static_cast<t>(r);
            d[1] = static_cast<t>(g);
            d[2] = static_cast<t>(b);
            d[3] = static_cast<t>(a);
            break;
        }

        case ColorFormat::RGBA16I: {
            typedef s16 t;
            auto* d = reinterpret_cast<t*>(data);
            d[0] = static_cast<t>(r);
            d[1] = static_cast<t>(g);
            d[2] = static_cast<t>(b);
            d[3] = static_cast<t>(a);
            break;
        }

        case ColorFormat::RGBA32I: {
            typedef s32 t;
            auto* d = reinterpret_cast<t*>(data);
            d[0] = static_cast<t>(r);
            d[1] = static_cast<t>(g);
            d[2] = static_cast<t>(b);
            d[3] = static_cast<t>(a);
            break;
        }

        case ColorFormat::RGBA8U: {
            typedef u8 t;
            auto* d = reinterpret_cast<t*>(data);
            d[0] = static_cast<t>(r);
            d[1] = static_cast<t>(g);
            d[2] = static_cast<t>(b);
            d[3] = static_cast<t>(a);
            break;
        }

        case ColorFormat::RGBA16U: {
            typedef u16 t;
            auto* d = reinterpret_cast<t*>(data);
            d[0] = static_cast<t>(r);
            d[1] = static_cast<t>(g);
            d[2] = static_cast<t>(b);
            d[3] = static_cast<t>(a);
            break;
        }

        case ColorFormat::RGBA32U: {
            typedef u32 t;
            auto* d = reinterpret_cast<t*>(data);
            d[0] = static_cast<t>(r);
            d[1] = static_cast<t>(g);
            d[2] = static_cast<t>(b);
            d[3] = static_cast<t>(a);
            break;
        }

        case ColorFormat::RGBA32F: {
            typedef f32 t;
            auto* d = reinterpret_cast<t*>(data);
            d[0] = rReal();
            d[1] = gReal();
            d[2] = bReal();
            d[3] = aReal();
            break;
        }
    }
}

Color Color::operator*(Real factor) const {
    Color r(*this);
    r *= factor;
    return r;
}

Color& Color::operator*=(Real factor) {
    r = math::clamp<u8>(static_cast<u8>(r * factor), 0, 255);
    g = math::clamp<u8>(static_cast<u8>(g * factor), 0, 255);
    b = math::clamp<u8>(static_cast<u8>(b * factor), 0, 255);
    a = math::clamp<u8>(static_cast<u8>(a * factor), 0, 255);
    return *this;
}

const Color Color::BLACK(0x00, 0x00, 0x00);
const Color Color::BLUE(0x00, 0x00, 0xFF);
const Color Color::GREEN(0x00, 0xFF, 0x00);
const Color Color::YELLOW(0xFF, 0xFF, 0x00);
const Color Color::RED(0xFF, 0x00, 0x00);
const Color Color::MAGENTA(0xFF, 0x00, 0xFF);
const Color Color::BROWN(0xAA, 0x55, 0x00);
const Color Color::WHITE(0xFF, 0xFF, 0xFF);
const Color Color::GRAY(0x88, 0x88, 0x88);
const Color Color::CYAN(0x00, 0xFF, 0xFF);

std::ostream& operator<<(std::ostream& s, const Color& c) {
    s << "(" << static_cast<u16>(c.r) << "," << static_cast<u16>(c.g) << "," << static_cast<u16>(c.b) << ","
      << static_cast<u16>(c.a) << ")";
    return s;
}

} /* namespace brew */
