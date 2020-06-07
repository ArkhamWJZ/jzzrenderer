//
// Created by 万健洲 on 2020/6/4.
//

#ifndef JZZRENDERER_VECTOR_H
#define JZZRENDERER_VECTOR_H

#include <bits/stdc++.h>

template<int DimCols,int DimRows,typename T> class mat;

template <int Dim, typename T> struct vec {
    private:
        T data[Dim];
    public:
        vec() { for (int i=Dim; i--; data[i] = T()); }
        T& operator[](const int i){return data[i];}
        const T& operator[](const int i) const {return data[i];}
};

typedef vec<2,  float> vec2f;
typedef vec<2,  int>   vec2i;
typedef vec<3,  float> vec3f;
typedef vec<3,  int>   vec3i;
typedef vec<4,  float> vec4f;
typedef mat<4,4,float> matrix;

/*******************************************************************************/
template <typename T> struct vec<2,T> {
    T x,y;
    vec() : x(T()), y(T()) {}
    vec(T X, T Y) : x(X), y(Y) {}
    T& operator[](const int i){ return i <= 0 ? x : y; }
    const T& operator[](const int i) const {return i <= 0 ? x : y; }
    float norm() {return std::sqrt(x*x + y*y);}
};

/*******************************************************************************/
template <typename T> struct vec<3,T> {
    T x,y,z;
    vec() : x(T()), y(T()), z(T()) {}
    vec(T X, T Y, T Z) : x(X), y(Y), z(Z) {}
    T& operator[](const int i){ return i <= 0 ? x : (i==1 ? y : z); }
    const T& operator[](const int i) const {return i <= 0 ? x : (i==1 ? y : z); }
    float norm() { return std::sqrt(x*x + y*y + z*z); }
    vec<3,T> & normalize(){
        *this = (*this) / norm();
        return *this;
    }
};

/*******************************************************************************/
template<int Dim,typename T> T operator*(const vec<Dim,T>& a, const vec<Dim,T>& b) {
    T c = T();
    for (int i=Dim; i--; c += a[i] * b[i]);
    return c;
}


template<int Dim,typename T>vec<Dim,T> operator+(vec<Dim,T> a, const vec<Dim,T>& b) {
    for (int i=Dim; i--; a[i]+=b[i]);
    return a;
}

template<int Dim,typename T>vec<Dim,T> operator-(vec<Dim,T> a, const vec<Dim,T>& b) {
    for (int i=Dim; i--; a[i] -= b[i]);
    return a;
}

template<int Dim,typename T,typename U> vec<Dim,T> operator*(vec<Dim,T> a, const U& b) {
    for (int i=Dim; i--; a[i] *= b);
    return a;
}

template<int Dim,typename T,typename U> vec<Dim,T> operator/(vec<Dim,T> a, const U& b) {
    for (int i=Dim; i--; a[i] /= b);
    return a;
}

template<int Len,int Dim,typename T> vec<Len,T> embed(const vec<Dim,T> &v, T fill=1) {
    vec<Len,T> c;
    for (int i=Len; i--; c[i] = (i < Dim ? v[i]:fill));
    return c;
}

