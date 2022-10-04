#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <mutex>

std::mutex mtx;
std::mutex mtx2;

int vg;
void pause_thread(int n)
{
  //int cont = 1;
  mtx.lock();
  vg = vg+1;
  
  if (n == vg)
  {
     std::cout << "Thread with ID: " << n << " VG: " << vg << "\n";
  }
  mtx.unlock();
}

int main()
{
  vg = 0;
  for(int i=1; i<100 ; i++){
  std::thread (pause_thread,i).detach();
  }
  
  std::this_thread::sleep_for (std::chrono::seconds(100));
  return 0;
}

/*
Spawning and detaching 3 threads...
End of threads
Thread with ID: 7
Thread with ID: 8
Thread with ID: 9
Thread with ID: 6
Thread with ID: 5
Thread with ID: 4
Thread with ID: 3
Thread with ID: 2
Thread with ID: 1
*/
