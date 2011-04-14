#ifndef MATH_MATRIX4D_H
#define MATH_MATRIX4D_H

#define SET_ROW(row, v1, v2, v3, v4 )    \
    _mat[(row)][0] = (v1); \
_mat[(row)][1] = (v2); \
_mat[(row)][2] = (v3); \
_mat[(row)][3] = (v4);

#define INNER_PRODUCT(a,b,r,c) \
    ((a)._mat[r][0] * (b)._mat[0][c]) \
+((a)._mat[r][1] * (b)._mat[1][c]) \
+((a)._mat[r][2] * (b)._mat[2][c]) \
+((a)._mat[r][3] * (b)._mat[3][c])

#include "Vec3d.h"
#include "Vec3f.h"
#include "Vec4d.h"
#include "Vec4f.h"
namespace math
{
    class Quat;

    class Matrix4d {
        public:
            typedef double value_type;

            inline Matrix4d() { makeIdentity(); };
            inline Matrix4d( const Matrix4d& mat) { set(mat.ptr()); };
            Matrix4d(value_type a00, value_type a01, value_type a02,value_type a03,
                    value_type a10, value_type a11, value_type a12,value_type a13,
                    value_type a20, value_type a21, value_type a22,value_type a23,
                    value_type a30, value_type a31, value_type a32,value_type a33);
            inline explicit Matrix4d( value_type const * const ptr ) { set(ptr); };
            inline explicit Matrix4d( float const * const ptr ) { set( (value_type*) ptr); };

            inline Matrix4d& operator = (const Matrix4d& rhs)
            {
                if( &rhs == this ) return *this;
                set(rhs.ptr());
                return *this;
            };

            inline void setCell(int row, int col, value_type value) {
                _mat[row][col] = value;
            }

            const value_type * ptr() const { return (const value_type *)_mat; };
            value_type* ptr() { return (value_type*)_mat; };

            value_type& operator [] (int i) {return ptr()[i];}
            value_type operator [] (int i) const {return ptr()[i];}
            value_type& operator()(int row, int col) { return _mat[row][col]; }
            value_type operator()(int row, int col) const { return _mat[row][col]; }

            // basic Matrix4d multiplication, our workhorse methods.
            void mult( const Matrix4d&, const Matrix4d& );
            void preMult( const Matrix4d& );
            void postMult( const Matrix4d& );

            /** Optimized version of preMult(translate(v)); */
            inline void preMultTranslate( const Vec3d& v );
            inline void preMultTranslate( const Vec3f& v );
            /** Optimized version of postMult(translate(v)); */
            inline void postMultTranslate( const Vec3d& v );
            inline void postMultTranslate( const Vec3f& v );

            /** Optimized version of preMult(scale(v)); */
            inline void preMultScale( const Vec3d& v );
            inline void preMultScale( const Vec3f& v );
            /** Optimized version of postMult(scale(v)); */
            inline void postMultScale( const Vec3d& v );
            inline void postMultScale( const Vec3f& v );

            inline Vec3f preMult( const Vec3f& v ) const;
            inline Vec3d preMult( const Vec3d& v ) const;
            inline Vec4f preMult( const Vec4f& v ) const;
            inline Vec4d preMult( const Vec4d& v ) const;
            inline Vec3f postMult( const Vec3f& v ) const;
            inline Vec3d postMult( const Vec3d& v ) const;
            inline Vec4f postMult( const Vec4f& v ) const;
            inline Vec4d postMult( const Vec4d& v ) const;
            inline Vec3f operator* ( const Vec3f& v ) const;
            inline Vec3d operator* ( const Vec3d& v ) const;
            inline Vec4f operator* ( const Vec4f& v ) const;
            inline Vec4d operator* ( const Vec4d& v ) const;
            inline void operator *= ( const Matrix4d& other ) 
            {    if( this == &other ) {
                                          Matrix4d temp(other);
                                          postMult( temp );
                                      }
            else postMult( other ); 
            }

            inline Matrix4d operator * ( const Matrix4d &m ) const
            {
                math::Matrix4d r;
                r.mult(*this,m);
                return  r;
            }
            int compare(const Matrix4d& m) const;
            bool operator < (const Matrix4d& m) const { return compare(m)<0; }
            bool operator == (const Matrix4d& m) const { return compare(m)==0; }
            bool operator != (const Matrix4d& m) const { return compare(m)!=0; }

        inline void set(const Matrix4d& rhs) { set(rhs.ptr()); };

