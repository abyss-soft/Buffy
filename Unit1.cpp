//---------------------------------------------------------------------------

#include <vcl.h>
#include <fstream.h>
#include <dos.h>
#include <dir.h>
#include <Sysutils.hpp>
#include <Registry.hpp>

#pragma hdrstop

#include <wininet.h>

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma comment(lib, "wininet.lib")
#pragma package(smart_init)
#pragma link "LMDBaseControl"
#pragma link "LMDBaseGraphicControl"
#pragma link "LMDBaseLabel"
#pragma link "LMDControl"
#pragma link "LMDCustomSimpleLabel"
#pragma link "LMDSimpleLabel"
#pragma link "LMDButtonControl"
#pragma link "LMDCheckBox"
#pragma link "LMDCustomCheckBox"
#pragma link "LMDCustomControl"
#pragma link "LMDCustomPanel"
#pragma link "LMDBrowseDlg"
#pragma link "LMDCustomComponent"
#pragma link "LMDOneInstance"
#pragma link "LMDTrayIcon"
#pragma link "LMDWndProcComponent"
#pragma link "LMDGraphicControl"
#pragma link "LMDScrollText"
#pragma link "LMDInformationLabel"
#pragma link "LMDCustomBevelPanel"
#pragma link "LMDCustomGroupBox"
#pragma link "LMDCustomParentPanel"
#pragma link "LMDGroupBox"
#pragma link "LMDBaseGraphicButton"
#pragma link "LMDCustomSpeedButton"
#pragma link "LMDSpeedButton"
#pragma link "LMDDrawEdge"
#pragma link "LMDCustomLabel"
#pragma link "LMDLabel"
#pragma link "LMDCustomGlyphLabel"
#pragma link "LMDGlyphLabel"
#pragma link "lmdcont"
#pragma link "LMDWaveComp"
#pragma resource "*.dfm"
TForm1 *Form1;
void ViewLog(String MFile);

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
// Для того чтобы удалить папку и все файлы в ней напишем функцию:
bool DeleteDir(AnsiString DirName)
{
TSearchRec sr;
if (DirName.Length())
 {
 if (!FindFirst(DirName+"\\*.*",faAnyFile,sr))
 do
  {
  if (!(sr.Name=="." || sr.Name==".."))// это удалять не надо
   if (((sr.Attr & faDirectory) == faDirectory ) ||
   (sr.Attr == faDirectory))// найдена папка
    {
    FileSetAttr(DirName+"\\"+sr.Name, faDirectory );// сброс всяких read-only
    DeleteDir(DirName+"\\"+sr.Name);//рекурсивно удаляем содержимое
    ViewLog(DirName+"\\"+sr.Name);
    RemoveDir(DirName + "\\"+sr.Name);// удаляем теперь уже пустую папку
    ViewLog(DirName + "\\"+sr.Name);
    }
    else// иначе найден файл
    {
    FileSetAttr(DirName+"\\"+sr.Name, 0);// сброс всяких read-only
    DeleteFile(DirName+"\\"+sr.Name);// удаляем файл
    ViewLog(DirName+"\\"+sr.Name);
    }
  }
 while (!FindNext(sr));// ищем опять, пока не найдем все
 FindClose(sr);
 }
//RemoveDir(DirName);
return true;
}

//---------------------------------------------------------------------------
// Функция Удаления файлов и папок
void ClearAll(void)
{
AnsiString FileName;
int i;
if((Form1->ListBoxFile->Items->Count<=0)&&(Form1->ListBoxDire->Items->Count<=0)) return;
//Delete Files !!!!!
//if(Application->MessageBox("Delete from ListBox ?", "Warning !!!!", MB_OKCANCEL)==IDOK)
//{
for(i=0;i<Form1->ListBoxFile->Items->Count;i++)
{
 FileName=Form1->ListBoxFile->Items->Strings[i];
 FileSetAttr(FileName, faArchive);
 if (DeleteFile(FileName)) ViewLog(FileName);
}
//}
//Delete Directory!!!
//if(Application->MessageBox("Delete from ListBox ?", "Warning !!!!", MB_OKCANCEL)==IDOK)
//{
for(int i=0;i<Form1->ListBoxDire->Items->Count;i++)
  {
  DeleteDir(Form1->ListBoxDire->Items->Strings[i]);
  }
//}
}

