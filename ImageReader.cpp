/*
 * =====================================================================================
 *
 *       Filename:  ImageReader.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/04/2011 05:09:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */
#include "ImageIO.h"
#include "math/Vec3.h"

using namespace ray;
using namespace ray::img;

Reader::Reader()
{

}
Texture* Reader::readTexture(const std::string& filepath)
{
    // guess file format from file extension
    size_t pos = filepath.rfind('.');
    if (pos == std::string::npos)
        return 0;
    std::string ext = filepath.substr(pos + 1);
    if (ext.compare("ppm") == 0)
        return readTexturePPM(filepath);
    else {
        std::cerr << "error: unknown file format" << std::endl;
        return 0;
    }
}
Texture* Reader::readTexturePPM(const std::string& filepath)
{
    std::ifstream infile;
    std::stringstream ss;
    infile.open(filepath.c_str());
    if ( infile.is_open() ) {
        Texture *t = new Texture;
        std::string tmp;
        std::string format;
        int width, height;
        int max;
        bool ret = false;
        // read format
        do {
            getline(infile, tmp);
            ret = checkComments(tmp);
        } while (ret);
        ss << tmp;
        ss >> format;

        // read width & height
        ret = false;
        do {
            getline(infile, tmp);
            ret = checkComments(tmp);
        } while (ret);
        std::istringstream iss(tmp);
        iss >> std::skipws >> width >> height;
        t->setWidth(width);
        t->setHeight(height);

        // read max value
        ret = false;
        do {

            getline(infile, tmp);
            ret = checkComments(tmp);
        } while (ret);
        std::istringstream iss1(tmp);
        iss1>> std::skipws >> max;

        // flush comments
        ret = false;
        char c = infile.peek();
        while ( c == '#' ) {
            getline(infile, tmp);
            c = infile.peek();
        } 

        PixelBuffer &buffer = t->getImageBuffer();
        buffer.resize(width * height);
        PixelBuffer::iterator it = buffer.begin();
        while (it != buffer.end()) {
            math::Vec4 data;
            infile >> data[0]
                >> data[1]
                >> data[2];
            data /= max;
            data[3] = 1.0f;
            it->set(data);
            it++;
            if (infile.eof()) {
                std::cerr << "error: unable to read file " << filepath << std::endl;
                delete t;
                return 0;
            }
        }
        return t;
    }
    return 0;
}
Texture* Reader::readTextureJPG(const std::string& filepath)
{
    std::cerr << "reading " << filepath << " is not implemented yet" << std::endl;
    return 0;
}
bool Reader::checkComments(std::string& buffer)
{
    size_t pos  = buffer.find('#');
    if (pos != std::string::npos)  {
        return true;
    }
    return false;
}
