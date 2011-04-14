/*
 * =====================================================================================
 *
 *       Filename:  Material.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/07/2011 10:08:00 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */

#include "Material.h"
#include "Texture.h"

using namespace ray;
using namespace math;

math::Vec3 ray::G_VN = math::Vec3(0.0f, 1.0f, 0.0f);
math::Vec3 ray::G_VE = math::Vec3(1.0f, 0.0f, 0.0f);
math::Vec3 ray::G_VC = G_VN ^ G_VC;

    Material::Material()
: _color(Vec4(1.0f, 1.0f, 1.0f, 1.0f)), _ambient(0.5f), 
    _diffuse(0.2f), _reflection(0.0f), _texture(0), _normalmap(0), 
    _uscale(1.0f), _vscale(1.0f), _fresnel_factor(1.0f), _fresnel_power(0.0f), _specular(0.8f)
{

}
Material& Material::operator=(const Material& rhs)
{
    _color = rhs._color;
    _ambient = rhs._ambient;
    _diffuse = rhs._diffuse;
    _reflection = rhs._reflection;
    return *this;
}
void Material::setColor(Vec4 color)
{
    _color = color;
}
Vec4& Material::getColor()
{
    return _color;
}
const Vec4& Material::getColor() const
{ 
    return _color;
}
void Material::setAmbient(float ambient)
{
    _ambient = ambient;
}
float Material::getAmbient() const
{
    return _ambient;
}
void Material::setDiffuse(float diffuse)
{
    _diffuse = diffuse;
}
float Material::getDiffuse() const
{
    return _diffuse;
}
void Material::setReflection(float reflection)
{
    _reflection = reflection;
}
float Material::getReflection() const 
{
    return _reflection;
}
void Material::setTexture(Texture* tex)
{
    _texture = tex;
}
Texture* Material::getTexture()
{
    return _texture;
}
const Texture* Material::getTexture() const
{
    return _texture;
}
void Material::setNormalMap(Texture* normalmap)
{
    _normalmap = normalmap;
}
Texture* Material::getNormalMap()
{
    return _normalmap;
}
const Texture* Material::getNormalMap() const
{
    return _normalmap;
}

