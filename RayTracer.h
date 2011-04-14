/*
 * =====================================================================================
 *
 *       Filename:  RayTracer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/04/2011 04:50:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */
#ifndef RAY_RAYTRACER_H
#define RAY_RAYTRACER_H

#include "Pixel.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

namespace ray 
{
    class Scene;
    class Ray;
    class Drawable;
    class RayTracer 
    {
        public:
            RayTracer();
            ~RayTracer();

            inline void setScene(Scene &scene) { _scene = &scene; }
            inline const Scene& getScene() const { return *_scene; }
            inline Scene& getScene() { return *_scene; }

            bool prepare();
            void run();

            inline PixelBuffer& getFrameBuffer() { return _pbuffer; }
            inline const PixelBuffer& getFrameBuffer() const { return _pbuffer; }
        private:
            math::Vec4 traceRay(const Ray& ray, uint32_t depth);
            math::Vec4 traceLights(const math::Vec3& intersection, Drawable *drawable );
                void clearBuffer();
            Scene *_scene;
            PixelBuffer _pbuffer;
            math::Vec3 _eye;
            math::Vec3 _screen_lowerleft;
            math::Vec3 _screen_upperright;
            float _dx;
            float _dz;
    };
}
#endif
