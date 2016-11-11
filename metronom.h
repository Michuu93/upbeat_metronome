const int dlugosc=500;  //dlugosc sciezki
static char nazwa[dlugosc],nazwaa[dlugosc],nazwag[dlugosc],nazwab[dlugosc]; 

void play(bool a)
{
     if (wav)
       PlaySound(a ? nazwaa : nazwab ,NULL,SND_ASYNC|SND_FILENAME);
       else
       PlaySound(MAKEINTRESOURCE(a ? id_wava : id_wavb),NULL,SND_ASYNC|SND_RESOURCE);
}
     
////BEEP DOWNBEAT/////////////////////////////////////
void metronom(int a, int b, int m, int loud, int silent, int checkbox)
{  
     int c;                   
     int suma,stoper,stoper0,d;        //licznik
     stoper=0;
     suma=loud+silent;
     stoper0=1;
do
{       
    if(checkbox==0)
	{ 
      d=60000/t;
      c=60000/t/10;      //dlugosc beepa  
      SetWindowText(B2,TEXT("Tap Tempo"))  ;    
     Beep(stoper%m==0? b : a ,c);   //akcent na raz    
     SetWindowText(B2,TEXT(""));
	 Sleep(d-c);
     stoper++; 
    }
     else
     {
         if(stoper0<=loud)
		 {
                          d=60000/t;
          c=60000/t/10;      //dlugosc beepa
        SetWindowText(B2,TEXT("Tap Tempo"))  ; 
         Beep(stoper%m==0? b : a ,c);   //akcent na raz 
          SetWindowText(B2,TEXT(""))  ; 
         Sleep(d-c);
         stoper++; 
         }
         else
         {
        
             Sleep(60000/t);
             
             stoper++; 
                       if(stoper%m==0) 
                       if(stoper0>=suma) stoper0=0;
             }
     } 
     if(stoper%m==0)
     stoper0++;
}
     while(started);  
     exitt=0;  
}


////BEEP UPBEAT//////////////////////////////////////////////
void synkopy(int a, int b, int m, int loud, int silent, int checkbox)
{
     int c,d;
     d=((60000/t)/2); 
     
     m*=2;              //zwiekszenie podzialu metrum
     
     int suma,stoper,stoper0;        //licznik  
     stoper=1;
     suma=loud+silent;
     stoper0=1;                       
     
do
{ 
	if(checkbox==0)
	{                      
     d=((60000/t)/2);
     if (stoper%m==1)
     {
                     c=60000/t/10;
                     SetWindowText(B2,TEXT("Tap Tempo"))  ; 
                      Beep(b,c); 
                      SetWindowText(B2,TEXT(""))  ; 
                      d=d-c;
                      }            
        else if (stoper%2==0) {
             c=60000/t/10;
             SetWindowText(B2,TEXT("Tap Tempo"))  ; 
              Beep(a,c); 
              SetWindowText(B2,TEXT(""))  ; 
              d=d-c;
              }              
      Sleep(d);
      stoper++;       
    }      
     else
     {
         if(stoper0<=loud)
		{                           
			d=((60000/t)/2);
			if (stoper%m==1) {
                             c=60000/t/10;
                             SetWindowText(B2,TEXT("Tap Tempo"))  ; 
                              Beep(b,c); 
                              SetWindowText(B2,TEXT(""))  ; 
                              d=d-c;
                              
                              }           //akcent na raz       
			else if (stoper%2==0) {
                 c=60000/t/10;
                SetWindowText(B2,TEXT("Tap Tempo"))  ; 
                  Beep(a,c);
                  SetWindowText(B2,TEXT(""))  ; 
                   d=d-c;}              
			Sleep(d);
			stoper++;       
		}    
        else
        {
             d=((60000/t)/2);
             Sleep(d);         
             if(stoper%m==0) 
				if(stoper0>=suma) 
				stoper0=0;
				stoper++; 
        }
     }   
     if(stoper%m==1)
     stoper0++;
     }         
     while(started);     
     exitt=0;
}