template <typename T> vec<3,T> cross(vec<3,T> v1, vec<3,T> v2) {
    return vec<3,T>(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}
template <typename T> T cross2D(vec<2,T> v1, vec<2,T> v2) {
    return v1.x*v2.y - v1.y*v2.x;
}
template <int Dim, typename T> std::ostream& operator<<(std::ostream& out, vec<Dim,T>& v) {
    for(unsigned int i=0; i<Dim; i++) {
        out << v[i] << " " ;
    }
    return out ;
}

/*******************************************************************************/
template<int DimRows,int DimCols,typename T> class mat {
    vec<DimCols,T> rows[DimRows];
public:
    mat() {}
    vec<DimCols,T>& operator[] (const int index) {return rows[index];}
    const vec<DimCols,T>& operator[] (const int index) const {return rows[index];}
    vec<DimRows,T> col(const int index) const {
        vec<DimRows,T> c;
        for (int i = DimRows; i--; c[i] = rows[i][index]);
        return c;
    }
    void set_col(int index, vec<DimRows,T> v) {
        for (int i = DimRows; i--; rows[i][index] = v[i]);
    }
    static mat<DimRows,DimCols,T> identity() {
        mat<DimRows,DimCols,T> c;
        for (int i=DimRows; i--; )
            for (int j = DimCols;j--; c[i][j] = (i==j));
        return c;
    }
    T det() const {
        T c = 0;
        c = (*this)[0][0]*(*this)[1][1]*(*this)[2][2] + (*this)[0][1]*(*this)[1][2]*(*this)[2][0] +
            (*this)[1][0]*(*this)[2][1]*(*this)[0][2] - (*this)[0][2]*(*this)[1][1]*(*this)[2][0] -
            (*this)[1][2]*(*this)[2][1]*(*this)[0][0] - (*this)[0][1]*(*this)[1][0]*(*this)[2][2];
        return c;
    }
    mat<DimRows-1,DimCols-1,T> get_minor(int row, int col) const {
        mat<DimRows-1,DimCols-1,T> c;
        for (int i = DimRows-1; i--; )
            for (int j = DimCols-1;j--; c[i][j] = rows[i < row ? i:i+1][j < col ? j:j+1]);
        return c;
    }
    T cofactor(int row, int col) const {
        return get_minor(row,col).det() * ((row+col)%2 ? -1 : 1);
    }
    mat<DimRows,DimCols,T> adjugate() const {
        mat<DimRows,DimCols,T> c;
        for (int i = DimRows; i--; )
            for (int j = DimCols; j--; c[j][i] = cofactor(i,j));
        return c;
    }
    mat<DimRows,DimCols,T> invert() {
        mat<DimRows,DimCols,T> c = adjugate();
        T tmp = c[0]*rows[0];
        return c/tmp;
    }
    mat<DimCols,DimRows,T> transpose() {
        mat<DimCols,DimRows,T> c;
        for (int i = DimCols; i--; c[i] = this->col(i));
        return c;
    }
};

/*******************************************************************************/
template<int DimRows,int DimCols,typename T> vec<DimRows,T> operator*(const mat<DimRows,DimCols,T>& a, const vec<DimCols,T>& b) {
    vec<DimRows,T> c;
    for (int i = DimRows; i--; c[i] = a[i]*b);
    return c;
}

template<int R1,int C1,int C2,typename T>mat<R1,C2,T> operator*(const mat<R1,C1,T>& a, const mat<C1,C2,T>& b) {
    mat<R1,C2,T> result;
    for (int i = R1; i--; )
        for (int j = C2; j--; result[i][j] = a[i]*b.col(j));
    return result;
}
template<int R1,int C1,int C2,typename T>mat<R1,C2,T> operator+(const mat<R1,C1,T>& a, const mat<C1,C2,T>& b) {
    mat<R1,C2,T> result;
    for (int i = R1; i--; )
        for (int j = C2; j--; result[i][j] = a[i][j]+b[i][j]);
    return result;
}
template<int R1,int C1,int C2,typename T>mat<R1,C2,T> operator-(const mat<R1,C1,T>& a, const mat<C1,C2,T>& b) {
    mat<R1,C2,T> result;
    for (int i = R1; i--; )
        for (int j = C2; j--; result[i][j] = a[i][j]-b[i][j]);
    return result;
}
template<int DimRows,int DimCols,typename T>mat<DimCols,DimRows,T> operator/(mat<DimRows,DimCols,T> a, const T& b) {
    for (int i = DimRows; i--; a[i]=a[i]/b);
    return a;
}

template <int DimRows,int DimCols,class T> std::ostream& operator<<(std::ostream& out, mat<DimRows,DimCols,T>& m) {
    for (int i = 0; i < DimRows; i++) out << m[i] << std::endl;
    return out;
}

#endif //JZZRENDERER_VECTOR_H
