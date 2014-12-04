//Simulacion.h

#include <iostream>    
#include <ctime>    
#include "Tiempo.h"
#include "Queue.h" 

const int PideQueHay = 5;
class Simulacion{
public:
  Simulacion();
  void abreTienda();
  void display(ostream & out);
  void service(int & busyTimeRemaining);
  void checkForNewCall();
private:
   int    myLengthOfSimulation;
   double myArrivalRate;
   int    myServicePercent[PideQueHay];
   int    myCallsReceived;
   double myTotalWaitingTime;
   Tiempo myTimer;
   Queue myIncomingCalls;
}; 