//---------------------------------------------------------------------------
// Функция вывода с LogView файлов, которые сейчас удаляются
void ViewLog(String MFile)
{
Form1->ListBoxLog->Items->Add(MFile);
}

//---------------------------------------------------------------------------
// Функция Записи в ini-файл
// NameSect -имя секции в Ini файле, в которую надо записывать
// Nomb -число, которое записываем (0 или 1)
void SaveByffySet(AnsiString NameSect, int Nomb)
{
 TIniFile *MyIni = new TIniFile(GetCurrentDir()+ "\\buffy.ini");
 MyIni->WriteString("Buffy",NameSect,Nomb);
 delete MyIni;
}
//---------------------------------------------------------------------------
//Функция проверяет наличия файла настройки
int TestMyFile(void)
{ AnsiString FileM;
 //узнаем из какого каталога запущена наша программа
AnsiString MyStartDir;
 ExtractFilePath(ParamStr(0));
MyStartDir=ExtractFilePath(Application->ExeName);   //тут MyStartDir - имя каталога, где находится Наша программа
 SetCurrentDir(MyStartDir); //устанавливаем наш каталог текущим, иначе мы сохраним файлы в другом месте

  FileM=GetCurrentDir()+ "\\buffy.ini";
  
 if(FileExists(FileM))
     return 0;
 else return 1;

}

//---------------------------------------------------------------------------
// Функция Чтения из ini-файла
void LoadBuffySet(void)
{
//считываем установки из ini файла
TStringList *MyList = new TStringList;
TIniFile *MyIni = new TIniFile(GetCurrentDir()+ "\\buffy.ini");
MyIni->ReadSectionValues("Buffy", MyList);
// применяем установки
if(MyList->Values["SaveLog"]==1) Form1->LMDCheckBox2->Checked=true;
if(MyList->Values["AutoExit"]==1) Form1->LMDCheckBox1->Checked=true;
if(MyList->Values["AutoDelete"]==1) Form1->LMDCheckBox3->Checked=true;
if(MyList->Values["NoClearLog"]==1) Form1->LMDCheckBox5->Checked=true;
if(MyList->Values["AutoStart"]==1) Form1->LMDCheckBox4->Checked=true;
if(MyList->Values["DelTIE"]==1) Form1->DelTIE->Checked=true;


if(MyList->Values["Russ"]==1) Form1->RadioButton1->Checked=true;
  else Form1->RadioButton2->Checked=true;
//Устанавливаем позицию LogView
Form1->PageControl1->Width=StrToInt(MyList->Values["Width"]);
delete MyList;
delete MyIni;
}

