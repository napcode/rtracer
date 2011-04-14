/*
 * =====================================================================================
 *
 *       Filename:  Material.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/05/2011 01:26:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */

#ifndef RAY_MATERIAL_H
#define RAY_MATERIAL_H

#include "math/Vec4.h"
#include "math/Vec3.h"


namespace ray
{
    extern math::Vec3 G_VN;
    extern math::Vec3 G_VE;
    extern math::Vec3 G_VC;
    class Texture;
    class Material 
    {
        public:
            Material();

            void setColor(math::Vec4 color);
            math::Vec4& getColor();
            const math::Vec4& getColor() const;

            // self radiation with color
            void setAmbient(float ambient);
            float getAmbient() const;

            void setDiffuse(float diffuse);
            float getDiffuse() const;

            void setReflection(float reflection);
            float getReflection() const;

            Material& operator=(const Material& rhs);

            void setTexture(Texture* tex);
            Texture* getTexture();
            const Texture* getTexture() const;

            void setNormalMap(Texture* normalmap);
            Texture* getNormalMap();
            const Texture* getNormalMap() const;

            float getScaleU() const {return _uscale;}
            float getScaleV() const {return _vscale;}
            void setScaleUV(float uscale, float vscale) {_uscale = uscale; _vscale = vscale;}

            void setFresnelFactor(float factor) { _fresnel_factor = factor;}
            float getFresnelFactor() const { return _fresnel_factor;}
            void setFresnelPower(float power) { _fresnel_power = power;}
            float getFresnelPower() const { return _fresnel_power;}

            void setTransparency(float value) { _color[3] = value; }
            float getTransparency( ) const { return _color[3]; }

            void setSpecular(float value) { _specular = value; }
            float getSpecular( ) const { return _specular; }
        private:
            math::Vec4 _color;
            float _ambient;
            float _diffuse;
            float _reflection;
            Texture *_texture;
            Texture *_normalmap;
            float _uscale;
            float _vscale;
            float _fresnel_factor;
            float _fresnel_power;
            float _specular;
    };
}

#endif
