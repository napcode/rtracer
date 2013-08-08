/*
 * =====================================================================================
 *
 *       Filename:  Ray.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/07/2011 01:06:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@apparatus.de
 *
 * =====================================================================================
 */

#include "Ray.h"

using namespace ray;
using namespace math;

Ray::Ray()
{

}

    Ray::Ray(const Vec3& origin, const Vec3& direction)
: _origin(origin), _direction(direction)
{

}