//---------------------------------------------------------------------------
// Функция Чтения из ini-файла настроек языка
void LoadBuffyLanguage(void)
{
//считываем установки из ini файла
TStringList *MyList = new TStringList;
TIniFile *MyIni = new TIniFile(GetCurrentDir()+ "\\buffy.ini");
if(Form1->RadioButton1->Checked==true)MyIni->ReadSectionValues("LanguageRus", MyList);
else  MyIni->ReadSectionValues("LanguageEngl", MyList);
// применяем установки
//настраиваем язык меню
Form1->N1->Caption=MyList->Values["Menu1"];
Form1->LoadSetting1->Caption=MyList->Values["File1"];
Form1->SaveSetting1->Caption=MyList->Values["File2"];
Form1->E1->Caption=MyList->Values["File3"];
Form1->History1->Caption=MyList->Values["Menu2"];
Form1->Master1->Caption=MyList->Values["Menu3"];
Form1->History2->Caption=MyList->Values["HistMen"];
Form1->License1->Caption=MyList->Values["HistMen1"];
//настраиваем язык TabSheet1
Form1->TabSheet1->Caption=MyList->Values["MFile1"];
Form1->TabSheet2->Caption=MyList->Values["MFile2"];
Form1->TabSheet3->Caption=MyList->Values["MFile3"];
Form1->BitBtn1->Caption=MyList->Values["Butom1"];
Form1->BitBtn2->Caption=MyList->Values["Butom2"];
Form1->BitBtn3->Caption=MyList->Values["Butom3"];
Form1->BitBtn4->Caption=MyList->Values["Butom4"];
//настраиваем язык TabSheet1->Options
Form1->GroupBox3->Caption=MyList->Values["Option1"];
Form1->LMDCheckBox3->Caption=MyList->Values["ADelete"];
Form1->BitBtn5->Caption=MyList->Values["ADelete1"];
Form1->DelTIE->Caption=MyList->Values["DelTIEF"];
//Setting
Form1->GroupBox4->Caption=MyList->Values["Option2"];
Form1->LMDCheckBox1->Caption=MyList->Values["AExit"];
Form1->LMDCheckBox2->Caption=MyList->Values["SaveLog"];
Form1->GroupBox6->Caption=MyList->Values["LogM"];
Form1->LMDCheckBox5->Caption=MyList->Values["SLgNClear"];
Form1->LMDCheckBox4->Caption=MyList->Values["AutoWind"];

//Language
Form1->GroupBox7->Caption=MyList->Values["Lng"];
Form1->RadioButton1->Caption=MyList->Values["Rus"];
Form1->RadioButton2->Caption=MyList->Values["Engl"];

//настраиваем язык LogView
Form1->TabSheet4->Caption=MyList->Values["MFile4"];

// Настраиваем Help
Form1->BitBtn1->Hint=MyList->Values["Butom1H"];
Form1->BitBtn2->Hint=MyList->Values["Butom2H"];
Form1->ListBoxFile->Hint=MyList->Values["LsBox1"];
Form1->ListBoxDire->Hint=MyList->Values["LsBox2"];
Form1->BitBtn3->Hint=MyList->Values["Butom3H"];
Form1->BitBtn4->Hint=MyList->Values["Butom4H"];
//Setting
Form1->LMDCheckBox3->Hint=MyList->Values["ADeleteH"];
Form1->BitBtn5->Hint=MyList->Values["ADelete1H"];
Form1->LMDCheckBox1->Hint=MyList->Values["AExitH"];
Form1->LMDCheckBox2->Hint=MyList->Values["SaveLogH"];
Form1->LMDCheckBox5->Hint=MyList->Values["SaveLog1H"];
Form1->LMDCheckBox4->Hint=MyList->Values["AutoWindH"];
Form1->DelTIE->Hint=MyList->Values["DelTIEHnt"];
//Настраиваем Tweak
Form1->TabSheet6->Caption=MyList->Values["MFile5"];
Form1->LMDGroupBox2->Caption=MyList->Values["TOption1"];
Form1->LMDGroupBox3->Caption=MyList->Values["TOption2"];
Form1->LMDGroupBox4->Caption=MyList->Values["TOption3"];
Form1->LMDGlyphLabel1->Caption=MyList->Values["NoSpy"];
Form1->LMDGlyphLabel1->Hint=MyList->Values["NoSpyH"];
Form1->LMDGlyphLabel2->Caption=MyList->Values["NoUser"];
Form1->LMDGlyphLabel2->Hint=MyList->Values["NoUserH"];
Form1->LMDGlyphLabel3->Caption=MyList->Values["NoHistDoc"];
Form1->LMDGlyphLabel3->Hint=MyList->Values["NoHistDocH"];
Form1->LMDGlyphLabel4->Caption=MyList->Values["ClrDoc"];
Form1->LMDGlyphLabel4->Hint=MyList->Values["ClrDocH"];
Form1->LMDGlyphLabel5->Caption=MyList->Values["WindSet"];
Form1->LMDGlyphLabel5->Hint=MyList->Values["WindSetH"];

//
Form1->LMDLabel1->Caption=MyList->Values["WarningM"];

//Вывод сообщений о "программе"
if(Form1->RadioButton1->Checked==true)
 {                             
  Form1->Label1->Caption="Данную программу придумал и создал Angel Dance.";
  Form1->Label3->Caption="По всем вопросам пишите:\
                        \nabyss-soft@narod.ru\
                        \nabyss_soft@inbox.ru\
                        \n(Здоровая критика приветствуется)\
                        \nТак же предлагайте, что еще вы хотите видеть в данной программе.\
                        \n                           (c) Abyss Soft 1995-2004";
  }
 else
   {
    Form1->Label1->Caption="This programm create && devise by Angel Dance. (c) Abyss Soft 1995-2004";
    Form1->Label3->Caption="For all questions, for more questions && request:\
                          \nabyss-soft@narod.ru\
                         \nabyss_soft@inbox.ru\
                         \n(Welcome is Telling Criticism)\
                         \nWhat do you like is this programm new feature?";

   }

delete MyList;
delete MyIni;
}
//---------------------------------------------------------------------------
//Функция заполнения ListBox'ов из файлов
// каталоги - из файла "Directory.AnD"
// файлы - из файла "Files.AnD"
void LoadBox(void)
{
AnsiString MyStartDir;
 ExtractFilePath(ParamStr(0));
MyStartDir=ExtractFilePath(Application->ExeName);   //тут MyStartDir - имя каталога, где находится Наша программа
 SetCurrentDir(MyStartDir); //устанавливаем наш каталог текущим, иначе мы фиг что загрузим

Form1->ListBoxFile->Items->LoadFromFile("Files.AnD");
Form1->ListBoxDire->Items->LoadFromFile("Directory.AnD");
}

