//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit1.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image2Click(TObject *Sender)
{
Form1->Image2Click(Form3);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Image2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
Image2->Picture->LoadFromFile(GetCurrentDir()+"\\design\\help_active_gr.jpg");
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Image2MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
Image2->Picture->LoadFromFile(GetCurrentDir()+"\\design\\help_gr.jpg");
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Image3Click(TObject *Sender)
{
Form3->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Image3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
Image3->Picture->LoadFromFile(GetCurrentDir()+"\\design\\exit_active_gr.jpg");
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Image3MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
Image3->Picture->LoadFromFile(GetCurrentDir()+"\\design\\exit_gr.jpg");
}
//---------------------------------------------------------------------------
