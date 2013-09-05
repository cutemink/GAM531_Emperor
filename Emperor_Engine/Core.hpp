#ifndef __I_CORE_HPP__
#define __I_CORE_HPP__

#include "iEngine.hpp"
#include "Settings.hpp"

class Core
   {
   private:
      Emperor::iEngine* gfxEngine;
      Emperor::Settings settings;
   protected:
      Emperor::iWindow* w1;

      Emperor::iNode* n1;
      Emperor::iNode* n2;

      Emperor::iNode* fn1;
      Emperor::iNode* fn2;
   public:
      Core();
      ~Core();
      void init();
      void run();
      void halt();
   };

#endif