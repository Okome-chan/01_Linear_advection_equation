
/*****************************************************************************/
//
//  finite_difference.cc
//  
//  ver 0.0.1   2020/12/14
//  developed by Yoneda
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
#include <unistd.h>

using namespace std;

int main(){

  int typ;          //simulation type (1: Backward, 2: Forward, 3: Center)
  int t;
  int tmax;         //time step
  int collumn;      //number of collumn
  double dt;        //dt
  double dx;        //dx
  double c;         //
  double r;         //Courant number
  double *u;        //u at time tn
  double *u_new;    //u at time tn+1
  FILE *fp;

  /**********************************/
  //Define values
  /**********************************/
  tmax=200;
  collumn=100;
  dx=0.5;
  dt=0.1;
  c=1;

  
  /**********************************/
  //Setting array
  /**********************************/
  u=(double *)malloc(sizeof(double)*collumn+1);
  u_new=(double *)malloc(sizeof(double)*collumn+1);

  /**********************************/
  //Define subroutine
  /**********************************/
  void initial_array(double *u,int collumn);
  void Backward(double *u_new, double *u, double r, int imax);
  void Forward(double *u_new, double *u, double r, int imax);
  void Center(double *u_new, double *u, double r, int imax);
  void update_value(double *u_new, double *u, int imax);
  void make_graph(double *u,double collumn,double dx,int t,FILE *fp);

  /**********************************/
  //set initial value
  /**********************************/
  initial_array(u,collumn);

  /**********************************/
  //select simulation type
  /**********************************/
  cout<<"1: Backward, 2: Forward, 3: Center"<<endl;
  cout<<"Please enter simulation type"<<endl;
  cin>>typ;

  /**********************************/
  // calculate Courant number
  /**********************************/
  r=c*dt/dx;
  t=0;
  make_graph(u,collumn,dx,t,fp);
  for(t=1; t<=tmax; t++){
    if(typ==1) Backward(u_new,u,r,collumn);
    if(typ==2) Forward(u_new,u,r,collumn);
    if(typ==3) Center(u_new,u,r,collumn);
    update_value(u_new,u,collumn);
    if(t%5==0) make_graph(u,collumn,dx,t,fp);
  }

  return 0;
}


//Initiallization of array
void initial_array(double *u,int collumn){
  int i;
  for(i=1;i<=collumn;i++){
    u[i]=0.;
  }
  for(i=11;i<=20;i++){
    u[i]=1.;
  }
  return;
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
      u_new[i]=u[i]-r*(u[i]-u[i-1]);
    }
  }
  return;
}

//Forward difference scheme
void Forward(double *u_new, double *u, double r, int imax){
  int i;
  for(i=1; i<imax; i++){
    //boundary condition
    if(i==1){
      u_new[i]=0.;
    }else if(i==imax){
      u_new[i]=0.;
    }else{
      u_new[i]=u[i]-r*(u[i+1]-u[i]);
    }
  }
  return;
}

//Center difference scheme
void Center(double *u_new, double *u, double r, int imax){
  int i;
  for(i=1; i<imax; i++){
    //boundary condition
    if(i==1){
      u_new[i]=0.;
    }else if(i==imax){
      u_new[i]=0.;
    }else{
      u_new[i]=u[i]-r/2.*(u[i+1]-u[i-1]);
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

//Make graph//
void make_graph(double *u,double collumn,double dx,int t,FILE *fp)
{
  int i;
  double x;
  char data_file[256];
  FILE *data;

  fp=popen("gnuplot -persist","w");
  fprintf(fp,"set terminal png size 400,400\n");
  fprintf(fp,"set output './output/%04d.tif'\n",t);
  fprintf(fp,"set xrange [0.0:50.0]\n");
  fprintf(fp,"set yrange [0.0:1.2]\n");
  //sleep(1);
  sprintf(data_file,"out.dat");
  data=fopen(data_file,"w");
  for(i=1;i<=collumn;i++){
    x=(double)i*dx;
    fprintf(data,"%f\t%f\n",x,u[i]);
  }
  fprintf(fp,"plot \"%s\" using 1:2 with lines title \"sim\"\n",data_file);
  fclose(data);
  fflush(fp);
  pclose(fp);

  return;
}
