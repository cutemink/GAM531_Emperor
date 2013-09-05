#ifndef __EMP_I_NODE_HPP__
#define __EMP_I_NODE_HPP__

#include "Common.hpp"
#include "Types.hpp"

namespace Emperor
   {

   class iNode
      {
      private:
      protected:
         iNode() {}
         virtual ~iNode() {}
      public:
         virtual void destroy() = 0;

         virtual void setPosition(const Vector<float,3>&) = 0;
         virtual Vector<float,3> getPosition() const = 0;
         virtual void translate(const Vector<float,3>&) = 0;

         virtual void scale(const Vector<float,3>&) = 0;

         virtual void rotate(const Vector<float,3>& axis, float angle) = 0;

         virtual const Matrix<float,4>& getLocalTransform() const = 0;

         virtual void attachTo(iNode* node) = 0;

         // Typically a frame old unless _recalcAbsTransform was called immediately beforehand.
         virtual const Matrix<float,4>& _getAbsTransform() const = 0;

         // Relatively slow. Try to avoid.
         virtual void _recalcAbsTransform() = 0;
      };

   }

#endif