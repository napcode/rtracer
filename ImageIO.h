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
        /**
         * enum describes all known image formats
         */
        enum FILEFORMAT {
            PPM,  
            JPG
        };

        /**
         * @brief writes images to disk
         *
         * a file writer class which is capable of writing various image formats
         */
        class Writer 
        {
            public:
                //! ctor
                Writer();

                /**
                 * set output format via file extension
                 * @param ext a reference to a string containing a well-established file extension
                 */
                void setFileFormat(const std::string& ext);
                /**
                 * set output format
                 * @param f the output file format
                 */
                inline void setFileFormat(FILEFORMAT f) { _fmt = f; }
                /**
                 * get the current output file format
                 * @return the current output file format
                 */
                inline FILEFORMAT getFileFormat() const { return _fmt; }

                /**
                 * set which filename shall be used for the next write() call
                 * @param prefix a reference to the new filename
                 */
                inline void setFileNamePrefix(const std::string& prefix) { _prefix = prefix; }
                /**
                 * get the current filename 
                 * @return a reference to the current filename
                 */
                inline std::string& getFileNamePrefix() { return _prefix; }
                /**
                 * get the current filename  - const version
                 * @return a reference to the current filename
                 */
                inline const std::string& getFileNamePrefix() const { return _prefix; }

                /**
                 * set the output path 
                 * @param path the new output path
                 */
                inline void setFilePath(const std::string& path) { _path = path; }
                /**
                 * get the output path 
                 * @return the current output path
                 */
                inline std::string& getFilePath() { return _path; }
                /**
                 * get the output path - const version
                 * @return the current output path
                 */
                inline const std::string& getFilePath() const { return _path; }

                /**
                 * construct and return the full output path (incl. filename) for the next write() operation
                 * @return the full output path 
                 */
                std::string getOutputFilePath() const;

                /**
                 * write the pixelbuffer to disk using the current format & name settings
                 * @param pbuffer a reference to the pixelbuffer
                 * @param height the height of the given pixelbuffer
                 * @param width the width of the given pixelbuffer
                 * @return true if writing was successfull
                 */
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
