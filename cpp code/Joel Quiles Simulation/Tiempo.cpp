//Tiempo.cpp
#include <cassert>
using namespace std;
#include "Tiempo.h"
class Tiempo{
   private:
   int misMinutos;
 public:
Tiempo::Tiempo(int algunTiempo){
   assert(algunTiempo >= 0);
   misMinutos = algunTiempo;
}
void Tiempo::set(int minutos){
   assert(minutos >= 0);
   misMinutos = minutos;
}
int Tiempo::getMinutos() const{
   return misMinutos;
}
void Tiempo::bajaTiempo(){
   misMinutos--;
}
}; 
