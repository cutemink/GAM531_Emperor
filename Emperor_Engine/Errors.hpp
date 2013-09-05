#ifndef __EMPEROR_ERROR_HPP__
#define __EMPEROR_ERROR_HPP__

#include <exception>
#include <string>

//derives exceptions from base exception
#define EMP_DEXP(n) class n : public Exception {public:\
   n(const char* m) : Exception(m) {}; n(const std::string& m) : Exception(m) {} };

namespace Emperor
   {

   class Exception : public std::exception
      {
      private:
         char msg[1024];
         Exception();
      protected:
      public:
         Exception(const char* message) : exception(msg) {strcpy_s(msg, message);}
         Exception(const std::string& message) : exception(msg) {strcpy_s(msg, message.c_str());}
         const char* what() {return msg;}
      };

   EMP_DEXP(FatalException);
   EMP_DEXP(DeviceFailureException);
   EMP_DEXP(DeviceInitFailureException);
   EMP_DEXP(ResourceLoadFailException);
   EMP_DEXP(NotImplementedException);

#undef EMP_DEXP

   }

#endif