//---------------------------------------------------------------------------
//Функция сохранения ListBox'ов в файлы
// каталоги - в файл "Directory.AnD"
// файлы - в файл "Files.AnD"
// Log - в файл "Buffy.log"
void SaveBox(void)
{
//узнаем из какого каталога запущена наша программа
AnsiString MyStartDir;
 ExtractFilePath(ParamStr(0));
MyStartDir=ExtractFilePath(Application->ExeName);   //тут MyStartDir - имя каталога, где находится Наша программа
 SetCurrentDir(MyStartDir); //устанавливаем наш каталог текущим, иначе мы сохраним файлы в другом месте
 //копируем в файл данные из ListBoxFile
 Form1->ListBoxTST->Clear();
//копируем из ListBoxFile в ListBoxTST
for(int i=0;i<Form1->ListBoxFile->Items->Count;i++)
  {
  Form1->ListBoxTST->Items->Add(Form1->ListBoxFile->Items->Strings[i]);
  }
//if(Form1->ListBoxTST->Items->Count<=0) return;
 Form1->ListBoxTST->Items->SaveToFile("Files.AnD");
  //--------------------------------------------------------------------
  //копируем в файл данные из ListBoxDire
  Form1->ListBoxTST->Clear();
//копируем из ListBoxDire в ListBoxTST
for(int i=0;i<Form1->ListBoxDire->Items->Count;i++)
  {
  Form1->ListBoxTST->Items->Add(Form1->ListBoxDire->Items->Strings[i]);
  }
//if(Form1->ListBoxTST->Items->Count<=0) return;
 Form1->ListBoxTST->Items->SaveToFile("Directory.AnD");
// Сохраняем Log
  if(Form1->LMDCheckBox2->Checked==true)
 {
   // если включена опция НЕ ОЧИЩАТЬ ЛОГ 
if(Form1->LMDCheckBox5->Checked==true)
   {
   int i=0; char *ch;
   AnsiString MText;
   ofstream file;
    file.open("Buffy.log", ios::app);
    if (!file) return;
      while (i<Form1->ListBoxLog->Items->Count)
       {
      MText=Form1->ListBoxLog->Items->Strings[i];
      ch=MText.c_str();
      file << ch << endl ;
      i++;
      if(i>Form1->ListBoxLog->Items->Count) break;
        }
     file.close();
   }
 else {
 Form1->ListBoxLog->Items->SaveToFile("Buffy.log");}
 }

if(TestMyFile()==0)
 {
//Сохраняем позицию левого LogView
SaveByffySet("Width", Form1->PageControl1->Width);
}

}

//---------------------------------------------------------------------------
//Функция сохранения LogBox'а в файл "Buffy.Log"
void SaveLog(void)
{
Form1->ListBoxLog->Items->SaveToFile("Buffy.Log");
}

