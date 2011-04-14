/*
 * =====================================================================================
 *
 *       Filename:  Texture.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/05/2011 01:27:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */

#ifndef RAY_TEXTURE_H
#define RAY_TEXTURE_H

#include <stdint.h>
#include <vector>
#include "math/Vec4.h"
#include "Pixel.h"

namespace ray
{
    class Texture
    {
        enum TYPE
        {
            RGB = 0, 
            ARGB, 
            ALPHA, 
            NORMAL
        };
        public:
        Texture();
        math::Vec4 getTexel(float u, float v) const;

        void setWidth(uint32_t width) {_width = width;}
        uint32_t getWidth() const {return _width;}
        void setHeight(uint32_t height) {_height = height;}
        uint32_t getHeight() const {return _height;}
        TYPE getType() const {return _type;}
        PixelBuffer& getImageBuffer() {return _texture;}
        const PixelBuffer& getImageBuffer() const {return _texture;}
        private:
        uint32_t _width;
        uint32_t _height;
        TYPE _type;
        PixelBuffer _texture;

    };
    typedef std::vector<Texture*> TextureVector;

}
#endif
