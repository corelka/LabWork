//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <string>
#include "math.h"
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
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
const double e=1.602*pow(10,(-19)); //заряд электрона
const double eta=0.8; //квантовая эффективность фотоприемника
const double nsp=1.4;
const double pi=3.14;

//temp
double alfa=0.2*0.115; //коэф затухания
int numb=16; //колво оптических каналов
int m=numb/2; //канал под влиянием
double L=100; //длина волокна
double dk=0.017;
double f0=12.5*pow(10,9);
double fe=7*pow(10,9);
int nus;



double pijk(double pi, double pj, double pk, double fi, double fj, double fk, double D)
{
double lambk=c/fk;
double gam=(2*pi*n)/(lambk*Aeff);
double b=((2*pi*lambk*lambk)/c)*fabs(fi-fk)*fabs(fj-fk)*(dk+(((lambk*lambk)/(2*c))*(fabs(fi-fk)+fabs(fj-fk))*dkd));
double at=((alfa*alfa)/((alfa*alfa)+(b*b)))*(1+((4*exp(alfa*L*(-1))*pow(sin((b*L)/2),2))/pow((1-exp(alfa*L*(-1))),2)));
double res=(at*D*D*gam*gam*pi*pj*pk*exp(alfa*L*(-1))*pow((((1-exp(alfa*L*(-1)))*1000)/alfa),2))/9;
return res;
}

double pfwmsum(double pinik,double* &sd)
{
double pfwm=0;
for(int i=1;i<=numb;i++)
        for (int j=i;j<=numb;j++)
                {
                int k=i+j-m;
                if ((k==i)||(k==j)||(k<1)||(k>numb))k=0;
                double D;
                if (i==j)D=3;
                        else D=6;
                if (k!=0)
                        pfwm+=pijk(pinik,pinik,pinik,sd[i-1],sd[j-1],sd[k-1],D);
                }
return pfwm;
}

double bm;


double G=1/exp(alfa*L*(-1));

double pase;

double paseinp(int nus)
{
return pase*(nus+1);
}

double paseaft(double pinik,int nus)
{
return 4*bm*bm*pinik*paseinp(nus)*(fe/f0);
}

double pfwmsinp(double pinik, int nus, double* &sd)
{double res=G*pfwmsum(pinik,sd)*(nus+1);
return  res;
}

double pfwmsaft(double pinik,int nus,double* &sd)
{double res=2*bm*bm*pinik*pfwmsinp(pinik,nus,sd)/8;
return res;
}

double q(double pinik, int nus, double* &sd)
{double res=(bm*pinik)/sqrt(paseaft(pinik,nus)+pfwmsaft(pinik,nus,sd));
return res;
}


double popt(int nus, int p, double pin)
{


double* l=new double[p];
double* f=new double[p];
for(int i=0;i<p;i++)
        {
        l[i]=(1550+0.8*i)*pow(10,(-9));
        f[i]=c/l[i];
        }

double gam=(2*pi*n)/((c/f[p/2])*Aeff);
double res=pow(((9*((2*nsp*(G-1)*h*f[p/2]*f0)*(nus+1)))/
(((c*c*alfa*alfa)/(pow((2*pi*l[p/2]*l[p/2]*dk),2)*pow((f[1]-f[0]),4)))
*
(1+(4*exp(pin*(-1))*0.7*0.7)/pow((1-exp(pin*(-1))),2))
*
(1/9.)*(gam*gam)*exp(pin*(-1))*pow((((1-exp(pin*(-1)))*1000)/alfa),2)
*
(1/pow(p,0.2))*log10(p)*190*1.12*G*(nus+1)
)),(1/3.));

delete [] l;
delete [] f;
return res;
}



String dotch(String l)
{
while (l!="" && l[1]==' ')
        l.Delete(1,1);

for(int i=1;i<=l.Length();i++)
        if(l[i]=='.')l[i]=',';
return l;
}








class triangle
{
private:
TLabel* k;
TLabel* b;
public:
triangle()
{}
triangle(int a,int l,TImage* &m)
{
m->Canvas->Pen->Style=psSolid;
m->Canvas->MoveTo(a-25,156);
m->Canvas->LineTo(a-25,220);
m->Canvas->LineTo(a+25,188);
m->Canvas->LineTo(a-25,156);
k=new TLabel(Form2);
k->Parent=Form2;
k->Top=173;
k->Left=a-20;
k->Caption="G";
k->Font->Size=20;
k->Font->Color=clBlack;
k->Visible=true;
k->Show();
b=new TLabel(Form2);
b->Parent=Form2;
b->Top=140;
b->Left=a-5;
b->Caption=IntToStr(l);
b->Font->Size=15;
b->Font->Color=clBlack;
b->Visible=true;
b->Show();
}
void conn(int a,int h,TImage* &m)
{
m->Canvas->MoveTo(a+25,188);
m->Canvas->LineTo(a+h-25,188);
}
void dele()
{if (k,b)
       {
       delete k;
       delete b;
       }
}
};

