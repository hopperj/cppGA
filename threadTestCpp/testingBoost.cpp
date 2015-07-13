#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
//#include <boost/thread/mutex.hpp>

//void workerFunc( boost::mutex *m)
void workerFunc( )
{

  //m->lock();
  boost::posix_time::seconds workTime(3);

  std::cout << "Worker: running" << std::endl;

  // Pretend to do something useful...
  boost::this_thread::sleep(workTime);

  std::cout << "Worker: finished" << std::endl;
  //m->unlock();
}

int main(int argc, char* argv[])
{
  //boost::mutex m1;

  std::cout << "main: startup" << std::endl;

  //boost::thread workerThread(workerFunc, &m1);
  boost::thread workerThread(workerFunc);

  std::cout << "main: waiting for thread" << std::endl;

  workerThread.join();

  std::cout << "main: done" << std::endl;

  return 0;
}