////BEEP SWING//////////////////////////////////////////////////////
void swing(int a, int b, int m, int loud, int silent, int checkbox)
{
    int c,d;
           
    int suma,stoper,licznik;        //licznik  
    stoper=3; 
    suma=loud+silent;
    licznik=m;                                 

do
{
	if(checkbox==0)
	{   
     d=((60000/t)/3);  
     if (stoper%3==0) {
                      c=60000/t/10;
                      SetWindowText(B2,TEXT("Tap Tempo"))  ; 
                       Beep(a,c);
                       SetWindowText(B2,TEXT(""))  ; 
                        d=d-c;}    //akcent 
        else if (stoper%3==2) {
             c=60000/t/10;
            SetWindowText(B2,TEXT("Tap Tempo"))  ; 
              Beep(b,c);
              SetWindowText(B2,TEXT(""))  ; 
               d=d-c; 
               licznik++;}                                         
     Sleep(d);
     stoper++; 
    }
    else
	{
        if((licznik/m)<=loud)
			{
				d=((60000/t)/3);  
				if (stoper%3==0) {
                                 c=60000/t/10;
                              SetWindowText(B2,TEXT("Tap Tempo"))  ; 
                                  Beep(a,c);
                                 SetWindowText(B2,TEXT(""))  ; 
                                   d=d-c;}   //akcent     
					else if (stoper%3==2) {
                         c=60000/t/10;
                       SetWindowText(B2,TEXT("Tap Tempo"))  ; 
                          Beep(b,c); 
                     SetWindowText(B2,TEXT(""))  ; 
                          d=d-c;
                            licznik++;}                                      
				Sleep(d);
				stoper++; 
			}
		else
			{
				d=(60000/t);
				for (int i=1;i<=m;i++) 
					{ 
						Sleep(d);  
						licznik++; 
                    }                  
                      if(licznik/m>=(suma+1)) licznik=m; 
			}		 
	}
}
     while(started);
     exitt=0;     
}


////WAV DOWNBEAT/////////////////////////////////////////////////////////////
void metronomw(int m, int loud, int silent, int checkbox)
{                         
    int suma, stoper, stoper0,c,d;           //licznik
    stoper=0;
    suma=loud+silent;
    stoper0=1;    
    
 
do
{  
    if(checkbox==0)
		{         
                   d=60000/t;
                   c=60000/t/10;  
                   SetWindowText(B2,TEXT("Tap Tempo"))  ;             
			if(stoper%m==0) play(false);//PlaySound(MAKEINTRESOURCE(id_wavb),NULL,SND_ASYNC|SND_RESOURCE);
                else play(true);//PlaySound(MAKEINTRESOURCE(id_wava),NULL,SND_ASYNC|SND_RESOURCE); 
                Sleep(c);      
        SetWindowText(B2,TEXT(""))  ; 
			Sleep(d-c);
     
			stoper++;        
		}  
    else
		{
			if(stoper0<=loud)
				{
                             d=60000/t;
                             c=60000/t/10;  
                   SetWindowText(B2,TEXT("Tap Tempo"))  ;  
                    if(stoper%m==0) play(false);//PlaySound(MAKEINTRESOURCE(id_wavb),NULL,SND_ASYNC|SND_RESOURCE);
						else play(true);//PlaySound(MAKEINTRESOURCE(id_wava),NULL,SND_ASYNC|SND_RESOURCE); 
						Sleep(c);      
        SetWindowText(B2,TEXT(""))  ; 
					Sleep(d-c);
					stoper++;
				}
			else 
				{
					Sleep(d);
					stoper++;
						if(stoper%m==0) 
							if(stoper0>=suma) stoper0=0;
                }
		}
    if(stoper%m==0)
		stoper0++;
}
while(started); 
exitt=0;    
}


////WAV UPBEAT///////////////////////////////////////////////
void synkopyw(int m, int loud, int silent, int checkbox)
{
     int d;
     
     
     m*=2;              //zwiekszenie podzialu metrum     
        
     int suma, stoper, stoper0,c;        //licznik  
     stoper=1;
     suma=loud+silent;
     stoper0=1;           
 
do
{  
    if(checkbox==0)
		{       
                d=(60000/t)/2;
                c=60000/t/10;  
                    if (stoper%m==1 || stoper%2==0) SetWindowText(B2,TEXT("Tap Tempo"))  ; 
			if (stoper%m==1) PlaySound(MAKEINTRESOURCE(id_wava),NULL,SND_ASYNC|SND_RESOURCE);   //akcent na raz  
				else if (stoper%2==0) PlaySound(MAKEINTRESOURCE(id_wavb),NULL,SND_ASYNC|SND_RESOURCE);  
                	Sleep(c);      
        SetWindowText(B2,TEXT(""))  ;       
			Sleep(d-c);
			stoper++;             
		}   
    else
		{
			if(stoper0<=loud)
				{
                             d=(60000/t)/2;
                             c=60000/t/10; 
                             if (stoper%m==1 || stoper%2==0) SetWindowText(B2,TEXT("Tap Tempo"))  ; 
                    if (stoper%m==1) PlaySound(MAKEINTRESOURCE(id_wava),NULL,SND_ASYNC|SND_RESOURCE);   //akcent na raz  
						else if (stoper%2==0) PlaySound(MAKEINTRESOURCE(id_wavb),NULL,SND_ASYNC|SND_RESOURCE);  
						Sleep(c);      
        SetWindowText(B2,TEXT(""))  ; 
					Sleep(d-c);      
					if(stoper%m==0) 
						if(stoper0>=suma) 
							stoper0=0;
					stoper++; 
				}
			else
				{
                    
					d=((60000/t)/2);
					Sleep(d);
					if(stoper%m==0) 
						if(stoper0>=suma) 
							stoper0=0;
					stoper++; 
				}
		}
    if(stoper%m==1)
		stoper0++;
}                  
while(started);
exitt=0;
}