void strelka(int a, TImage* &m)
{
m->Canvas->MoveTo(a,150);
m->Canvas->LineTo(a+52,150);
m->Canvas->LineTo(a+45,144);
m->Canvas->MoveTo(a+52,150);
m->Canvas->LineTo(a+45,156);
m->Canvas->MoveTo(a,150);
m->Canvas->LineTo(a-52,150);
m->Canvas->LineTo(a-45,144);
m->Canvas->MoveTo(a-52,150);
m->Canvas->LineTo(a-45,156);
}
void strela(TImage* &m)
{
m->Canvas->Ellipse(0,0,57,57);
m->Canvas->MoveTo(28-15,28+15);
m->Canvas->LineTo(28,28-20);
m->Canvas->LineTo(28,28-10);
m->Canvas->MoveTo(28,28-20);
m->Canvas->LineTo(28-8,28-12);
m->Canvas->MoveTo(28,28+20);
m->Canvas->LineTo(28+15,28-15);
m->Canvas->LineTo(28+15,28-5);
m->Canvas->MoveTo(28+15,28-15);
m->Canvas->LineTo(28+7,28-7);
}

bool isint(String l)
{bool t=true;
for(int i=1;i<=l.Length();i++)
        if(l[i]<'0' || l[i]>'9')t=false;
return t;
}

bool isfloat(String l)
{bool t=true;
int dc=1;
for(int i=1;i<=l.Length();i++)
        {
        if(dc!=0 && (l[i]=='.' || l[i]==',')){dc=0;continue;}
        if(l[i]<'0' || l[i]>'9')t=false;
        }
return t;
}





