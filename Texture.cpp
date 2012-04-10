/*
 * =====================================================================================
 *
 *       Filename:  Texture.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/11/2011 02:56:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */

#include "Texture.h"
#include <iostream>
using namespace ray;
using namespace math;

Texture::Texture()
   : _width(0), _height(0)
{}

Vec4 Texture::getTexel(float u, float v) const
{
    float fu = u * _width;
    float fv = v * _height;

    int u1 = ((int)fu) % _width;
    int v1 = ((int)fv) % _height;
    int u2 = (u1 + 1) % _width;
    int v2 = (v1 + 1) % _height;

    Vec4 c1, c2, c3, c4;
    if ( _texture.size() > 0 ) {
        if ( v1 > 0 || ( u1 > 0 && u2 > 0 )) {
            c1 = _texture[u1 + v1 * _width].get();
            c2 = _texture[u2 + v1 * _width].get();
        }
        if ( v2 > 0 || ( u1 > 0 && u2 > 0)) {
            c3 = _texture[u1 + v2 * _width].get();
            c4 = _texture[u2 + v2 * _width].get();
        }
    }
    return (c1 + c2 + c3 + c4)* 0.25f;
}
