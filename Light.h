/*
 * =====================================================================================
 *
 *       Filename:  Light.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/14/2011 02:18:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */
#ifndef RAY_LIGHT_H
#define RAY_LIGHT_H

#include "Drawable.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include <vector>

namespace ray
{
    /**
     * @brief a light source for the scene
     *
     * class describes various light sources and their properties
     */
    class Light : public IIntersectable
    {
        public:
            /**
             * enum with all available types
             */
            enum TYPE
            {
                DIRECTIONAL,  /*!< this light hits every surface from the same direction */
                POINT,        /*!< an omnidirectional point light source, casts shadows and decays with distance  */
                SPOT          /*!< a spot light which casts shadows, decays and has a given light cone */
            };

            /**
             * ctor
             * @param name the name of the light
             */
            Light(const std::string& name = "unnamed_light");
            /**
             * ctor
             * @param pos the position of the light source
             * @param name the name of the light
             */
            Light(const math::Vec3& pos, const std::string& name = "unnamed_light");
            /**
             * ctor
             * @param pos the position of the light source
             * @param color the color of the light source
             * @param name the name of the light
             */
            Light(const math::Vec3& pos, const math::Vec4& color, const std::string& name = "unnamed_light");
            //! dtor
            virtual ~Light();

            /**
             * set a new color for this light source
             * @param color the new color
             */
            inline void setColor(const math::Vec4& color) { _color = color; }
            /**
             * get a current color for this light source
             * @return the current color
             */
            inline math::Vec4& getColor() { return _color; }
            /**
             * get a current color for this light source - const version
             * @return the current color
             */
            inline const math::Vec4& getColor() const { return _color; }

            /**
             * set a new transparency for this light source <br>
             * as of now, this is meaningless
             * @param alpha the new transparency
             */
            inline void setTransparency(float alpha) { _color[3] = alpha; }
            /**
             * get the current transparency for this light source <br>
             * as of now, this is meaningless
             * @return the current transparency
             */
            inline float getTransparency() const { return _color[3]; } 

            /**
             * set a new position for this light source 
             * @param position the new position
             */
            inline void setPosition(const math::Vec3& position) { _position = position; }
            /**
             * get a current position for this light source 
             * @return the current position
             */
            inline math::Vec3& getPosition() { return _position; }
            /**
             * get a current position for this light source - const version
             * @return the current position
             */
            inline const math::Vec3& getPosition() const { return _position; }

            /**
             * set a new direction for this light source 
             * @param normal the new direction
             */
            inline void setDirection(const math::Vec3& normal) { _normal = normal; }
            /**
             * get a current direction for this light source 
             * @return the current direction
             */
            inline math::Vec3& getDirection() { return _normal; }
            /**
             * get a current direction for this light source - const version
             * @return the current direction
             */
            inline const math::Vec3& getDirection() const { return _normal; }

            /**
             * set a new name for this light source 
             * @param name the new name
             */
            inline void setName(const std::string& name) { _name = name; }
            /**
             * get a current name for this light source 
             * @return the current name
             */
            inline std::string& getName() { return _name; }
            /**
             * get a current name for this light source - const version
             * @return the current name
             */
            inline const std::string& getName() const { return _name; }

            /**
             * reimplemented from IIntersectable 
             */
            virtual bool intersect(const Ray& r, math::Vec3& point, float &dist) const;

            /**
             * get the TYPE of the light source
             * @return the type of the light source
             */
            inline TYPE getType() const { return _type; }
            /**
             * set the TYPE of the light source
             * @param t the new type of the light source
             */
            inline void setType(TYPE t) { _type = t; }

            /**
             * get the intensity of the light source
             * @return the intensity of the light source
             */
            inline float getIntensity() const { return _intensity; } 
            /**
             * set the intensity of the light source
             * @param intensity the new intensity of the light source
             */
            inline void setIntensity(float intensity) { _intensity = intensity; }
        private:
            std::string _name;
            math::Vec3 _position;
            math::Vec4 _color;
            math::Vec3 _normal;
            float _size;
            float _cutoff;
            TYPE _type;
            float _intensity;
    };
    typedef std::vector<Light*> LightVector;
}
#endif 
