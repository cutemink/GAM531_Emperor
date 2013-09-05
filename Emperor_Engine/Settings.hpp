#ifndef __EMP_SETTINGS_HPP__
#define __EMP_SETTINGS_HPP__

#include "Common.hpp"

namespace Emperor
   {
   struct Settings
      {
      Vector<int,2> resolution;
      bool fullscreen;

      //backed in defaults
      Settings() : resolution(Coord(800,600)), fullscreen(false) {}
      ~Settings() {}

      bool loadFromFile(const String&);
      bool saveToFile(const String&);
      };
   }

#endif