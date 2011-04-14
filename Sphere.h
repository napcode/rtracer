/*
 * =====================================================================================
 *
 *       Filename:  Sphere.h
 *
 *    Description:  definition of a drawable sphere
 *
 *        Version:  1.0
 *        Created:  04/14/2011 02:24:07 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */
#ifndef RAY_SPHERE_H
#define RAY_SPHERE_H

#include "Drawable.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
namespace ray
{
    /**
     * a drawable sphere
     */
    class Sphere : public Drawable
    {
        public:
            /**
             * ctor <br>
             */
            Sphere();
            /**
             * ctor <br>
             * @param center center of the new sphere
             * @param radius radius of the new sphere
             */
            Sphere(const math::Vec3& center, float radius);
            /**
             * ctor <br>
             * @param name name of the new sphere
             * @param center center of the new sphere
             * @param radius radius of the new sphere
             */
            Sphere(const std::string& name, const math::Vec3& center, float radius);

            /**
             * reimplemented from Drawable
             */
            math::Vec3 getNormalAt(const math::Vec3& at = 0) const;
            /**
             * reimplemented from Drawable 
             */
            math::Vec4 getColorAt(const math::Vec3& at = 0) const;

            /**
             * set the center of the sphere 
             * @param center the new center of the sphere
             */
            void setCenter(const math::Vec3& center);
            /**
             * get the center of the sphere 
             * @return the center of the sphere
             */
            math::Vec3& getCenter();
            /**
             * get the center of the sphere - const variant
             * @return the center of the sphere
             */
            const math::Vec3& getCenter() const;

            /**
             * set the radius of the sphere 
             * @param radius the new radius of the sphere
             */
            void setRadius(float radius);
            /**
             * get the radius of the sphere 
             * @return the radius of the sphere
             */
            float getRadius() const;

            /**
             * reimplemented from IIntersectable 
             */
            bool intersect(const Ray& r, math::Vec3& point, float &dist) const;

            /**
             * reimplemented from Drawable 
             */
            inline bool isSphere() const {return true;};
            /**
             * reimplemented from Drawable 
             */
            inline bool isBox() const {return false;};
            /**
             * reimplemented from Drawable 
             */
            inline bool isPlane() const {return false;};
        protected:
            math::Vec3 _center;
            float _radius;
        private:
            math::Vec3 getNormalImpl();
    };
}
#endif
