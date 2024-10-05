#include "nodolistadoble.h"

nodoListadoble::nodoListadoble(const std::string& correo, const std::string& contenido, const std::string& fecha,
                               const std::string& hora, const std::string& imagen)
                            : correo(correo), contenido(contenido), fecha(fecha), hora(hora),
                              imagen(imagen), comentarios(5), siguiente(nullptr), anterior(nullptr) {}
