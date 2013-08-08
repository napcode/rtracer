#include "Matrix4f.h"
#include "Quat.h"
#include <limits>

using namespace math;

Matrix4f::Matrix4f( value_type a00, value_type a01, value_type a02, value_type a03,
                  value_type a10, value_type a11, value_type a12, value_type a13,
                  value_type a20, value_type a21, value_type a22, value_type a23,
                  value_type a30, value_type a31, value_type a32, value_type a33)
{
    SET_ROW(0, a00, a01, a02, a03 )
    SET_ROW(1, a10, a11, a12, a13 )
    SET_ROW(2, a20, a21, a22, a23 )
    SET_ROW(3, a30, a31, a32, a33 )
}
void Matrix4f::set( value_type a00, value_type a01, value_type a02, value_type a03,
                  value_type a10, value_type a11, value_type a12, value_type a13,
                  value_type a20, value_type a21, value_type a22, value_type a23,
                  value_type a30, value_type a31, value_type a32, value_type a33)
{
    SET_ROW(0, a00, a01, a02, a03 )
    SET_ROW(1, a10, a11, a12, a13 )
    SET_ROW(2, a20, a21, a22, a23 )
    SET_ROW(3, a30, a31, a32, a33 )
}

void Matrix4f::mult( const Matrix4f& lhs, const Matrix4f& rhs )
{   
    if (&lhs==this)
    {
        postMult(rhs);
        return;
    }
    if (&rhs==this)
    {
        preMult(lhs);
        return;
    }

// PRECONDITION: We assume neither &lhs nor &rhs == this
// if it did, use preMult or postMult instead
    _mat[0][0] = INNER_PRODUCT(lhs, rhs, 0, 0);
    _mat[0][1] = INNER_PRODUCT(lhs, rhs, 0, 1);
    _mat[0][2] = INNER_PRODUCT(lhs, rhs, 0, 2);
    _mat[0][3] = INNER_PRODUCT(lhs, rhs, 0, 3);
    _mat[1][0] = INNER_PRODUCT(lhs, rhs, 1, 0);
    _mat[1][1] = INNER_PRODUCT(lhs, rhs, 1, 1);
    _mat[1][2] = INNER_PRODUCT(lhs, rhs, 1, 2);
    _mat[1][3] = INNER_PRODUCT(lhs, rhs, 1, 3);
    _mat[2][0] = INNER_PRODUCT(lhs, rhs, 2, 0);
    _mat[2][1] = INNER_PRODUCT(lhs, rhs, 2, 1);
    _mat[2][2] = INNER_PRODUCT(lhs, rhs, 2, 2);
    _mat[2][3] = INNER_PRODUCT(lhs, rhs, 2, 3);
    _mat[3][0] = INNER_PRODUCT(lhs, rhs, 3, 0);
    _mat[3][1] = INNER_PRODUCT(lhs, rhs, 3, 1);
    _mat[3][2] = INNER_PRODUCT(lhs, rhs, 3, 2);
    _mat[3][3] = INNER_PRODUCT(lhs, rhs, 3, 3);
}

void Matrix4f::preMult( const Matrix4f& other )
{
    // brute force method requiring a copy
    //Matrix_implementation tmp(other* *this);
    // *this = tmp;

    // more efficient method just use a value_type[4] for temporary storage.
    value_type t[4];
    for(int col=0; col<4; ++col) {
        t[0] = INNER_PRODUCT( other, *this, 0, col );
        t[1] = INNER_PRODUCT( other, *this, 1, col );
        t[2] = INNER_PRODUCT( other, *this, 2, col );
        t[3] = INNER_PRODUCT( other, *this, 3, col );
        _mat[0][col] = t[0];
        _mat[1][col] = t[1];
        _mat[2][col] = t[2];
        _mat[3][col] = t[3];
    }

}

