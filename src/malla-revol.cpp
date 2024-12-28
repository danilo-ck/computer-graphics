// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas creadas por revolución de un perfil (implementación). Clase 'MallaRevol' y derivadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de las clases 
// **    + MallaRevol: malla indexada de triángulos obtenida por 
// **      revolución de un perfil (derivada de MallaInd)
// **    + MallaRevolPLY: malla indexada de triángulos, obtenida 
// **      por revolución de un perfil leído de un PLY (derivada de MallaRevol)
// **    + algunas clases derivadas de MallaRevol
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   using namespace glm;

   // COMPLETAR: práctica 4: creación de las normales y materiales/texturas
   vector<vec3> normales_perfil;

   // Calcular las normales del perfil
   for (int i = 0; i < perfil.size() - 1; i++) {
      float delta_x = (perfil[i + 1] - perfil[i])[0];
      float delta_y = (perfil[i + 1] - perfil[i])[1];
      vec3 normal(vec3(delta_y, -delta_x, 0.0f));

      if (length(normal) != 0.0)
         normal = normalize(normal);
      
      normales_perfil.push_back(normal);
   }

   vector<vec3> normales_vertices;

   // Calcular las normales de los vértices
   normales_vertices.push_back(normales_perfil[0]);
   for (int i = 1; i < perfil.size() - 1; i++) {
      normales_vertices.push_back(normalize(normales_perfil[i - 1] + normales_perfil[i]));
   }
   normales_vertices.push_back(normales_perfil[perfil.size() - 2]);

   vector<float> distancias, coordenadas_textura, sumas_parciales;
   float suma_total;

   // Calcular las distancias entre los puntos del perfil
   for (int i = 0; i < perfil.size() - 1; i++) {
      distancias.push_back(sqrt(length(perfil[i + 1] - perfil[i])));
   }

   // Calcular las sumas parciales de las distancias
   sumas_parciales.push_back(0.0f);
   for (int i = 1; i < perfil.size(); i++) {
      sumas_parciales.push_back(sumas_parciales[i - 1] + distancias[i - 1]);
   }

   suma_total = sumas_parciales[perfil.size() - 1];

   // Calcular las coordenadas de textura
   coordenadas_textura.push_back(0.0f);
   for (int i = 1; i < perfil.size(); i++)
      coordenadas_textura.push_back(sumas_parciales[i] / suma_total);
   
   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   //
   // ............................... 

   // Crear los vértices de la malla de revolución
   for (int i = 0; i < num_copias; i++) {
      for (int j = 0; j < perfil.size(); j++) {
         float angulo = (2 * M_PI * i) / (num_copias - 1);

         std::vector<std::vector<float>> matriz_rotacion = 
         {  {cos(angulo), 0.0, sin(angulo)},
            {0 ,1, 0},
            {-sin(angulo), 0, cos(angulo)},
         };

         glm::vec3 vertice_rotado = {
            matriz_rotacion[0][0] * perfil[j][0] + matriz_rotacion[0][1] * perfil[j][1] + matriz_rotacion[0][2] * perfil[j][2],
            matriz_rotacion[1][0] * perfil[j][0] + matriz_rotacion[1][1] * perfil[j][1] + matriz_rotacion[1][2] * perfil[j][2],
            matriz_rotacion[2][0] * perfil[j][0] + matriz_rotacion[2][1] * perfil[j][1] + matriz_rotacion[2][2] * perfil[j][2],
         };

         vertices.push_back(vertice_rotado);

         // Práctica 4: Calcular las normales de los vértices rotados
         vec3 normal_rotada = vec3(normales_vertices[j][0] * cos(angulo), normales_vertices[j][1], -normales_vertices[j][0] * sin(angulo));
         if (length(normal_rotada) != 0.0)
            normalize(normal_rotada);
         nor_ver.push_back(normal_rotada);
         
         // Calcular las coordenadas de textura de los vértices rotados
         cc_tt_ver.push_back({float(i) / (num_copias - 1), 1 - coordenadas_textura[j]});
      }
   }

   // Crear los triángulos de la malla de revolución
   for (int i = 0; i < num_copias - 1; i++) {
      for (int j = 0; j < perfil.size() - 1; j++) {
         int indice = i * perfil.size() + j;

         triangulos.push_back({indice, indice + perfil.size(), indice + perfil.size() + 1});
         triangulos.push_back({indice, indice + perfil.size() + 1, indice + 1});
      }
   }
}


// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................
   std::vector<glm::vec3> perfil;
   LeerVerticesPLY(nombre_arch,perfil);
   inicializar(perfil,nperfiles);


}

// Práctica 2: Clases Cilindro, Cono y Esfera

// Cilindro con el centro de la base en el origen, y con radio y altura 1

Cilindro::Cilindro(const int num_verts_per, const unsigned nperfiles){
   ponerNombre("cilindro");
   std::vector<glm::vec3> perfil = std::vector<glm::vec3>();

   perfil.push_back(glm::vec3(0.0,0.0,0.0));

   for(int i=0; i<num_verts_per-2; i++){
      float altura = i*(1.0/(num_verts_per-3));
      perfil.push_back(glm::vec3(1.0,altura,0.0));
   }

   perfil.push_back(glm::vec3(0.0,1.0,0.0));

   inicializar(perfil,nperfiles);
}

Esfera::Esfera(const int num_verts_per, const unsigned nperfiles){
   ponerNombre("esfera");
   std::vector<glm::vec3> perfil = std::vector<glm::vec3>();
   float perimetro = (2*M_PI/(num_verts_per-1));
   for(int i=0; i<num_verts_per; i++){
      perfil.push_back(glm::vec3(cos(i*perimetro),sin(i*perimetro),0.0));
   }
   inicializar(perfil,nperfiles);
}

Cono::Cono(const int num_verts_per, const unsigned nperfiles){
   ponerNombre("cono");
   std::vector<glm::vec3> perfil = std::vector<glm::vec3>();

   perfil.push_back(glm::vec3(0.0,0.0,0.0));

   for(int i=0; i<num_verts_per; i++){
      float altura = i*(1.0/(num_verts_per-2));
      float x = (num_verts_per-2-i)*(1.0/(num_verts_per-2));
      perfil.push_back(glm::vec3(x,altura,0.0));
   }
   inicializar(perfil,nperfiles);
}

