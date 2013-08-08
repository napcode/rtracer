/*
 * =====================================================================================
 *
 *       Filename:  RayTracer.cpp
 *
 *    Description:  j
 *
 *        Version:  1.0
 *        Created:  04/04/2011 04:54:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@apparatus.de
 *
 * =====================================================================================
 */

#include "RayTracer.h"
#include "Scene.h"
#include <float.h>
#include <iostream>
#include <stdlib.h>
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
using namespace ray;
using namespace math;

    RayTracer::RayTracer()
: _scene(0)
{

}
RayTracer::~RayTracer()
{

}
bool RayTracer::prepare(uint32_t height, uint32_t width)
{
    _height = height;
    _width = width;
    _pbuffer.resize(height * width);
    _eye.set(0.0f, -5.0f, 0.0f);

    clearBuffer();
    return true;
}
void RayTracer::clearBuffer()
{
    PixelBuffer::iterator pixel = _pbuffer.begin();
    while (pixel != _pbuffer.end()) {
        (*pixel).set( _scene->getBackgroundColor() );
        ++pixel;
    }
}
void RayTracer::trace(uint32_t first_pixel, uint32_t last_pixel)
{
    PixelBuffer::iterator pixel = _pbuffer.begin();

    // screen coordinates are scaled so that height==1.0f in world coordinates
    // screen is always at y = 0.0f (x-z plane)
    float scale = 1.0f / (_height); 
    _screen_upperright.set( (_width * scale), 0.0f, 1.0f);
    _screen_lowerleft.set( -(_width * scale), 0.0f, -1.0f);
    _dx = (_screen_upperright.x() * 2) / (_width);
    _dz = (_screen_upperright.z() * 2) / _height;

    Vec3 pixelcoord; // current pixel coordinates in world coordinates

    uint32_t depth = 0;
    // start tracing with the upper left pixel
    pixelcoord[0] = (first_pixel % _width) * _dx + _screen_lowerleft.x();
    pixelcoord[2] = 1.0f - (first_pixel / _width) * _dz;
    uint32_t pixelindex = first_pixel;

    // main loop: trace from 1st to last pixel
    while (pixelindex < last_pixel) {
        // create an eye <-> current_pixel ray
        Vec3 direction = pixelcoord - _eye; 
        direction.normalize();
        Ray ray(_eye, direction);

        // trace that ray
        _pbuffer[pixelindex].set(this->traceRay(ray, depth));
        depth++;

        ++pixelindex;
        if (pixelindex % (_width) == 0) {
            pixelcoord[0] = _screen_lowerleft.x();
            pixelcoord[2] -= _dz;
        }
        else {
            pixelcoord[0] += _dx;
        }
    }
}
Vec4 RayTracer::traceRay(const Ray& ray, uint32_t trace_depth)
{
    Vec3 intersection;              /* last point of intersection */
    float min_distance = FLT_MAX;   /* distance to intersection   */
    float tmp_distance;             /* there are multiple inters. */
    Drawable *hit_drawable = 0;     /* which drawable did we hit  */

    DrawableVector::iterator drawable = _scene->getDrawables().begin();
    Vec4 out_color;
    while (drawable != _scene->getDrawables().end()) {
        // create ray
        float tmp;
        Vec3 tmp_intersection;
        if ( (*drawable)->intersect(ray, tmp_intersection, tmp) ) {
            tmp_distance = (tmp_intersection - ray.getOrigin()).length();
            if (min_distance > tmp_distance) {
                min_distance = tmp_distance;
                hit_drawable = (*drawable);
                intersection = tmp_intersection;
            }
        }
        ++drawable;
    }

    if(hit_drawable) {
        Vec4 reflection_color;
        Vec3 obj_normal = hit_drawable->getNormalAt(intersection);

        // do reflection
        // FIXME: still work-in-progress (currently inactive)
        if ( hit_drawable->getMaterial().getReflectionFactor() > 0.0f  && trace_depth < MAX_TRACE_DEPTH ) {
            Vec3 par = obj_normal * ( obj_normal * ray.getDirection() );
            Vec3 reflection = ray.getDirection() - par * 2.0f;
            reflection.normalize();
            Ray reflected_ray(intersection, reflection);
            reflection_color = traceRay(reflected_ray, trace_depth + 1);
        }
        // do shadows and specular
        out_color = traceLights(intersection, hit_drawable, ray.getDirection());
    }

    return out_color;
}
Vec4 RayTracer::traceLights(const Vec3& intersection, Drawable *drawable, Vec3 eye )
{
    Vec4 out_color;
    Vec4 spec_color;
    Vec4 diffuse_color =  drawable->getColorAt(intersection);
    float factor_ambient = drawable->getMaterial().getAmbientFactor();
    LightVector::iterator light = _scene->getLights().begin();
    while (light != _scene->getLights().end()) {
        //Vec3 light_direction = intersection - (*light)->getPosition();
        Vec3 light_direction = (*light)->getPosition() - intersection;
        float lightdist = light_direction.length();
        light_direction.normalize();

        Ray ray(intersection, light_direction);
        float light_scaling = drawable->getNormalAt(intersection) * light_direction;  // no effect if light ray and object normal are orthogonal
        if (light_scaling < 0) 
            light_scaling = 0.0f;

        // check for shadows
        DrawableVector::iterator object = _scene->getDrawables().begin();
        Drawable *hitobject = 0;
        while (object != _scene->getDrawables().end()) {
            float tmp;
            Vec3 tmp_intersection;
            // nothing to do if current object is the drawable
            if ( ((*object) != drawable) && (*object)->intersect(ray, tmp_intersection, tmp) ) {
                // object is between drawable and current light
                Vec3 intersection_vec = tmp_intersection - (*light)->getPosition();
                float dist = intersection_vec.length();
                if ( dist < lightdist) {
                    hitobject = *object;
                    break;
                }

            }
            object++;
        }

        // do specular component
        if ( !hitobject ) {
            switch ((*light)->getType()) {
                case Light::DIRECTIONAL:
                    out_color += (*light)->getColor() * (*light)->getIntensity();
                    out_color += (*light)->getAmbientColor() * factor_ambient;
                    break;
                case Light::POINT:
                    {
                    out_color += (*light)->getColor() * (*light)->getIntensity() * light_scaling * 1.0f/(lightdist);
                    Vec3 half =  light_direction - eye;
                    half.normalize();
                    Vec3 normal = drawable->getNormalAt(intersection);
                    normal.normalize();
                    float shine = 16.0f;
                    float temp = MAX(0.0, normal * half);
                    float spec_val = pow(temp, shine);
                    spec_color += (*light)->getColor() * (*light)->getIntensity() * spec_val * drawable->getMaterial().getReflectionFactor();
                    out_color += (*light)->getAmbientColor() * factor_ambient;
                    break;
                    }
                default:
                    break;
            }
        }

        light++;
    }
    out_color = diffuse_color.componentMultiply(out_color);
    out_color += spec_color;
    return out_color;
}
