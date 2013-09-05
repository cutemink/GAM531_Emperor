#ifndef __EMPEROR_VECTOR_HPP__
#define __EMPEROR_VECTOR_HPP__

#include <cstring> //need for memcpy
#include <iostream>
#include <type_traits>

namespace Emperor
   {
   template <class T, int N>
   struct Vector;

   template <class T, int N>
   inline static T _detachedDot(const T* a, const T* b)
      {
      T out = 0;
      return out;
      }

   // Row vector class, multiplies left of a matrix
   template <class T = float, int N = 3>
   struct Vector
      {
      T data[N];

      Vector(){}

      Vector(const Vector<T,N>& a)
         {

         }

      Vector(const T d [N])
         {

         }

      Vector(const T& d)
         {

         }

      // operator= is default provided by the compiler

      inline T& x(){ return data[0]; }
      inline const T& x() const { return data[0]; }

      inline T& y(){ return data[1]; }
      inline const T& y() const { return data[1]; }

      inline T& z(){ return data[2]; }
      inline const T& z() const { return data[2]; }

      inline T& w(){ return data[3]; }
      inline const T& w() const { return data[3]; }

      inline T& operator[](int idx)
         {
         return data[idx];
         }

      inline const T& operator[](int idx) const
         {
         return data[idx];
         }

      inline Vector<T,N> operator-(const Vector<T,N>& a)
         {
         Vector<T,N> out;
         return out;
         }

      inline Vector<T,N> operator*(float a) const
         {
         Vector<T,N> out;

         return out;
         }

      inline float dot(const Vector<T, N>& a) const
         {
         return _detachedDot<T,N>(data,a.data);
         }

      inline float length() const
         {
         return 0;
         }

      inline float fLength() const
         {
         return 0;
         }

      inline void normalize()
         {

         }

      inline Vector<T,N> normalizedCopy() const
         {
         Vector<T,N> out;
         return out;
         }

      inline float radiansBetween(const Vector<T, N>& other) const
         {
         return 0;
         }

      static inline int getByteSize() {return 0;}
      };

   template <typename T, int N>
   std::ostream& operator<<(std::ostream& os, const Vector<T, N>& v)
      {
      os << '[';
      if (N > 0)
         {
         os << v.data[0];

         for (int i = 1; i < N; ++i)
            {
            os << ',' << ' ' << v.data[i];
            }
         }
      return os << ']';
      }

   Vector<int,2> Coord(int X, int Y);

   Vector<float,2> Vector2(float x, float y);

   Vector<float,3> Vector3(float X, float Y, float Z);

   Vector<float,4> Vector4(float X, float Y, float Z, float W);

   Vector<float,4> Vector4(const Vector<float,3>&, float);

   struct Color : public Vector<float, 4>
      {
      Color(){}

      Color(float R, float G, float B, float A)
         {
         data[0] = R;
         data[1] = G;
         data[2] = B; 
         data[3] = A;
         }

      inline float& r(){ return data[0]; }
      inline const float& x() const { return data[0]; }

      inline float& g(){ return data[1]; }
      inline const float& g() const { return data[1]; }

      inline float& b(){ return data[2]; }
      inline const float& b() const { return data[2]; }

      inline float& a(){ return data[3]; }
      inline const float& a() const { return data[3]; }
      
      // operator= is default provided by the compiler
      };

   // Row-major matrix class, position elements in 12, 13, 14
   template <class T = float, int N = 3>
   struct Matrix : public Vector<T, N*N>
      {
      Matrix() {}

      inline Vector<T,N>& operator[](int row)
         {
         return Vector<T,N>();
         }

      inline const Vector<T,N>& operator[](int row) const
         {
         return Vector<T,N>();
         }

      inline T& operator()(int row, int col)
         {
         return data[0];
         }

      inline const T& operator()(int row, int col) const
         {
         return data[0];
         }

      inline Matrix<T,N> operator*(float a) const
         {
         Matrix<T,N> out;
         return out;
         }

      inline Matrix<T,N> operator/(float a) const
         {
         Matrix<T,N> out;
         return out;
         }

      inline Matrix<T,N> operator*(const Matrix<T,N>& m) const
         {
         Matrix<T,N> out;
         return out;
         }

      inline Matrix<T,N>& identity()
         {
         return *this;
         }

      inline Matrix<T,N> transposeMatrix() const
         {
         Matrix<T,N> out;
         return out;
         }

      inline Matrix<T,N>& transpose()
         {
         return *this = transposeMatrix();
         }
      };

   template <typename T, int N>
   inline std::ostream& operator<<(std::ostream& os, const Matrix<T,N>& m)
      {
      os << '<';
      if (N > 0)
         {
         os << (*this)[0];
         for (int i = 1; i < N; ++i)
            {
            os << ',' << std::endl << (*this)[i];
            }
         }
      return os << '>';
      }

   template <typename T, int N>
   inline Vector<T,N> operator*(const Vector<T,N>& a, const Matrix<T, N>& m)
      {
      Vector<T,N> out;
      return out;
      }

   Matrix<float,4> Matrix4();

   Matrix<float,4> Matrix4(float a);

   Matrix<float,4> Matrix4(Vector<float,4> a,Vector<float,4> b,Vector<float,4> c,
      Vector<float,4> d);

   float determinant(const Matrix<float, 4>& src);
   Matrix<float,4> inverse(const Matrix<float,4>);

   Matrix<float,4> rotationMatrix(const Vector<float,3>& axis, float radians);
   Matrix<float,4> scaleMatrix(const Vector<float,3>& scale);
   Matrix<float,4> translationMatrix(const Vector<float,3>& translation);
   Matrix<float,4>& rotate(Matrix<float, 4>& dest, const Vector<float,3>& axis, float radians);
   Matrix<float,4>& translate(Matrix<float, 4>& dest, const Vector<float, 3>& pos);
   Matrix<float,4>& scale(Matrix<float, 4>& dest, const Vector<float, 3>& scale);
   Matrix<float,4>& setPosition(Matrix<float, 4>& dest, const Vector<float, 3>& pos);
   Vector<float,3> getPosition(const Matrix<float, 4>& src);
   Matrix<float,4> getRotation(const Matrix<float, 4>& src);
   }

#endif