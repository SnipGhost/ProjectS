//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "main.h"
#include "inifiles.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TLayer *Layer;
TIniFile *Ini;
//---------------------------------------------------------------------------
SCircle *Planet;
//---------------------------------------------------------------------------
__fastcall TLayer::TLayer(TComponent* Owner): TForm(Owner)
{
 OpenDialog1->FileName = GetCurrentDir() + "\\data\\templates\\system01.s.ini";
 UnicodeString File = OpenDialog1->FileName;
 CheckFileName(File);
 Label1->Text = File;
}
//---------------------------------------------------------------------------
void TLayer::CheckFileName(UnicodeString &F)
{
 if (F.Length() > 62)
 {
  F.Delete(29, F.Length()-29*2);
  F.Insert("...", 29);
 }
}
//---------------------------------------------------------------------------
void __fastcall TLayer::Button1Click(TObject *Sender)
{
 SetDir(true);
 Ini = new TIniFile(OpenDialog1->FileName);
 World.C = StrToInt(Ini->ReadString("World", "C", "0"));
 World.G = StrToFloat(Ini->ReadString("World", "G", "6,67384"));
 World.P = StrToFloat(Ini->ReadString("World", "P", "10"));
 World.T = StrToInt(Ini->ReadString("World", "T", "1"));
 World.B = StrToBool(Ini->ReadString("World", "B", "true"));
 World.Color = StringToColor(Ini->ReadString("World", "Color", "0xFF000000"));
 Timer1->Interval = StrToInt(Ini->ReadString("World", "I", "50"));
 Planet = new SCircle[World.C+1];
 for (int i = 1; i <= World.C; i++)
 {
  Planet[i].name = Ini->ReadString("Obj"+IntToStr(i), "name", "Unknown");
  Planet[i].x = StrToFloat(Ini->ReadString("Obj"+IntToStr(i), "x", "0"));
  Planet[i].y = StrToFloat(Ini->ReadString("Obj"+IntToStr(i), "y", "0"));
  Planet[i].vx = StrToFloat(Ini->ReadString("Obj"+IntToStr(i), "vx", "0"));
  Planet[i].vy = StrToFloat(Ini->ReadString("Obj"+IntToStr(i), "vy", "0"));
  Planet[i].mass = StrToFloat(Ini->ReadString("Obj"+IntToStr(i), "mass", "1"));
  Planet[i].radius = StrToFloat(Ini->ReadString("Obj"+IntToStr(i), "radius", "1"));
  Planet[i].color = StringToColor(Ini->ReadString("Obj"+IntToStr(i), "color", "0xFF000000"));
  UnicodeString s = Ini->ReadString("Obj"+IntToStr(i), "interacts", "0");
  while (s.Length() > 0)
  {
   UnicodeString a = s[1];
   if (a != "0") { Planet[i].inter.push_back(&Planet[StrToInt(a)]); }
   s.Delete(1, 1);
  }
 }
 Panel->Visible = false;
 Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TLayer::Timer1Timer(TObject *Sender)
{
 Canvas->BeginScene();
 if (World.B) ClearCanvas(Canvas, World.Color);
 for (int i = 1; i <= World.C; i++)
 {
  Planet[i].Interact(World);
  Planet[i].Move(World);
  Planet[i].Draw(Canvas);
 }
 Canvas->EndScene();
}
//---------------------------------------------------------------------------
void __fastcall TLayer::Button2Click(TObject *Sender)
{
 if (OpenDialog1->Execute())
 {
  UnicodeString File = OpenDialog1->FileName;
  CheckFileName(File);
  Label1->Text = File;
 }
}
//---------------------------------------------------------------------------
void __fastcall TLayer::FormClose(TObject *Sender, TCloseAction &Action)
{
 delete Ini;
 exit(0);
}
//---------------------------------------------------------------------------
