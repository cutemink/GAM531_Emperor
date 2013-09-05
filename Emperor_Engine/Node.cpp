#include "Node.hpp"
#include "Engine.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   void Node<RS>::setPosition(const Vector<float,3>& pos)
      {
      Emperor::setPosition(localT, pos);
      }

   template <RenderSystem RS>
   Vector<float,3> Node<RS>::getPosition() const
      {
      return Emperor::getPosition(localT);
      }

   template <RenderSystem RS>
   void Node<RS>::translate(const Vector<float,3>& p)
      {
      Emperor::translate(localT, p);
      }

   template <RenderSystem RS>
   void Node<RS>::scale(const Vector<float,3>& s)
      {
      Emperor::scale(localT, s);
      }

   template <RenderSystem RS>
   void Node<RS>::rotate(const Vector<float,3>& axis, float radians)
      {
      Emperor::rotate(localT, axis, radians);
      }


   template <RenderSystem RS>
   void Node<RS>::attachTo(iNode* p)
      {

      }

   template <RenderSystem RS>
   void Node<RS>::_removeChild(Node* a)
      {

      }

   template <RenderSystem RS>
   void Node<RS>::_updateAbs(const Matrix<float,4>& a)
      {

      }

   template <RenderSystem RS>
   void Node<RS>::_recalcAbsTransform()
      {
      _tempAbs = localT;
      auto* p = parent;
      while (p)
         {
         _tempAbs = _tempAbs * p->localT;
         p = p->parent;
         }
      }

   template <RenderSystem RS>
   const Matrix<float,4>& Node<RS>::_getAbsTransform() const
      {
      return _tempAbs;
      }

   template <RenderSystem RS>
   void Node<RS>::destroy()
      {
      const auto t = children;
      for(auto i = t.begin(), end = t.end(); i < end; i++)
         (*i)->attachTo(0);
      const auto o = objects;
      for(auto i = o.begin(), end = o.end(); i < end; i++)
         (*i)->attachTo(0);
      if(parent)
         parent->_removeChild(this);
      NodeManager<RS>::getPtr()->removeObject(this);
      delete this;
      }

   template <RenderSystem RS>
   void Node<RS>::_notifyDetach(SceneObject<RS>* a)
      {
      auto i = searchList(objects.begin(), objects.end(), a);
      if(i != objects.end())
         objects.erase(i);
      }

#if (EMP_USE_OPENGL == ON)
   template class Node<RS_GL43>;
#endif

#if (EMP_USE_DIRECTX == ON)
   template class Node<RS_DX11>;
#endif
   }