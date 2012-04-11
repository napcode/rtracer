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

    /**
     * @brief Class for storing material properties
     */
    class Material 
    {
        public:
            //! ctor
            Material();

            /**
             * Set the color of this Material. This has no effect when a Texture is assigned.
             * @param color the new color of this Material
             */
            inline void setColor(math::Vec4 color) { _color = color; }
            /**
             * get the color of this Material. This color has no effect when a Texture is assigned.
             * @return the current color of this Material
             */
            inline math::Vec4& getColor() { return _color; }
            /**
             * get the color of this Material. This color has no effect when a Texture is assigned. const version
             * @return the current color of this Material
             */
            inline const math::Vec4& getColor() const { return _color; }

            /**
             * set the ambient factor for this Material. The ambient term has the effect of "self-radiance".
             * @param ambient the new ambient factor for the Material
             */
            inline void setAmbientFactor(float ambient) { _ambient = ambient; }
            /**
             * get the ambient factor for this Material. The ambient term has the effect of "self-radiance".
             * @return the current ambient foactor for this Material
             */
            inline float getAmbientFactor() const { return _ambient; }

            /**
             * Set the diffuse factor for this Material. This term is currently not used.
             * @param diffuse the new diffuse factor
             */
            inline void setDiffuseFactor(float diffuse) { _diffuse = diffuse; }
            /**
             * get the diffuse factor for this Material. This term is currently not used.
             * @return the diffuse factor
             */
            inline float getDiffuseFactor() const { return _diffuse; }

            /**
             * set a new reflection factor for this Material. This term is currently not used.
             * @return the reflection factor
             */
            inline void setReflectionFactor(float reflection) { _reflection = reflection; }
            /**
             * get the reflection factor for this Material. This term is currently not used.
             * @return the reflection factor
             */
            inline float getReflectionFactor() const { return _reflection; }

            /**
             * assignment operator
             */
            Material& operator=(const Material& rhs);

            /**
             * attach a texture to this Material. Material does not manage (delete) the texture when destructed.
             * @param tex a pointer to the new Texture
             */
            inline void setTexture(Texture* tex) { _texture = tex; }
            /**
             * get the attached texture of this Material. Material does not manage (delete) the texture when destructed.
             * @return a pointer to the attached Texture or 0 if no Texture is attached
             */
            inline Texture* getTexture() { return _texture; }
            /**
             * get the attached texture of this Material. Material does not manage (delete) the texture when destructed. const version
             * @return a pointer to the attached Texture or 0 if no Texture is attached
             */
            inline const Texture* getTexture() const { return _texture; }

            /**
             * attach a normal map to this Material. Material does not manage (delete) the normal map when destructed.
             * @param normalmap a pointer to the new normal map
             */
            inline void setNormalMap(Texture* normalmap) { _normalmap = normalmap; }
            /**
             * get the attached normal map of this Material. Material does not manage (delete) the normal map when destructed. 
             * @return a pointer to the attached normal map or 0 if no normal map is attached
             */
            inline Texture* getNormalMap() { return _normalmap; }
            /**
             * get the attached normal map of this Material. Material does not manage (delete) the normal map when destructed. const version
             * @return a pointer to the attached normal map or 0 if no normal map is attached
             */
            inline const Texture* getNormalMap() const { return _normalmap; }

            /**
             * get the scale factor for the U axis. needed for texturing
             * @return the scale factor
             */
            inline float getScaleU() const {return _uscale;}
            /**
             * get the scale factor for the V axis. needed for texturing
             * @return the scale factor
             */
            inline float getScaleV() const {return _vscale;}
            /**
             * set the UV-scaling for both axes. 
             * @param uscale the new scaling in u direction
             * @param vscale the new scaling in v direction
             */
            inline void setScaleUV(float uscale, float vscale) {_uscale = uscale; _vscale = vscale;}

            /**
             * set the alpha value for this Material. This is not implemented yet.
             * @param value the new alpha/transparency value
             */
            inline void setTransparency(float value) { _color[3] = value; }
            /**
             * get the alpha value for this Material. This is not implemented yet.
             * @return the alpha/transparency value
             */
            inline float getTransparency( ) const { return _color[3]; }

            /**
             * set the specular factor or this Material. This is not implemented yet.
             * @param value the new specular factor 
             */
            inline void setSpecular(float value) { _specular = value; }
            /**
             * get the specular factor for this Material. This is not implemented yet.
             * @return the specular factor
             */
            inline float getSpecular( ) const { return _specular; }
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
