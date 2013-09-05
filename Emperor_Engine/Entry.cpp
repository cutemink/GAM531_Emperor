#include "Common.hpp"
#include "Core.hpp"

int main(int argc, const char* argv[])
   {
   try
      {
      Core c;
      c.init();
      c.run(); 
      }
   catch(Emperor::Exception& e)
      {
      LOG(e.what());
      LOG("Fatal exception has been thrown, Engine will now shutdown...");
      char i;
      std::cin >> i;
      }
   return 0;
   }