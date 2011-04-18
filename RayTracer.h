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

    /**
     * @brief the main interface to the ray tracer
     * this class implements the actual ray tracer
     */
    class RayTracer 
    {
        public:
            //! ctor
            RayTracer();
            //! dtor
            ~RayTracer();

            /**
             * attach a Scene to the ray tracer
             * @param scene a reference to the Scene
             */
            inline void setScene(Scene &scene) { _scene = &scene; }
            /**
             * retrieve the current Scene of the ray tracer - const version
             * @return a reference to the Scene 
             */
            inline const Scene& getScene() const { return *_scene; }
            /**
             * retrieve the current Scene of the ray tracer 
             * @return a reference to the Scene 
             */
            inline Scene& getScene() { return *_scene; }

            /**
             * prepare the instance to do some work. This sets up the frame buffer to the configured size etc.
             * @return true if ray tracer is ready to work
             */
            bool prepare();
            /**
             * fire!
             */
            void run();

            /**
             * get the frame buffer of the ray tracer
             * @return a reference to the pixel buffer
             */
            inline PixelBuffer& getFrameBuffer() { return _pbuffer; }
            /**
             * get the frame buffer of the ray tracer - const version
             * @return a reference to the pixel buffer
             */
            inline const PixelBuffer& getFrameBuffer() const { return _pbuffer; }
        private:
            /**
             * trace the given ray
             * @param ray a reference to the ray to be traced
             * @param depth the current tracing depth, needed for recursion. (not implemented yet)
             * @return the final color of the pixel (at this recursion)
             */
            math::Vec4 traceRay(const Ray& ray, uint32_t depth);

            /**
             * if a ray has hit something, we'd like to check if this intersection is in the line of sight of any of the light sources. This calculated lighting and shadows.
             * @param intersection the point of intersection of the eye -> drawable ray
             * @param drawable the drawable the ray has intersected
             * @return the light color of the current pixel/intersection
             */
            math::Vec4 traceLights(const math::Vec3& intersection, Drawable *drawable );

            /**
             * clear the framebuffer to the background color of the scene
             */
            void clearBuffer();
            
            // members
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
