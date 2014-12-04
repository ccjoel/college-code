#include <iostream>
#include "Timer.h"
#include <cassert>
class Llamada{
private:
   int miTiempoDeLlegada;
   int miTiempoDeServicio;
public:
Llamada::Llamada(){ 
   miTiempoDeLlegada = miTiempoDeServicio = 0; 
}
Llamada::Llamada(const Tiempo & t, int serviceTime){ 
   miTiempoDeLlegada = t.getMinutos();
   miTiempoDeServicio = serviceTime;
}
int Llamada::cuandoLlego() const{
   return miTiempoDeLlegada;
}
int Llamada::tiempoEnServir() const{
   return miTiempoDeServicio;
}
void Llamada::display(ostream & out) const{
  out << "Tiempo de llegada:    " << miTiempoDeLlegada << endl
	      << "Tiempo en servir:    " << miTiempoDeServicio << endl;
}
};

ostream & operator<<(ostream & out, const Llamada & unaLlamada){
   unaLlamada.display(out);
   return out;
}
