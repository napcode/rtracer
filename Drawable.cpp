/*
 * =====================================================================================
 *
 *       Filename:  Drawables.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/07/2011 09:13:02 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */

#include "Drawable.h"

using namespace ray;

    Drawable::Drawable(const std::string& name)
: _name(name)
{}
Drawable::~Drawable()
{}

