/*
 * =====================================================================================
 *
 *       Filename:  Pixel.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/07/2011 10:46:36 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */

#include "Pixel.h"

using namespace ray;
using namespace math;

Pixel::Pixel()
{
}
math::Vec4::value_type Pixel::r() const
{
    return _data[0];
}
void Pixel::r(math::Vec4::value_type r)
{
    _data[0] = r;
}
math::Vec4::value_type Pixel::g() const
{
    return _data[1];
}
void Pixel::g(math::Vec4::value_type g)
{
    _data[1] = g;
}
math::Vec4::value_type Pixel::b() const
{
    return _data[2];
}
void Pixel::b(math::Vec4::value_type b)
{
    _data[2] = b;
}
void Pixel::set(const Vec3f& color)
{
    _data[0] = color.x();
    _data[1] = color.y();
    _data[2] = color.z();
}
void Pixel::set(const Vec4f& color)
{
    _data[0] = color.x();
    _data[1] = color.y();
    _data[2] = color.z();
    _data[3] = color.w();
}
void Pixel::accumulate(const Vec4f& color)
{
    _data = _data * (1.0f - color.w()) + color * color.w();
}
void Pixel::saturate()
{
    if (_data[0] > 1.0f) _data[0] = 1.0f;
    if (_data[1] > 1.0f) _data[1] = 1.0f;
    if (_data[2] > 1.0f) _data[2] = 1.0f;
}

Vec4 Pixel::get() const
{
    return _data;
}
Pixel& Pixel::operator=(const Pixel& rhs)
{
    _data = rhs._data;
    return *this;
}
PixelBuffer ray::clampPixelBuffer(const PixelBuffer& buffer)
{
    PixelBuffer retbuffer;
    retbuffer.resize(buffer.size());
    PixelBuffer::const_iterator it_in = buffer.begin();
    PixelBuffer::iterator it_out = retbuffer.begin();
    while (it_in != buffer.end()) {
        *it_out = *it_in;
        it_out->saturate();
        it_in++;
        it_out++;
    }
    return retbuffer;
}
