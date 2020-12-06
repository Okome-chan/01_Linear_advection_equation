
/*****************************************************************************/
//
//
//
//
//
//
//
/*****************************************************************************/

#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <complex>
#include <math.h>
#include <time.h>

using namespace std;

int main(){

  int t;
  int tmax;         //time step
  double dt;        //dt
  double dx;        //dx
  double c;         //
  double r;         //Courant number
  double *u;        //u at time tn
  double *u_new;    //u at time tn+1

  // calculate Courant number
  r=c*dt/dx;
  for(t=1; t<=tmax; t++){
    Backward(u_new,u.r.collumn);
    update_value(u_new,u,collumn);
  }

  return 0;
}

//Backward difference scheme
void Backward(double *u_new, double *u, double r, int imax){
  int i;
  for(i=1; i<=imax; i++){
    //boundary condition
    if(i==1){
      u_new[i]=0.;
    }else if(i==imax){
      u_new[i]=0.;
    }else{
      u_new[i]=(1.-r)*u[i]+r*u[i-1];
    }
  }
  return;
}

//Update simulated values
void update_value(double *u_new, double *u, int imax){
  int i;
  for(i=1; i<=imax; i++){
    u[i]=u_new[i];
  }
}
