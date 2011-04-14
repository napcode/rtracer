/*
 * =====================================================================================
 *
 *       Filename:  ImageIO.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/04/2011 05:05:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */
#ifndef RAY_IMAGEIO_H
#define RAY_IMAGEIO_H

#include <stdint.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "RayTracer.h"
#include "Pixel.h"
#include "Texture.h"
namespace ray
{
    namespace img
    {
        enum FILEFORMAT {
            PPM,  
            JPG
        };
        class Writer 
        {
            public:
                Writer();
                void setFileFormat(const std::string& ext);
                void setFileFormat(FILEFORMAT f);
                FILEFORMAT getFileFormat() const;

                void setFileNamePrefix(const std::string& prefix);

                std::string& getFileNamePrefix();
                const std::string& getFileNamePrefix() const;

                std::string& getFilePath() ;
                const std::string& getFilePath() const;

                std::string getOutputFilePath() const;

                bool write(const PixelBuffer &pbuffer, uint32_t height, uint32_t width );
            private:
                std::string getFileExtension() const;
                bool writePPM(const PixelBuffer &buffer, uint32_t height, uint32_t width);
                bool writeJPG(const PixelBuffer &buffer, uint32_t height, uint32_t width);
                std::string _prefix;
                std::string _path;
                FILEFORMAT _fmt;
        };
        class Reader
        {
            public:
                Reader();
                Texture* readTexture(const std::string& filepath);
            private:
                Texture* readTexturePPM(const std::string& filepath);
                Texture* readTextureJPG(const std::string& filepath);
                bool checkComments(std::string& infile);
        };
        class ImageIO
        {
            public:
                static ImageIO& getInstance();
                Writer& getWriter();
                const Writer& getWriter() const;
                Reader& getReader();
                const Reader& getReader() const;
            private:
                ImageIO();
                ~ImageIO();
                Reader *_reader;
                Writer *_writer;
                static ImageIO *_instance;

        };
    }
}
#endif