void __fastcall TForm1::FormCreate(TObject *Sender)
{
Edit1->Text="";
Edit2->Text="";
Edit3->Text="";
Edit4->Text="";
Edit5->Text="";
Edit6->Text="";
Edit7->Text="";

Label9->Caption="x Transmission Rate";
Label10->Caption="x Transmission Rate";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit8Exit(TObject *Sender)
{
String t=Edit8->Text;
if (t.Length()>9)t.SetLength(9);
if (t!="")
{
while (t!="" && t[1]==' ')
        t.Delete(1,1);

if (isfloat(t) && t!="")
{
if (ComboBox1->Text=="Русский")
{
Label9->Caption="x "+t+" Гбит/с";
Label10->Caption="x "+t+" Гбит/с";
}
else
{
Label9->Caption="x "+t+" Gbit/s";
Label10->Caption="x "+t+" Gbit/s";
}
}
else if(t!="")
{
if (ComboBox1->Text=="Русский")
{
Label9->Caption="Ошибочка...";
Label10->Caption="...и опять...";
}
else
{
Label9->Caption="lol..There is an error...";
Label10->Caption="and another one...";
}
}
}
else
{
if (ComboBox1->Text=="Русский")
{
Label9->Caption="x Скорость пер.";
Label10->Caption="x Скорость пер.";
}
else
{
Label9->Caption="x Transmission Rate";
Label10->Caption="x Transmission Rate";
}
}
}
//---------------------------------------------------------------------------




void __fastcall TForm1::ComboBox1Select(TObject *Sender)
{
if (ComboBox1->Text=="Русский")
{
Image4->Picture->LoadFromFile(GetCurrentDir()+"\\design\\scheme_ru.jpg");
Image5->Picture->LoadFromFile(GetCurrentDir()+"\\design\\show_the_graph_ru.jpg");

Form1->Caption="Главная";
Form2->Caption="Схема";
Form3->Caption="Графики";
Form4->Caption="Помощь";

Label1->Caption="Коэффициент затухания:";
Label2->Caption="Количество опт. каналов:";
Label3->Caption="Длинна волокна:";
Label4->Caption="Дисперсия оптоволокна:";
Label5->Caption="Полоса частот оптоволокна:";
Label6->Caption="Полоса частот эл. усилителя:";
Label7->Caption="Количество усилителей:";
Label8->Caption="Скорость передачи:";

Label11->Caption="дБ/км";
Label12->Caption="км";
Label13->Caption="Гбит/с";
Label14->Caption="пс/(нм*км)";
Label15->Caption="шт.";
Label16->Caption="шт.";

Label17->Caption="Межканальный интервал:";
//Button1->Caption="Построить графики";
//Button2->Caption="Показать схему";
//Button3->Caption="Помощь";
//Button4->Caption="Выход";
Form2->StaticText1->Caption="ПОМ";
Form2->StaticText1->Font->Size=17;
Form2->StaticText2->Caption="ПРОМ";
Form2->StaticText2->Font->Size=17;

Chart1->Title->Text->Clear();
Chart1->Title->Text->Add("Количество нелинейных продуктов");

Form3->Chart1->Title->Text->Clear();
Form3->Chart1->Title->Text->Add("Влияние уровня передачи на Q-фактор");

Form3->Chart2->Title->Text->Clear();
Form3->Chart2->Title->Text->Add("Влияние уровня передачи на уроаень помех ЧВС");
Form3->Chart2->Title->Text->Add("и усиленного спонтанного излучения");

Form3->Chart3->Title->Text->Clear();
Form3->Chart3->Title->Text->Add("Зависимость оптимального уровня передачи от");
Form3->Chart3->Title->Text->Add("количества каналов системы WDM");

Form3->Chart4->Title->Text->Clear();
Form3->Chart4->Title->Text->Add("Зависимость оптимального уровня передачи от");
Form3->Chart4->Title->Text->Add("затухания оптического волокна");
}
if (ComboBox1->Text=="English")
{
Image4->Picture->LoadFromFile(GetCurrentDir()+"\\design\\scheme.jpg");
Image5->Picture->LoadFromFile(GetCurrentDir()+"\\design\\show_the_graph.jpg");

Form1->Caption="Main";
Form2->Caption="Block diagram";
Form3->Caption="Graph";
Form4->Caption="Help";
Label1->Caption="Attenuation coefficient of cabel:";
Label2->Caption="Number of optical channels:";
Label3->Caption="Lenght of fiber:";
Label4->Caption="Dispertion of Optical Fiber:";
Label5->Caption="Bandwidth of optical filter:";
Label6->Caption="Bandwidth of elecrical amplifier:";
Label7->Caption="Number of amplifires:";
Label8->Caption="Transmission Rate:";

Label11->Caption="dB/km";
Label12->Caption="km";
Label13->Caption="Gbit/s";
Label14->Caption="ps/(nm*km)";
Label15->Caption="un.";
Label16->Caption="un.";

Label17->Caption="Inter-channel spacing:"     ;
//Button1->Caption="Build the graph";
//Button2->Caption="Draw diagram";
//Button3->Caption="Help";
//Button4->Caption="Exit";
Form2->StaticText1->Caption="TOM";
Form2->StaticText1->Font->Size=22;
Form2->StaticText2->Font->Size=22;
Form2->StaticText2->Caption="ROM";

Chart1->Title->Text->Clear();
Chart1->Title->Text->Add("Calculated amount of Nonlinear Products");

Form3->Chart1->Title->Text->Clear();
Form3->Chart1->Title->Text->Add("Influence of transmission level on Q-factor");

Form3->Chart2->Title->Text->Clear();
Form3->Chart2->Title->Text->Add("Influence of the transmission level on noise level of FWM and");
Form3->Chart2->Title->Text->Add("amplified spontaneous emission");

Form3->Chart3->Title->Text->Clear();
Form3->Chart3->Title->Text->Add("The dependence of the optimum level of transmission signal");
Form3->Chart3->Title->Text->Add("on the number of WDM system channels");

Form3->Chart4->Title->Text->Clear();
Form3->Chart4->Title->Text->Add("The dependence of the optimum level of transmission signal");
Form3->Chart4->Title->Text->Add("on the optical fiber attenuation");
}
TForm1::Edit8Exit(Form1);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Image2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
Image2->Picture->LoadFromFile(GetCurrentDir()+"\\design\\help_active.jpg");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image2MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
Image2->Picture->LoadFromFile(GetCurrentDir()+"\\design\\help.jpg");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image2Click(TObject *Sender)
{
wchar_t URL[100];
if (ComboBox1->Text=="Русский")
AnsiString(GetCurrentDir()+"\\hint.pdf").WideChar(URL,100);
else
AnsiString(GetCurrentDir()+"\\hint_eng.pdf").WideChar(URL,100);
Form4->CppWebBrowser1->Navigate(URL,0,NULL,NULL,NULL);
Form4->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
Image3->Picture->LoadFromFile(GetCurrentDir()+"\\design\\exit_active.jpg");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Image3MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
Image3->Picture->LoadFromFile(GetCurrentDir()+"\\design\\exit.jpg");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image3Click(TObject *Sender)
{
Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image4MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (ComboBox1->Text=="English")
Image4->Picture->LoadFromFile(GetCurrentDir()+"\\design\\scheme_active.jpg");
else
Image4->Picture->LoadFromFile(GetCurrentDir()+"\\design\\scheme_active_ru.jpg");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image4MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if (ComboBox1->Text=="English")
Image4->Picture->LoadFromFile(GetCurrentDir()+"\\design\\scheme.jpg");
else
Image4->Picture->LoadFromFile(GetCurrentDir()+"\\design\\scheme_ru.jpg");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image4Click(TObject *Sender)
{

Form2->Image1->Picture->Bitmap=NULL;
try
{
alfa=StrToFloat(dotch(Edit1->Text));
numb=StrToFloat(dotch(Edit2->Text));
m=numb/2;
L=StrToFloat(dotch(Edit3->Text));
dk=StrToFloat(dotch(Edit4->Text));
f0=StrToFloat(dotch(Edit5->Text));
fe=StrToFloat(dotch(Edit6->Text));
nus=StrToFloat(Edit7->Text);
if (nus<1)throw 20;
}
catch (...)
{
ShowMessage("Wrong input data!");
return;
}

if(nus>10)
        {
        ShowMessage("So many amplifiers...");
        return;
        }

int nj=nus;
int a=0;
int h=0;
triangle m(950,nj+1,Form2->Image1);
bool mt7=false;
if(nj>7)
        {
        nj=2;
        mt7=true;
        }
a=240+500/(2*nj);
h=500/nj;
triangle *mass=new triangle[nj];
for (int i=0;i<nj;i++)
        {
        if (mt7==true)
        {
        if(i==1)mass[i]=triangle(a+h*i,nus,Form2->Image1);
        else
        {
        mass[i]=triangle(a+h*i,i+1,Form2->Image1);
        Form2->Label6->Left=a+h*i;
        Form2->Label7->Left=a+h*i;
        Form2->Label8->Left=a+h*i;
        }

        Form2->Image1->Canvas->Pen->Style=psDash;
        mass[i].conn(a+h*i,h,Form2->Image1);
        }
        else
        {
        if(i==0)
        {Form2->Label6->Left=a+h*i;Form2->Label7->Left=a+h*i;Form2->Label8->Left=a+h*i;}
        mass[i]=triangle(a+h*i,i+1,Form2->Image1);
        if((i+1)!=nj)
        mass[i].conn(a+h*i,h,Form2->Image1);
        }
        }
Form2->Image1->Canvas->Pen->Style=psSolid;
Form2->Image1->Canvas->MoveTo(97,188);
Form2->Image1->Canvas->LineTo(a-25,188);
Form2->Image1->Canvas->MoveTo(a+h*(nj-1)+25,188);
Form2->Image1->Canvas->LineTo(950-25,188);
Form2->Image1->Canvas->MoveTo(950+25,188);
Form2->Image1->Canvas->LineTo(1000,188);
strelka(172,Form2->Image1);
strelka(820,Form2->Image1);
strela(Form2->Image2);
strela(Form2->Image3);
Form2->Image1->Canvas->Pen->Style=psDash;
Form2->Image1->Canvas->MoveTo(896,120);
Form2->Image1->Canvas->LineTo(896,257);
Form2->Image1->Canvas->LineTo(1089,257);
Form2->Image1->Canvas->LineTo(1089,120);
Form2->Image1->Canvas->LineTo(896,120);
Form2->Label1->Caption=FloatToStr(L)+" km";
Form2->Label2->Caption=FloatToStr(L)+" km";

Form1->Series1->Clear();
Chart1->BottomAxis->Maximum=numb+1;

int *p=new int [numb];
for(int i=0;i<numb;i++)
p[i]=0;
for(int i=1;i<=numb;i++)
        for(int j=1;j<=numb;j++)
                for(int k=j;k<=numb;k++)
                        {
                        int s=j+k-i;
                        if (s>=1 && s<=numb && (s!=k && s!=j && j!=k))
                        p[i-1]+=1;
                        }
for(int i=0;i<numb;i++)
Series1->Add(p[i],i+1);
delete [] p;



Form1->Hide();
bool op=true;
if(Form3->Visible==true){op=false;Form3->Hide();}
Form2->ShowModal();
for (int i=0;i<nj;i++)
mass[i].dele();
m.dele();
if(op==false)Form3->Show();
Form1->Show();
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image5MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (ComboBox1->Text=="English")
Image5->Picture->LoadFromFile(GetCurrentDir()+"\\design\\show_the_graph_active.jpg");
else
Image5->Picture->LoadFromFile(GetCurrentDir()+"\\design\\show_the_graph_active_ru.jpg");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image5MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{if (ComboBox1->Text=="English")
Image5->Picture->LoadFromFile(GetCurrentDir()+"\\design\\show_the_graph.jpg");
else
Image5->Picture->LoadFromFile(GetCurrentDir()+"\\design\\show_the_graph_ru.jpg");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image5Click(TObject *Sender)
{
        Form3->Series1->Clear();
        Form3->Series2->Clear();
        Form3->Series3->Clear();
        Form3->Series4->Clear();
        Form3->Series5->Clear();
        Series1->Clear();
int rate;
try
{
alfa=StrToFloat(dotch(Edit1->Text));
if (alfa<0.1 || alfa>4)throw Exception("ex");
numb=StrToFloat(dotch(Edit2->Text));
if (numb<4 || numb >80)throw Exception("ex");
m=numb/2;
L=StrToFloat(dotch(Edit3->Text));
if (L<20 || L>200)throw Exception("ex");
dk=StrToFloat(dotch(Edit4->Text));
if (dk<2 || dk>20)throw Exception("ex");
f0=StrToFloat(dotch(Edit5->Text));
if (f0<0.1 || f0>5)throw Exception("ex");
fe=StrToFloat(dotch(Edit6->Text));
if (fe<0.1 || fe>20)throw Exception("ex");
nus=StrToFloat(Edit7->Text);
if (nus<1)throw Exception("ex");
rate=int(StrToFloat(dotch(Edit8->Text))*1000000000);
if (rate<0 || rate>10000000000)throw Exception("ex");
}
catch (...)
{
ShowMessage("Wrong input data!");
return;
}

dk*=0.001;
alfa*=0.115;
fe*=rate;
f0*=rate;

if(nus>10)
        {
        ShowMessage("So many amplifiers...");
        return;
        }



double* lamb_mat=new double[numb];
double* fkan=new double[numb];

for(int i=0;i<numb;i++)
        {
        lamb_mat[i]=(1550+0.8*i)*pow(10,(-9));
        fkan[i]=c/lamb_mat[i];
        }
bm=((eta*e)/(h*fkan[m]));
pase=(2*nsp*(G-1)*h*fkan[m]*f0);
double pink[65];
int k=-25;

for (int i=0;i<65;i++)
        {
        pink[i]=k;
        Form3->Series1->Add(q(pow(10,(0.1*pink[i]-3)),nus,fkan),pink[i],clRed);//в зависимости от кол-ва усилков
        Form3->Series2->Add(10*log10(paseaft(pow(10,(0.1*pink[i]-3)),0)*1000),pink[i],clRed);
        Form3->Series3->Add(10*log10(pfwmsaft(pow(10,(0.1*pink[i]-3)),0,fkan)*1000),pink[i]);
        k++;
        }


for (int nu=4;nu<=64;nu++)
        Form3->Series4->Add(10*log10(popt(0,nu,alfa*L)*1000),nu);
/*for (int pin=1;pin<=10;pin++)
        Form3->Series5->Add(10*log10(popt(0,numb,pin)*1000),pin);
*/
int y=ComboBox2->ItemIndex;
switch(y)
{
case 0: {for (int i=0;i<10;i++) Form3->Series5->Add((1.45*i-6.83),i);break;}
case 1: {for (int i=0;i<10;i++) Form3->Series5->Add((1.45*i-2.82),i);break;}
case 2: {for (int i=0;i<10;i++) Form3->Series5->Add((1.45*i+1.2),i);break;}
case 3: {for (int i=0;i<10;i++) Form3->Series5->Add((1.45*i+5.22),i);break;}
default: break;
}

Form3->Show();

delete [] lamb_mat;
delete [] fkan;


Chart1->BottomAxis->Maximum=numb+1;

int *m=new int [numb];
for(int i=0;i<numb;i++)
m[i]=0;
for(int i=1;i<=numb;i++)
        for(int j=1;j<=numb;j++)
                for(int k=j;k<=numb;k++)
                        {
                        int s=j+k-i;
                        if (s>=1 && s<=numb && (s!=k && s!=j && j!=k))
                        m[i-1]+=1;
                        }
for(int i=0;i<numb;i++)
Series1->Add(m[i],i+1);
delete [] m;
}
//---------------------------------------------------------------------------




