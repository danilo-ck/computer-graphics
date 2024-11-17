#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"
#include "modelo-jer.h"

using namespace std;
using namespace glm;

Esferas::Esferas(const int num_verts_per, const unsigned nperfiles, float radio){
    vector<vec3> perfil = vector<vec3>();
    float perimetro = 2*M_PI*radio;
    float division_perimtero = perimetro/(num_verts_per-1);
    for(int i=0; i<num_verts_per; i++){
        perfil.push_back(vec3(radio*cos(i*division_perimtero),radio*sin(i*division_perimtero),0.0));
    }
    inicializar(perfil,nperfiles);
}

Robot::Robot() {
    ponerNombre("robot");
    
    // Nodo raíz
    NodoGrafoEscena *robot = new NodoGrafoEscena();
    unsigned ind_pos_robot = robot->agregar(translate(vec3{0.0, 0.0, 0.0}));
    
    // Torso ajustado (más delgado y proporcionado)
    NodoGrafoEscena *torso = new NodoGrafoEscena();
    torso->agregar(scale(vec3{0.8, 1.2, 0.6}));
    torso->ponerColor({0.4, 0.4, 0.5});
    torso->agregar(new Cubo());
    
    // Pecho reposicionado
    NodoGrafoEscena *pecho = new NodoGrafoEscena();
    pecho->agregar(translate(vec3{0.0, 0.2, 0.31}));
    pecho->agregar(scale(vec3{0.6, 0.4, 0.1}));
    pecho->ponerColor({0.6, 0.1, 0.1});
    pecho->agregar(new Cubo());
    
    // Cabeza reposicionada más arriba
    NodoGrafoEscena *cabeza = new NodoGrafoEscena();
    unsigned ind_rot_cabeza = cabeza->agregar(rotate(0.0f, vec3{0.0, 1.0, 0.0}));
    cabeza->agregar(translate(vec3{0.0, 1.5, 0.0}));
    
    // Casco de la cabeza
    NodoGrafoEscena *casco = new NodoGrafoEscena();
    casco->agregar(scale(vec3{0.6, 0.7, 0.6}));
    casco->ponerColor({0.3, 0.3, 0.35});
    casco->agregar(new Esferas(30, 30, 1.0));
    
    // Ojos mejorados (con brillo)
    NodoGrafoEscena *ojo_izq = new NodoGrafoEscena();
    ojo_izq->agregar(translate(vec3{-0.25, 0.1, 0.5}));
    ojo_izq->agregar(scale(vec3{0.12, 0.08, 0.05}));
    ojo_izq->ponerColor({0.0, 0.8, 0.8});
    ojo_izq->agregar(new Esferas(20, 20, 1.0));
    
    NodoGrafoEscena *ojo_der = new NodoGrafoEscena();
    ojo_der->agregar(translate(vec3{0.25, 0.1, 0.5}));
    ojo_der->agregar(scale(vec3{0.12, 0.08, 0.05}));
    ojo_der->ponerColor({0.0, 0.8, 0.8});
    ojo_der->agregar(new Esferas(20, 20, 1.0));
    
    cabeza->agregar(casco);
    cabeza->agregar(ojo_izq);
    cabeza->agregar(ojo_der);
    
    // Brazos con punto de rotación en el hombro
    NodoGrafoEscena *brazo_izq = new NodoGrafoEscena();
    brazo_izq->agregar(translate(vec3{-0.9, 0.8, 0.0}));  // Primero posicionamos el punto de rotación
    unsigned ind_rot_brazo_izq = brazo_izq->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));  // Luego la rotación
    brazo_izq->agregar(translate(vec3{0.0, -0.4, 0.0}));  // Desplazamiento para centrar el brazo
    brazo_izq->agregar(scale(vec3{0.2, 0.8, 0.2}));
    brazo_izq->ponerColor({0.4, 0.4, 0.45});
    brazo_izq->agregar(new Cubo());
    
    NodoGrafoEscena *brazo_der = new NodoGrafoEscena();
    brazo_der->agregar(translate(vec3{0.9, 0.8, 0.0}));  // Primero posicionamos el punto de rotación
    unsigned ind_rot_brazo_der = brazo_der->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));  // Luego la rotación
    brazo_der->agregar(translate(vec3{0.0, -0.4, 0.0}));  // Desplazamiento para centrar el brazo
    brazo_der->agregar(scale(vec3{0.2, 0.8, 0.2}));
    brazo_der->ponerColor({0.4, 0.4, 0.45});
    brazo_der->agregar(new Cubo());
    
    // IMPORTANTE: Agregar los brazos al robot
    robot->agregar(torso);
    robot->agregar(pecho);
    robot->agregar(cabeza);
    robot->agregar(brazo_izq);
    robot->agregar(brazo_der);
    
    // Piernas reposicionadas
    NodoGrafoEscena *pierna_izq = new NodoGrafoEscena();
    unsigned ind_rot_pierna_izq = pierna_izq->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));
    pierna_izq->agregar(translate(vec3{-0.3, -1.2, 0.0}));
    pierna_izq->agregar(scale(vec3{0.2, 0.8, 0.2}));
    pierna_izq->ponerColor({0.5, 0.5, 0.5});
    pierna_izq->agregar(new Cubo());
    
    NodoGrafoEscena *pierna_der = new NodoGrafoEscena();
    unsigned ind_rot_pierna_der = pierna_der->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));
    pierna_der->agregar(translate(vec3{0.3, -1.2, 0.0}));
    pierna_der->agregar(scale(vec3{0.2, 0.8, 0.2}));
    pierna_der->ponerColor({0.5, 0.5, 0.5});
    pierna_der->agregar(new Cubo());
    
    // Agregar todo al nodo raíz
    robot->agregar(torso);
    robot->agregar(cabeza);
    robot->agregar(pierna_izq);
    robot->agregar(pierna_der);
    
    // Guardar punteros a matrices
    pm_rot_cabeza = cabeza->leerPtrMatriz(ind_rot_cabeza);
    pm_rot_brazo_izq = brazo_izq->leerPtrMatriz(ind_rot_brazo_izq);
    pm_rot_brazo_der = brazo_der->leerPtrMatriz(ind_rot_brazo_der);
    pm_rot_pierna_izq = pierna_izq->leerPtrMatriz(ind_rot_pierna_izq);
    pm_rot_pierna_der = pierna_der->leerPtrMatriz(ind_rot_pierna_der);
    pm_pos_robot = robot->leerPtrMatriz(ind_pos_robot);
    // Agregar el robot completo
    agregar(robot);
    
}

