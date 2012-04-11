/*
 * =====================================================================================
 *
 *       Filename:  config.h
 *
 *    Description:  some defines to config various aspects of the ray tracer
 *
 *        Version:  1.0
 *        Created:  04/04/2011 04:50:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathias Buhr (), buhr@informatik.tu-freiberg.de
 *        Company:  TU-Bergakademie Freiberg
 *
 * =====================================================================================
 */

/**
 * @file config.h
 * header which defines various parameters of the raytracer
 * @author Mathias Buhr
 *
 * @mainpage RTracer - A C++ Ray Tracer
 * This is the class-documentation for the RTracer project. Feel free to add some useful
 * stuff here. Not everything is explained in "verbose"-mode. If anything is
 * unclear, either contact me or just add the documentation yourself. 
 *
 *  For questions and problems contact:
 *  	- Mathias Buhr <mathias.buhr@informatik.tu-freiberg.de>
 */

#ifndef CONFIG_H
#define CONFIG_H
/**
 * @def IMG_WIDTH 
 * height of output image 
 */
#define IMG_WIDTH 1280          
/**
 * @def IMG_HEIGHT 
 * height of output image 
 */
#define IMG_HEIGHT 1024         
/**
 * @def MAX_TRACE_DEPTH 
 * max iterations for recursive tracing
 */
#define MAX_TRACE_DEPTH 1      
/**
 * @def VERSION 
 * version string 
 */
#define VERSION "v0.1beta"      

#endif
