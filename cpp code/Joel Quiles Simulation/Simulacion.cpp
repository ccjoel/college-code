//Simulacion.cpp
#include <iostream>
using namespace std;
#include <cstdlib> 
#include <ctime>
#include "Simulacion.h"
#include "Llamada.cpp"
#include <cassert>
#include "Tiempo.h"

Simulacion::Simulacion(){
   int LPH, Perc, sumaTotal = 0;
   myCallsReceived = 0; myTotalWaitingTime = 0;
   cout << "Entre la razon de llegada(por hora): ";
   cin >> LPH;
   myArrivalRate = LPH / 60.0;
   cout << "Entre personas atendidas en\n";
   for (int i = 0; i < PideQueHay; i++){
      cout << "  <= " << i + 1 << " minutos. ";      cin >> Perc;
      sumaTotal += Perc;
      myServicePercent[i] = sumaTotal;
   }
   myServicePercent[PideQueHay - 1] = 100;
   cout << "Entre el numero de minutos a correr la simulacion: ";
   cin >> myLengthOfSimulation;
  myTimer.set(myLengthOfSimulation);
  long seed = long(time(0));   
  srand(seed);
}

void Simulacion::abreTienda(){
  int busyTimeRemaining = 0;
  while (myTimer.getMinutos() > 0){
    service(busyTimeRemaining);
    checkForNewCall();
    myTimer.bajaTiempo();
  }

  while (!myIncomingCalls.empty()){
    service(busyTimeRemaining);
    myTimer.bajaTiempo();
  }
  display(cout);
}

void Simulacion::display(ostream & out){
   out << "\nNumero de personas servidas:                " << myCallsReceived
       << "\nMedia de tiempo de espera de cada persona:  "
       <<      myTotalWaitingTime / myCallsReceived
       << " minutos" << endl;
}

void Simulacion::service(int & busyTimeRemaining){
   if (busyTimeRemaining > 0)
      busyTimeRemaining--;   
   else
      if (!myIncomingCalls.empty()){
         Llamada nextCall = myIncomingCalls.front();
         myIncomingCalls.dequeue();         
         busyTimeRemaining = nextCall.tiempoEnServir();
         myTotalWaitingTime += 
                nextCall.cuandoLlego() - myTimer.getMinutos();
      }
}

void Simulacion::checkForNewCall(){
   int x = rand() % 100;
   if (x < 100 * myArrivalRate){
      int r = rand() % 100;
      int serviceTime = 0;
      while (r > myServicePercent[serviceTime])
         serviceTime++;
      Llamada newCall(myTimer, serviceTime + 1);
      myIncomingCalls.enqueue(newCall);
      myCallsReceived++;
   }
}