//---------------------------------------------------------------------------
void __fastcall TForm1::E1Click(TObject *Sender)
{
exit(0);        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
if(OpenDialog1->Execute())
  { String IFile=OpenDialog1->FileName;
    ListBoxFile->Items->Add(IFile);
    //Label1->Caption=IFile;
  }        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{
 if(LMDBrowseDlg1->Execute())
  { String IDire=LMDBrowseDlg1->SelectedFolder;
    ListBoxDire->Items->Add(IDire);
   }        
}
//---------------------------------------------------------------------------
//Функция удаления Temporary Internet Files
BOOL DelTempFiles()
{
    BOOL bResult = FALSE;
    BOOL bDone = FALSE;
    LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL;  
 
    DWORD  dwTrySize, dwEntrySize = 4096; // размер буфера    
    HANDLE hCacheDir = NULL;    
    DWORD  dwError = ERROR_INSUFFICIENT_BUFFER;
    
    do 
    {                               
        switch (dwError)
        {
            // need a bigger buffer
            case ERROR_INSUFFICIENT_BUFFER: 
                delete [] lpCacheEntry;            
                lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];
                lpCacheEntry->dwStructSize = dwEntrySize;
                dwTrySize = dwEntrySize;
                BOOL bSuccess;
                if (hCacheDir == NULL)                
                  
                    bSuccess = (hCacheDir 
                      = FindFirstUrlCacheEntry(NULL, lpCacheEntry,
                      &dwTrySize)) != NULL;
                else
                    bSuccess = FindNextUrlCacheEntry(hCacheDir, lpCacheEntry, &dwTrySize);

                if (bSuccess)
                    dwError = ERROR_SUCCESS;    
                else
                {
                    dwError = GetLastError();
                    dwEntrySize = dwTrySize; // возвращаем новый размер буфера
                }
                break;

             // уже всё удалено
            case ERROR_NO_MORE_ITEMS:
                bDone = TRUE;
                bResult = TRUE;                
                break;

             // если нет ошибок
            case ERROR_SUCCESS:                       
        
                // кукисы не удалять
                //if (!(lpCacheEntry->CacheEntryType & COOKIE_CACHE_ENTRY))                
                   
                 DeleteUrlCacheEntry(lpCacheEntry->lpszSourceUrlName);
                    
                // Удаляем следующий элемент
                dwTrySize = dwEntrySize;
                if (FindNextUrlCacheEntry(hCacheDir, lpCacheEntry, &dwTrySize))
                    dwError = ERROR_SUCCESS;          
     
                else
                {
                    dwError = GetLastError();
                    dwEntrySize = dwTrySize; // возвращаем новый размер буфера
                }                    
                break;

            // по умолчанию
            default:
                bDone = TRUE;                
                break;
        }

        if (bDone)
        {   
            delete [] lpCacheEntry; 
            if (hCacheDir)
                FindCloseUrlCache(hCacheDir);         
                                  
        }
    } while (!bDone);
    return bResult;
}


