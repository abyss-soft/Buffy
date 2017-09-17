//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include "LMDBaseControl.hpp"
#include "LMDBaseGraphicControl.hpp"
#include "LMDBaseLabel.hpp"
#include "LMDControl.hpp"
#include "LMDCustomSimpleLabel.hpp"
#include "LMDSimpleLabel.hpp"
#include "LMDButtonControl.hpp"
#include "LMDCheckBox.hpp"
#include "LMDCustomCheckBox.hpp"
#include "LMDCustomControl.hpp"
#include "LMDCustomPanel.hpp"
#include "LMDBrowseDlg.hpp"
#include "LMDCustomComponent.hpp"
#include <Dialogs.hpp>
#include "LMDOneInstance.hpp"
#include "LMDTrayIcon.hpp"
#include "LMDWndProcComponent.hpp"
#include "LMDGraphicControl.hpp"
#include "LMDScrollText.hpp"
#include <Graphics.hpp>
#include "LMDInformationLabel.hpp"
#include "LMDCustomBevelPanel.hpp"
#include "LMDCustomGroupBox.hpp"
#include "LMDCustomParentPanel.hpp"
#include "LMDGroupBox.hpp"
#include "LMDBaseGraphicButton.hpp"
#include "LMDCustomSpeedButton.hpp"
#include "LMDSpeedButton.hpp"
#include "LMDDrawEdge.hpp"
#include "LMDCustomLabel.hpp"
#include "LMDLabel.hpp"
#include "LMDCustomGlyphLabel.hpp"
#include "LMDGlyphLabel.hpp"
#include "lmdcont.hpp"
#include <MPlayer.hpp>
#include "LMDWaveComp.hpp"

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:    // IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *E1;
        TSplitter *Splitter3;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TSplitter *Splitter1;
        TListBox *ListBoxFile;
        TGroupBox *GroupBox1;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TStatusBar *StatusBar1;
        TPageControl *PageControl2;
        TTabSheet *TabSheet4;
        TListBox *ListBoxLog;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TOpenDialog *OpenDialog1;
        TLMDBrowseDlg *LMDBrowseDlg1;
        TListBox *ListBoxTST;
        TListBox *ListBoxDire;
        TGroupBox *GroupBox2;
        TBitBtn *BitBtn3;
        TBitBtn *BitBtn4;
        TMenuItem *SaveSetting1;
        TMenuItem *LoadSetting1;
        TGroupBox *GroupBox3;
        TLMDCheckBox *LMDCheckBox3;
        TBitBtn *BitBtn5;
        TGroupBox *GroupBox4;
        TLMDCheckBox *LMDCheckBox1;
        TGroupBox *GroupBox5;
        TTimer *TimerExit;
        TLMDCheckBox *LMDCheckBox4;
        TLMDOneInstance *LMDOneInstance1;
        TGroupBox *GroupBox6;
        TLMDCheckBox *LMDCheckBox2;
        TLMDCheckBox *LMDCheckBox5;
        TGroupBox *GroupBox7;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TMenuItem *History1;
        TTabSheet *TabSheet5;
        TMenuItem *History2;
        TMenuItem *License1;
        TLabel *Label1;
        TImage *Image1;
        TLabel *Label3;
        TMenuItem *Master1;
        TGroupBox *GroupBox8;
        TLMDCheckBox *DelTIE;
        TTabSheet *TabSheet6;
        TLMDGroupBox *LMDGroupBox1;
        TLMDGroupBox *LMDGroupBox2;
        TLMDGroupBox *LMDGroupBox3;
        TLMDGroupBox *LMDGroupBox4;
        TLMDSpeedButton *LMDSpeedButton1;
        TLMDSpeedButton *LMDSpeedButton2;
        TLMDSpeedButton *LMDSpeedButton3;
        TLMDSpeedButton *LMDSpeedButton4;
        TLMDSpeedButton *LMDSpeedButton5;
        TLMDSpeedButton *LMDSpeedButton6;
        TLMDSpeedButton *LMDSpeedButton7;
        TLMDSpeedButton *LMDSpeedButton8;
        TLMDSpeedButton *LMDSpeedButton9;
        TLMDSpeedButton *LMDSpeedButton10;
        TLMDLabel *LMDLabel1;
        TLMDGlyphLabel *LMDGlyphLabel1;
        TLMDGlyphLabel *LMDGlyphLabel2;
        TLMDGlyphLabel *LMDGlyphLabel3;
        TLMDGlyphLabel *LMDGlyphLabel4;
        TLMDGlyphLabel *LMDGlyphLabel5;
        void __fastcall E1Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall LoadSetting1Click(TObject *Sender);
        void __fastcall SaveSetting1Click(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall LMDCheckBox3Change(TObject *Sender);
        void __fastcall LMDCheckBox2Change(TObject *Sender);
        void __fastcall BitBtn5Click(TObject *Sender);
        void __fastcall TimerExitTimer(TObject *Sender);
        void __fastcall Splitter3Moved(TObject *Sender);
        void __fastcall PageControl1Change(TObject *Sender);
        void __fastcall LMDCheckBox5Change(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall LMDCheckBox4Change(TObject *Sender);
        void __fastcall History2Click(TObject *Sender);
        void __fastcall License1Click(TObject *Sender);
        void __fastcall Master1Click(TObject *Sender);
        void __fastcall DelTIEChange(TObject *Sender);
        void __fastcall LMDCheckBox1Change(TObject *Sender);
        void __fastcall LMDSpeedButton1Click(TObject *Sender);
        void __fastcall LMDSpeedButton6Click(TObject *Sender);
        void __fastcall LMDSpeedButton2Click(TObject *Sender);
        void __fastcall LMDSpeedButton7Click(TObject *Sender);
        void __fastcall LMDSpeedButton3Click(TObject *Sender);
        void __fastcall LMDSpeedButton8Click(TObject *Sender);
        void __fastcall LMDSpeedButton4Click(TObject *Sender);
        void __fastcall LMDSpeedButton9Click(TObject *Sender);
        void __fastcall LMDSpeedButton10Click(TObject *Sender);
        void __fastcall LMDSpeedButton5Click(TObject *Sender);
private:        // User declarations
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
