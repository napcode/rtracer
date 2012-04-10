/*
 * =====================================================================================
 *
 *       Filename:  ImageIO.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/04/2011 05:06:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */

#include "ImageIO.h"
using namespace ray;
using namespace ray::img;

ImageIO* ImageIO::_instance = NULL;

ImageIO& ImageIO::getInstance()
{
        if (!_instance)
               _instance = new ImageIO();
        return *_instance;
}
ImageIO::ImageIO()
        : _reader(new Reader), _writer(new Writer)
{
}
ImageIO::~ImageIO()
{
        delete _writer;
        delete _reader;
}

Writer& ImageIO::getWriter() 
{
        return *_writer;
}
const Writer& ImageIO::getWriter() const
{
        return *_writer;
}
Reader& ImageIO::getReader() 
{
        return *_reader;
}
const Reader& ImageIO::getReader() const
{
        return *_reader;
}
