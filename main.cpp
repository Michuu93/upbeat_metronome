#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <ctime>
#include <conio.h> //getch(); i kbhit();
#include <direct.h> //œcie¿ka
#define SND_FILENAME 0x20000
#define SND_LOOP 8 
#define SND_ASYNC 1 
#include "pliki.h"
#include <fstream>

using namespace std;
 
bool fileExists (const char* fileName)
{
     ifstream plik(fileName);
     if (plik.good()) 
     {
                      plik.close();
                      return true;
                      }
                      else
                      return false;
}


void setVolume(USHORT kanalLewy, USHORT kanalPrawy)
     {
                      ULONG glosnosc = (kanalLewy << 24) | (kanalPrawy << 8);
	                  waveOutSetVolume((HWAVEOUT)WAVE_MAPPER, glosnosc);
                   }

int i, t=90,error=0;
static int tempo, metrum, dzwiek=1, typ=1, loud=1, silent=1, nsignature=4, checkbox=0, volume=255, pomocnicza=100, started=0, exitt=0;
static HWND hwndEdit,B1,B2,Opt[30];
clock_t tap1=0,tap2,klik1,klik2,spr1,spr2;
double dif,klik3,zap;
static bool wav=false;
void OnSize(const HWND,int,int,UINT);
#include "metronom.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hinst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR lpCmdLine, int nCmdShow)
{
  MSG  msg ;    
  WNDCLASS wc = {0};
  wc.lpszClassName = TEXT("UpBeat Metronome");
  wc.hInstance     = hInstance ;
  wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wc.lpfnWndProc   = WndProc ;
  wc.hCursor       = LoadCursor(0, IDC_ARROW);
  wc.hIcon         = LoadIcon(hInstance,MAKEINTRESOURCE(id_icon));

  g_hinst = hInstance;
  
  InitCommonControls(); ///od slidera!!!!!!!!!!!
  
  RegisterClass(&wc);
  CreateWindow( wc.lpszClassName, TEXT("UpBeat Metronome"),
                WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
                400, 200, 400, 260, 0, 0, hInstance, 0);  

  while( GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return (int) msg.wParam;
}

DWORD WINAPI myThread(LPVOID lpParameter)
{
      main_metronom(typ,dzwiek,metrum,loud,silent,checkbox,nsignature); /////////////////////WYWOLANIE METRONOMU
      return 0;
      }
      
HANDLE myHandle; 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{    
  switch(msg)  
  {
	case WM_CREATE:
	{         
        B1=CreateWindow(TEXT("button"), TEXT("Start"),    
		             WS_VISIBLE | WS_CHILD ,
		             307, 21, 80, 25, hwnd, (HMENU) 1, NULL, NULL);   
					 
		B2=CreateWindow(TEXT("button"), TEXT("Tap Tempo"),    
		             WS_VISIBLE | WS_CHILD ,
		             307, 58, 80, 25, hwnd, (HMENU) 3, NULL, NULL);  

	    CreateWindow(TEXT("button"), TEXT("Quit"),    
		             WS_VISIBLE | WS_CHILD ,
		             307, 93, 80, 25, hwnd, (HMENU) 2, NULL, NULL);
                    
           ////////////////////////////////////////////////
		   
           
		Opt[20] = CreateWindow(TEXT("button"), TEXT("Music Score"), 
                WS_CHILD | WS_VISIBLE  | BS_GROUPBOX,
                140, 10, 160, 110, hwnd, (HMENU) 0, g_hinst, NULL);
    	
		Opt[8] = CreateWindow(TEXT("Edit"), TEXT("90"), WS_CHILD| WS_VISIBLE |WS_BORDER | ES_NUMBER,
				250, 35, 30, 20, hwnd, (HMENU) 0, NULL, NULL); 
        Opt[12] = CreateWindow(TEXT("STATIC"), "Tempo (bpm):", 
				WS_CHILD | WS_VISIBLE | SS_LEFT,
				150, 35, 100, 30, hwnd, (HMENU) 0, NULL, NULL);
				
           ////////////////////////////////////////////////
                
        Opt[7] = CreateWindow(TEXT("Edit"), TEXT("4"), WS_CHILD | WS_VISIBLE | WS_BORDER |ES_NUMBER,
				250, 60, 20, 20, hwnd, (HMENU) 0, NULL, NULL); 
        Opt[9] = CreateWindow(TEXT("STATIC"), "Time\nsignature:", 
				WS_CHILD | WS_VISIBLE | SS_LEFT,
				150, 68, 100, 42, hwnd, (HMENU) 0, NULL, NULL);
		    	     
        Opt[13] = CreateWindowEx(0,"COMBOBOX", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
				250, 85, 42, 20*5, hwnd,(HMENU) 0,((LPCREATESTRUCT)lParam)->hInstance, NULL);
 
				SendMessage(Opt[13], CB_ADDSTRING,0, (LPARAM)"2");
				SendMessage(Opt[13], CB_ADDSTRING,0, (LPARAM)"4");
				SendMessage(Opt[13], CB_ADDSTRING,0, (LPARAM)"8");
				SendMessage(Opt[13], CB_ADDSTRING,0, (LPARAM)"16");
				SendMessage(Opt[13],CB_SETCURSEL,(WPARAM)1,0);   
				
           ////////////////////////////////////////////////
		   
        Opt[11]=CreateWindow(TEXT("button"), TEXT("Beat type"), 
                WS_CHILD | WS_VISIBLE  | BS_GROUPBOX,
                10, 10, 120, 110, hwnd, (HMENU) 0, g_hinst, NULL);
        Opt[1]= CreateWindow(TEXT("button"), TEXT("Downbeat"),
                WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON,
                20, 35, 100, 20, hwnd, (HMENU)21, g_hinst, NULL);
        Opt[2]=  CreateWindow(TEXT("button"), TEXT("Upbeat"),
                WS_CHILD | WS_VISIBLE| BS_AUTORADIOBUTTON |BST_CHECKED,
                20, 60, 100, 20, hwnd, (HMENU)22 , g_hinst, NULL);
        Opt[3]=CreateWindow(TEXT("button"), TEXT("Swing"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                20, 85, 100, 20, hwnd, (HMENU)23 , g_hinst, NULL);
        SendMessage (Opt[1], BM_SETCHECK, 1, 0) ;
        
           ////////////////////////////////////////////////
		   
		Opt[4]=CreateWindow(TEXT("button"), TEXT("Sound"), 
                WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                10, 120, 120, 100, hwnd, (HMENU) 0, g_hinst, NULL);
        Opt[5]=CreateWindow(TEXT("button"), TEXT("WAV"),
                WS_CHILD | WS_VISIBLE | WS_GROUP| BS_AUTORADIOBUTTON,
                20, 140, 50, 30, hwnd, (HMENU)31 ,g_hinst, NULL);
                SendMessage (Opt[5], BM_SETCHECK, 1, 0);
        Opt[6]=CreateWindow(TEXT("button"), TEXT("Beep"),
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                20, 165, 55, 30, hwnd, (HMENU)32 , g_hinst, NULL);
		        
           ////////////////////////////////////////////////  
		    
		Opt[10]=CreateWindow(TEXT("button"), TEXT("by FX-Team"),
                WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                290,210,100,15, hwnd, (HMENU)41, g_hinst, NULL);
		Opt[0]=CreateWindow(TEXT("static"), TEXT("by FX-Team"),
                WS_CHILD | WS_VISIBLE,
                305,205,100,15, hwnd, (HMENU) 0, g_hinst, NULL);
                EnableWindow (Opt[0], FALSE);
                
           //////////////////////////////////////////////// 
           
		Opt[15] = CreateWindow(TEXT("button"), TEXT("Cycle    "), 
                WS_CHILD | WS_VISIBLE  | BS_GROUPBOX,
                140, 120, 195, 80, hwnd, (HMENU) 0, g_hinst, NULL);   
		Opt[14] = CreateWindow(TEXT("button"), "", 
		        WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		        189, 123, 10, 10, hwnd, (HMENU) 61, NULL, NULL); 
		Opt[16] = CreateWindow(TEXT("STATIC"), "Number of loud bars:", 
		        WS_CHILD | WS_VISIBLE | SS_LEFT,
		        150, 145, 150, 20, hwnd, (HMENU) 0, NULL, NULL);        
		Opt[17] = CreateWindow(TEXT("STATIC"), "Number of silent bars:", 
		        WS_CHILD | WS_VISIBLE | SS_LEFT,
		        150, 170, 150, 20, hwnd, (HMENU) 0, NULL, NULL); 
		Opt[18] = CreateWindow(TEXT("Edit"), TEXT("1"),
                WS_CHILD | WS_VISIBLE | WS_BORDER |ES_NUMBER,
				305, 145, 20, 20, hwnd, (HMENU) 0, NULL, NULL);
		Opt[19] = CreateWindow(TEXT("Edit"), TEXT("1"),
                WS_CHILD | WS_VISIBLE | WS_BORDER |ES_NUMBER,
				305, 168, 20, 20, hwnd, (HMENU) 0, NULL, NULL);		
	    Opt[21] =CreateWindow (TRACKBAR_CLASS, "",
                WS_CHILD | WS_VISIBLE | TBM_SETRANGE, 
                88, 136, 38, 80,hwnd, (HMENU) 0, NULL, NULL);   
                SendMessage(Opt[21],TBM_SETRANGE,0,MAKELONG(1,52));/////////ustawienia slider   
        Opt[22]=CreateWindow(TEXT("static"), TEXT("100 %"),
                WS_CHILD | WS_VISIBLE,
                39,194,40,13, hwnd, (HMENU) 0, g_hinst, NULL);            
                  
///////////////////////////////////////////////////////////////////////////////////////////// 
               
                for (i=16;i<=19;i++) EnableWindow (Opt[i], FALSE);
                
           ////////////////////////////////////////////////  
                                                  
	    break;
	}     
        case WM_VSCROLL:
              OnSize(hwnd,LOWORD(lParam),HIWORD(lParam),static_cast<UINT>(wParam));
                   char napis[100];
                         SetWindowText(NULL,TEXT(itoa(HIWORD(wParam),napis,10)));
                          
                         if (atoi(napis)!= 0)
                            {
                            volume=atoi(napis);   
                            volume=(52-volume)*5; 
                           }                                        
                         
                         SetWindowText(NULL,TEXT(itoa(LOWORD(wParam),napis,10)));///klikanie po lini
                         if (atoi(napis)==3)  volume=volume-50;                                 //  
                         if (atoi(napis)==2)  volume=volume+50;                                 //
                         
                         
                         
                          if (atoi(napis)!=5) //if na zmienianie wysokosci suwaka strza³kami
                          {
                           if (volume<=250 && volume>=5)
                            {
                            if (atoi(napis)==0)  volume=volume+5; 
                            if (atoi(napis)==1)  volume=volume-5;
                            }      
                          if (volume==255)
                            if (atoi(napis)==1)
                               volume=volume-5;
                          if (volume==0)
                             if (atoi(napis)==0)
                                volume=volume+5;
                                }                       
                         pomocnicza=volume*100/255;

                      SetWindowText(Opt[22],TEXT(strcat(itoa(pomocnicza,napis,10), " %")));                 
                         setVolume(volume, volume);                
        break;
	
      case WM_COMMAND:
        switch(LOWORD(wParam))
        {            
	      case 1:
	       if (!started)
           {            
                         spr2=clock();
                         zap=difftime(spr2,spr1);
                         
                       spr1=clock();//Beep(100,100);
                       if (zap>=100)
                       {    
                        
                       EnableWindow (B1, FALSE);  
                for (i=1; i<=20; i++)  EnableWindow (Opt[i], FALSE);
                
                EnableWindow (Opt[14], TRUE); 
                EnableWindow (Opt[14], FALSE);  
                EnableWindow (Opt[10], TRUE); 
                SetWindowText(B2,TEXT(""))  ;                               
              
                char napis[100];
                GetWindowText(Opt[8],napis,99);                
                tempo=atoi(napis); 
                t=tempo;           
     
                GetWindowText(Opt[7],napis,99);                
                metrum=atoi(napis);  
                
                GetWindowText(Opt[18],napis,99);                
                loud=atoi(napis); 
                
                GetWindowText(Opt[13],napis,99);                
                nsignature=atoi(napis); 
                
                GetWindowText(Opt[19],napis,99);                
                silent=atoi(napis);
                
                SetWindowText(B1,TEXT("Stop"));
                
               wav = fileExists("a.wav") && fileExists("b.wav") ? true : false;
                
                if (error==1) 
                   {
                   klik2=clock();
                   klik3=difftime(klik2,klik1);
                      if (klik3>=2200) error=0;
                   }
               // if (error==1) Sleep(2000);
                //if (error==0) Sleep(300);
                 EnableWindow (B1, TRUE);
                 
                          spr1=clock();      
	            started=1;
	            exitt=1;
	            
	            if (metrum<=0)
                {
                             metrum=4;
                             SetWindowText(Opt[7],TEXT("4")); 
                             }
	            if (tempo<=20)
                {
                             tempo=20;
                             t=tempo;
                             SetWindowText(Opt[8],TEXT("20"));
                             } 
                
                if (tempo>=400)
                {
                             tempo=400;
                             t=tempo;
                             SetWindowText(Opt[8],TEXT("400"));
                             } 
   	            
                if (loud<=0)
                {
                             loud=1;
                             SetWindowText(Opt[18],TEXT("1")); 
                             }
                             
   	            if (silent<=0)
                {
                             silent=1;
                             SetWindowText(Opt[19],TEXT("1")); 
                             }
	            
             
             unsigned int myCounter=0;
             DWORD myThreadID;       
             myHandle = CreateThread(0,0,myThread,&myCounter,0,&myThreadID); 
             
             //error=0;            
             }}
             
             else
             {     
                     spr2=clock();
                         zap=difftime(spr2,spr1);
                         
                       spr1=clock();//Beep(100,100);
                       if (zap>=100)
                       {         
                started=0;
               // SetWindowText(B1,TEXT("Please wait"));             
				 EnableWindow (B1, FALSE);
				 SetWindowText(B2,TEXT("Tap Tempo"))  ; 
				 
				 ///////////////////////////////////////
				 error=1;
				 
				 int pomoc,i8;
				 pomoc=60000/tempo;
				 for(i8=100;i8<=pomoc;i8=i8+100)
                    {
                    Sleep(100);
                    if(exitt==0) {error=0;i8=40000;}
                    }
                    exitt=0;
                  
                    
                 CloseHandle(myHandle); 
                 
				 /////////////////////////////////////////////
				 /////////////////////////////////////////////
				 if (error==1) Sleep(2000);
                //if (error==0) Sleep(300);
				for(i=1;i<=15;i++) EnableWindow (Opt[i], TRUE);  
                 for(i=20;i<=20;i++) EnableWindow (Opt[i], TRUE);   
                 if (checkbox==1) for(i=16;i<=19;i++) EnableWindow (Opt[i], TRUE); 
                 EnableWindow (Opt[14], FALSE);
                 EnableWindow (Opt[14], TRUE); 	 
                SetWindowText(B2,TEXT("Tap Tempo"));  
                SetWindowText(B1,TEXT("Start")); 
                spr1=clock(); 
                if (exitt==0) EnableWindow (B1, TRUE);  
                if (error==1) spr1=clock();       
             } }
	        break;

	        case 2:
                 if (started) CloseHandle(myHandle);
                 setVolume(255, 255);
                 PostQuitMessage(0);
            break;
            
            case 3:       
                 char napis[10];
                 tap2=clock();             
                 dif=difftime(tap2,tap1); 
                 if (dif<3000)
                 {  
                    tempo=60000/((int)dif);
                    if (tempo<=20) tempo=20;
                       if (tempo>=400) tempo=400;
                          SetWindowText(Opt[8],TEXT(itoa(tempo,napis,10)));
                          if(nsignature==2)
                          tempo=tempo/2;
                          if(nsignature==8)
                          tempo*=2;
                          if(nsignature==16)
                          tempo*=4;                
                              }
                             tap1=tap2;
                 t=tempo;
            break;
                   
            case 21:
                 EnableWindow (Opt[7], TRUE);
                 EnableWindow (Opt[9], TRUE);
                 EnableWindow (Opt[13], TRUE);
                 typ=1;
            break;
			
            case 22:
                 EnableWindow (Opt[7], TRUE);
                 EnableWindow (Opt[9], TRUE);
                 EnableWindow (Opt[13], TRUE);
                 typ=2;
            break;
			
            case 23:
                 typ=3;
            break;
            
            case 31:
                 dzwiek=1;
                 EnableWindow (Opt[21], TRUE);
                 EnableWindow (Opt[22], TRUE);
            break; 
			
            case 32:
                 dzwiek=2;
                 EnableWindow (Opt[21], FALSE);
                 EnableWindow (Opt[22], FALSE);                 
            break;  
            
            case 41:
                 MessageBox(hwnd,"UpBeat Metronome v1.0 by FX-Team:\n• FX\n• Michuu^^\n• Niko\nwww.fx-team.fulara.com\n\nNote:\nIf you want custom sounds,\nput files: 'a.wav' and 'b.wav' to .exe directory.","Info",0);
            break; 
                 
            //CHECKBOX
            case 61:                 
                 if (checkbox==0)
                 {
                                 for (i=15;i<=19;i++) EnableWindow (Opt[i], TRUE);
                                 checkbox=1;
                                 EnableWindow (Opt[14], FALSE);
                                 EnableWindow (Opt[14], TRUE);
                                 }
                                 
                 else if (checkbox==1)
                 {
                                 for (i=16;i<=19;i++) EnableWindow (Opt[i], FALSE);
                                 checkbox=0;
                                 EnableWindow (Opt[14], FALSE);
                                 EnableWindow (Opt[14], TRUE);
                                 }
			break;
        }
	break;
	          
      case WM_DESTROY:
      {
         if (started) CloseHandle(myHandle); 
         setVolume(255, 255);
         PostQuitMessage(0);
         break;
      }
  }
  return DefWindowProc(hwnd, msg, wParam, lParam);
}	

void OnSize(const HWND hwnd,int cx,int cy,UINT flags)
{
HWND hTrackbar=reinterpret_cast<HWND>(static_cast<LONG_PTR>
                                     (GetWindowLongPtr(hwnd,GWLP_USERDATA)));
}
