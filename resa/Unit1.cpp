//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

const double c=300000000; //скорость света
const double Aeff=50*pow(10,(-12));  //эффективная площадь оптического волокна
const double n=2.68*pow(10,(-20)); //коэффициент нелинейности показателя приломления
const double dkd=80000; //производная дисперсии ОВ
const double h=6.626*pow(10,(-34)); //постоянная планка
//const double e=1.602*pow(10,(-19)); //заряд электрона
//const double eta=0.8; //квантовая эффективность фотоприемника
const double nsp=1.4;
const double pi=3.14;

//temp
double alfa=0.2*0.115; //коэф затухания
//int numb=16; //колво оптических каналов
//int m=numb/2; //канал под влиянием
double L=100; //длина волокна
double dk=0.017;
double f0=12.5*pow(10,9);
//double fe=7*pow(10,9);
//double* Pin=new double[numb];
//double* lamb_mat=new double[numb];
//double* fkan=new double[numb];


double G=1/exp(alfa*L*(-1));

double pase;

double paseinp(int nus)
{
return pase*(nus+1);
}


double popt(int nus,double* &l,double* &f,int p)
{


double gam=(2*pi*n)/((c/f[p/2])*Aeff);
return pow(((9*paseinp(nus))/
(((c*c*alfa*alfa)/(pow((2*pi*l[p/2]*l[p/2]*dk),2)*pow((f[1]-f[0]),4)))
*
(1+(4*exp(alfa*L*(-1))*0.7*0.7)/pow((1-exp(alfa*L*(-1))),2))
*
(1/9.)*(gam*gam)*exp(alfa*L*(-1))*pow((((1-exp(alfa*L*(-1)))*1000)/alfa),2)
*
(1/pow(p,0.2))*log10(p)*190*1.12*G*(nus+1)
)),(1/3.));
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
//double m=
for(int numb=4;numb<=64;numb++)

{
double* lamb_mat=new double[numb];
double* fkan=new double[numb];
for(int i=0;i<numb;i++)
        {
        lamb_mat[i]=(1550+0.8*i)*pow(10,(-9));
        fkan[i]=c/lamb_mat[i];
        }
pase=(2*nsp*(G-1)*h*fkan[numb/2]*f0);
Series1->Add(10*log10(popt(1000000,lamb_mat,fkan,numb)*1000),numb);
delete [] fkan;
delete [] lamb_mat;
}


}
//---------------------------------------------------------------------------
