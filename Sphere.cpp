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
 *         Author:  Mathias Buhr (), buhr@apparatus.de
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
#ifdef OPTIMIZED
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
#else
	math::Vec3 vec = _center - ray.getOrigin();
	float hyp = vec.length();

	vec.normalize();
	float alpha = vec * ray.getDirection();

	float ank = cos(acos(alpha)) * hyp;
	float gka = sin(acos(alpha)) * hyp;
	float ankBuffer = ank;

	if(gka >= _radius) return false;
	
	hyp = _radius;
	ank = sqrt( (hyp * hyp) - (gka * gka) );

	point = ray.getOrigin() + ray.getDirection() * (ankBuffer - ank);

	return true;
#endif
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
		//Matze I
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

		/*
		//Matze II
        float u = acos(pos.x() / _radius );
        float v = acos(pos.y() / _radius );
		*/

		/*
		//Flatmapping
		math::Vec3f normal = getNormalAt(pos);
		normal.normalize();
		float u = (asin(normal[0])/M_PI + 0.5) * getMaterial().getScaleU();
		float v = (asin(normal[1])/M_PI + 0.5) * getMaterial().getScaleV();
		*/

		//Spheremapping
		math::Vec3f normal = getNormalAt(pos);
		normal.normalize();
		float u = atan2(normal[1],normal[0])*getMaterial().getScaleU();
		float v = acos(normal[2]/_radius)*getMaterial().getScaleV();

        return tex->getTexel(u, v);
    }
    else 
        return getMaterial().getColor();
}
