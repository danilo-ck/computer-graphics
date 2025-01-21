#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"
#include "modelo-jer.h"

using namespace std;
using namespace glm;


Robot::Robot() {
    unsigned ident = 1;



    // Nodo raíz
    ponerNombre("robot");
    NodoGrafoEscena *robot = new NodoGrafoEscena();
    unsigned ind_pos_robot = robot->agregar(translate(vec3{0.0, 0.0, 0.0}));

    // Texturas y materiales
    TexturaXY* multiculor = new TexturaXY("tiles-1557136_1280.jpg");
    Material* materialOjos = new Material(multiculor, 0.7, 0.2, 1.0, 50.0);
    Material* materialBlanco = new Material(0.5, 0.9, 0.5, 50.0); // Material blanco metálico
    Material* materialNegro = new Material(0.1, 0.1, 0.1, 50.0); // Material negro difuso

    // Cuerpo 
    NodoGrafoEscena *cuerpo = new NodoGrafoEscena();
    cuerpo->ponerNombre("cuerpo");
    cuerpo->ponerIdentificador(ident++);
    cuerpo->agregar(translate(vec3{0.0, -0.15, 0.0}));
    cuerpo->agregar(scale(vec3{0.6, 1.2, 0.6}));
    cuerpo->agregar(materialBlanco);
    cuerpo->agregar(new Cilindro(80, 80));

    // Crear la cabeza
    NodoGrafoEscena *cabeza = new NodoGrafoEscena();
    NodoGrafoEscena *ojos = new NodoGrafoEscena();

    // Ojos (esferas)
    NodoGrafoEscena *ojo_izq = new NodoGrafoEscena();
    ojo_izq->ponerNombre("ojo-izquierdo");
    ojo_izq->ponerIdentificador(ident++);
    ojo_izq->agregar(translate(vec3{-0.25, 1.2, 0.45}));
    ojo_izq->agregar(scale(vec3{0.1, 0.1, 0.1}));
    ojo_izq->agregar(materialOjos);
    ojo_izq->agregar(new Esfera(60, 60));
    

    NodoGrafoEscena *ojo_der = new NodoGrafoEscena();
    ojo_der->ponerNombre("ojo-derecho");
    ojo_der->ponerIdentificador(ident++);
    ojo_der->agregar(translate(vec3{0.25, 1.2, 0.45}));
    ojo_der->agregar(scale(vec3{0.1, 0.1, 0.1}));
    ojo_der->agregar(materialOjos);
    ojo_der->agregar(new Esfera(60, 60));
    ojos->agregar(ojo_izq);
    ojos->agregar(ojo_der);

    // Esfera Cabeza 
    cabeza->ponerNombre("cabeza");
    cabeza->ponerIdentificador(ident++);
    unsigned ind_rot_cabeza = cabeza->agregar(rotate(0.0f, vec3{0.0, 1.0, 0.0}));
    cabeza->agregar(ojos);
    cabeza->agregar(scale(vec3{0.55, 0.55, 0.55}));
    cabeza->agregar(translate(vec3{0.0, 2.0, 0.0})); 
    cabeza->agregar(materialBlanco);
    cabeza->agregar(new Esfera(100, 100));
    

    // Brazos cilindros y esferas 
    NodoGrafoEscena *brazo_der = new NodoGrafoEscena();
    brazo_der->ponerNombre("brazo-derecho");
    brazo_der->ponerIdentificador(ident++);
    brazo_der->agregar(translate(vec3{-0.78, 0.3, 0.0}));
    unsigned ind_rot_brazo_der = brazo_der->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));

    // Mano derecha
    NodoGrafoEscena *mano_der = new NodoGrafoEscena();
    mano_der->agregar(translate(vec3{0.0, -0.6, 0.0}));
    mano_der->agregar(scale(vec3{0.25, 0.25, 0.25}));
    mano_der->agregar(materialBlanco);
    mano_der->agregar(new Esfera(60, 60));
    brazo_der->agregar(mano_der);

    // Brazo derecho (cilindro)
    NodoGrafoEscena *brazo_sup_der = new NodoGrafoEscena();
    brazo_sup_der->agregar(translate(vec3{0.0, -0.6, 0.0}));
    brazo_sup_der->agregar(scale(vec3{0.15, 1.2, 0.15}));
    brazo_sup_der->agregar(materialNegro);
    brazo_sup_der->agregar(new Cilindro(10, 20));
    brazo_der->agregar(brazo_sup_der);

    // Hombro derecho
    NodoGrafoEscena *hombro_der = new NodoGrafoEscena();
    hombro_der->agregar(translate(vec3{0.0, 0.6, 0.0}));
    hombro_der->agregar(scale(vec3{0.25, 0.25, 0.25}));
    hombro_der->agregar(materialBlanco);
    hombro_der->agregar(new Esfera(60, 60));
    brazo_der->agregar(hombro_der);

    // Brazo izquierdo
    NodoGrafoEscena *brazo_izq = new NodoGrafoEscena();
    brazo_izq->ponerNombre("brazo-izquierdo");
    brazo_izq->ponerIdentificador(ident++);
    brazo_izq->agregar(translate(vec3{0.78, 0.3, 0.0}));
    unsigned ind_rot_brazo_izq = brazo_izq->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));

    // Mano izquierda
    NodoGrafoEscena *mano_izq = new NodoGrafoEscena();
    mano_izq->agregar(translate(vec3{0.0, -0.6, 0.0}));
    mano_izq->agregar(scale(vec3{0.25, 0.25, 0.25}));
    mano_izq->agregar(materialBlanco);
    mano_izq->agregar(new Esfera(60, 60));
    brazo_izq->agregar(mano_izq);

    // Brazo superior izquierdo
    NodoGrafoEscena *brazo_sup_izq = new NodoGrafoEscena();
    brazo_sup_izq->agregar(translate(vec3{0.0, -0.6, 0.0}));
    brazo_sup_izq->agregar(scale(vec3{0.15, 1.2, 0.15}));
    brazo_sup_izq->agregar(materialNegro);
    brazo_sup_izq->agregar(new Cilindro(10, 20));
    brazo_izq->agregar(brazo_sup_izq);

    // Hombro izquierdo
    NodoGrafoEscena *hombro_izq = new NodoGrafoEscena();
    hombro_izq->agregar(translate(vec3{0.0, 0.6, 0.0}));
    hombro_izq->agregar(scale(vec3{0.25, 0.25, 0.25}));
    hombro_izq->agregar(materialBlanco);
    hombro_izq->agregar(new Esfera(60, 60));
    brazo_izq->agregar(hombro_izq);

    // Piernas mejoradas con cilindros y esferas en las articulaciones
    NodoGrafoEscena *pierna_izq = new NodoGrafoEscena();
    pierna_izq->ponerNombre("pierna-izquierda");
    pierna_izq->ponerIdentificador(ident++);
    unsigned ind_rot_pierna_izq = pierna_izq->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));
    pierna_izq->agregar(translate(vec3{-0.3, -0.4, 0.0}));

    // Pierna superior izquierda
    NodoGrafoEscena *pierna_sup_izq = new NodoGrafoEscena();
    pierna_sup_izq->agregar(translate(vec3{0.0, -0.8, 0.0}));
    pierna_sup_izq->agregar(scale(vec3{0.15, 1.1, 0.15}));
    pierna_sup_izq->agregar(materialNegro);
    pierna_sup_izq->agregar(new Cilindro(10, 20));
    pierna_izq->agregar(pierna_sup_izq);

    // Pie izquierdo
    NodoGrafoEscena *pie_izq = new NodoGrafoEscena();
    pie_izq->agregar(translate(vec3{0.0, -0.8, 0.0}));
    pie_izq->agregar(scale(vec3{0.25, 0.25, 0.25}));
    pie_izq->agregar(materialBlanco);
    pie_izq->agregar(new Esfera(20, 20));
    pierna_izq->agregar(pie_izq);

    // Pierna derecha (similar a la izquierda)
    NodoGrafoEscena *pierna_der = new NodoGrafoEscena();
    pierna_der->ponerNombre("pierna-derecha");
    pierna_der->ponerIdentificador(ident++);
    unsigned ind_rot_pierna_der = pierna_der->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));
    pierna_der->agregar(translate(vec3{0.3, -0.4, 0.0}));

    // Pierna superior derecha
    NodoGrafoEscena *pierna_sup_der = new NodoGrafoEscena();
    pierna_sup_der->agregar(translate(vec3{0.0, -0.8, 0.0}));
    pierna_sup_der->agregar(scale(vec3{0.15, 1.1, 0.15}));
    pierna_sup_der->agregar(materialNegro);
    pierna_sup_der->agregar(new Cilindro(10, 20));
    pierna_der->agregar(pierna_sup_der);

    // Pie derecho
    NodoGrafoEscena *pie_der = new NodoGrafoEscena();
    pie_der->agregar(translate(vec3{0.0, -0.8, 0.0}));
    pie_der->agregar(scale(vec3{0.25, 0.25, 0.25}));
    pie_der->agregar(materialBlanco);
    pie_der->agregar(new Esfera(20, 20));
    pierna_der->agregar(pie_der);

    // Agregar todo al robot
    robot->agregar(cuerpo);
    robot->agregar(cabeza);
    robot->agregar(brazo_izq);
    robot->agregar(brazo_der);
    robot->agregar(pierna_izq);
    robot->agregar(pierna_der);

    // Guardar punteros a matrices
    pm_rot_cabeza = cabeza->leerPtrMatriz(ind_rot_cabeza);
    pm_rot_brazo_izq = brazo_izq->leerPtrMatriz(ind_rot_brazo_izq);
    pm_rot_brazo_der = brazo_der->leerPtrMatriz(ind_rot_brazo_der);
    pm_rot_pierna_izq = pierna_izq->leerPtrMatriz(ind_rot_pierna_izq);
    pm_rot_pierna_der = pierna_der->leerPtrMatriz(ind_rot_pierna_der);
    pm_pos_robot = robot->leerPtrMatriz(ind_pos_robot);

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
        case 1: // Movimiento del brazo izquierdo desde el hombro
            *pm_rot_brazo_izq = translate(vec3{0.0, 0.6, 0.0}) * 
                               rotate(float(sin(2*M_PI*t_sec)), vec3{1.0, 0.0, 0.0}) *
                               translate(vec3{0.0, -0.6, 0.0});
            break;
        case 2: // Movimiento del brazo derecho desde el hombro
            *pm_rot_brazo_der = translate(vec3{0.0, 0.6, 0.0}) * 
                               rotate(float(-sin(2*M_PI*t_sec)), vec3{1.0, 0.0, 0.0}) *
                               translate(vec3{0.0, -0.6, 0.0});
            break;
        case 3: // Movimiento de la pierna izquierda (muy sutil)
            *pm_rot_pierna_izq = rotate(float(sin(2*M_PI*t_sec) * 0.2), vec3{1.0, 0.0, 0.0});
            break;
        case 4: // Movimiento de la pierna derecha (muy sutil)
            *pm_rot_pierna_der = rotate(float(-sin(2*M_PI*t_sec) * 0.2), vec3{1.0, 0.0, 0.0});
            break;
        case 5: // Salto desde posición inicial
            float altura = 1.0f;
            float velocidad = 3.0f;
            float salto = pow(abs(sin(velocidad * t_sec)), 0.5);
            *pm_pos_robot = translate(vec3{0.0, -0.6 + altura * salto, 0.0});
            break;
    }
}
