//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
#include <Xml.Win.msxmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <FMX.Colors.hpp>
#include <FMX.ListBox.hpp>
#include <System.UIConsts.hpp>
//---------------------------------------------------------------------------
#include "Engine.h"
#include <FMX.Menus.hpp>
#include <FMX.ExtCtrls.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.StdCtrls.hpp>
//---------------------------------------------------------------------------
class TLayer : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TCalloutPanel *Panel;
	TCornerButton *Button1;
	TCornerButton *Button2;
	TLabel *Label1;
	TOpenDialog *OpenDialog1;
	TLabel *Label2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TLayer(TComponent* Owner);
	AnsiString Dir;
	SWorld World;
	void CheckFileName(UnicodeString &F);
	void SetDir(bool TheDir)
	{if (TheDir) Dir = GetCurrentDir() + "\\data";}
};
//---------------------------------------------------------------------------
extern PACKAGE TLayer *Layer;
//---------------------------------------------------------------------------
#endif