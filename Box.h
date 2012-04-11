/*
 * =====================================================================================
 *
 *       Filename:  Box.h
 *
 *    Description:  definition of a drawable box
 *
 *        Version:  1.0
 *        Created:  04/14/2011 02:25:26 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */
#ifndef RAY_BOX_H
#define RAY_BOX_H

#include "Drawable.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

#define BOX_DELTA 0.0001f


namespace ray
{

    /**
     * @brief a drawable with the appearance of a cuboid. Texture mapping is
     * implemented 
     */
    class Box : public Drawable
    {
        public:

            //! ctor
            Box();

            /**
             * ctor
             * @param center the center of the box
             * @param width width of the box
             * @param height height of the box
             * @param depth depth of the box
            */
            Box(const math::Vec3& center, float width, float height, float depth);

            /**
             * ctor
             * @param center the center of the box
             * @param vec1 1st normal
             * @param vec2 2nd normal
             * @param width width of the box
             * @param height height of the box
             * @param depth depth of the box
             */
            Box(const math::Vec3& center, const math::Vec3& vec1, const math::Vec3& vec2, float width, float height, float depth);

            /**
             * ctor
             * @param name name of the box
             * @param center the center of the box
             * @param vec1 1st normal
             * @param vec2 2nd normal
             * @param width width of the box
             * @param height height of the box
             * @param depth depth of the box
             */
            Box(const std::string& name, const math::Vec3& center, const math::Vec3& vec1, const math::Vec3& vec2, float width, float height, float depth);

            /**
             * reimplemented from Drawable
             */
            math::Vec3 getNormalAt(const math::Vec3& at = 0) const;
            /**
             * reimplemented from Drawable
             */
            math::Vec4 getColorAt(const math::Vec3& at = 0) const;

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
            inline bool isBox() const {return true;};
            /**
             * reimplemented from Drawable
             */
            inline bool isPlane() const {return false;};

        private:
            void setNormals(const math::Vec3& vec1=math::Vec3(1.0f, 0.0f, 0.0f), const math::Vec3& vec2=math::Vec3(0.0f, 1.0f, 0.0f));

            void setDimensions(float width=1.0f, float height=1.0f, float deep=1.0f);

            math::Vec3 _center;
            math::Vec3 _normals[3];
            float _dimensions[3];
    };
}
#endif
