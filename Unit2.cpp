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
char *License="ПРОГРАММА  \' Buffy \' ПОСТАВЛЯЕТСЯ ПО  ПРИНЦИПУ \"AS IS \".\
             \nНИКАКИХ ГАРАНТИЙ  НЕ ПРИЛАГАЕТСЯ И НЕ ПРЕДУСМАТРИВАЕТСЯ.\
             \nВЫ ИСПОЛЬЗУЕТЕ ЭТО ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ НА СВОЙ РИСК.\
             \nАВТОР НЕ БУДЕТ ОТВЕЧАТЬ НИ ЗА КАКИЕ ПОТЕРИ ИЛИ ИСКАЖЕНИЯ\
             \nДАННЫХ В ПРОЦЕССЕ ИСПОЛЬЗОВАНИЯ ИЛИ НЕПРАВИЛЬНОГО\
             \nИСПОЛЬЗОВАНИЯ ЭТОГО ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ.\
             \nПРОГРАММА РАСПРОСТРАНЯЕТСЯ ПОД ЛИЦЕНЗИЕЙ GPL.\
             \n\n\nВы можете свободно копировать, давать друзьям, знакомым, записывать на CD,\
             \nа также распространять данную программу любыми другими способами не \
             \nспрашивая разрешения у автора (хотя ссылка желательна).\a";
char *History="Как-то мой друг ( администратор в игровом клубе ) высказал мысль,\
               \nчто, мол, никто не может написать простую программу, которая \
               \nбы удаляла мусор из временных каталогов и при этом не \
               \nзанимала бы память. Вот так появилась первая версия программы \'Buffy\'.\
               \nС тех пор прошло много времени, но программой продолжали пользоваться, до\
               \nтех пор, пока на смену Windows9x не пришел Windows2000/XP. Первая версия \
               \nпрограммы уже не справлялась со своими обязанностями, поэтому мне пришлось\
               \nполностью переписывать всю программу заново, вот так появилась эта версия.\
               \nНадеюсь она вам понравиться.\a";
char *Used="Как известно многим, в некоторых каталогах хранятся файлы, которые\
          \nпрограммы \"забыли\" удалить. Когда таких файлов становиться мегабайт на 200-1200~\
          \nэто очень раздражает, а если такое происходит изо дня в день, так просто бесит.\
          \nЕсли у вас один компьютер, то вы еще можно вручную удалять эти файлы, ну, а если\
          \nвы администратор в игровом клубе тогда вам без программы просто не обойтись.\a"; 

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

