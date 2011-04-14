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
#include "config.h"
#include "RayTracer.h"
#include "Scene.h"
#include "ImageIO.h"
#include "Pixel.h"
#include "Texture.h"

int main()
{
    std::cout << "Raytracer " << VERSION << std::endl;
    // get an instance to of RayTracer
    ray::RayTracer tracer;
    ray::Scene scene;

    // create the default scene
    scene.createDefaultScene();
    // attach this scene to the tracer
    tracer.setScene(scene);
    // setup framebuffer etc.
    tracer.prepare();

    // trace!
    tracer.run();

    // write the framebuffer to disk
    ray::img::ImageIO& imgio = ray::img::ImageIO::getInstance();
    // use PPM format
    imgio.getWriter().setFileFormat("ppm");
    // the file shall be named "output.XXX"
    imgio.getWriter().setFileNamePrefix("output");

    // clamp pixel buffer, some pixels may reach invalid values
    ray::PixelBuffer buffer = ray::clampPixelBuffer(tracer.getFrameBuffer());
    // write the the file
    imgio.getWriter().write(buffer, IMG_HEIGHT, IMG_WIDTH);
    //  tell the user that we're done
    std::cout << "Image has been written to " << imgio.getWriter().getOutputFilePath() << std::endl;
    return 0;
}
