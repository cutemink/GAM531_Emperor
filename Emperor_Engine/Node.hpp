#ifndef __EMP_NODE_HPP__
#define __EMP_NODE_HPP__

#include "Common.hpp"
#include "SceneObject.hpp"
#include "iNode.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   class Node : public iNode
      {
      private:
         Matrix<float,4> localT;
         Matrix<float,4> _tempAbs;

         uint32 nIndex;

         Node* parent;
         ArrayList<Node*> children;
         ArrayList<SceneObject<RS>*> objects;
      protected:
         ~Node() {}
      public:
         Node(uint32 i) : parent(0), _tempAbs(Matrix4(0)), nIndex(i)
            {

            }

         void destroy();

         void setPosition(const Vector<float,3>&);
         Vector<float,3> getPosition() const;
         void translate(const Vector<float,3>&);

         void scale(const Vector<float,3>&);

         void rotate(const Vector<float,3>& axis, float angle);

         const Matrix<float,4>& getLocalTransform() const {return localT;}

         void attachTo(iNode* p);

         void _addChild(Node* a) {}
         void _removeChild(Node*);

         uint32 getIndex() {return nIndex;}

         inline Matrix<float,4> _getAbs() const {return _tempAbs;}
         inline void _setAbs(const Matrix<float,4>& a) {_tempAbs = a;}
         void _updateAbs(const Matrix<float,4>&);

         const Matrix<float,4>& _getAbsTransform() const;

         void _recalcAbsTransform();

         void _notifyAttach(SceneObject<RS>* a) {}
         void _notifyDetach(SceneObject<RS>*);
      };
   }

#endif
