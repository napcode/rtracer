/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield 
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/

#ifndef MATH_QUAT_H
#define MATH_QUAT_H 1

#include "Vec3.h"
#include "Vec3d.h"
#include "Vec4d.h"

namespace math {

class Matrix4f;
class Matrix4d;

/** A quaternion class. It can be used to represent an orientation in 3D space.*/
class Quat
{

    public:

        typedef double value_type;

        value_type  _v[4];    // a four-vector

        inline Quat() { _v[0]=0.0; _v[1]=0.0; _v[2]=0.0; _v[3]=1.0; }

        inline Quat( value_type x, value_type y, value_type z, value_type w )
        {
            _v[0]=x;
            _v[1]=y;
            _v[2]=z;
            _v[3]=w;
        }

        inline Quat( value_type angle, const Vec3& axis)
        {
            makeRotate(angle,axis);
        }
        inline Quat( value_type angle, const Vec3d& axis)
        {
            makeRotate(angle,axis);
        }

        inline Quat( value_type angle1, const Vec3& axis1, 
                     value_type angle2, const Vec3& axis2,
                     value_type angle3, const Vec3& axis3)
        {
            makeRotate(angle1,axis1,angle2,axis2,angle3,axis3);
        }

        inline Quat& operator = (const Quat& v) { _v[0]=v._v[0];  _v[1]=v._v[1]; _v[2]=v._v[2]; _v[3]=v._v[3]; return *this; }

        inline bool operator == (const Quat& v) const { return _v[0]==v._v[0] && _v[1]==v._v[1] && _v[2]==v._v[2] && _v[3]==v._v[3]; }

        inline bool operator != (const Quat& v) const { return _v[0]!=v._v[0] || _v[1]!=v._v[1] || _v[2]!=v._v[2] || _v[3]!=v._v[3]; }

        inline bool operator <  (const Quat& v) const
        {
            if (_v[0]<v._v[0]) return true;
            else if (_v[0]>v._v[0]) return false;
            else if (_v[1]<v._v[1]) return true;
            else if (_v[1]>v._v[1]) return false;
            else if (_v[2]<v._v[2]) return true;
            else if (_v[2]>v._v[2]) return false;
            else return (_v[3]<v._v[3]);
        }

        /* ----------------------------------
           Methods to access data members
        ---------------------------------- */

        inline void set(value_type x, value_type y, value_type z, value_type w)
        {
            _v[0]=x;
            _v[1]=y;
            _v[2]=z;
            _v[3]=w;
        }
        
     
        void set(const Matrix4f& matrix);
        void get(Matrix4f& matrix) const;
        void set(const Matrix4d& matrix);
        void get(Matrix4d& matrix) const;

        inline value_type & operator [] (int i) { return _v[i]; }
        inline value_type   operator [] (int i) const { return _v[i]; }

        inline value_type & x() { return _v[0]; }
        inline value_type & y() { return _v[1]; }
        inline value_type & z() { return _v[2]; }
        inline value_type & w() { return _v[3]; }

        inline value_type x() const { return _v[0]; }
        inline value_type y() const { return _v[1]; }
        inline value_type z() const { return _v[2]; }
        inline value_type w() const { return _v[3]; }

        /** return true if the Quat represents a zero rotation, and therefore can be ignored in computations.*/
        bool zeroRotation() const { return _v[0]==0.0 && _v[1]==0.0 && _v[2]==0.0 && _v[3]==1.0; } 


         /* ------------------------------------------------------------- 
                   BASIC ARITHMETIC METHODS            
        Implemented in terms of Vec4s.  Some Vec4 operators, e.g.
        operator* are not appropriate for quaternions (as
        mathematical objects) so they are implemented differently.
        Also define methods for conjugate and the multiplicative inverse.            
        ------------------------------------------------------------- */
        /// Multiply by scalar 
        inline const Quat operator * (value_type rhs) const
        {
            return Quat(_v[0]*rhs, _v[1]*rhs, _v[2]*rhs, _v[3]*rhs);
        }

        /// Unary multiply by scalar 
        inline Quat& operator *= (value_type rhs)
        {
            _v[0]*=rhs;
            _v[1]*=rhs;
            _v[2]*=rhs;
            _v[3]*=rhs;
            return *this;        // enable nesting
        }

        /// Binary multiply 
        inline const Quat operator*(const Quat& rhs) const
        {
            return Quat( rhs._v[3]*_v[0] + rhs._v[0]*_v[3] + rhs._v[1]*_v[2] - rhs._v[2]*_v[1],
                 rhs._v[3]*_v[1] - rhs._v[0]*_v[2] + rhs._v[1]*_v[3] + rhs._v[2]*_v[0],
                 rhs._v[3]*_v[2] + rhs._v[0]*_v[1] - rhs._v[1]*_v[0] + rhs._v[2]*_v[3],
                 rhs._v[3]*_v[3] - rhs._v[0]*_v[0] - rhs._v[1]*_v[1] - rhs._v[2]*_v[2] );
        }

        /// Unary multiply 
        inline Quat& operator*=(const Quat& rhs)
        {
            value_type x = rhs._v[3]*_v[0] + rhs._v[0]*_v[3] + rhs._v[1]*_v[2] - rhs._v[2]*_v[1];
            value_type y = rhs._v[3]*_v[1] - rhs._v[0]*_v[2] + rhs._v[1]*_v[3] + rhs._v[2]*_v[0];
            value_type z = rhs._v[3]*_v[2] + rhs._v[0]*_v[1] - rhs._v[1]*_v[0] + rhs._v[2]*_v[3];
            _v[3]   = rhs._v[3]*_v[3] - rhs._v[0]*_v[0] - rhs._v[1]*_v[1] - rhs._v[2]*_v[2];

            _v[2] = z;
            _v[1] = y;
            _v[0] = x;

            return (*this);            // enable nesting
        }

