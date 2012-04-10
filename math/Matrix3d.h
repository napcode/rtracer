#ifndef MATH_MATRIX3D_H
#define MATH_MATRIX3D_H

namespace math {

    class Matrix3d
    {
        public:
            typedef double value_type;
            Matrix3d() { makeIdentity(); }
            Matrix3d( const Matrix3d& mat ) { set(mat.ptr()); }
            Matrix3d( value_type a00, value_type a01, value_type a02,
                    value_type a10, value_type a11, value_type a12,
                    value_type a20, value_type a21, value_type a22 )
            {
                set( a00, a01, a02, a10, a11, a12, a20, a21, a22 );
            }
            ~Matrix3d() {}
            value_type& operator()(int row, int col) { return _mat[row][col]; }
            value_type operator()(int row, int col) const { return _mat[row][col]; }

            Matrix3d& operator = (const Matrix3d& rhs)
            {
                if( &rhs == this ) return *this;
                set(rhs.ptr());
                return *this;
            }

            void set(const Matrix3d& rhs) { set(rhs.ptr()); }

            void set(value_type const * const ptr)
            {
                value_type* local_ptr = (value_type*)_mat;
                for(int i=0;i<9;++i) local_ptr[i]=ptr[i];
            }

            void set(value_type a00, value_type a01, value_type a02,
                    value_type a10, value_type a11, value_type a12,
                    value_type a20, value_type a21, value_type a22 )
            {
                _mat[0][0]=a00; _mat[0][1]=a01; _mat[0][2]=a02;
                _mat[1][0]=a10; _mat[1][1]=a11; _mat[1][2]=a12;
                _mat[2][0]=a20; _mat[2][1]=a21; _mat[2][2]=a22;
            }

            value_type* ptr() { return (value_type*)_mat; }
            const value_type* ptr() const { return (const value_type*)_mat; }

            value_type& operator [] (int i) {return ptr()[i];}
            value_type operator [] (int i) const {return ptr()[i];}

            void makeIdentity() { set( 1, 0, 0, 0, 1, 0, 0, 0, 1 ); }

        protected:
            value_type _mat[3][3];
    };
}
#endif
