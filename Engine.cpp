//---------------------------------------------------------------------------
#include "Engine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void ClearCanvas(TCanvas *Canvas, TColor color)
{
 Canvas->Stroke->Color = color;
 Canvas->Fill->Color = color;
 Canvas->FillRect(
 TRectF(0, 0, Canvas->Width, Canvas->Height), 0, 0, AllCorners, 0xFF);
}
//---------------------------------------------------------------------------
