/*
 * =====================================================================================
 *
 *       Filename:  Plane.cpp
 *
 *    Description:  implementation of class Plane
 *
 *        Version:  1.0
 *        Created:  04/14/2011 02:28:22 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Mathias Buhr (), buhr@apparatus.de
 *
 * =====================================================================================
 */

#include "Plane.h"
#include "Texture.h"

using namespace ray;
using namespace math;

Plane::Plane()
    : Drawable("unnamed_plane"), _normal(0.0f, 0.0f, 1.0f), _position(0.0f, 0.0f, 0.0f)
{
    prepare();
}
Plane::Plane(const Vec3& normal, const Vec3& position)
    : Drawable("unnamed_plane"), _normal(normal), _position(position)
{
    prepare();
} 
    Plane::Plane(const std::string& name, const Vec3& normal, const Vec3& position)
: Drawable(name), _normal(normal), _position(position)
{
    prepare();
} 
void Plane::prepare()
{
    // just to be safe
    _normal.normalize();

    // get u/v axes for texturing
    double   h[3];
    double  d;
    double  s = ( _normal[0] > 0.0) ? 1.0 : -1.0;
    double  f = s/(s + _normal[0]);
    h[0] = _normal[0]+s;  
    h[1] = _normal[1]; 
    h[2] = _normal[2];
    d = f*h[1]; 
    _u_axis[0] = -d*h[0]; 
    _u_axis[1] = 1.0-d*h[1]; 
    _u_axis[2] = -d*h[2];
    d = f*h[2]; 
    _v_axis[0] = -d*h[0]; 
    _v_axis[1] = -d*h[1]; 
    _v_axis[2] = 1.0-d*h[2];
}
void Plane::setNormal(const Vec3& normal)
{
    _normal = normal;
    _normal.normalize(); 
}
Vec3& Plane::getNormal() 
{
    return _normal;
}
const Vec3& Plane::getNormal()  const
{
    return _normal;
}
Vec3 Plane::getNormalAt(const Vec3& pos) const
{
    const Texture *tex = getMaterial().getNormalMap();
    if ( tex ) {
        float u = fabs((pos * _u_axis) * getMaterial().getScaleU() );
        float v = fabs((pos * _v_axis) * getMaterial().getScaleV() );
        Vec4 tmp = ( tex->getTexel(u, v) - Vec4(0.5f, 0.5f, 0.5f, 0.5f) ) * 2.0f;
        return Vec3(tmp[0], tmp[1], tmp[2]);
    }
    else 
        return getNormal();
}
Vec4 Plane::getColorAt(const Vec3& pos) const
{
    const Texture *tex = getMaterial().getTexture();
    if ( tex ) {
        float u = fabs((pos * _u_axis) * getMaterial().getScaleU() );
        float v = fabs((pos * _v_axis) * getMaterial().getScaleV() );
        Vec4 t = tex->getTexel(u, v); //( getMaterial().getColor() );
        return t;
    }
    else 
        return getMaterial().getColor();
}
void Plane::setPosition(const Vec3& position)
{
    _position = position;
}
Vec3& Plane::getPosition() 
{
    return _position;
}
const Vec3& Plane::getPosition()  const
{
    return _position;
}
bool Plane::intersect(const Ray& ray, Vec3& point, float &dist) const
{
    Vec3 ab = ray.getDirection();
    dist =  ( _position*_normal - _normal * ray.getOrigin() ) / ( _normal * ab);

    if (dist >= 0.0f) {
        point = ray.getOrigin() + ab * dist;
        return true;
    }

    return false;
} 
