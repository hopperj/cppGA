

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>



using namespace std;

void foo()
{
  // do stuff...
}

void bar(double *x)
{
  // do stuff...
  cout << "testing: " << *x << endl;
  *x = 22.2;
  cout << "testing: " << *x << endl;
}







int main(){
  vector< double > list = {0.1, 0.2, 0.3};
  vector< thread > threads = vector< thread >(3);
  thread t;
  for( int i=0; i<list.size(); i++){

    threads[i] = thread(bar, &list[i]);
  }
  //thread first (foo);     // spawn new thread that calls foo()
  //thread second (bar,&list[1]);  // spawn new thread that calls bar(0)

  //cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  //first.join();                // pauses until first finishes
  //second.join();               // pauses until second finishes
  for( int i=0; i<list.size(); i++){
    threads[i].join();
  }
  for( int i=0; i<list.size(); i++){
    cout << list[i] << endl;
  }
  cout << "foo and bar completed.\n";

}
