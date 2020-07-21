#include"Header.h"
using namespace std;
int main()
{
cx_mat * Oascend0=new cx_mat[N0];
cx_mat * Oascend1=new cx_mat[5];
//cx_mat * Oascend2=new cx_mat[int(N0/9)];
cx_mat * Oascend2=new cx_mat[1];

cx_mat * Isometry0=new cx_mat[N0];
cx_mat * Isometry1=new cx_mat[2];

cx_mat * Uni0=new cx_mat[N0];
cx_mat * Uni1=new cx_mat[1];

cx_mat * Env=new cx_mat[1];
cx_mat * EnvU=new cx_mat[1];
cx_mat * EnvIso=new cx_mat[2];

cx_mat * Rho0=new cx_mat[N0];
cx_mat * Rho1=new cx_mat[int(N0)-1];
//cx_mat * Rho2=new cx_mat[int(N0/9)];
cx_mat * Rho2=new cx_mat[1];
vec time;
vec Ent_t;
vec Ent_f;
Ent_f.zeros(1000);


cx_mat U;
cx_mat V;
vec s;
cx_mat ham;
cx_mat eigvec;
cx_mat eigvec1;
vec eigval;
vec eigval1;
double Gamma=1;
double E1,E2;
double NormReal;
cx_mat DX;
int Count;
int BreakWhile=1;
cx_mat Unih;
cx_mat IsoLh;
cx_mat IsoRh;
cx_mat Z;

//cx_mat * RhoFidel=new cx_mat[Lay];
//cx_mat * RhoFidelp=new cx_mat[Lay];
//
double J=CouplingJ;
double traceH2=0;
cx_mat * Oout=new cx_mat[1];

ofstream Energy;
Energy.open("Files/Energy.text");

ofstream Ent;
Ent.open("Files/Ent.text");

vec * Checker=new vec[1];
Checker[0].zeros(4);
Checker[0](1)=2200.594;



//UniInitial(Uni0,Uni1,Isometry0,Isometry1);
//OInitial(Oascend0,Oascend1,J, traceH2);
//cout<< traceH2;
vec Xlvec;
Xlvec.zeros(6);
Xlvec(0)=Xi1[0];
Xlvec(1)=Xi1[1];
Xlvec(2)=Xi1[2];
Xlvec(3)=Xi1[3];
Xlvec(4)=Xi1[4];
Xlvec(5)=Xi1[5];

int NumInter=1;
int NumIso=0;
int NumUni=0;
int BoundryRight=1;
int BoundryLeft=1;
int NumInterLeft=0;
int NumInterRight=4;
int NumRhoup=0;
int NumRhodown=1;
int NumRhoLeft=0;
int NumRhoRight=4;
int w;

//UniInitial(Uni0,Uni1,Isometry0,Isometry1);

w=1;
for(int qq=0;qq<=TotallRepeat;qq++){
cout<<"qq="<<qq;

UniInitial(Uni0,Uni1,Isometry0,Isometry1);
OInitial(Oascend0,Oascend1,J, traceH2);

for(int qp=0;qp<=w;qp++){

/*************************************Left*****************************************/
for(int i=0;i<=20;i++){
Ascen(Oascend1,Uni1,Isometry1,NumInter,NumIso,NumUni,BoundryRight,BoundryLeft,NumInterLeft,NumInterRight,Xlvec,Oout);
Rho2[0]=Oout[0];

EnvIsoLeft(Oascend1,Rho2, Uni1, Isometry1,NumInter,NumRhoup,NumIso,NumUni,BoundryRight,BoundryLeft,
NumInterLeft,NumInterRight,Xlvec,Oout);
E1=abs(trace(Oout[0]*Isometry1[NumIso]));

if(E1>E2 || i==0){
IsoLh=Isometry1[NumIso];
E2=E1;}else{
Isometry1[NumIso]=IsoLh;
//cout<<"NotOptimized2="<<i<<endl;
break;
}

svd_econ(U, s, V, Oout[0],'b',"std");
Isometry1[NumIso]=V*trans(U);
}

Ascen(Oascend1,Uni1,Isometry1,NumInter,NumIso,NumUni,BoundryRight,BoundryLeft,NumInterLeft,NumInterRight,Xlvec,Oout);
//cout<<"E2="<<abs((trace(Oout[0]*strans(Oout[0])))*(1.00/pow(2,N0)))<<endl;
/************************************************************************/


/***********************************Uni**************************************************/
for(int i=0;i<=20;i++){
Ascen(Oascend1,Uni1,Isometry1,NumInter,NumIso,NumUni,BoundryRight,BoundryLeft,NumInterLeft,NumInterRight,Xlvec,Oout);
Rho2[0]=Oout[0];

EnvUni(Oascend1,Rho2, Uni1, Isometry1,NumInter,NumRhoup,NumIso,NumUni,BoundryRight,BoundryLeft,NumInterLeft,NumInterRight,
Xlvec,Oout);
E1=abs(trace(Oout[0]*Uni1[NumUni]));

if(E1>E2 || i==0){
Unih=Uni1[0];
E2=E1;}
else{
Uni1[0]=Unih;
//cout<<"NotOptimized1="<<i<<endl;
break;
}

svd_econ(U, s, V, Oout[0],'b',"std");
Uni1[0]=V*trans(U);
}

Ascen(Oascend1,Uni1,Isometry1,NumInter,NumIso,NumUni,BoundryRight,BoundryLeft,NumInterLeft,NumInterRight,Xlvec,Oout);
//cout<<"E1="<<setprecision(16)<<abs((trace(Oout[0]*strans(Oout[0])))*(1.00/pow(2,N0)))<<endl;



/*************************************Right*****************************************/
for(int i=0;i<=20;i++){
Ascen(Oascend1,Uni1,Isometry1,NumInter,NumIso,NumUni,BoundryRight,BoundryLeft,NumInterLeft,NumInterRight,Xlvec,Oout);
Rho2[0]=Oout[0];

EnvIsoRight(Oascend1,Rho2, Uni1, Isometry1,NumInter,NumRhoup,NumIso,NumUni,BoundryRight,BoundryLeft,
NumInterLeft,NumInterRight,Xlvec,Oout);
E1=abs(trace(Oout[0]*Isometry1[NumIso+1]));


if(E1>E2 || i==0){
IsoRh=Isometry1[NumIso+1];
E2=E1;}else{
Isometry1[NumIso+1]=IsoRh;
//cout<<"NotOptimized3="<<i<<endl;
break;
}

svd_econ(U, s, V, Oout[0],'b',"std");
Isometry1[NumIso+1]=V*trans(U);
}

Ascen(Oascend1,Uni1,Isometry1,NumInter,NumIso,NumUni,BoundryRight,BoundryLeft,NumInterLeft,NumInterRight,Xlvec,Oout);
//cout<<"E3="<<abs((trace(Oout[0]*strans(Oout[0])))*(1.00/pow(2,N0)))<<endl;
cout<<"Acc="<<traceH2
-abs((trace(Oout[0]*strans(Oout[0])))*(1.00/pow(2,N0)))<<endl;



Checker[0](0)=Checker[0](1);
Checker[0](1)=traceH2-abs((trace(Oout[0]*strans(Oout[0])))*(1.00/pow(2,N0)));


if(abs(Checker[0](0))>0.000001){
if( (((abs(Checker[0](0)-Checker[0](1)))/(abs(Checker[0](0))))< Accuracy) && (qp==w) )
;
else if(qp==w)
w=w+1;
}else{
if( (abs(Checker[0](0)-Checker[0](1))< 0.00000000001) && (qp==w) )
;
else if(qp==w)
w=w+1;
}

if(qp>80){
cout<<"Num > 40:";
break;
}
}

cout<<endl<<"TotalIteration="<<w<<endl;


double t=0;
complex<double> sum;
complex<double> img(0,1);

cx_mat Ohelp;
cx_mat Ohelp1;
cx_mat Ohelp2;
cx_mat Ohelp3;
cx_mat Ohelp4;
cx_mat U_t;
cx_mat D_t;

cx_vec sigma;
int X0=Xlvec(0);
int X1=Xlvec(1);
int X2=Xlvec(2);
int X2b=Xlvec(3);
int X3=Xlvec(4);
int X4=Xlvec(5);
sigma.zeros(32*32);

time.zeros(1000);
Ent_t.zeros(1000);
//cout<<"hi0";
t=0;
for(int q=0;q<1000;q++){
if((q>=0) && (q<20))
t=t+0.02;
if((q>=20) && (q<40))
t=t+0.02;
if((q>=40) && (q<60))
t=t+0.02;
if((q>=60) && (q<80))
t=t+0.02;
if((q>=80) && (q<1000))
t=t+0.02;

time(q)=t;
Ohelp.zeros(X3*X4*X2b,X3*X4*X2b);
for(int g=0;g<X3*X4*X2b;g++)
for(int gp=0;gp<X3*X4*X2b;gp++){sum=0;
for(int z=0;z<X2;z++)
for(int zp=0;zp<X2b;zp++)
sum=sum+Isometry1[0](0*X2*X1+0*X2+z,g)*Isometry1[1](zp*X4*X3+0*X4+0,gp)*Uni1[0](0*32+1*16+1*8+0*4+0*2+0,z*X2b+zp);
Ohelp(g,gp)=conj(sum);
//cout<<sum<<endl;
}

Ohelp4.zeros(X3*X4*X2b,X3*X4*X2b);
for(int i=0;i<X3*X4*X2b;i++)
for(int j=0;j<X3*X4*X2b;j++)
Ohelp4(i,j)=exp(+t*img*Oout[0](i,j))*Ohelp(i,j);

Ohelp.zeros(X3*X4*X2b,X3*X4*X2b);

for(int gp=0;gp<X3*X4*X2b;gp++)
for(int x=0;x<X0;x++)
for(int v=0;v<X1;v++)
for(int z=0;z<X2;z++){sum=0;
for(int g=0;g<X3*X4*X2b;g++)
sum=sum+Isometry1[0](x*X1*X2+v*X2+z,g)*Ohelp4(g,gp);
Ohelp(x*X1*X2+v*X2+z,gp)=sum;
}


Ohelp3.zeros(X3*X4*X2b,X3*X4*X2b);
for(int x=0;x<X0;x++)
for(int v=0;v<X1;v++)
for(int z=0;z<X2;z++)
for(int xb=0;xb<X2b;xb++)
for(int vb=0;vb<X3;vb++)
for(int zb=0;zb<X4;zb++){sum=0;
for(int gp=0;gp<X3*X4*X2b;gp++)
sum=sum+Isometry1[1](xb*X4*X3+vb*X4+zb,gp)*Ohelp(x*X1*X2+v*X2+z,gp);
Ohelp3(x*X1*X2+v*X2+z,xb*X4*X3+vb*X4+zb)=sum;
}

Ohelp2.zeros(X0*X1*X2*X4*X3*X2b,1);
for(int c=0;c<X0;c++)
for(int v=0;v<X1;v++)
for(int s=0;s<X2;s++)
for(int b=0;b<X2b;b++)
for(int vb=0;vb<X3;vb++)
for(int zb=0;zb<X4;zb++){sum=0;
for(int m=0;m<X2;m++)
for(int x=0;x<X2b;x++)
sum=sum+Ohelp3(c*X1*X2+v*X2+m,x*X4*X3+vb*X4+zb)*Uni1[0](s*X2b+b,m*X2b+x);
Ohelp2(c*X1*X2*X4*X3*X2b+v*X2*X4*X3*X2b+s*X4*X3*X2b+b*X4*X3+vb*X4+zb,0)=sum;
}

Ohelp.zeros(X1*X2*X0,X1*X2b*X0);
for(int g=0;g<X0;g++)
for(int n=0;n<X1;n++)
for(int sb=0;sb<X2b;sb++)
for(int c=0;c<X0;c++)
for(int v=0;v<X1;v++)
for(int s=0;s<X2;s++){sum=0;
for(int vb=0;vb<X3;vb++)
for(int zb=0;zb<X4;zb++)
for(int b=0;b<X2b;b++)
sum=sum+Ohelp2(c*X1*X2*X4*X3*X2b+v*X2*X4*X3*X2b+s*X4*X3*X2b+b*X4*X3+vb*X4+zb)*conj(Ohelp2(g*X1*X2*X4*X3*X2b+n*X2*X4*X3*X2b+sb*X4*X3*X2b+b*X4*X3+vb*X4+zb));
Ohelp(g*X1*X2+n*X2+sb,c*X1*X2+v*X2+s)=sum;
}
eig_sym(eigval, eigvec, Ohelp,"std");
sum=0;
for(int i=0;i<X1*X2*X0;i++){
if(eigval(i)>0.00000000000001)
sum=(-eigval(i)*(   (log(eigval(i)))/log(2)   ))+sum;
}
Ent_t(q)=real(sum);
}

Ent_f=Ent_f+Ent_t;
cout<<Ent_f*(1.0/(qq+1))<<endl;

for(int i=0;i<1000;i++)
Ent<<time(i)<<"  "<<Ent_f(i)*(1.0/(qq+1))<<endl;
Ent<<endl<<endl;

}


return 0;
}