        inline void set(float const * const ptr)
        {
            value_type* local_ptr = (value_type*)_mat;
            for(int i=0;i<16;++i) local_ptr[i]=(value_type)ptr[i];
        }
        
        inline void set(double const * const ptr)
        {
            value_type* local_ptr = (value_type*)_mat;
            for(int i=0;i<16;++i) local_ptr[i]=(value_type)ptr[i];
        }

        void set(value_type a00, value_type a01, value_type a02,value_type a03,
                 value_type a10, value_type a11, value_type a12,value_type a13,
                 value_type a20, value_type a21, value_type a22,value_type a23,
                 value_type a30, value_type a31, value_type a32,value_type a33);

        inline Vec3d getTrans() const { return Vec3d(_mat[3][0],_mat[3][1],_mat[3][2]); } 
        void setTrans( value_type tx, value_type ty, value_type tz );
        void setTrans( const Vec3f& v );
        void setTrans( const Vec3d& v );
        Quat getRotate() const;
        void setRotate(const Quat& q);
        void makeRotate( const Vec3f& from, const Vec3f& to );
        void makeRotate( const Vec3d& from, const Vec3d& to );
        void makeRotate( value_type angle, const Vec3f& axis );
        void makeRotate( value_type angle, const Vec3d& axis );
        void makeRotate( value_type angle, value_type x, value_type y, value_type z );
        void makeRotate( const Quat& );
        void makeRotate( value_type angle1, const Vec3f& axis1, 
                         value_type angle2, const Vec3f& axis2,
                         value_type angle3, const Vec3f& axis3);
        void makeRotate( value_type angle1, const Vec3d& axis1, 
                         value_type angle2, const Vec3d& axis2,
                         value_type angle3, const Vec3d& axis3);
        inline Vec3d getScale() const {
          Vec3d x_vec(_mat[0][0],_mat[1][0],_mat[2][0]); 
          Vec3d y_vec(_mat[0][1],_mat[1][1],_mat[2][1]); 
          Vec3d z_vec(_mat[0][2],_mat[1][2],_mat[2][2]); 
          return Vec3d(x_vec.length(), y_vec.length(), z_vec.length()); 
        }
        protected:
            value_type	_mat[4][4];

            void makeIdentity() {
                SET_ROW(0,    1, 0, 0, 0 )
                    SET_ROW(1,    0, 1, 0, 0 )
                    SET_ROW(2,    0, 0, 1, 0 )
                    SET_ROW(3,    0, 0, 0, 1 )
            };
    };
}

using namespace math;

inline Vec3f Matrix4d::postMult( const Vec3f& v ) const
{
    value_type d = 1.0f/(_mat[3][0]*v.x()+_mat[3][1]*v.y()+_mat[3][2]*v.z()+_mat[3][3]) ;
    return Vec3f( (_mat[0][0]*v.x() + _mat[0][1]*v.y() + _mat[0][2]*v.z() + _mat[0][3])*d,
            (_mat[1][0]*v.x() + _mat[1][1]*v.y() + _mat[1][2]*v.z() + _mat[1][3])*d,
            (_mat[2][0]*v.x() + _mat[2][1]*v.y() + _mat[2][2]*v.z() + _mat[2][3])*d) ;
}

inline Vec3d Matrix4d::postMult( const Vec3d& v ) const
{
    value_type d = 1.0f/(_mat[3][0]*v.x()+_mat[3][1]*v.y()+_mat[3][2]*v.z()+_mat[3][3]) ;
    return Vec3d( (_mat[0][0]*v.x() + _mat[0][1]*v.y() + _mat[0][2]*v.z() + _mat[0][3])*d,
            (_mat[1][0]*v.x() + _mat[1][1]*v.y() + _mat[1][2]*v.z() + _mat[1][3])*d,
            (_mat[2][0]*v.x() + _mat[2][1]*v.y() + _mat[2][2]*v.z() + _mat[2][3])*d) ;
}

inline Vec3f Matrix4d::preMult( const Vec3f& v ) const
{
    value_type d = 1.0f/(_mat[0][3]*v.x()+_mat[1][3]*v.y()+_mat[2][3]*v.z()+_mat[3][3]) ;
    return Vec3f( (_mat[0][0]*v.x() + _mat[1][0]*v.y() + _mat[2][0]*v.z() + _mat[3][0])*d,
            (_mat[0][1]*v.x() + _mat[1][1]*v.y() + _mat[2][1]*v.z() + _mat[3][1])*d,
            (_mat[0][2]*v.x() + _mat[1][2]*v.y() + _mat[2][2]*v.z() + _mat[3][2])*d);
}

