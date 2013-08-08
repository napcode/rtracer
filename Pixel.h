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
 *         Author:  Mathias Buhr (), buhr@apparatus.de
 *
 * =====================================================================================
 */
#ifndef RAY_PIXEL_H
#define RAY_PIXEL_H

#include <vector>
#include "os.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
namespace ray 
{
    /**
     * @brief a picture element
     */
    class Pixel 
    {
        public:
            //! ctor
            Pixel();

            /**
             * get the value of the red channel
             * @return the value of the red channel
             */
            math::Vec4::value_type r() const;
            /**
             * set the value of the red channel
             * @param r the new value of the red channel
             */
            void r(math::Vec4::value_type r);

            /**
             * get the value of the green channel
             * @return the value of the green channel
             */
            math::Vec4::value_type g() const;
            /**
             * set the value of the green channel
             * @param g the new value of the green channel
             */
            void g(math::Vec4::value_type g);

            /**
             * get the value of the blue channel
             * @return the value of the blue channel
             */
            math::Vec4::value_type b() const;
            /**
             * set the value of the blue channel
             * @param b the new value of the blue channel
             */
            void b(math::Vec4::value_type b);

            /**
             * set the pixel to a given color 
             * @param color a vector containing all color information
             */
            void set(const math::Vec3& color);
            /**
             * set the pixel  to a given color
             * @param color a vector containing all color information + transparency
             */
            void set(const math::Vec4& color);

            /**
             * combine this pixel with the given color. useful for transparency stuff
             * @param color a color vector with transparency < 1.0f
             */
            void accumulate(const math::Vec4& color);

            /**
             * clamp the pixel so it can be written/displayed
             */
            void saturate();

            /**
             * get the current color of the pixel
             * @return a vector with the current color
             */
            math::Vec4 get() const;

            /**
             * assignment operator
             */
            Pixel& operator=(const Pixel& rhs);
        private:
            math::Vec4 _data;

    };
    typedef std::vector<Pixel> PixelBuffer;
    PixelBuffer clampPixelBuffer(const PixelBuffer& buffer);
}
#endif 
