#pragma once

namespace Renderer
{


enum class InternalFormat
{
    R8,
    RG8,
    RGB8,
    RGBA8,

    R16,
    RG16,
    RGB16,
    RGBA16,

    R16F,
    RG16F,
    RGB16F,
    RGBA16F,

    R32F,
    RG32F,
    RGB32F,
    RGBA32F,

    R8I,
    RG8I,
    RGBA8I,

    R8UI,
    RG8UI,
    RGBA8UI,

    R16I,
    RG16I,
    RGBA16I,

    R16UI,
    RG16UI,
    RGBA16UI,

    R32I,
    RG32I,
    RGBA32I,

    R32UI,
    RG32UI,
    RGBA32UI,

    Depth16,
    Depth24,
    Depth32F,

    Depth24Stencil8,
    Depth32FStencil8
};

enum class Format
{
    Red,
    RG,
    RGB,
    RGBA,

    RedInteger,
    RGInteger,
    RGBInteger,
    RGBAInteger,

    DepthComponent,
    DepthStencil
};

enum class DataType
{
    UnsignedByte,
    Byte,

    UnsignedShort,
    Short,

    UnsignedInt,
    Int,

    HalfFloat,
    Float
};

enum class TextureType
{
    Texture2D,
    Texture3D,
    TextureCube
};

namespace Helper{

unsigned int ToGL(InternalFormat format);
unsigned int ToGL(Format format);
unsigned int ToGL(DataType type);
unsigned int ToGL(TextureType type);

} // Helper

} // Renderer
