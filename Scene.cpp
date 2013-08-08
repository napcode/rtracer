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
 *         Author:  Mathias Buhr (), buhr@apparatus.de
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
        delete (*itt).second;
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
    if (_textures["stone"])
        p1->getMaterial().setTexture(_textures["stone"]);
    _drawables.push_back(p1);

    Sphere *s2 = new Sphere(Vec3(-2.0f, 8.0f, 0.0f), 1.0f);
    s2->setName("Sphere2");
    s2->getMaterial().setReflectionFactor(0.5f);
    s2->getMaterial().setColor(Vec4f(0.0f, 1.0f, 0.0f, 1.0f));
    _drawables.push_back(s2);

    Sphere *s1 = new Sphere(Vec3(0.0f, 4.0f, 0.0f), 0.6f);
    s1->setName("Sphere1");
    s1->getMaterial().setColor(Vec4f(1.0f, 1.0f, 0.0f, 1.0f));
    s1->getMaterial().setReflectionFactor(0.2f);
    _drawables.push_back(s1);

    Vec3 n1(1.0f, 0.0f, 0.0f);
    Vec3 n2(0.0f, 1.0f, 0.0f);
    math::Matrix4 m;
    m.makeRotate(0.3f, Y_AXIS);
    n1 = m * n1;

    Box *b1 = new Box(Vec3(2.0f, 5.0f, 0.0f),n1,n2,  1.0f, 1.0f, 1.0f);
    b1->getMaterial().setColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    b1->getMaterial().setReflectionFactor(0.5f);
    if (_textures["metal"])
        b1->getMaterial().setTexture(_textures["metal"]);
    _drawables.push_back(b1);
}
void Scene::loadTextures()
{
    ray::img::ImageIO& imgio = ray::img::ImageIO::getInstance();
    std::string filename = "data/floor_stone.ppm";
    Texture * t = imgio.getReader().readTexture(filename);
    if (t)
        _textures.insert(std::pair<std::string, Texture*>("stone", t));
    else
        std::cerr << "Error: unable to read " << filename << std::endl;
    filename = "data/metal1.ppm";
    t = imgio.getReader().readTexture(filename);
    if (t)
        _textures.insert(std::pair<std::string, Texture*>("metal", t));
    else
        std::cerr << "Error: unable to read " << filename << std::endl;
}
void Scene::createLights()
{
    {
        // directional, static
        Light *l = new Light(Vec3(0.0f, 0.0f, 5.0f));
        l->setIntensity(0.1f);
        l->setAmbientColor(Vec4(0.0f, 0.0f, 0.0f, 1.0f));
        l->setName("L1");
        _lights.push_back(l);
    }

    {
        // point light
        Light *l = new Light(Vec3(-2.0f, 4.0f, 5.0f));
        l->setIntensity(3.0f);
        l->setColor(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
        l->setType(Light::POINT);
        l->setName("L2");
        _lights.push_back(l);
    }

    {
        // point light
        Light *l = new Light(Vec3(0.0f, 00.0f, 8.0f));
        l->setIntensity(7.0f);
        l->setColor(Vec4(1.0f, 0.8, 0.8f, 1.0f));
        l->setType(Light::POINT);
        l->setName("L3");
     //   _lights.push_back(l);
    }
}
