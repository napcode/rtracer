/*
 * =====================================================================================
 *
 *       Filename:  Primitives.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/05/2011 01:22:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@apparatus.de
 *
 * =====================================================================================
 */

#ifndef RAY_DRAWABLES_H
#define RAY_DRAWABLES_H

#include <vector>
#include <string>
#include "Material.h"
#include "Ray.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

namespace ray
{
    /**
     * @brief abstract interface for intersectable objects 
     */
    class IIntersectable
    {
        public:
            /**
             * abstract interface for intersectable objects <br>
             * test if the given ray intersects this object
             * @param r the incoming ray
             * @param point output parameter - if there is any intersection, the point of intersection on the surface of the object will be returned through this reference 
             * @param dist output parameter - if there is any intersection, the distance from the origin of the ray to the intersection will be returned via this parameter
             * @return true if any intersection occurs
             */
            virtual bool intersect(const Ray& r, math::Vec3& point, float &dist) const = 0;
    };

    /**
     * @brief abstract interface for drawable objects
     */
    class Drawable : public IIntersectable
    {
        public:
            //! ctor
            Drawable(const std::string& name = "unknown_drawable");
            //! dtor
            virtual ~Drawable();

            /**
             * set the Material of this Drawable
             * @param material a reference to the new Material of this Drawable
             */
            inline void setMaterial(const Material& material) { _material = material; }
            /**
             * get the Material of this Drawable
             * @return a reference to the Material of this Drawable
             */
            inline Material& getMaterial() { return _material; }
            /**
             * get the Material of this Drawable - const version
             * @return a reference to the Material of this Drawable
             */
            inline const Material& getMaterial() const { return _material; }

            /**
             * get the normal on the surface of the sphere at a given position
             * @param at the position of the normal
             * @return the normal vector 
             */
            virtual math::Vec3 getNormalAt(const math::Vec3& at = 0) const = 0;
            /**
             * get the color on the surface of the sphere at a given position
             * @param at the position where the color sample shall be taken
             * @return the color vector 
             */
            virtual math::Vec4 getColorAt(const math::Vec3& at = 0) const = 0;

            /**
             * set the name of this Drawable
             * @param name a reference to the new name of this Drawable
             */
            inline void setName(const std::string& name) { _name = name; }
            /**
             * get the name of this Drawable 
             * @return a reference to the name of this Drawable
             */
            inline std::string& getName() { return _name; }
            /**
             * get the Material of this Drawable - const version
             * @return a reference to the name of this Drawable
             */
            inline const std::string& getName() const { return _name; }

            /**
             * checks if this drawable is a Sphere
             * @return true if Drawable is an instance Sphere
             */
            virtual bool isSphere() const = 0;
            /**
             * checks if this drawable is a Box
             * @return true if Drawable is an instance Box
             */
            virtual bool isBox() const = 0;
            /**
             * checks if this drawable is a Plane
             * @return true if Drawable is an instance Plane
             */
            virtual bool isPlane() const = 0;
        protected:
            std::string _name;
            Material _material;
    };


    typedef std::vector<Drawable*> DrawableVector;
}

#endif