void Matrix4f::postMult( const Matrix4f& other )
{
    // brute force method requiring a copy
    //Matrix_implementation tmp(*this * other);
    // *this = tmp;

    // more efficient method just use a value_type[4] for temporary storage.
    value_type t[4];
    for(int row=0; row<4; ++row)
    {
        t[0] = INNER_PRODUCT( *this, other, row, 0 );
        t[1] = INNER_PRODUCT( *this, other, row, 1 );
        t[2] = INNER_PRODUCT( *this, other, row, 2 );
        t[3] = INNER_PRODUCT( *this, other, row, 3 );
        SET_ROW(row, t[0], t[1], t[2], t[3] )
    }
}
int Matrix4f::compare(const Matrix4f& m) const
{
    const Matrix4f::value_type* lhs = reinterpret_cast<const Matrix4f::value_type*>(_mat);
    const Matrix4f::value_type* end_lhs = lhs+16;
    const Matrix4f::value_type* rhs = reinterpret_cast<const Matrix4f::value_type*>(m._mat);
    for(;lhs!=end_lhs;++lhs,++rhs)
    {
        if (*lhs < *rhs) return -1;
        if (*rhs < *lhs) return 1;
    }
    return 0;
}
void Matrix4f::setTrans( value_type tx, value_type ty, value_type tz )
{
    _mat[3][0] = tx;
    _mat[3][1] = ty;
    _mat[3][2] = tz;
}
void Matrix4f::setTrans( const Vec3f& v )
{
    _mat[3][0] = v[0];
    _mat[3][1] = v[1];
    _mat[3][2] = v[2];
}
void Matrix4f::setTrans( const Vec3d& v )
{
    _mat[3][0] = v[0];
    _mat[3][1] = v[1];
    _mat[3][2] = v[2];
}
#define QX  q._v[0]
#define QY  q._v[1]
#define QZ  q._v[2]
#define QW  q._v[3]
void Matrix4f::setRotate(const Quat& q)
{
    double length2 = q.length2();
    if (fabs(length2) <= std::numeric_limits<double>::min())
    {
        _mat[0][0] = 0.0; _mat[1][0] = 0.0; _mat[2][0] = 0.0;
        _mat[0][1] = 0.0; _mat[1][1] = 0.0; _mat[2][1] = 0.0;
        _mat[0][2] = 0.0; _mat[1][2] = 0.0; _mat[2][2] = 0.0;
    }
    else
    {
        double rlength2;
        // normalize quat if required.
        // We can avoid the expensive sqrt in this case since all 'coefficients' below are products of two q components.
        // That is a square of a square root, so it is possible to avoid that
        if (length2 != 1.0)
        {
            rlength2 = 2.0/length2;
        }
        else
        {
            rlength2 = 2.0;
        }
        
        // Source: Gamasutra, Rotating Objects Using Quaternions
        //
        //http://www.gamasutra.com/features/19980703/quaternions_01.htm
        
        double wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
        
        // calculate coefficients
        x2 = rlength2*QX;
        y2 = rlength2*QY;
        z2 = rlength2*QZ;
        
        xx = QX * x2;
        xy = QX * y2;
        xz = QX * z2;
        
        yy = QY * y2;
        yz = QY * z2;
        zz = QZ * z2;
        
        wx = QW * x2;
        wy = QW * y2;
        wz = QW * z2;
        
        // Note.  Gamasutra gets the matrix assignments inverted, resulting
        // in left-handed rotations, which is contrary to OpenGL and OSG's 
        // methodology.  The matrix assignment has been altered in the next
        // few lines of code to do the right thing.
        // Don Burns - Oct 13, 2001
        _mat[0][0] = 1.0 - (yy + zz);
        _mat[1][0] = xy - wz;
        _mat[2][0] = xz + wy;
        
        
        _mat[0][1] = xy + wz;
        _mat[1][1] = 1.0 - (xx + zz);
        _mat[2][1] = yz - wx;
        
        _mat[0][2] = xz - wy;
        _mat[1][2] = yz + wx;
        _mat[2][2] = 1.0 - (xx + yy);
    }

#if 0
    _mat[0][3] = 0.0;
    _mat[1][3] = 0.0;
    _mat[2][3] = 0.0;

    _mat[3][0] = 0.0;
    _mat[3][1] = 0.0;
    _mat[3][2] = 0.0;
    _mat[3][3] = 1.0;
#endif
}
Quat Matrix4f::getRotate() const
{
    Quat q;

    value_type s;
    value_type tq[4];
    int    i, j;

    // Use tq to store the largest trace
    tq[0] = 1 + _mat[0][0]+_mat[1][1]+_mat[2][2];
    tq[1] = 1 + _mat[0][0]-_mat[1][1]-_mat[2][2];
    tq[2] = 1 - _mat[0][0]+_mat[1][1]-_mat[2][2];
    tq[3] = 1 - _mat[0][0]-_mat[1][1]+_mat[2][2];

    // Find the maximum (could also use stacked if's later)
    j = 0;
    for(i=1;i<4;i++) j = (tq[i]>tq[j])? i : j;

    // check the diagonal
    if (j==0)
    {
        /* perform instant calculation */
        QW = tq[0];
        QX = _mat[1][2]-_mat[2][1]; 
        QY = _mat[2][0]-_mat[0][2]; 
        QZ = _mat[0][1]-_mat[1][0]; 
    }
    else if (j==1)
    {
        QW = _mat[1][2]-_mat[2][1]; 
        QX = tq[1];
        QY = _mat[0][1]+_mat[1][0]; 
        QZ = _mat[2][0]+_mat[0][2]; 
    }
    else if (j==2)
    {
        QW = _mat[2][0]-_mat[0][2]; 
        QX = _mat[0][1]+_mat[1][0]; 
        QY = tq[2];
        QZ = _mat[1][2]+_mat[2][1]; 
    }
    else /* if (j==3) */
    {
        QW = _mat[0][1]-_mat[1][0]; 
        QX = _mat[2][0]+_mat[0][2]; 
        QY = _mat[1][2]+_mat[2][1]; 
        QZ = tq[3];
    }

    s = sqrt(0.25/tq[j]);
    QW *= s;
    QX *= s;
    QY *= s;
    QZ *= s;

    return q;

}
void Matrix4f::makeRotate( const Vec3f& from, const Vec3f& to )
{
    makeIdentity();

    Quat quat;
    quat.makeRotate(from,to);
    setRotate(quat);
}
void Matrix4f::makeRotate( const Vec3d& from, const Vec3d& to )
{
    makeIdentity();

    Quat quat;
    quat.makeRotate(from,to);
    setRotate(quat);
}

