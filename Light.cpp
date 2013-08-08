/*
 * =====================================================================================
 *
 *       Filename:  Light.cpp
 *
 *    Description:  implementation of class light
 *
 *        Version:  1.0
 *        Created:  04/14/2011 02:19:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@apparatus.de
 *
 * =====================================================================================
 */

#include "Light.h"

using namespace ray;
using namespace math;

Light::Light(const std::string& name)
: _name(name), _color(1.0f, 1.0f, 1.0f, 1.0f), _ambient_color(0.0f, 0.0f, 0.0f, 1.0f), _normal(0.0f, 1.0f, 0.0f), _type(DIRECTIONAL), _intensity(0.1f)
{

}
Light::Light(const math::Vec3& pos, const std::string& name)
: _name(name), _position(pos), _color(1.0f, 1.0f, 1.0f, 1.0f), _ambient_color(0.0f, 0.0f, 0.0f, 1.0f), _normal(0.0f, 1.0f, 0.0f), _type(DIRECTIONAL), _intensity(0.1f)
{

}
Light::Light(const math::Vec3& pos, const math::Vec4& color, const std::string& name)
: _name(name), _position(pos), _color(color), _ambient_color(0.0f, 0.0f, 0.0f, 1.0f), _normal(0.0f, 1.0f, 0.0f), _type(DIRECTIONAL), _intensity(0.1f)
{

}
Light::~Light()
{

}
bool Light::intersect(const Ray& ray, Vec3& point,  float& dist) const
{
    float radius = 1.0f;
    Vec3 m = ray.getOrigin() - _position;
    float b = m * ray.getDirection();
    float c = m * m - radius * radius;

    if (c > 0.0f && b > 0.0f)
        return false;
    float discr = b*b - c;
    if (discr < 0.0f) 
        return false;

    dist = -b - sqrt(discr);

    if ( dist < 0.0f )
        dist = 0.0f;
    point = ray.getOrigin() + ray.getDirection() * dist;
    return true;
}
