/*
 * =====================================================================================
 *
 *       Filename:  Plane.h
 *
 *    Description:  definition of a drawable plane
 *
 *        Version:  1.0
 *        Created:  04/14/2011 02:22:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@apparatus.de
 *
 * =====================================================================================
 */
#ifndef RAY_DRAWABLE_H
#define RAY_DRAWABLE_H

#include "Drawable.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

namespace ray
{
    /**
     * @brief a drawable with the appearance of a plane. Texture mapping is
     * implemented 
     */
    class Plane : public Drawable
    {
        public:
            //! ctor
            Plane();
            /**
             * ctor
             * @param normal the normal vector of the plane
             * @param position the position vector of the plane
             */
            Plane(const math::Vec3& normal, const math::Vec3& position);
            /**
             * ctor
             * @param name the name of the plane
             * @param normal the normal vector of the plane
             * @param position the position vector of the plane
             */
            Plane(const std::string& name, const math::Vec3& normal, const math::Vec3& position);

            /**
             * set a new normal vector of the plane
             * @param normal the new normal vector
             */
            void setNormal(const math::Vec3& normal);
            /**
             * get the normal vector of the plane
             * @return a reference to the normal vector
             */
            math::Vec3& getNormal();
            /**
             * get the normal vector of the plane - const variant
             * @return a reference to the normal vector
             */
            const math::Vec3& getNormal()  const;

            /**
             * reimplemented from Drawable 
             */
            math::Vec3 getNormalAt(const math::Vec3& at = 0) const;
            /**
             * reimplemented from Drawable 
             */
            math::Vec4 getColorAt(const math::Vec3& at = 0) const;

            /**
             * set a new position vector of the plane
             * @param position the new position vector
             */
            void setPosition(const math::Vec3& position);
            /**
             * get the position vector of the plane
             * @return a reference to the position vector
             */
            math::Vec3& getPosition();
            /**
             * get the position vector of the plane - const version
             * @return a reference to the position vector
             */
            const math::Vec3& getPosition() const;

            /**
             * reimplemented from IIntersectable 
             */
            bool intersect(const Ray& r, math::Vec3& point, float &dist) const;

            /**
             * reimplemented from Drawable 
             */
            inline bool isSphere() const {return false;};
            /**
             * reimplemented from Drawable 
             */
            inline bool isBox() const {return false;};
            /**
             * reimplemented from Drawable 
             */
            inline bool isPlane() const {return true;};
        private:
            void prepare();
            math::Vec3f _normal;
            math::Vec3f _position;
            math::Vec3f _u_axis;
            math::Vec3f _v_axis;

    };
}
#endif
