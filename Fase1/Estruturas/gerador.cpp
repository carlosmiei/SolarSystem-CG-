#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Ponto.h"
using namespace std;



vector<Ponto*> cone(float raio, float altura, int slices,int camadas){
    vector<Ponto*> pontos;
    float angulo = ((2*M_PI)/slices);
    float xA,zA,xP,zP;

    float alturaIntermedia = altura / camadas;
    
    for (int i=0; i < slices;i++) {


        xA = raio * sin(i*angulo);
        zA = raio * cos(i*angulo);


        xP = raio * sin((i+1)*angulo);
        zP = raio * cos((i+1)*angulo);

        Ponto *p = new Ponto(0.0f, 0.0f,0.0f);
        pontos.push_back(p);
        
        p = new Ponto(xP, 0.0f, zP);
        pontos.push_back(p);
        
        p = new Ponto((xA, 0.0f, zA);
        pontos.push_back(p);


        for(int j=0; j < camadas; j++){

            float yA = j*alturaIntermedia;
            float yCima = (j+1)*alturaIntermedia;

            float raioIntermedioCima = raio * ((altura-yCima) /altura);
            float raioIntermedioBaixo = raio * ((altura-yA) /altura);

            xA = raioIntermedioBaixo * sin(i*angulo);
            zA = raioIntermedioBaixo * cos(i*angulo);


            xP = raioIntermedioBaixo * sin((i+1)*angulo);
            zP = raioIntermedioBaixo * cos((i+1)*angulo);

            float xACima = raioIntermedioCima * sin(i*angulo);
            float zACima = raioIntermedioCima * cos(i*angulo);

            float xPCima = raioIntermedioCima * sin((i+1)*angulo);
            float zPCima = raioIntermedioCima * cos((i+1)*angulo);


            p = new Ponto(xA, yA, zA);
            pontos.push_back(p);

            p = new Ponto(xP,yA, zP);
            pontos.push_back(p);
            
            p = new Ponto(xPCima,yCima, zPCima);
            pontos.push_back(p);
            
            p = new Ponto(xA,yA, zA);
            pontos.push_back(p);

            p = new Ponto(xPCima,yCima, zPCima);
            pontos.push_back(p);
            
            p = new Ponto(xAcima,yCima, zACima);
            pontos.push_back(p);

        }


        glEnd();

    }

    
    return pontos;
    
}

vector<Ponto*> esfera(float raio, int fatias, int camadas){

    float alpha = (2*M_PI) / (float) fatias, beta = (M_PI) / (float) camadas;
    float x1, y1, z1, x2, y2, z2, x3, z3, x4,z4;

    vector<Ponto*> pontos;

    for(int i = 0; i<fatias; i++){

        for(int j = 0; j<camadas; j++) {

            y1 = raio * cos(beta*j);

            x1 = raio * sin(beta*j) * sin(alpha*i);
            z1 = raio * sin(beta*j) * cos(alpha*i);

            x2 = raio * sin(beta*j) * sin(alpha * (i+1));
            z2 = raio * sin(beta*j) * cos(alpha * (i+1));

            y2 = raio * cos(beta * (j+1));

            x3 = raio * sin(beta * (j+1)) * sin(alpha*i);
            z3 = raio * sin(beta * (j+1)) * cos(alpha*i);

            x4 = raio * sin(beta * (j+1)) * sin(alpha * (i+1));
            z4 = raio * sin(beta * (j+1)) * cos(alpha * (i+1));

            glColor3f(0.0,0.0,1.0f);

            //glVertex3f(x4, y2, z4);
            Ponto *p = new Ponto(x4, y2, z4);
            pontos.push_back(p);
            //glVertex3f(x2, y1, z2);
            p = new Ponto(x2, y1, z2);
            pontos.push_back(p);
            //glVertex3f(x1, y1, z1);
            p = new Ponto(x1, y1, z1);
            pontos.push_back(p);

            //glVertex3f(x4, y2, z4);
            p = new Ponto(x4, y2, z4);
            pontos.push_back(p);
            //glVertex3f(x1, y1, z1);
            p = new Ponto(x1, y1, z1);
            pontos.push_back(p);
            //glVertex3f(x3, y2, z3);
            p = new Ponto(x3, y2, z3);
            pontos.push_back(p);

        }

    }

    return pontos;

}

vector<Ponto*> plane(float lado){

	float coord = lado/2.0f;
	vector<Ponto*> pontos;
    //Plane
    
    Ponto *p = new Ponto(-coord, 0.0f, coord);
    pontos.push_back(p);
  	p = new Ponto(coord, 0.0f, -coord);
  	pontos.push_back(p);
    p = new Ponto(-coord, 0.0f, -coord);
    pontos.push_back(p);
    p = new Ponto(-coord, 0.0f, coord);
    pontos.push_back(p);
  	p = new Ponto(coord, 0.0f, coord);
  	pontos.push_back(p);
    p = new Ponto(coord, 0.0f, -coord);
    pontos.push_back(p);
    return pontos;
}

int comparaFigura(string a){

	if(a.compare("plane")==0) return 1;
  if(a.compare("sphere")==0) return 4;

	return 0;
}

int main (int argc, char** argv) {
  ofstream myfile;
  vector<Ponto*> pontos;

  int aux = comparaFigura(argv[1]);
  switch(aux){
  	case 1: {
  		myfile.open(argv[3]);
  		string tam(argv[2]);
  		float lado = stof(tam);
  		pontos = plane(lado);
  		break;
  	}
    case 4:{
      myfile.open(argv[5]);

      string raio(argv[2]);
      float r = stof(raio); // Nao podia fazer logo stof(argv[2])

      string fatias(argv[3]);
      int f = stoi(fatias);
      
      string camadas(argv[4]);
      int c = stoi(camadas);

      pontos = esfera(r, f, c);
      break;
    }

  	default: break; 
  }
  

  for(Ponto* p: pontos){
  	string escreve = p->toString();
  	myfile << escreve + "\n";
  }

  
  myfile.close();

  return 0;
}