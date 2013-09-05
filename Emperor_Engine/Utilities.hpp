#ifndef __EMP_UTILITIES_HPP__
#define __EMP_UTILITIES_HPP__

namespace Emperor
   {
   template <class T, unsigned int N>
   class Roster
      {
      private:
         T data[N];
         unsigned int indices[N];

         unsigned int freeIndices;
      protected:
      public:
         Roster();
         virtual ~Roster() {}

         unsigned int push_back(T val);
         void erase(unsigned int index);

         const T* getArray() {return data;}

         T& operator[](unsigned int index);
      };

   template <class T, unsigned int N>
   Roster<T,N>::Roster()
      {
      unsigned int i = N;
      while(i--)
         indices[i] = i;
      freeIndices = N;
      }

   template <class T, unsigned int N>
   unsigned int Roster<T,N>::push_back(T val)
      {
      freeIndices--;
      unsigned int swap = indices[freeIndices];
      indices[freeIndices] = indices[0];
      indices[0] =  swap;

      data[swap] = val;
      return swap;
      }

   template <class T, unsigned int N>
   void Roster<T,N>::erase(unsigned int index)
      {
      for(unsigned int i = 0; i < N; i++)
         {
         if(indices[i] == index)
            {
            indices[i] = indices[freeIndices];
            indices[freeIndices] = index;
            freeIndices++;
            return;
            }
         }
      }

   template <class T, unsigned int N>
   T& Roster<T,N>::operator[](unsigned int index)
      {
      return data[index];
      }


   static inline std::vector<std::string> SplitString(const std::string& s, char d)
      {
      std::stringstream ss(s);
      std::string a;
      std::vector<std::string> out;

      while(std::getline(ss, a, d))
         out.push_back(a);

      return out;
      }

   template <class T, unsigned int N = 8>
   class LinearSet
      {
      private:
         T* data;
         unsigned int size;
         unsigned int aSize;
      protected:
         void growList()
            {
            T* nData = new T[aSize *= 2];
            for(unsigned int i = 0; i<size; i++)
               nData[i] = data[i];
            delete [] data;
            data = nData;
            }

      public:
         LinearSet()
            {
            data = new T[N];
            aSize = N;
            size = 0;
            }

         ~LinearSet()
            {
            delete [] data;
            }

         unsigned int push_back(T d)
            {
            //find if it already exists
            for(unsigned int i = 0; i < size; i++)
               if(data[i] == d)
                  return i;

            //if not found, add
            if(size == aSize)
               growList();

            data[size] = d;
            return size++;
            }

         unsigned int getSize() const 
            {
            return size;
            }

         void getData(T* d) const
            {
            unsigned int i = size;
            while(i--)
               d[i] = data[i];
            }

         T* getDataPtr()
            {
            return data;
            }
      };

   template <class D>
   class Singleton
      {
      private:
         static D* self;
      protected:
      public:
         Singleton() 
            {
            if(!self)
               self = (D*)this;
            else
               throw(0);
            }
         virtual ~Singleton() {self = 0;}

         static D* getPtr() {return self;}
      };

   template <class D> 
   D* Singleton<D>::self = nullptr;

   static void findReplace(std::string& str, const std::string& find, const std::string& replace)
      {
      unsigned int i = 0;
      while((i = str.find(find, i)) != std::string::npos)
         {
         str.replace(i, find.length(), replace);
         i += replace.length();
         }
      }

   /**
    * Integral logarithmic function. Uses base 2. Not very efficient but gets
    * the job done.
    */
   static inline size_t intLog2(size_t val)
      {
      size_t rv = 0;
      while (val > 1)
         {
         val /= 2;
         rv++;
         }
      return rv;
      }
   }

#endif