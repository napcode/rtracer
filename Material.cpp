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
 *         Author:  Mathias Buhr (), buhr@apparatus.de
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

