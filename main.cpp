/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/04/2011 04:43:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "RayTracer.h"
#include "Scene.h"
#include "ImageIO.h"
#include "Pixel.h"
#include "Texture.h"

/* some global variables */
/* that's not exactly a nice example for "good coding style" */
int img_width;          
int img_height;
std::string filename;

void parseArguments(int argc, char **argv)
{
    if (argc == 1) {
        std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
        std::cout << "   -o: output prefix for filename, e.g. \"output\"" << std::endl;
        std::cout << "   -w: width of image to be generated" << std::endl;
        std::cout << "   -h: height of image to be generated" << std::endl;
        return;
    }
    for (int i = 1; i < argc; i++) { 

        if (strcmp(argv[i],"-o")==0) {
            filename.assign(argv[i + 1]);
        } else if (strcmp(argv[i],"-w")==0) {
            img_width = atoi(argv[i + 1]);
        } else if (strcmp(argv[i],"-h")==0) {
            img_height = atoi(argv[i + 1]);
        } 
    }
}
int main(int argc, char **argv)
{
    img_width = IMG_WIDTH;
    img_height = IMG_HEIGHT;
    filename = "output";
    parseArguments(argc, argv);

    std::cout << "Raytracer " << VERSION << std::endl;
    std::cout << "Tracing " << img_width << "x" << img_height << " pixels"  << std::endl;
    // get an instance of the RayTracer
    ray::RayTracer tracer;
    ray::Scene scene;

    // create the default scene
    scene.createDefaultScene();
    // attach this scene to the tracer
    tracer.setScene(scene);
    // setup framebuffer etc.
    tracer.prepare(img_height, img_width);

    // trace!
    tracer.trace(0, img_height*img_width);

    // write the framebuffer to disk
    // 1st we need a ref to ImageIO interface
    ray::img::ImageIO& imgio = ray::img::ImageIO::getInstance();
    // tell the interface to use the PPM format
    imgio.getWriter().setFileFormat("ppm");
    // the file shall be named "output.XXX"
    imgio.getWriter().setFileNamePrefix(filename);

    // clamp pixel buffer as some pixels may reach invalid values
    ray::PixelBuffer buffer = ray::clampPixelBuffer(tracer.getFrameBuffer());
    // write the the file
    imgio.getWriter().write(buffer, img_height, img_width);
    //  tell the user that we're done
    std::cout << "Image has been written to " << imgio.getWriter().getOutputFilePath() << std::endl;
    return EXIT_SUCCESS;
}
