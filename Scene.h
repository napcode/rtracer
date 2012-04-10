/*
 * =====================================================================================
 *
 *       Filename:  Scene.h
 *
 *    Description:  definition of a traceable scene
 *
 *        Version:  1.0
 *        Created:  04/04/2011 05:03:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */
#ifndef RAY_SCENE_H
#define RAY_SCENE_H

#include "Drawable.h"
#include "Texture.h"
#include "Light.h"
#include <stdint.h>

namespace ray
{
    /**
     * an instance of this class holds all relevant data for a drawable scene<br>
     * memory management is done here
     */
    class Scene
    {
        public:
            //! ctor
            Scene();
            /**
             * dtor <br>
             * all associated data is deleted on destruction & all reference to the data of this scene become invalid
             */
            ~Scene();

            //! create a static default scene
            void createDefaultScene(); 

            /**
             * get the number of drawables in the scene
             * @return the number of drawables
             */
            inline uint32_t getNumDrawables() const { return _drawables.size(); }
            /**
             * get a list with all drawbles
             * @return a list with drawables
             */
            inline DrawableVector& getDrawables() { return _drawables; }
            /**
             * get a list with all drawbles - const variant
             * @return a list with drawables
             */
            inline const DrawableVector& getDrawables() const { return _drawables; }

            /**
             * get the number of lights in the scene
             * @return the number of lights
             */
            inline uint32_t getNumLights() const { return _lights.size(); }
            /**
             * get a list with all lights  
             * @return a list with lights
             */
            inline LightVector& getLights() { return _lights; }
            /**
             * get a list with all lights - const variant
             * @return a list with lights
             */
            inline const LightVector& getLights() const { return _lights; }

            /**
             * set the background color of the scene
             * @param color the new color vector, color[3] is ignored (no alpha)
             */
            inline void setBackgroundColor(const math::Vec3& color) { _backgroundcolor = color; }
            /**
             * get the current background color of the scene
             * @return the current color vector
             */
            inline math::Vec3& getBackgroundColor() { return _backgroundcolor; }
            /**
             * get the current background color of the scene - const variant
             * @return the current color vector
             */
            inline const math::Vec3& getBackgroundColor() const { return _backgroundcolor; }
        private:
            void loadTextures();
            void createLights();
            DrawableVector _drawables;
            LightVector _lights;
            TextureVector _textures;
            math::Vec3 _backgroundcolor;
    };
}
#endif