///WAV SWING/////////////////////////////////////////////////
void swingw(int m, int loud, int silent, int checkbox)
{ 
    int d,suma,stoper,licznik,c;      //licznik  
    stoper=3; 
	suma=loud+silent;
	licznik=m;         

do
{  
	if(checkbox==0)
		{ 
			d=((60000/t)/3); 
			 c=60000/t/10; 
                             if (stoper%3==0 || stoper%3==2) SetWindowText(B2,TEXT("Tap Tempo"))  ; 
			if (stoper%3==0) PlaySound(MAKEINTRESOURCE(id_wava),NULL,SND_ASYNC|SND_RESOURCE);     
				else if (stoper%3==2) {PlaySound(MAKEINTRESOURCE(id_wavb),NULL,SND_ASYNC|SND_RESOURCE); licznik++;}//akcent  
				Sleep(c);      
        SetWindowText(B2,TEXT(""))  ;  
			Sleep(d-c);
			stoper++; 
		}  
	else
		{
			if((licznik/m)<=loud)
				{
					d=((60000/t)/3); 
					c=60000/t/10; 
                             if (stoper%3==0 || stoper%3==2) SetWindowText(B2,TEXT("Tap Tempo"))  ; 
				    if (stoper%3==0) PlaySound(MAKEINTRESOURCE(id_wava),NULL,SND_ASYNC|SND_RESOURCE);     
						else if (stoper%3==2) {PlaySound(MAKEINTRESOURCE(id_wavb),NULL,SND_ASYNC|SND_RESOURCE); licznik++;}//akcent 
                        Sleep(c);      
        SetWindowText(B2,TEXT(""))  ;   
					Sleep(d-c);
					stoper++; 
				}
			else
				{
					d=(60000/t);
					for (int i=1;i<=m;i++) 
						{ 
							Sleep(d);  
							licznik++; 
						}                  
                    if(licznik/m>=(suma+1)) licznik=m; 
				}
		}
}
while(started);
exitt=0;
}


/////////////*PROGRAM GLOWNY*/////////////
int main_metronom(int typ, int dzwiek, int metrum, int loud,int silent, int checkbox, int nsignature)
{    
    if(nsignature==2)
    tempo=tempo/2;
    if(nsignature==8)
    tempo*=2;
    if(nsignature==16)
    tempo*=4;
    t=tempo;
    
    int a,b;
    a=440;  //czestotliwosc beepa
    b=880;  //czestotliwosc beepa akcentujacego   
    
                          
    getcwd(nazwag,dlugosc);
    strcpy (nazwaa,nazwag);
    strcat (nazwaa, "\\a.wav");
    strcpy (nazwab,nazwag);
    strcat (nazwab, "\\b.wav");
 
           switch(typ)
            {
                  case 1: 
                       if (dzwiek==1) metronomw(metrum, loud, silent, checkbox);
                       else metronom(a,b,metrum,loud, silent, checkbox);
                       break;
                  case 2:
                       if (dzwiek==1) synkopyw(metrum, loud, silent, checkbox);
                       else synkopy(a,b,metrum,loud, silent, checkbox);
                       break;
                  case 3:
                       if (dzwiek==1) swingw(metrum, loud, silent, checkbox);
                       else swing(a,b,metrum,loud, silent, checkbox);
                       break;
                  default: 
                           SetWindowText(B2,TEXT("Tap Tempo"))  ; 
                           exitt=0; 
                  break;
            }
            
    SetWindowText(B2,TEXT("Tap Tempo"))  ; 
    exitt=0; 
    return 0;
}