        /// Divide by scalar 
        inline Quat operator / (value_type rhs) const
        {
            value_type div = 1.0/rhs;
            return Quat(_v[0]*div, _v[1]*div, _v[2]*div, _v[3]*div);
        }

        /// Unary divide by scalar 
        inline Quat& operator /= (value_type rhs)
        {
            value_type div = 1.0/rhs;
            _v[0]*=div;
            _v[1]*=div;
            _v[2]*=div;
            _v[3]*=div;
            return *this;
        }

        /// Binary divide 
        inline const Quat operator/(const Quat& denom) const
        {
            return ( (*this) * denom.inverse() );
        }

        /// Unary divide 
        inline Quat& operator/=(const Quat& denom)
        {
            (*this) = (*this) * denom.inverse();
            return (*this);            // enable nesting
        }

        /// Binary addition 
        inline const Quat operator + (const Quat& rhs) const
        {
            return Quat(_v[0]+rhs._v[0], _v[1]+rhs._v[1],
                _v[2]+rhs._v[2], _v[3]+rhs._v[3]);
        }

        /// Unary addition
        inline Quat& operator += (const Quat& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            _v[2] += rhs._v[2];
            _v[3] += rhs._v[3];
            return *this;            // enable nesting
        }

        /// Binary subtraction 
        inline const Quat operator - (const Quat& rhs) const
        {
            return Quat(_v[0]-rhs._v[0], _v[1]-rhs._v[1],
                _v[2]-rhs._v[2], _v[3]-rhs._v[3] );
        }

        /// Unary subtraction 
        inline Quat& operator -= (const Quat& rhs)
        {
            _v[0]-=rhs._v[0];
            _v[1]-=rhs._v[1];
            _v[2]-=rhs._v[2];
            _v[3]-=rhs._v[3];
            return *this;            // enable nesting
        }

        /** Negation operator - returns the negative of the quaternion.
        Basically just calls operator - () on the Vec4 */
        inline const Quat operator - () const
        {
            return Quat (-_v[0], -_v[1], -_v[2], -_v[3]);
        }

        /// Length of the quaternion = sqrt( vec . vec )
        value_type length() const
        {
            return sqrt( _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] + _v[3]*_v[3]);
        }

        /// Length of the quaternion = vec . vec
        value_type length2() const
        {
            return _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] + _v[3]*_v[3];
        }

        /// Conjugate 
        inline Quat conj () const
        { 
             return Quat( -_v[0], -_v[1], -_v[2], _v[3] );
        }

        /// Multiplicative inverse method: q^(-1) = q^*/(q.q^*)
        inline const Quat inverse () const
        {
             return conj() / length2();
         }

      /* -------------------------------------------------------- 
               METHODS RELATED TO ROTATIONS
        Set a quaternion which will perform a rotation of an
        angle around the axis given by the vector (x,y,z).
        Should be written to also accept an angle and a Vec3?

        Define Spherical Linear interpolation method also

        Not inlined - see the Quat.cpp file for implementation
        -------------------------------------------------------- */
        void makeRotate( value_type  angle, 
                          value_type  x, value_type  y, value_type  z );
        void makeRotate ( value_type  angle, const Vec3& vec );

        void makeRotate ( value_type  angle1, const Vec3& axis1, 
                          value_type  angle2, const Vec3& axis2,
                          value_type  angle3, const Vec3& axis3);

        /** Make a rotation Quat which will rotate vec1 to vec2.
            Generally take a dot product to get the angle between these
            and then use a cross product to get the rotation axis
            Watch out for the two special cases when the vectors
            are co-incident or opposite in direction.*/
        void makeRotate( const Vec3& vec1, const Vec3& vec2 );
        void makeRotate( const Vec3d& from, const Vec3d& to );
    
        void makeRotate_original( const Vec3& vec1, const Vec3& vec2 );
        void makeRotate_original( const Vec3d& vec1, const Vec3d& vec2 );

        /** Return the angle and vector components represented by the quaternion.*/
        void getRotate ( value_type & angle, value_type & x, value_type & y, value_type & z ) const;

        /** Return the angle and vector represented by the quaternion.*/
        void getRotate ( value_type & angle, Vec3& vec ) const;
        void getRotate ( value_type & angle, Vec3d& vec ) const;

        /** Spherical Linear Interpolation.
        As t goes from 0 to 1, the Quat object goes from "from" to "to". */
        void slerp   ( value_type  t, const Quat& from, const Quat& to);
               
        /** Rotate a vector by this quaternion.*/
        Vec3 operator* (const Vec3& v) const
        {
            // nVidia SDK implementation
            Vec3 uv, uuv; 
            Vec3 qvec(_v[0], _v[1], _v[2]);
            uv = qvec ^ v;
            uuv = qvec ^ uv; 
            uv *= ( 2.0f * _v[3] ); 
            uuv *= 2.0f; 
            return v + uv + uuv;
        }
               
        inline Vec4d asVec4() const
        {
            return Vec4d(_v[0], _v[1], _v[2], _v[3]);
        }

        inline Vec3d asVec3() const
        {
            return Vec3d(_v[0], _v[1], _v[2]);
        }
       
    protected:
    
};    // end of class prototype

}    // end of namespace

#endif

