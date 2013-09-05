#include "Vector.hpp"

namespace Emperor
   {
   Vector<int,2> Coord(int X, int Y)
      {
      Vector<int,2> out;
      out.x() = X;
      out.y() = Y;
      return out;
      }

   Vector<float,2> Vector2(float x, float y)
      {
      Vector<float,2> out;
      out.x() = x;
      out.y() = y;
      return out;
      }

   Vector<float,3> Vector3(float X, float Y, float Z)
      {
      Vector<float, 3> out;
      out.x() = X;
      out.y() = Y;
      out.z() = Z;
      return out;
      }

   Vector<float,4> Vector4(float X, float Y, float Z, float W)
      {
      Vector<float, 4> out;
      out.x() = X;
      out.y() = Y;
      out.z() = Z;
      out.w() = W;
      return out;
      }

   Vector<float,4> Vector4(const Vector<float, 3>& a, float b)
      {
      Vector<float,4> out;
      out.x() = a.x();
      out.y() = a.y();
      out.z() = a.z();
      out.w() = b;
      return out;
      }

   Matrix<float,4> Matrix4() 
      {
      return Matrix<float,4>();
      }

   Matrix<float,4> Matrix4(float a)
      {
      int i = 16;
      Matrix<float,4> out;
      while(i--)
         out.data[i] = a;
      return out;
      }

   Matrix<float,4> Matrix4(Vector<float,4> a,Vector<float,4> b,Vector<float,4> c,Vector<float,4> d)
      {
      Matrix<float,4> out;
      out[0] = a;
      out[1] = b;
      out[2] = c;
      out[3] = d;
      return out;
      }

   float determinant(const Matrix<float, 4>& m)
      {
      float value;
      value =
         m(0,3)*m(1,2)*m(2,1)*m(3,0) - m(0,2)*m(1,3)*m(2,1)*m(3,0) - m(0,3)*m(1,1)*m(2,2)*m(3,0) + m(0,1)*m(1,3)*m(2,2)*m(3,0)+
         m(0,2)*m(1,1)*m(2,3)*m(3,0) - m(0,1)*m(1,2)*m(2,3)*m(3,0) - m(0,3)*m(1,2)*m(2,0)*m(3,1) + m(0,2)*m(1,3)*m(2,0)*m(3,1)+
         m(0,3)*m(1,0)*m(2,2)*m(3,1) - m(0,0)*m(1,3)*m(2,2)*m(3,1) - m(0,2)*m(1,0)*m(2,3)*m(3,1) + m(0,0)*m(1,2)*m(2,3)*m(3,1)+
         m(0,3)*m(1,1)*m(2,0)*m(3,2) - m(0,1)*m(1,3)*m(2,0)*m(3,2) - m(0,3)*m(1,0)*m(2,1)*m(3,2) + m(0,0)*m(1,3)*m(2,1)*m(3,2)+
         m(0,1)*m(1,0)*m(2,3)*m(3,2) - m(0,0)*m(1,1)*m(2,3)*m(3,2) - m(0,2)*m(1,1)*m(2,0)*m(3,3) + m(0,1)*m(1,2)*m(2,0)*m(3,3)+
         m(0,2)*m(1,0)*m(2,1)*m(3,3) - m(0,0)*m(1,2)*m(2,1)*m(3,3) - m(0,1)*m(1,0)*m(2,2)*m(3,3) + m(0,0)*m(1,1)*m(2,2)*m(3,3);
      return value;
      }

   Matrix<float,4> inverse(const Matrix<float,4> m)
      {
      Matrix<float,4> out;
      out.data[0] = m(1,2)*m(2,3)*m(3,1) - m(1,3)*m(2,2)*m(3,1) + m(1,3)*m(2,1)*m(3,2) - m(1,1)*m(2,3)*m(3,2) - m(1,2)*m(2,1)*m(3,3) + m(1,1)*m(2,2)*m(3,3);
      out.data[1] = m(0,3)*m(2,2)*m(3,1) - m(0,2)*m(2,3)*m(3,1) - m(0,3)*m(2,1)*m(3,2) + m(0,1)*m(2,3)*m(3,2) + m(0,2)*m(2,1)*m(3,3) - m(0,1)*m(2,2)*m(3,3);
      out.data[2] = m(0,2)*m(1,3)*m(3,1) - m(0,3)*m(1,2)*m(3,1) + m(0,3)*m(1,1)*m(3,2) - m(0,1)*m(1,3)*m(3,2) - m(0,2)*m(1,1)*m(3,3) + m(0,1)*m(1,2)*m(3,3);
      out.data[3] = m(0,3)*m(1,2)*m(2,1) - m(0,2)*m(1,3)*m(2,1) - m(0,3)*m(1,1)*m(2,2) + m(0,1)*m(1,3)*m(2,2) + m(0,2)*m(1,1)*m(2,3) - m(0,1)*m(1,2)*m(2,3);
      out.data[4] = m(1,3)*m(2,2)*m(3,0) - m(1,2)*m(2,3)*m(3,0) - m(1,3)*m(2,0)*m(3,2) + m(1,0)*m(2,3)*m(3,2) + m(1,2)*m(2,0)*m(3,3) - m(1,0)*m(2,2)*m(3,3);
      out.data[5] = m(0,2)*m(2,3)*m(3,0) - m(0,3)*m(2,2)*m(3,0) + m(0,3)*m(2,0)*m(3,2) - m(0,0)*m(2,3)*m(3,2) - m(0,2)*m(2,0)*m(3,3) + m(0,0)*m(2,2)*m(3,3);
      out.data[6] = m(0,3)*m(1,2)*m(3,0) - m(0,2)*m(1,3)*m(3,0) - m(0,3)*m(1,0)*m(3,2) + m(0,0)*m(1,3)*m(3,2) + m(0,2)*m(1,0)*m(3,3) - m(0,0)*m(1,2)*m(3,3);
      out.data[7] = m(0,2)*m(1,3)*m(2,0) - m(0,3)*m(1,2)*m(2,0) + m(0,3)*m(1,0)*m(2,2) - m(0,0)*m(1,3)*m(2,2) - m(0,2)*m(1,0)*m(2,3) + m(0,0)*m(1,2)*m(2,3);
      out.data[8] = m(1,1)*m(2,3)*m(3,0) - m(1,3)*m(2,1)*m(3,0) + m(1,3)*m(2,0)*m(3,1) - m(1,0)*m(2,3)*m(3,1) - m(1,1)*m(2,0)*m(3,3) + m(1,0)*m(2,1)*m(3,3);
      out.data[9] = m(0,3)*m(2,1)*m(3,0) - m(0,1)*m(2,3)*m(3,0) - m(0,3)*m(2,0)*m(3,1) + m(0,0)*m(2,3)*m(3,1) + m(0,1)*m(2,0)*m(3,3) - m(0,0)*m(2,1)*m(3,3);
      out.data[10] = m(0,1)*m(1,3)*m(3,0) - m(0,3)*m(1,1)*m(3,0) + m(0,3)*m(1,0)*m(3,1) - m(0,0)*m(1,3)*m(3,1) - m(0,1)*m(1,0)*m(3,3) + m(0,0)*m(1,1)*m(3,3);
      out.data[11] = m(0,3)*m(1,1)*m(2,0) - m(0,1)*m(1,3)*m(2,0) - m(0,3)*m(1,0)*m(2,1) + m(0,0)*m(1,3)*m(2,1) + m(0,1)*m(1,0)*m(2,3) - m(0,0)*m(1,1)*m(2,3);
      out.data[12] = m(1,2)*m(2,1)*m(3,0) - m(1,1)*m(2,2)*m(3,0) - m(1,2)*m(2,0)*m(3,1) + m(1,0)*m(2,2)*m(3,1) + m(1,1)*m(2,0)*m(3,2) - m(1,0)*m(2,1)*m(3,2);
      out.data[13] = m(0,1)*m(2,2)*m(3,0) - m(0,2)*m(2,1)*m(3,0) + m(0,2)*m(2,0)*m(3,1) - m(0,0)*m(2,2)*m(3,1) - m(0,1)*m(2,0)*m(3,2) + m(0,0)*m(2,1)*m(3,2);
      out.data[14] = m(0,2)*m(1,1)*m(3,0) - m(0,1)*m(1,2)*m(3,0) - m(0,2)*m(1,0)*m(3,1) + m(0,0)*m(1,2)*m(3,1) + m(0,1)*m(1,0)*m(3,2) - m(0,0)*m(1,1)*m(3,2);
      out.data[15] = m(0,1)*m(1,2)*m(2,0) - m(0,2)*m(1,1)*m(2,0) + m(0,2)*m(1,0)*m(2,1) - m(0,0)*m(1,2)*m(2,1) - m(0,1)*m(1,0)*m(2,2) + m(0,0)*m(1,1)*m(2,2);
      out = out / determinant(m);
      return out;
      }

   Matrix<float,4> rotationMatrix(const Vector<float,3>& axis, float radians)
      {
      float c = cosf(radians), s = sinf(radians), t = 1.0f - c;

      auto a = axis.normalizedCopy();
      Matrix<float,4> n;
      n(0,0) = t*a.x()*a.x() + c;       n(0,1) = t*a.x()*a.y() + a.z()*s; n(0,2) = t*a.x()*a.z() - a.y()*s; n(0,3) = 0;
      n(1,0) = t*a.x()*a.y() - a.z()*s; n(1,1) = t*a.y()*a.y() + c;       n(1,2) = t*a.y()*a.z() + a.x()*s; n(1,3) = 0;
      n(2,0) = t*a.x()*a.z() + a.y()*s; n(2,1) = t*a.y()*a.z() - a.x()*s; n(2,2) = t*a.z()*a.z() + c;       n(2,3) = 0;
      n(3,0) = 0;                       n(3,1) = 0;                       n(3,2) = 0;                       n(3,3) = 1;
      return n;
      }

   Matrix<float,4> scaleMatrix(const Vector<float,3>& scale)
      {
      Matrix<float,4> m;
      return m;
      }

   Matrix<float,4> translationMatrix(const Vector<float,3>& translation)
      {
      Matrix<float,4> m;
      m.identity();
      return m;
      }

   Matrix<float,4>& rotate(Matrix<float, 4>& dest, const Vector<float,3>& axis, float radians)
      {
      return dest;
      }

   Matrix<float,4>& translate(Matrix<float, 4>& dest, const Vector<float, 3>& pos)
      {
      return dest;
      }

   Matrix<float,4>& scale(Matrix<float, 4>& dest, const Vector<float, 3>& scale)
      {
      return dest;
      }

   Matrix<float,4>& setPosition(Matrix<float, 4>& dest, const Vector<float, 3>& pos)
      {
      return dest;
      }

   Vector<float, 3> getPosition(const Matrix<float, 4>& src)
      {
      return Vector<float, 3>(src.data + 12);
      }
   }
