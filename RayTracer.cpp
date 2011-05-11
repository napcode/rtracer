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
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */

#include "RayTracer.h"
#include "Scene.h"
#include <float.h>
#include <iostream>
#include <stdlib.h>

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
    pixelcoord[0] = (first_pixel % _width) * _dx;
    pixelcoord[2] = 1.0f - (first_pixel / _width) * _dz;
    uint32_t pixelindex = first_pixel;
    while (pixelindex <= last_pixel) {
        Vec3 direction = pixelcoord - _eye; 
        direction.normalize();
        Ray ray(_eye, direction);

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
    Vec3 intersection;
    float min_distance = FLT_MAX;
    float tmp_distance;
    Drawable *drawable = 0;

    DrawableVector::iterator object = _scene->getDrawables().begin();
    Vec4 out_color;
    while (object != _scene->getDrawables().end()) {
        // create ray
        float tmp;
        Vec3 tmp_intersection;
        if ( (*object)->intersect(ray, tmp_intersection, tmp) ) {
            tmp_distance = (tmp_intersection - ray.getOrigin()).length();
            if (min_distance > tmp_distance) {
                min_distance = tmp_distance;
                drawable = (*object);

                Vec4 reflection_color;
                Vec3 obj_normal = drawable->getNormalAt(tmp_intersection);
                Vec4 obj_color =  drawable->getColorAt(tmp_intersection);
                Vec4 ambient_color = obj_color * drawable->getMaterial().getAmbient();

                // do reflection
                if ( drawable->getMaterial().getReflection() > 0.0f  && trace_depth < MAX_TRACE_DEPTH ) {
                    Vec3 par = obj_normal * ( obj_normal * ray.getDirection() );
                    Vec3 reflection = ray.getDirection() - par * 2.0f;
                    reflection.normalize();
                    Ray reflected_ray(tmp_intersection, reflection);
                    reflection_color = traceRay(reflected_ray, trace_depth + 1);
                }
                // do shadows and specular
                Vec4 lighting_color = traceLights(tmp_intersection, drawable);

                // trace if this object is closer than the last one
                // this ignores transparency
                out_color = ambient_color + obj_color.componentMultiply(lighting_color);
            }
        }
        ++object;
    }

    return out_color;
}
Vec4 RayTracer::traceLights(const Vec3& intersection, Drawable *drawable )
{
    Vec4 out_color;
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
                    break;
                case Light::POINT:
                    out_color += (*light)->getColor() * (*light)->getIntensity() * light_scaling * 1.0f/(lightdist);
                default:
                    break;
            }
        }

        light++;
    }
    return out_color;
}