//---------------------------------------------------------------------------
//Мастер первоначальной настройки настройки
void Master(void)
{
char *UserN, *TempN, *TmpN, *HomeDrvN;
AnsiString tmp;
//получаем имя пользователя в компьютере
UserN=getenv("USERNAME");
TempN=getenv("TEMP");
TmpN=getenv("TMP");
HomeDrvN=getenv("HOMEDRIVE");

tmp=(AnsiString)HomeDrvN + "\\Documents and Settings\\"+(AnsiString)UserN +"\\Local Settings\\Temp";
if (DirectoryExists(tmp)) Form1->ListBoxDire->Items->Add(tmp);
tmp="";

//tmp=(AnsiString)HomeDrvN + "\\Documents and Settings\\"+(AnsiString)UserN +"\\Local Settings\\Temporary Internet Files";
//if (DirectoryExists(tmp)) Form1->ListBoxDire->Items->Add(tmp);
//tmp="";

tmp=(AnsiString)HomeDrvN + "\\Documents and Settings\\"+(AnsiString)UserN+"\\Local Settings\\History";

if (DirectoryExists(tmp)) Form1->ListBoxDire->Items->Add(tmp);
tmp="";

tmp=(AnsiString)HomeDrvN + "\\Documents and Settings\\"+(AnsiString)UserN+"\\Recent";
if (DirectoryExists(tmp)) Form1->ListBoxDire->Items->Add(tmp);
tmp="";

tmp=(AnsiString)HomeDrvN + "\\Documents and Settings\\"+(AnsiString)UserN+"\\Cookies";
if (DirectoryExists(tmp)) Form1->ListBoxDire->Items->Add(tmp);
tmp="";

if (DirectoryExists(TempN)) Form1->ListBoxDire->Items->Add(TempN);
if (DirectoryExists(TmpN)) Form1->ListBoxDire->Items->Add(TmpN);
// Узнаем Windows-директорию
char WinDrN[MAX_PATH];
GetWindowsDirectory(WinDrN, MAX_PATH);

tmp=(AnsiString)WinDrN+"\\Temp";
if (DirectoryExists(tmp)) Form1->ListBoxDire->Items->Add(tmp);

//Включение опций настройки по умолчанию
SaveByffySet("AutoDelete", 1);
SaveByffySet("AutoExit", 1);
SaveByffySet("AutoStart", 1);
SaveByffySet("DelTIE", 1);
SaveByffySet("SaveLog", 1);

Form1->LMDCheckBox3->Checked=true;
Form1->LMDCheckBox1->Checked=true;
Form1->LMDCheckBox4->Checked=true;
Form1->DelTIE->Checked=true;
Form1->LMDCheckBox2->Checked=true;
//------
//Запускаем обработчик события
Form1->LMDCheckBox4Change(Form1);

SaveBox();

}

//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
if(TestMyFile()==1)
 {
  Application->MessageBox("File settings 'buffy.ini' is not found", "Error !",MB_OK );
  exit(1);
 }

LoadBuffyLanguage();

ListBoxFile->Clear();
ListBoxDire->Clear();
ListBoxLog->Clear();
LoadBox();

LoadBuffySet();

//Если включен AutoDelete
if(LMDCheckBox3->Checked==true) ClearAll();

//Если включен AutoExit
if(LMDCheckBox1->Checked==true)
   {
    TimerExit->Enabled=true;
    Form1->WindowState=wsMinimized;
   }


//ограничения Beta-версии
struct date d;
   getdate(&d);
  if(d.da_year>2004) exit(0);


}

//---------------------------------------------------------------------------
// удаление имени файла из ListBoxFiles
void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
 int ind;     // номер выделенной строки в ListBox'e
  ind = ListBoxFile->ItemIndex;
  if (ind==-1)
       {
        Application->MessageBox("ListBox is Clear....", "Ops....", MB_OK);
        return;
        }
ListBoxTST->Clear();
//копируем из ListBoxFile в ListBoxTST
for(int i=0;i<Form1->ListBoxFile->Items->Count;i++)
  {
  if(ind==i) continue;
  Form1->ListBoxTST->Items->Add(Form1->ListBoxFile->Items->Strings[i]);
  }
//копируем из ListBoxTST в ListBox1  для проверки того что у нас получилось
ListBoxFile->Clear();
for(int i=0;i<Form1->ListBoxTST->Items->Count;i++)
  {
  Form1->ListBoxFile->Items->Add(Form1->ListBoxTST->Items->Strings[i]);
  }
  
ListBoxTST->Clear();
SaveBox();
}

//---------------------------------------------------------------------------
// удаление имени каталога из ListBoxDire
void __fastcall TForm1::BitBtn4Click(TObject *Sender)
{
 int ind;     // номер выделенной строки в ListBox'e
  ind = ListBoxDire->ItemIndex;
  if (ind==-1)
       {
        Application->MessageBox("ListBox is Clear....", "Ops....", MB_OK);
        return;
        }
ListBoxTST->Clear();
//копируем из ListBoxDire в ListBoxTST
for(int i=0;i<Form1->ListBoxDire->Items->Count;i++)
  {
  if(ind==i) continue;
  Form1->ListBoxTST->Items->Add(Form1->ListBoxDire->Items->Strings[i]);
  }
//копируем из ListBoxTST в ListBoxDire  для проверки того что у нас получилось
ListBoxDire->Clear();
for(int i=0;i<Form1->ListBoxTST->Items->Count;i++)
  {
  Form1->ListBoxDire->Items->Add(Form1->ListBoxTST->Items->Strings[i]);
  }
  
ListBoxTST->Clear();
SaveBox();
}

