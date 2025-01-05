#include "latapeones.h"

using namespace std;
using namespace glm;

Peon::Peon(int nperfiles) : MallaRevolPLY("peon.ply", nperfiles) {}

Lata::Lata(const std::string & nombre_arch) {
    NodoGrafoEscena* actual = new NodoGrafoEscena();

    unsigned identTapa = 0;
    unsigned identBase = 1;
    unsigned identCara = 2;

    Textura* cocacola = new Textura(nombre_arch);
    Material* materialLata = new Material(cocacola, 0.75, 0.65, 0.25, 50.0);
    Material* materialBases = new Material(0.35, 0.45, 0.25, 50.0);

    NodoGrafoEscena* base = new NodoGrafoEscena();
    NodoGrafoEscena* cara = new NodoGrafoEscena();
    NodoGrafoEscena* tapa = new NodoGrafoEscena();

    base->agregar(translate(vec3(0.0, 0.0, 0.0)));
    base->agregar(scale(vec3(1.0, 1.0, 1.0)));
    base->agregar(materialBases);
    base->agregar(new MallaRevolPLY("lata-pinf.ply", 32));

    tapa->agregar(translate(vec3(0.0, 0.0, 0.0)));
    tapa->agregar(scale(vec3(1.0, 1.0, 1.0)));
    tapa->agregar(materialBases);
    tapa->agregar(new MallaRevolPLY("lata-psup.ply", 32));
    

    cara->agregar(translate(vec3(0.0, 0.0, 0.0)));
    cara->agregar(scale(vec3(1.0, 1.0, 1.0)));
    cara->agregar(materialLata);
    cara->agregar(new MallaRevolPLY("lata-pcue.ply", 32));

    actual->agregar(base);
    actual->agregar(cara);
    actual->agregar(tapa);

    agregar(actual);
}

LataPeones::LataPeones() {
    NodoGrafoEscena* actual = new NodoGrafoEscena();

    unsigned identPeonMadera = 1;
    unsigned identPeonBlanco = 2;
    unsigned identPeonNegro = 3;
    unsigned identLata = 4;

    TexturaXY* texturaXY_madera = new TexturaXY("text-madera.jpg");
    Material* materialPeonMadera = new Material(texturaXY_madera, 0.5, 0.6, 0.5, 50.0);
    Material* materialPeonBlanco = new Material(0.3, 1.0, 0, 0.0);
    Material* materialPeonNegro = new Material(0.5, 0.2, 0.9, 15.0);

    NodoGrafoEscena* peonMadera = new NodoGrafoEscena();
    NodoGrafoEscena* peonNegro = new NodoGrafoEscena();
    NodoGrafoEscena* peonBlanco = new NodoGrafoEscena();

    Lata* lata = new Lata("lata-coke.jpg");
    lata->ponerNombre("Lata de Coca-Cola");
    lata->ponerIdentificador(identLata);

    peonMadera->ponerNombre("Peón de madera");
    peonMadera->ponerIdentificador(identPeonMadera);
    peonMadera->agregar(translate(vec3(0.0, 0.2, 0.85)));
    peonMadera->agregar(scale(vec3(0.15, 0.15, 0.15)));
    peonMadera->agregar(materialPeonMadera);
    peonMadera->agregar(new Peon(32));

    peonBlanco->ponerNombre("Peón blanco");
    peonBlanco->ponerIdentificador(identPeonBlanco);
    peonBlanco->agregar(translate(vec3(0.45, 0.2, 0.85)));
    peonBlanco->agregar(scale(vec3(0.15, 0.15, 0.15)));
    peonBlanco->ponerColor(vec3(1.0, 1.0, 1.0));
    peonBlanco->agregar(materialPeonBlanco);
    peonBlanco->agregar(new Peon(32));

    peonNegro->ponerNombre("Peón Negro");
    peonNegro->ponerIdentificador(identPeonNegro);
    peonNegro->agregar(translate(vec3(0.9, 0.2, 0.85)));
    peonNegro->agregar(scale(vec3(0.15, 0.15, 0.15)));
    peonNegro->ponerColor(vec3(0.0, 0.0, 0.0));
    peonNegro->agregar(materialPeonNegro);
    peonNegro->agregar(new Peon(32));


    actual->agregar(peonMadera);
    actual->agregar(peonBlanco);
    actual->agregar(peonNegro);

    actual->agregar(lata);

    agregar(actual);
}