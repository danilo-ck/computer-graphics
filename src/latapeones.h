#ifndef LATAPEONES_H
#define LATAPEONES_H

#include "grafo-escena.h"
#include "malla-revol.h"

class LataPeones : public NodoGrafoEscena {
    public:
        LataPeones();
};

class Lata : public NodoGrafoEscena {
    public:
        Lata(const std::string & nombre_arch);
};

class Peon : public MallaRevolPLY{
    public:
        Peon(int nperfiles);
};

#endif