//----------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include "LMDCustomComponent.hpp"
#include "LMDCustomFormFill.hpp"
#include "LMDFormFill.hpp"
#include "LMDWndProcComponent.hpp"
#include "LMDBaseControl.hpp"
#include "LMDBaseGraphicControl.hpp"
#include "LMDBaseLabel.hpp"
#include "LMDControl.hpp"
#include "LMDCustomDockLabel.hpp"
#include "LMDCustomSimpleLabel.hpp"
#include "LMDDockLabel.hpp"
#include "LMDGraphicControl.hpp"
#include "LMDScrollText.hpp"
#include "LMDCustomGlyphLabel.hpp"
#include "LMDGlyphLabel.hpp"
//----------------------------------------------------------------------------
class TAboutBox : public TForm
{
__published:
        TLMDFormFill *LMDFormFill1;
        TLMDDockLabel *LMDDockLabel3;
        TLMDDockLabel *LMDDockLabel4;
        TTimer *Timer1;
        TLMDGlyphLabel *NLicense;
        TLMDGlyphLabel *MHistory;
        TTimer *Timer2;
        TLMDGlyphLabel *MUsed;
        TTimer *Timer3;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall Timer3Timer(TObject *Sender);
private:
public:
	virtual __fastcall TAboutBox(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAboutBox *AboutBox;
//----------------------------------------------------------------------------
#endif    
