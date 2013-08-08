/*
 * =====================================================================================
 *
 *       Filename:  Ray.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/07/2011 01:06:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@apparatus.de
 *
 * =====================================================================================
 */

#ifndef RAY_RAY_H
#define RAY_RAY_H

#include "math/Vec3.h"

namespace ray
{
    /**
     * @brief this seems to be important for a raytracer...but...actually...it isn't
     */
    class Ray
    {
        public:
            //! ctor
            Ray();
            /**
             * ctor
             * @param origin position vector of the ray
             * @param direction directional vector of the ray
             */
            Ray(const math::Vec3& origin, const math::Vec3& direction);
            
            /**
             * set a new position vector of this ray
             * @param origin the new position vector
             */
            void setOrigin(const math::Vec3& origin) { _origin = origin; }
            /**
             * get the position vector of this ray 
             * @return a reference to the position vector
             */
            math::Vec3& getOrigin() { return _origin; }
            /**
             * get the position vector of this ray - const version
             * @return a reference to the position vector
             */
            const math::Vec3& getOrigin() const { return _origin; }

            /**
             * set a new directional vector of this ray
             * @param origin the new directional vector
             */
            void setDirection(const math::Vec3& direction) { _direction = direction; }
            /**
             * get the directional vector of this ray 
             * @return a reference to the directional vector
             */
            math::Vec3& getDirection() { return _direction; }
            /**
             * get the directional vector of this ray - const version
             * @return a reference to the directional vector
             */
            const math::Vec3& getDirection() const { return _direction; }
        private:
            math::Vec3 _origin;
            math::Vec3 _direction;
    };
}
#endif
