#include "Cilindro.h"
#include <cmath>

#define ALTURA_OK(Ponto, centro, altura) (Ponto.Y() > (centro.Y() - altura/2.)) && (Ponto.Y() < (centro.Y() + altura/2.))

/* TODO: adaptar para cilindro */
Cilindro::Cilindro(int _indice_textura, float _raio, float _altura, const Ponto_3D& _centro) : Objeto_3D ( _indice_textura )
{
  raio = _raio;
  centro =  _centro;
  altura = _altura;
}

//Foley capítulo 15.10, fórmula 15.17
Intersection Cilindro::Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold)
{
  float a, b, c, delta;
  Intersection intersection;

  // valores intermediários
  float t1, t2;
  Ponto_3D P1, P2;

  Vetor_3D K = Vetor_3D(r_vis.X0() - centro.X(),
                        0,
                        r_vis.Z0() - centro.Z());

  Vetor_3D direcao = Vetor_3D(r_vis.Direcao());
  direcao.setY(0);

  // montando a equação do 2º grau at2 + bt + c = 0
  a = direcao.produtoEscalar(direcao);
  b = 2*(direcao.produtoEscalar(K));
  c = K.produtoEscalar(K) - raio*raio;

  delta = b*b - 4*a*c;
  if (delta >= 0) {
      t1 = (-b - sqrt(delta)) /(2*a);
      t2 = (-b + sqrt(delta)) /(2*a);

      P1 = P2 = r_vis.Origem();

      P1 += r_vis.Direcao()*t1;
      P2 += r_vis.Direcao()*t2;

      // Verifica se pelo menos um dos pontos está dentro do cilindro
      if ( (ALTURA_OK(P1, centro, altura)) || (ALTURA_OK(P2, centro, altura)) ) {
          intersection = Intersection::nearest(
              Intersection(this, t1),
              Intersection(this, t2), threshold);
      }
  }

  return intersection;
}

Vetor_3D Cilindro::normal( const Ponto_3D& ponto ) const
{
    Vetor_3D tmp;

    tmp = ponto - centro;
    tmp.setY(0);
    tmp.normaliza();

    return tmp;
}

TexturePoint Cilindro::pontoTextura(const Ponto_3D& ponto) const
{
    float theta;
    Vetor_3D tmp(ponto - centro);
    Vetor_3D tmp_xz(tmp);

    tmp.normaliza();

    tmp_xz.setY(0);
    tmp_xz.normaliza();

    theta  = acosf(tmp_xz.Z());

    return TexturePoint(theta/M_PI, .5 - tmp.Y()/2.);
}
