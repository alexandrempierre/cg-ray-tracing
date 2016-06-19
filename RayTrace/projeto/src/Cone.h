#ifndef CONE_H
#define CONE_H

#include "Objeto_3d.h"

//* classe Cone #Cone#
class Cone : public Objeto_3D {
  protected:
    float altura;
  public:
 //* Construtor e Destrutor
  	/* TODO: mudar raio para raio e altura */
    Cone(int _indice_textura, float _raio, float _altura, const Ponto_3D& _centro);
    ~Cone() {}
 //* interseção e Normal
    Intersection Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold) ;
    Vetor_3D normal( const Ponto_3D& ponto ) const ;
    TexturePoint pontoTextura(const Ponto_3D& ponto) const;
};
#endif // CONE_H
