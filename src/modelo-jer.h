#ifndef MODELO_JER_H
#define MODELO_JER_H

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"

using namespace std;
using namespace glm;

class Esferas : public MallaRevol {
    public:
        Esferas(const int num_verts_per, const unsigned nperfiles, float radio);
};

class Robot : public NodoGrafoEscena {
    protected:
        mat4 *pm_rot_cabeza = nullptr;
        mat4 *pm_rot_brazo_izq = nullptr;
        mat4 *pm_rot_brazo_der = nullptr;
        mat4 *pm_rot_pierna_izq = nullptr;
        mat4 *pm_rot_pierna_der = nullptr;
        mat4 *pm_pos_robot = nullptr;

    public:
        Robot();
        unsigned leerNumParametros() const;
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

#endif // MODELO_JER_H