//---------------------------------------------------------------------------


void __fastcall TForm1::LoadSetting1Click(TObject *Sender)
{
LoadBox();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveSetting1Click(TObject *Sender)
{
SaveBox();        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormDestroy(TObject *Sender)
{
SaveBox();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LMDCheckBox3Change(TObject *Sender)
{
if(LMDCheckBox3->Checked==true)
 { SaveByffySet("AutoDelete", 1); ClearAll();}
  else SaveByffySet("AutoDelete", 0);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::LMDCheckBox2Change(TObject *Sender)
{
if(LMDCheckBox2->Checked==true)
 { SaveByffySet("SaveLog", 1); SaveLog();}
  else SaveByffySet("SaveLog", 0);

}
//---------------------------------------------------------------------------




void __fastcall TForm1::BitBtn5Click(TObject *Sender)
{
if(Application->MessageBox("Clear from Directory and Files ?", "Warning !!!!", MB_OKCANCEL)==IDOK)
 {
  ClearAll();
 } 
}
//---------------------------------------------------------------------------


void __fastcall TForm1::TimerExitTimer(TObject *Sender)
{
if((Form1->WindowState==wsNormal) || (Form1->WindowState==wsMaximized))
 return;
  else exit(0);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Splitter3Moved(TObject *Sender)
{
if(PageControl1->ActivePage==TabSheet3)Form1->PageControl1->Width=409;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PageControl1Change(TObject *Sender)
{
if(PageControl1->ActivePage==TabSheet3)Form1->PageControl1->Width=409;
if(PageControl1->ActivePage==TabSheet6)Form1->PageControl1->Width=500;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::LMDCheckBox5Change(TObject *Sender)
{
if(LMDCheckBox5->Checked==true)
 { SaveByffySet("NoClearLog", 1); SaveLog();}
  else SaveByffySet("NoClearLog", 0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
if(RadioButton1->Checked==true)
 { SaveByffySet("Russ", 1); SaveLog();}
 LoadBuffyLanguage();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
if(RadioButton2->Checked==true)
 { SaveByffySet("Russ", 0); SaveLog();}
 LoadBuffyLanguage();        
}

//---------------------------------------------------------------------------

void __fastcall TForm1::LMDCheckBox4Change(TObject *Sender)
{
AnsiString S_run;
//определяем имя и путь нашего файла
char ExeName[MAX_PATH];
GetModuleFileName(HInstance, ExeName, sizeof(ExeName));

if(LMDCheckBox4->Checked==true)
 { SaveByffySet("AutoStart", 1);


//Записываем себя в автозагрузку реестра для текущего пользователя.
 TRegistry *Reg1 = new TRegistry;
 Reg1->RootKey = HKEY_CURRENT_USER;
 Reg1->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false);
 Reg1->WriteString("Buffy",ExeName);
 Reg1->CloseKey();
 delete Reg1;
  }
// удаляем себя из Автозагрузки

  else
   { SaveByffySet("AutoStart", 0);
 TRegistry *Reg2 = new TRegistry;
 Reg2->RootKey = HKEY_CURRENT_USER;
 Reg2->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false);
 Reg2->DeleteValue("Buffy");
 Reg2->CloseKey();
 delete Reg2;

  }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::History2Click(TObject *Sender)
{
AboutBox->LMDDockLabel3->Caption="Немного истории или как появилась данная программа:";
AboutBox->LMDDockLabel3->Left=95;
AboutBox->LMDDockLabel4->Visible=true;
AboutBox->Timer2->Enabled=true;
AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::License1Click(TObject *Sender)
{
AboutBox->LMDDockLabel3->Caption="Лицензия (на всякий случай)";
AboutBox->LMDDockLabel3->Left=207;


AboutBox->LMDDockLabel4->Visible=false;
AboutBox->Timer1->Enabled=true;
AboutBox->ShowModal();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Master1Click(TObject *Sender)
{
if(Application->MessageBox("You want to start the Master an Settings?", "Master..", MB_OKCANCEL)==IDOK)
 {
  Master();
  Form1->Master1->Visible=false;
  Application->MessageBox("Your settings are preserved!", "Master..", MB_OK);
 } 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DelTIEChange(TObject *Sender)
{
if(DelTIE->Checked==true)
 { SaveByffySet("DelTIE", 1);  DelTempFiles();}
  else SaveByffySet("DelTIE", 0);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::LMDCheckBox1Change(TObject *Sender)
{
if(LMDCheckBox1->Checked==true)
 {
  SaveByffySet("AutoExit", 1);
  Form1->WindowState=wsMinimized;
  TimerExit->Enabled=true;
 }
  else SaveByffySet("AutoExit", 0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LMDSpeedButton1Click(TObject *Sender)
{
 TRegistry *Reg1 = new TRegistry;
 Reg1->RootKey = HKEY_CURRENT_USER;
 Reg1->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", true);
 Reg1->WriteInteger("NoInstrumentation",1);
 Reg1->CloseKey();
 delete Reg1;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::LMDSpeedButton6Click(TObject *Sender)
{
 TRegistry *Reg1 = new TRegistry;
 Reg1->RootKey = HKEY_CURRENT_USER;
 Reg1->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", true);
 Reg1->WriteInteger("NoInstrumentation",0);
 Reg1->CloseKey();
 delete Reg1;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::LMDSpeedButton2Click(TObject *Sender)
{
 TRegistry *Reg1 = new TRegistry;
 Reg1->RootKey = HKEY_LOCAL_MACHINE;
 Reg1->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", true);
 Reg1->WriteInteger("DontDisplayLastUserName",1);
 Reg1->CloseKey();
 delete Reg1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LMDSpeedButton7Click(TObject *Sender)
{
 TRegistry *Reg1 = new TRegistry;
 Reg1->RootKey = HKEY_LOCAL_MACHINE;
 Reg1->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", true);
 Reg1->WriteInteger("DontDisplayLastUserName",0);
 Reg1->CloseKey();
 delete Reg1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LMDSpeedButton3Click(TObject *Sender)
{
 TRegistry *Reg1 = new TRegistry;
 Reg1->RootKey = HKEY_LOCAL_MACHINE;
 Reg1->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\explorer", true);
 Reg1->WriteInteger("NoRecentDocsHistory",1);
 Reg1->CloseKey();
 delete Reg1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LMDSpeedButton8Click(TObject *Sender)
{
 TRegistry *Reg1 = new TRegistry;
 Reg1->RootKey = HKEY_LOCAL_MACHINE;
 Reg1->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\explorer", true);
 Reg1->WriteInteger("NoRecentDocsHistory",0);
 Reg1->CloseKey();
 delete Reg1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LMDSpeedButton4Click(TObject *Sender)
{
 TRegistry *Reg1 = new TRegistry;
 Reg1->RootKey = HKEY_LOCAL_MACHINE;
 Reg1->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\explorer", true);
 Reg1->WriteInteger("ClearRecentDocsOnExit",1);
 Reg1->CloseKey();
 delete Reg1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LMDSpeedButton9Click(TObject *Sender)
{
 TRegistry *Reg1 = new TRegistry;
 Reg1->RootKey = HKEY_LOCAL_MACHINE;
 Reg1->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\explorer", true);
 Reg1->WriteInteger("ClearRecentDocsOnExit",0);
 Reg1->CloseKey();
 delete Reg1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LMDSpeedButton10Click(TObject *Sender)
{
 int val=0x01;
 TRegistry *Reg1 = new TRegistry;
 Reg1->RootKey = HKEY_CURRENT_USER;
 Reg1->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\explorer", true);
 Reg1->WriteBinaryData("NoSaveSettings",&val,sizeof(val));
 Reg1->CloseKey();
 delete Reg1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LMDSpeedButton5Click(TObject *Sender)
{
 TRegistry *Reg1 = new TRegistry;
 Reg1->RootKey = HKEY_CURRENT_USER;
 Reg1->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\explorer", true);
 Reg1->DeleteValue("NoSaveSettings");
 Reg1->CloseKey();
 delete Reg1;
}
//---------------------------------------------------------------------------





