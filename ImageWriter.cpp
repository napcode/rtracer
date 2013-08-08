/*
 * =====================================================================================
 *
 *       Filename:  ImageWriter.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/04/2011 05:10:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@apparatus.de
 *
 * =====================================================================================
 */

#include "ImageIO.h"
#include <iostream>
#include <fstream>
using namespace ray;
using namespace ray::img;

Writer::Writer()
    : _prefix("outfile"), _fmt(PPM)
{

}
void Writer::setFileFormat(const std::string& ext)
{
    if (ext.compare("ppm") == 0)
        _fmt = PPM;
    else if (ext.compare("jpg") == 0)
        _fmt = JPG;

}
bool Writer::write(const PixelBuffer &buffer, uint32_t height, uint32_t width )
{
    bool ret = false;
    switch (_fmt) {
        case PPM:
            ret = writePPM(buffer, height, width);
            break;
        case JPG:
            ret = writeJPG(buffer, height, width);
            break;
        default:
            std::cerr << "fileformat not implemented" << std::endl;
    }
    return ret;
}
bool Writer::writePPM(const PixelBuffer &buffer, uint32_t height, uint32_t width)
{
    std::ofstream outfile;
    outfile.open(getOutputFilePath().c_str());
    if ( outfile.is_open() ) {
        outfile << "P3" << std::endl;
        outfile << width << " " << height << std::endl;
        outfile << "255" << std::endl;
        PixelBuffer::const_iterator it = buffer.begin();
        uint32_t i= 0;
        while (it != buffer.end()) {
            math::Vec4 out = it->get() * 255.0f;
            outfile << (int)out.x() << " " 
                << (int)out.y() << " "
                << (int)out.z() << " ";
            ++i;
            if (i % (width) == 0)
                outfile << std::endl;
            it++;
        }
        return true;
    }
    return false;
}
bool Writer::writeJPG(const PixelBuffer &buffer, uint32_t height, uint32_t width)
{
    return false;
}
std::string Writer::getOutputFilePath() const
{
    if (_path.length() > 0)
        return _path + std::string("/") + _prefix + std::string(".") + getFileExtension();
    else
        return _prefix + std::string(".") + getFileExtension();
} 
std::string Writer::getFileExtension() const
{
    switch (_fmt) {
        case PPM:
            return std::string("ppm");
        case JPG:
            return std::string("jpg");
        default:
            std::cerr << "format not implemented" << std::endl;
            return std::string();
    }
}
