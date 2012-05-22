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

#include "os.h"
#include <map>
#include <string>
#include "math/Vec4.h"
#include "Pixel.h"

namespace ray
{
    /**
     * @brief a texture class
     * stores all data needed for texturing
     */
    class Texture
    {
        /**
         * enum with all available types. Currently not in use
         */
        enum TYPE
        {
            RGB = 0, 
            ARGB, 
            ALPHA, 
            NORMAL
        };
        public:
        //! ctor
        Texture();

        /**
         * get the texture element (a pixel) at the given UV coordinates
         * @param u u coordinate
         * @param v v coordinate
         */
        math::Vec4 getTexel(float u, float v) const;

        /**
         * set the width of the Texture
         * @param width the width of the Texture
         */
        void setWidth(uint32_t width) {_width = width;}
        /**
         * get the width of the Texture
         * @return the width of the Texture
         */
        uint32_t getWidth() const {return _width;}
        /**
         * set the height of the Texture
         * @param height the height of the Texture
         */
        void setHeight(uint32_t height) {_height = height;}
        /**
         * get the height of the Texture
         * @return the height of the Texture
         */
        uint32_t getHeight() const {return _height;}

        /**
         * get the TYPE of the Texture. Currently not used.
         */
        TYPE getType() const {return _type;}

        /**
         * get the pixel buffer (e.g. the data) of the Texture
         * @return a reference to the pixel buffer
         */
        PixelBuffer& getImageBuffer() {return _texture;}
        /**
         * get the pixel buffer (e.g. the data) of the Texture - const version
         * @return a reference to the pixel buffer
         */
        const PixelBuffer& getImageBuffer() const {return _texture;}
        private:
        uint32_t _width;
        uint32_t _height;
        TYPE _type;
        PixelBuffer _texture;

    };
    typedef std::map<std::string, Texture*> TextureVector;

}
#endif
