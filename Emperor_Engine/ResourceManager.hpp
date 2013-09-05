#ifndef __EMP_RESOURCE_MANAGER_HPP__
#define __EMP_RESOURCE_MANAGER_HPP__

#include "Common.hpp"

namespace Emperor
   {
   template <class T>
   class ResourceManager
      {
      private:
      protected:
         HashMap<String, T*> resources;

         virtual T* createResource(const String& r) = 0;
      public:
         ResourceManager() {}
         virtual ~ResourceManager()
            {
            auto t = resources;
            for(auto i = t.begin(), end = t.end(); i != end; i++)
               {
               (*i).second->destroy();
               }
            }

         T* newResource(const String& r)
            {
            T* out = 0;
            if(resources.find(r) == resources.end())
               {
               out = new T();
               resources[r] = out;
               }
            else
               LOG("A resource with that name already exists, aborting...");
            return out;
            }

         T* getResource(const String& resource)
            {
            T* out = 0;
            auto i = resources.find(resource);
            if(i != resources.end())
               out = (*i).second;
            else
               out = createResource(resource);
            return out;
            }

         void removeResource(T* a)
            {
            auto i = resources.begin(), end = resources.end();
            for(; i != end; i++)
               if((*i).second == a)
                  break;
            if(i != end)
               resources.erase(i);
            }

         void preloadResources(const ArrayList<String>& s)
            {
            auto end = s.end();
            for(auto i = s.begin(); i<end; i++)
               getResource(*i);
            }
      };
   }
#endif