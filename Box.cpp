/*
 * =====================================================================================
 *
 *       Filename:  Box.cpp
 *
 *    Description:  implementation of class Box
 *
 *        Version:  1.0
 *        Created:  04/14/2011 02:26:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */

#include "Box.h"
#include "Texture.h"
#include "config.h"

using namespace ray;

Box::Box()
   : Drawable("unnamed_box"), _center(0.0f, 0.0f, 0.0f)
{
    setNormals();
    setDimensions();
}

Box::Box(const math::Vec3& center, float width, float height, float depth)
    : Drawable("unnamed_box"), _center(center)
{
    setNormals();
    setDimensions(width, height, depth);
}

Box::Box(const math::Vec3& center, const math::Vec3& vec1, const math::Vec3& vec2, float width, float height, float depth)
    : Drawable("unnamed_box"), _center(center)
{
    setNormals(vec1, vec2);
    setDimensions(width, height, depth);
}

Box::Box(const std::string& name, const math::Vec3& center, const math::Vec3& vec1, const math::Vec3& vec2, float width, float height, float depth)
    : Drawable(name), _center(center)
{
    setNormals(vec1, vec2);
    setDimensions(width, height, depth);
}

math::Vec3 Box::getNormalAt(const math::Vec3& pos) const
{
    const Texture *tex = getMaterial().getNormalMap();
    math::Vec3 pnt1,pnt2;
    float scalar1,scalar2;

    for ( int i=0 ; i<3 ; i++ ) {
        // get center of face with negative normal i
        pnt1 = _center -  _normals[i] * _dimensions[i];
        // get center of face with positive normal i
        pnt2 = _center +  _normals[i] * _dimensions[i];

        // scalar-products for testing -> 'pos' in face one or two
        scalar1 = (pos - pnt1) * _normals[i];
        scalar2 = (pos - pnt2) * _normals[i];

        // if 'pos' in face one get normal from map
        // BOX_DELTA of rounding
        if (scalar1 <= BOX_DELTA && scalar1 >= -BOX_DELTA) {
            if ( tex ) {
                float u = fabs((pos * _normals[(i+1)%3]) * getMaterial().getScaleU() );
                float v = fabs((pos * _normals[(i+2)%3]) * getMaterial().getScaleV() );
                math::Vec4 tmp = ( tex->getTexel(u, v) - math::Vec4(0.5f, 0.5f, 0.5f, 0.5f) ) * 2.0f;
                return math::Vec3(tmp[0], tmp[1], tmp[2]);
            }
            else {
                return math::Vec3(0.0, 0.0, 0.0) - _normals[i];
            }
        }

        // if 'pos' in face two get normal from map
        // BOX_DELTA of rounding
        if (scalar2 <= BOX_DELTA && scalar2 >= -BOX_DELTA) {
            if ( tex ) {
                float u = fabs((pos * _normals[(i+1)%3]) * getMaterial().getScaleU() );
                float v = fabs((pos * _normals[(i+2)%3]) * getMaterial().getScaleV() );
                math::Vec4 tmp = ( tex->getTexel(u, v) - math::Vec4(0.5f, 0.5f, 0.5f, 0.5f) ) * 2.0f;
                return math::Vec3(tmp[0], tmp[1], tmp[2]);
            }
            else {
                return _normals[i];
            }
        }
    }
    return math::Vec3(0.0f, 0.0f, 0.0f);
}

math::Vec4 Box::getColorAt(const math::Vec3& pos) const
{
    const Texture *tex = getMaterial().getTexture();
    math::Vec3 pnt1,pnt2;
    float scalar1,scalar2;

    for ( int i=0 ; i<3 ; i++ ) {
        // get center of face with negative normal i
        pnt1 = _center -  _normals[i] * _dimensions[i];
        // get center of face with positive normal i
        pnt2 = _center +  _normals[i] * _dimensions[i];

        // scalar-products for testing -> 'pos' in face one or two
        scalar1 = (pos - pnt1) * _normals[i];
        scalar2 = (pos - pnt2) * _normals[i];

        // if 'pos' in face one or face two get color of texture
        // BOX_DELTA of rounding
        if ((scalar1 <= BOX_DELTA && scalar1 >= -BOX_DELTA)  ||  (scalar2 <= BOX_DELTA && scalar2 >= -BOX_DELTA)) {
            if ( tex ) {
                float u = fabs((pos * _normals[(i+1)%3]) * getMaterial().getScaleU() );
                float v = fabs((pos * _normals[(i+2)%3]) * getMaterial().getScaleV() );
                return tex->getTexel(u, v);
            }
            else {
                return getMaterial().getColor();
            }
        }
    }
    return math::Vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

bool Box::intersect(const Ray& r, math::Vec3& point, float &dist) const
{
    math::Vec3 ray_dir = r.getDirection();
    math::Vec3 ray_ori = r.getOrigin();

    // used as center of current face
    math::Vec3 pnt;

    for ( int i=0 ; i<3 ; i++ ) {
        // select the face
        if (_normals[i] * ray_dir > 0) {
            pnt = _center -  _normals[i] * _dimensions[i];
        }
        else {
            pnt = _center +  _normals[i] * _dimensions[i];
        }

        // distance
        dist =  (( pnt - ray_ori )* _normals[i]) / (ray_dir* _normals[i]);

        if (dist >= 0.0f) {
            // intersection point
            point = ray_ori + ray_dir * dist;
            // vector between center of face and intersection
            math::Vec3 tmp = (pnt - point);
            // distances between intersection and bisectors
            float tmp1 = (tmp ^ _normals[(i+1)%3]).length();
            float tmp2 = (tmp ^ _normals[(i+2)%3]).length();
            // bounding box
            if ( tmp1 <= _dimensions[(i+2)%3] && tmp2 <= _dimensions[(i+1)%3] )
                return true;
        }
    }
    return false;
}

void Box::setNormals(const math::Vec3& vec1, const math::Vec3& vec2)
{
    _normals[0] = vec1;
    _normals[1] = vec2;
    _normals[2] = _normals[0] ^ _normals[1];

    _normals[0].normalize();
    _normals[1].normalize();
    _normals[2].normalize();
}

void Box::setDimensions(float width, float height, float depth)
{
    _dimensions[0] = 0.5f * width;
    _dimensions[1] = 0.5f * height;
    _dimensions[2] = 0.5f * depth;
}