void Matrix4f::makeRotate( value_type angle, const Vec3f& axis )
{
    makeIdentity();

    Quat quat;
    quat.makeRotate( angle, axis);
    setRotate(quat);
}
void Matrix4f::makeRotate( value_type angle, const Vec3d& axis )
{
    makeIdentity();

    Quat quat;
    quat.makeRotate( angle, axis);
    setRotate(quat);
}

void Matrix4f::makeRotate( value_type angle, value_type x, value_type y, value_type z ) 
{
    makeIdentity();

    Quat quat;
    quat.makeRotate( angle, x, y, z);
    setRotate(quat);
}

void Matrix4f::makeRotate( const Quat& quat )
{
    makeIdentity();

    setRotate(quat);
}

void Matrix4f::makeRotate( value_type angle1, const Vec3f& axis1, 
                         value_type angle2, const Vec3f& axis2,
                         value_type angle3, const Vec3f& axis3)
{
    makeIdentity();

    Quat quat;
    quat.makeRotate(angle1, axis1, 
                    angle2, axis2,
                    angle3, axis3);
    setRotate(quat);
}

void Matrix4f::makeRotate( value_type angle1, const Vec3d& axis1, 
                         value_type angle2, const Vec3d& axis2,
                         value_type angle3, const Vec3d& axis3)
{
    makeIdentity();

    Quat quat;
    quat.makeRotate(angle1, axis1, 
                    angle2, axis2,
                    angle3, axis3);
    setRotate(quat);
}
