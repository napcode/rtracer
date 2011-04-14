/*
 * =====================================================================================
 *
 *       Filename:  Scene.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/04/2011 05:04:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */
#include "Scene.h"
#include "ImageIO.h"
#include "math/Matrix4.h"
#include "Plane.h"
#include "Sphere.h"
#include "Box.h"

using namespace ray;
using namespace math;

    Scene::Scene()
:_backgroundcolor(0.0f, 0.0f, 0.0f)
{

}
Scene::~Scene()
{
    DrawableVector::iterator it = _drawables.begin();
    while (it != _drawables.end()) {
        delete *it;
        it++;
    }
    _drawables.clear();

    LightVector::iterator itl = _lights.begin();
    while (itl != _lights.end()) {
        delete *itl;
        itl++;
    }
    _lights.clear();

    TextureVector::iterator itt = _textures.begin();
    while (itt != _textures.end()) {
        delete *itt;
        itt++;
    }
    _textures.clear();
}
void Scene::createDefaultScene()
{
    loadTextures();
    createLights();

    Vec3 t = (Vec3(0.0f, 0.0f, 1.0f));
    Plane *p1 = new Plane(t, Vec3(0.0f, 0.0f, -1.0f));
    p1->setName("Plane1");
    p1->getMaterial().setColor(Vec4f(0.0f, 0.0f, 1.0f, 1.0f));
    p1->getMaterial().setAmbient(0.1f);
    p1->getMaterial().setDiffuse(1.0f);
    p1->getMaterial().setReflection(0.0f);
    p1->getMaterial().setTexture(_textures[0]);
    _drawables.push_back(p1);

    Sphere *s2 = new Sphere(Vec3(-2.0f, 8.0f, 0.0f), 1.0f);
    s2->setName("Sphere2");
    s2->getMaterial().setReflection(0.0f);
    s2->getMaterial().setAmbient(0.1f);
    s2->getMaterial().setDiffuse(1.0f);
    s2->getMaterial().setColor(Vec4f(0.0f, 1.0f, 0.0f, 1.0f));
    _drawables.push_back(s2);

    Sphere *s1 = new Sphere(Vec3(0.0f, 4.0f, 0.0f), 0.6f);
    s1->setName("Sphere1");
    s1->getMaterial().setReflection(0.0f);
    s1->getMaterial().setAmbient(0.1f);
    s1->getMaterial().setDiffuse(1.0f);
    s1->getMaterial().setColor(Vec4f(1.0f, 1.0f, 0.0f, 1.0f));
    //s1->getMaterial().setTexture(_textures[1]);
    //s1->getMaterial().setFresnelFactor(1.0f);
    //s1->getMaterial().setFresnelPower(0.0f);
    _drawables.push_back(s1);
}
void Scene::loadTextures()
{
    ray::img::ImageIO& imgio = ray::img::ImageIO::getInstance();
    Texture * t = imgio.getReader().readTexture("data/floor_stone.ppm");
    if (t)
        _textures.push_back(t);
    t = imgio.getReader().readTexture("data/metal1.ppm");
    if (t)
        _textures.push_back(t);
}
void Scene::createLights()
{
    // directional, static
    Light *l1 = new Light(Vec3(0.0f, 0.0f, 5.0f));
    l1->setIntensity(0.01f);
    l1->setName("L1");
    _lights.push_back(l1);

    // point light
    l1 = new Light(Vec3(-8.0f, 0.0f, 10.0f));
    l1->setIntensity(5.0f);
    l1->setColor(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    l1->setType(Light::POINT);
    l1->setName("L2");
    _lights.push_back(l1);
}
