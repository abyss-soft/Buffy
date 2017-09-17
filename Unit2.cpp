//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------
#pragma link "LMDCustomComponent"
#pragma link "LMDCustomFormFill"
#pragma link "LMDFormFill"
#pragma link "LMDWndProcComponent"
#pragma link "LMDBaseControl"
#pragma link "LMDBaseGraphicControl"
#pragma link "LMDBaseLabel"
#pragma link "LMDControl"
#pragma link "LMDCustomDockLabel"
#pragma link "LMDCustomSimpleLabel"
#pragma link "LMDDockLabel"
#pragma link "LMDGraphicControl"
#pragma link "LMDScrollText"
#pragma link "LMDCustomGlyphLabel"
#pragma link "LMDGlyphLabel"
#pragma resource "*.dfm"
TAboutBox *AboutBox;
long l;
char *License="���������  \' Buffy \' ������������ ��  �������� \"AS IS \".\
             \n������� ��������  �� ����������� � �� �����������������.\
             \n�� ����������� ��� ����������� ����������� �� ���� ����.\
             \n����� �� ����� �������� �� �� ����� ������ ��� ���������\
             \n������ � �������� ������������� ��� �������������\
             \n������������� ����� ������������ �����������.\
             \n��������� ���������������� ��� ��������� GPL.\
             \n\n\n�� ������ �������� ����������, ������ �������, ��������, ���������� �� CD,\
             \n� ����� �������������� ������ ��������� ������ ������� ��������� �� \
             \n��������� ���������� � ������ (���� ������ ����������).\a";
char *History="���-�� ��� ���� ( ������������� � ������� ����� ) �������� �����,\
               \n���, ���, ����� �� ����� �������� ������� ���������, ������� \
               \n�� ������� ����� �� ��������� ��������� � ��� ���� �� \
               \n�������� �� ������. ��� ��� ��������� ������ ������ ��������� \'Buffy\'.\
               \n� ��� ��� ������ ����� �������, �� ���������� ���������� ������������, ��\
               \n��� ���, ���� �� ����� Windows9x �� ������ Windows2000/XP. ������ ������ \
               \n��������� ��� �� ����������� �� ������ �������������, ������� ��� ��������\
               \n��������� ������������ ��� ��������� ������, ��� ��� ��������� ��� ������.\
               \n������� ��� ��� �����������.\a";
char *Used="��� �������� ������, � ��������� ��������� �������� �����, �������\
          \n��������� \"������\" �������. ����� ����� ������ ����������� �������� �� 200-1200~\
          \n��� ����� ����������, � ���� ����� ���������� ��� ��� � ����, ��� ������ �����.\
          \n���� � ��� ���� ���������, �� �� ��� ����� ������� ������� ��� �����, ��, � ����\
          \n�� ������������� � ������� ����� ����� ��� ��� ��������� ������ �� ��������.\a"; 

AnsiString OutText;

//---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------



void __fastcall TAboutBox::Timer1Timer(TObject *Sender)
{
if((AnsiString)License[l]=="\a") {AboutBox->Timer1->Enabled=false; return;}
OutText=OutText+(AnsiString)License[l];
AboutBox->NLicense->Caption=OutText;
l++;
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::FormCreate(TObject *Sender)
{
l=0;
OutText="";
}
//---------------------------------------------------------------------------


void __fastcall TAboutBox::FormClose(TObject *Sender, TCloseAction &Action)
{
l=0;
OutText="";
AboutBox->NLicense->Caption=OutText;
AboutBox->MHistory->Caption=OutText;
AboutBox->MUsed->Caption=OutText;
AboutBox->Timer1->Enabled=false;
AboutBox->Timer2->Enabled=false;
AboutBox->Timer3->Enabled=false;

}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::Timer2Timer(TObject *Sender)
{
if((AnsiString)History[l]=="\a") {AboutBox->Timer2->Enabled=false;OutText="";l=0; AboutBox->Timer3->Enabled=true; return;}
OutText=OutText+(AnsiString)History[l];
AboutBox->MHistory->Caption=OutText;
l++;
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::Timer3Timer(TObject *Sender)
{
if((AnsiString)Used[l]=="\a") {AboutBox->Timer3->Enabled=false; return;}
OutText=OutText+(AnsiString)Used[l];
AboutBox->MUsed->Caption=OutText;
l++;        
}
//---------------------------------------------------------------------------