unsigned Robot::leerNumParametros() const {
    return 6; // número de parámetros de animación
}

void Robot::actualizarEstadoParametro(const unsigned iParam, const float t_sec) {
    switch(iParam) {
        case 0: // Rotación de la cabeza
            *pm_rot_cabeza = rotate(float(sin(t_sec)), vec3{0.0, 1.0, 0.0});
            break;
        case 1: // Movimiento del brazo izquierdo
            *pm_rot_brazo_izq = rotate(float(sin(2*M_PI*t_sec)), vec3{1.0, 0.0, 0.0});
            break;
        case 2: // Movimiento del brazo derecho
            *pm_rot_brazo_der = rotate(float(-sin(2*M_PI*t_sec)), vec3{1.0, 0.0, 0.0});
            break;
        case 3: // Movimiento de la pierna izquierda (muy sutil)
            *pm_rot_pierna_izq = rotate(float(sin(2*M_PI*t_sec) * 0.2), vec3{1.0, 0.0, 0.0});
            break;
        case 4: // Movimiento de la pierna derecha (muy sutil)
            *pm_rot_pierna_der = rotate(float(-sin(2*M_PI*t_sec) * 0.2), vec3{1.0, 0.0, 0.0});
            break;
        case 5: // Salto más dinámico
            float altura = 1.0f;  // Aumentada la altura máxima
            float velocidad = 3.0f;  // Aumentada la frecuencia
            float salto = pow(abs(sin(velocidad * t_sec)), 0.5); // Función exponencial para efecto de impulso
            *pm_pos_robot = translate(vec3{0.0, altura * salto, 0.0});
            break;
    }
}
