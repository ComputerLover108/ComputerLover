 #include "zthread/Thread.h"
 #include <iostream>

 using namespace ZThread;

 class aRunnable : public Runnable {

   void run() {

     Thread::sleep(1000);
     std::cout << "Hello from another thread" << std::endl;

   }

 };

 int main() {

   try {
     
     // Implictly constructs a Task
     Thread t(new aRunnable);

   } catch(Synchronization_Exception& e) { 
     std::cerr << e.what() << std::endl; 
   }

   std::cout << "Hello from the main thread" << std::endl;

   // Output:

   // Hello from the main thread
   // Hello from another thread

   return 0;

 }
