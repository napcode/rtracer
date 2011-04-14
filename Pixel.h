/*
 * =====================================================================================
 *
 *       Filename:  Pixel.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/05/2011 09:52:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */
#ifndef RAY_PIXEL_H
#define RAY_PIXEL_H

#include <vector>
#include <stdint.h>
#include "math/Vec3.h"
#include "math/Vec4.h"
namespace ray 
{
    class Pixel 
    {
        public:
            Pixel();

            math::Vec4::value_type r() const;
            void r(math::Vec4::value_type r);

            math::Vec4::value_type g() const;
            void g(math::Vec4::value_type g);

            math::Vec4::value_type b() const;
            void b(math::Vec4::value_type b);

            void set(const math::Vec3& color);
            void set(const math::Vec4& color);
            void accumulate(const math::Vec4& color);
            void saturate();
            math::Vec4 get() const;

            Pixel& operator=(const Pixel& rhs);
        private:
            math::Vec4 _data;

    };
    typedef std::vector<Pixel> PixelBuffer;
    PixelBuffer clampPixelBuffer(const PixelBuffer& buffer);
}
#endif 
