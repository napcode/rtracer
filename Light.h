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
    class Light : public IIntersectable
    {
        public:
            enum TYPE
            {
                DIRECTIONAL, 
                POINT,
                SPOT
            };
            Light(const std::string& name = "unnamed_light");
            Light(const math::Vec3& pos, const std::string& name = "unnamed_light");
            Light(const math::Vec3& pos, const math::Vec4& color, const std::string& name = "unnamed_light");
            virtual ~Light();

            void setColor(const math::Vec4& color) { _color = color; }
            math::Vec4& getColor() { return _color; }
            const math::Vec4& getColor() const { return _color; }

            float getTransparency() const { return _color[3]; } 
            void setTransparency(float alpha) { _color[3] = alpha; }

            void setPosition(const math::Vec3& position) { _position = position; }
            math::Vec3& getPosition() { return _position; }
            const math::Vec3& getPosition() const { return _position; }

            void setDirection(const math::Vec3& normal) { _normal = normal; }
            math::Vec3 getDirection() const { return _normal; }

            void setName(const std::string& name) { _name = name; }
            std::string& getName() { return _name; }
            const std::string& getName() const { return _name; }

            bool isOmnidirectional() const { if (_normal.length() < 0.0001f) return true; else return false;}
            bool isDirectional() const { return !isOmnidirectional();}

            virtual bool intersect(const Ray& r, math::Vec3& point, float &dist) const;

            TYPE getType() const { return _type; }
            void setType(TYPE t) { _type = t; }

            float getIntensity() const { return _intensity; } 
            void setIntensity(float intensity) { _intensity = intensity; }
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
