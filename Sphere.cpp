/*
 * =====================================================================================
 *
 *       Filename:  Sphere.cpp
 *
 *    Description:  implementation of class Sphere
 *
 *        Version:  1.0
 *        Created:  04/14/2011 02:27:00 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */

#include "Sphere.h"
#include "Texture.h"

using namespace ray;
using namespace math;

Sphere::Sphere()
    :Drawable("unnamed_sphere"), _center(0.0f, 0.0f, 0.0f), _radius(1.0f)
{

}
Sphere::Sphere(const Vec3& center, float radius)
    : Drawable("unnamed_sphere"), _center(center), _radius(radius)
{
}
    Sphere::Sphere(const std::string& name, const Vec3& center, float radius)
: Drawable(name), _center(center), _radius(radius)
{
}
void Sphere::setCenter(const Vec3& center)
{
    _center = center;
}
Vec3& Sphere::getCenter()
{
    return _center;
}
const Vec3& Sphere::getCenter() const
{
    return _center;
}
void Sphere::setRadius(float radius)
{
    _radius = radius;
}
float Sphere::getRadius() const
{
    return _radius;
}
bool Sphere::intersect(const Ray& ray, Vec3& point,  float& dist) const
{

    Vec3 m = ray.getOrigin() - _center;
    float b = m * ray.getDirection();
    float c = m * m - _radius * _radius;

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
Vec3 Sphere::getNormalAt(const Vec3& pos) const
{
    const Texture *tex = getMaterial().getNormalMap();
    if ( tex ) {
        Vec3 vp = (pos - _center) * _radius;
        float phi = acosf( -(vp*G_VN) );
        float u, v;
        v = phi * (1.0f / (getMaterial().getScaleV() *M_PI));
        float theta = acosf( ( G_VE*vp ) / sinf(phi) ) * (2.0f / M_PI);
        if ( G_VC * vp >= 0)
            u = (1.0f - theta) * (1.0f / getMaterial().getScaleU());
        else
            u = theta * (1.0f / getMaterial().getScaleU() );
        Vec4 tmp = (tex->getTexel(u, v) - Vec4(0.5f, 0.5f, 0.5f, 0.5f)) * 2.0f; 
        return Vec3(tmp[0], tmp[1], tmp[2]);
    }
    else 
        return (pos - _center) * _radius;
}
Vec4 Sphere::getColorAt(const Vec3& pos) const
{
    const Texture *tex = getMaterial().getTexture();
    if ( tex ) {
        /* 
           Vec3 vp = (pos - _center) * _radius;
           float phi = acosf( -(vp*G_VN) );
           float u, v;
           v = phi * (1.0f / (getMaterial().getScaleV() *M_PI));
           float theta = acosf( ( G_VE*vp ) / sinf(phi) ) * (2.0f / M_PI);
           if ( G_VC * vp >= 0)
           u = (1.0f - theta) * (1.0f / getMaterial().getScaleU());
           else
           u = theta * (1.0f / getMaterial().getScaleU() );
           */
        float u = pos.x() / (sqrt(pos.x()*pos.x() + pos.y()*pos.y() + pos.z()*pos.z()));
        float v = pos.y() / (sqrt(pos.x()*pos.x() + pos.y()*pos.y() + pos.z()*pos.z()));
        return tex->getTexel(u, v);//.componentMultiply( getMaterial().getColor() );
    }
    else 
        return getMaterial().getColor();
}
