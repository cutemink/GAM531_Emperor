#ifndef __EMP_BASE_MANAGER_HPP__
#define __EMP_BASE_MANAGER_HPP__

#include "Common.hpp"
#include "Buffers.hpp"

namespace Emperor
   {
   template <class T>
   class BaseManager
      {
      private:
      protected:
         ArrayList<T*> objects;
         ArrayList<T*> activeObjects;
      public:
         BaseManager() {}
         virtual ~BaseManager()
            {

            }

         T* createObject()
            {
            return new T();
            }

         void removeObject(T* o)
            {
            }

         void activateObject(T* o)
            {
            }

         void deactivateObject(T* o)
            {
            }
      };

   template <class T>
   class IterativeManager : public BaseManager<T>
      {
      private:
      protected:
         typename ArrayList<T*>::iterator it;

      public:
         IterativeManager() {}
         virtual ~IterativeManager() {}

         void prepareLoop() {it = activeObjects.begin();}
         virtual bool bindNext() = 0;

         T* getCurrent() {return *(it - 1);}
      };
   }

#endif