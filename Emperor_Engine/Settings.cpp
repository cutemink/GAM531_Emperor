#include "Settings.hpp"

namespace Emperor
   {
   static void _parseFile(const ArrayList<String>& c, Settings& s)
      {
      for(auto i = c.begin(); i < c.end(); ++i)
         {
         auto res = SplitString(*i, '=');
         if(res.size() < 2) continue; //skip malformed
         if(res[0] == "resolution")
            {
            auto r = SplitString(res[1], 'x');
            if(r.size() < 2) continue; //skip malformed
            int x = atoi(r[0].c_str());
            int y = atoi(r[1].c_str());
            if(x & y)
               s.resolution = Coord(x, y);
            }
         else if(res[0] == "fullscreen")
            {
            if(res[1] == "true")
               s.fullscreen = true;
            else if(res[1] == "false")
               s.fullscreen = false;
            }
         }
      }

   bool Settings::loadFromFile(const String& filename)
      {
      return false;
      }

   bool Settings::saveToFile(const String& filename)
      {
      return false;
      }
   }