inline Vec3d Matrix4d::preMult( const Vec3d& v ) const
{
    value_type d = 1.0f/(_mat[0][3]*v.x()+_mat[1][3]*v.y()+_mat[2][3]*v.z()+_mat[3][3]) ;
    return Vec3d( (_mat[0][0]*v.x() + _mat[1][0]*v.y() + _mat[2][0]*v.z() + _mat[3][0])*d,
            (_mat[0][1]*v.x() + _mat[1][1]*v.y() + _mat[2][1]*v.z() + _mat[3][1])*d,
            (_mat[0][2]*v.x() + _mat[1][2]*v.y() + _mat[2][2]*v.z() + _mat[3][2])*d);
}

inline Vec4f Matrix4d::postMult( const Vec4f& v ) const
{
    return Vec4f( (_mat[0][0]*v.x() + _mat[0][1]*v.y() + _mat[0][2]*v.z() + _mat[0][3]*v.w()),
            (_mat[1][0]*v.x() + _mat[1][1]*v.y() + _mat[1][2]*v.z() + _mat[1][3]*v.w()),
            (_mat[2][0]*v.x() + _mat[2][1]*v.y() + _mat[2][2]*v.z() + _mat[2][3]*v.w()),
            (_mat[3][0]*v.x() + _mat[3][1]*v.y() + _mat[3][2]*v.z() + _mat[3][3]*v.w())) ;
}
inline Vec4d Matrix4d::postMult( const Vec4d& v ) const
{
    return Vec4d( (_mat[0][0]*v.x() + _mat[0][1]*v.y() + _mat[0][2]*v.z() + _mat[0][3]*v.w()),
            (_mat[1][0]*v.x() + _mat[1][1]*v.y() + _mat[1][2]*v.z() + _mat[1][3]*v.w()),
            (_mat[2][0]*v.x() + _mat[2][1]*v.y() + _mat[2][2]*v.z() + _mat[2][3]*v.w()),
            (_mat[3][0]*v.x() + _mat[3][1]*v.y() + _mat[3][2]*v.z() + _mat[3][3]*v.w())) ;
}

inline Vec4f Matrix4d::preMult( const Vec4f& v ) const
{
    return Vec4f( (_mat[0][0]*v.x() + _mat[1][0]*v.y() + _mat[2][0]*v.z() + _mat[3][0]*v.w()),
            (_mat[0][1]*v.x() + _mat[1][1]*v.y() + _mat[2][1]*v.z() + _mat[3][1]*v.w()),
            (_mat[0][2]*v.x() + _mat[1][2]*v.y() + _mat[2][2]*v.z() + _mat[3][2]*v.w()),
            (_mat[0][3]*v.x() + _mat[1][3]*v.y() + _mat[2][3]*v.z() + _mat[3][3]*v.w()));
}

inline Vec4d Matrix4d::preMult( const Vec4d& v ) const
{
    return Vec4d( (_mat[0][0]*v.x() + _mat[1][0]*v.y() + _mat[2][0]*v.z() + _mat[3][0]*v.w()),
            (_mat[0][1]*v.x() + _mat[1][1]*v.y() + _mat[2][1]*v.z() + _mat[3][1]*v.w()),
            (_mat[0][2]*v.x() + _mat[1][2]*v.y() + _mat[2][2]*v.z() + _mat[3][2]*v.w()),
            (_mat[0][3]*v.x() + _mat[1][3]*v.y() + _mat[2][3]*v.z() + _mat[3][3]*v.w()));
}
inline Vec3f operator* (const Vec3f& v, const Matrix4d& m )
{
    return m.preMult(v);
}

inline Vec3d operator* (const Vec3d& v, const Matrix4d& m )
{
    return m.preMult(v);
}

inline Vec4f operator* (const Vec4f& v, const Matrix4d& m )
{
    return m.preMult(v);
}

inline Vec4d operator* (const Vec4d& v, const Matrix4d& m )
{
    return m.preMult(v);
}

inline Vec3f Matrix4d::operator* (const Vec3f& v) const
{
    return postMult(v);
}

inline Vec3d Matrix4d::operator* (const Vec3d& v) const
{
    return postMult(v);
}

inline Vec4f Matrix4d::operator* (const Vec4f& v) const
{
    return postMult(v);
}

inline Vec4d Matrix4d::operator* (const Vec4d& v) const
{
    return postMult(v);
}
#endif	/* _MATRIX_H */

