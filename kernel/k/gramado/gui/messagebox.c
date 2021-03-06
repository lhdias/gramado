/*
 * File: gui\messagebox.c
 *
 * Descri��o:
 *     Mostra um Message Box na tela.
 *     Faz parte do m�dulo Window Manager do tipo MB.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2017 - Revision.
 */

 
#include <kernel.h>


unsigned long MessageBoxProcedure( struct window_d *window, 
                                   int msg, 
								   unsigned long long1, 
								   unsigned long long2 );

								   
	
/*
void messageboxIn(int type, char *title, char *string);
void messageboxIn(int type, char *title, char *string)
{
	//@todo: melhorar esse filtro.
    if( (void*) gui->shellWindow == NULL ){
		return;
	};
	
	MessageBox( (struct window_d *) gui->shellWindow, (int) type, (char *) title, (char *) string );
    return;				 
};
*/	

/*
void messageboxOut(struct window_d *parent_window, int type, char *title, char *string);
void messageboxOut(struct window_d *parent_window, int type, char *title, char *string)
{	
	MessageBox( (struct window_d *) parent_window, (int) type, (char *) title, (char *) string );
    return;				 
};
*/	

								   
/*
 * MessageBox:
 *     Cria uma Window Frame e apresenta uma mensagem nela.
 *     
 */
void MessageBox( struct window_d *parent_window,  //Window frame handle.      
                 int type,                        //Message Box type.
				 char *title,                     //Title for the window frame.
				 char *string )                   //Message string.
{	
	//
	// Set up.
	//
	
	//Elementos.
	int Button = 0;
	int Icon = 0;
	//continua...
	
	//unsigned long x  = (unsigned long) (1*(800/3));	
	//unsigned long y  = (unsigned long) (1*(600/3));
    //unsigned long cx = (unsigned long) (1*(800/3));
    //unsigned long cy = (unsigned long) (1*(600/3));	

    //ret�ngulo abaixo do grid.
	
	//x
	unsigned long x  = (unsigned long) (800 -320 -2); //deslocamento x
    unsigned long cx = (unsigned long) 320; //largura   
	
	//y
	unsigned long y  = (unsigned long) (600 -240 -2 -240 -2); //deslocamento y
    unsigned long cy = (unsigned long) 240; //altura	

	
	struct window_d *hWnd;    //Window.
	struct window_d *pWnd;    //Parent.
	struct window_d *bWnd;    //Button.

	
	//No GUI.
	if(VideoBlock.useGui != 1){
		printf("MessageBox: No GUI\n");
	    return;	
	};
	
	if( (void*) gui->screen == NULL ){
	    return;
	};
	
	// Parent.
	if( (void*) parent_window == NULL ){
	    pWnd = gui->screen;
	}else{
	    pWnd = (void*) parent_window;
	};
	
	
	//
	// Quando criamos um message box, criamos uma janela.
	// do tipo que tem bot�o. ??
	//
	
	
//creatingFrame:
	
	// Creating a Window Frame for the Message Box. 
	// Obs: N�o queremos muitos tipos, isso � desnecess�rio.
	
	switch(type)
	{
		//
		// 765432(D=1) ??
		//
				
	    // Com bot�o, considera o t�tulo.
	    case 1:
		    Button = 1;
	        hWnd = (void*) CreateWindow( 3, 0, 0, title, x, y, cx, cy, pWnd, 0, COLOR_WHITESMOKE, COLOR_WINDOW); 
		    break;
			
		// Sem bot�o, considera o t�tulo.	
	    case 2:
		    Button = 0;
	        hWnd = (void*) CreateWindow( 3, 0, 0, title, x, y, cx, cy, pWnd, 0, COLOR_WHITESMOKE, COLOR_WINDOW); 
	        break;
			
		// Com bot�o, T�tulo de alerta.	
	    case 3:
	        Button = 1;
			hWnd = (void*) CreateWindow( 3, 0, 0, "Alert", x, y, cx, cy, pWnd, 0, COLOR_WHITESMOKE, COLOR_WINDOW); 
	        break;
			
		//Com bot�o, t�tulo de mensagem do sistema.	
	    case 4:
		    Button = 1;
	        hWnd = (void*) CreateWindow( 3, 0, 0, "System Message", x, y, cx, cy, pWnd, 0, COLOR_WHITESMOKE, COLOR_WINDOW); 
	        break;
			
		//Tipo negligenciado. Usamos o formato padr�o.	
		default:
		    Button = 1;
	        hWnd = (void*) CreateWindow( 3, 0, 0, "Error", x, y, cx, cy, pWnd, 0, COLOR_WHITESMOKE, COLOR_WINDOW); 
		    break;
	};
	
	//
    // Register.
	//
	
	if((void*) hWnd == NULL){
	    printf("MessageBox:");
		refresh_screen();
	    while(1){};
	}else{   
		
		RegisterWindow(hWnd);
        set_active_window(hWnd);
		
		//@todo: O foco deve estar no bot�o e n�o na janela ativa ??
		SetFocus(hWnd);  	 
		//...
	};
	
	//
	// Icon
	//
	//if ( Icon == 1){};
	
	//
    // String. (Uma string dentro da client area.)
    //
	
	//@todo: Calcular o tamanho da string.
	//size_t S;
	//S = (size_t) strlen( (const char*) string);
	
d_string:
	draw_text( hWnd, 1*(cx/16), (cy-16), COLOR_WINDOWTEXT, string);

	//
    // Button: 
	//    (Um bot�o dentro da client area.)
    //    @todo: � preciso criar um bot�o do tipo janela.
	//           para colocar foco na janela.
	//
	//
	//
d_button:	
    if(Button == 1)
	{
		//@todo: Criar uma janela do tipo bot�o para setar o foco.
        //       Pegar o tamanho da string para definir o tamanho do bot�o.
        draw_button( hWnd, "Close", 1, (cx-56-8), (cy-24-8), 56, 24, COLOR_BUTTONFACE); 
		//draw_button( hWnd, "Close", 1, 12*(cx/16), 8*(cy/16), 48, 24, COLOR_BLACK);		
    
	    //   
	    // @todo: FOCO NO BOT�O !!!
	    //
		
		//SetFocus(??);
	};
	
/*
    ** Outra maneira de cria um bot�o ***
    ** Obs: Retorna o haldle da janela **
    ** Obs: Precisamos de um handle para setar o foco. ***
	** e o bot�o ter� o message box como janela m�e.
	
        bWnd = CreateWindow( 11, 0, 0, "Close", 
		                     cx-102, y+2, 100, 24, 
							 hWnd, 0, 0, 0);
							 
	    if( (void*) bWnd == NULL )
	    {
	        printf("MessageBox error: Button Struct.\n");
		    refresh_screen();
	        while(1){};
	    }
	    else
	    {
		    SetFocus(bWnd);   //o bot�o tem o foco de entrada.
			RegisterWindow(bWnd); 
	    };	
*/		
	
	
	//
	// Continua ...
	//
	
	CurrentWindow = (void*) hWnd;
	SetProcedure( (unsigned long) &MessageBoxProcedure );	
	
done:
    //SetFocus(bWnd);    //@todo: Setar foco no bot�o.		
    refresh_screen();		   
    return;
};


/*
 * MessageBoxProcedure:
 *     O procedimento padr�o de message box.
 */																
unsigned long 
MessageBoxProcedure( struct window_d *window, 
                     int msg, 
   				     unsigned long long1, 
					 unsigned long long2 )
{
    switch(msg)
	{
        case MSG_KEYDOWN:
            switch(long1)
            {
                case VK_ESCAPE:	
				    SetProcedure( (unsigned long) &system_procedure);
                    return (unsigned long) 0;				   
				    break;
				   
                default:
				    return (unsigned long) 0;
                    break; 
            };
        break;
	
        case MSG_SYSKEYDOWN:                 
            switch(long1)	       
            {	
				//Test.
				case VK_F1:
				    //DestroyWindow(window);
                    break;
					
                case VK_F2:
				    //Nothing.
					break;
									
				default:
				    return (unsigned long) 0;
				    break;
		    };              
        break;
		
	    case MSG_SYSKEYUP:
		   return (unsigned long) 0; 
           break;
		
        //@todo case command .. button ??
		
		default:
		    return (unsigned long) 0;
            break;		
	};
	
	
done:
	//Refresh screen. 
	if(VideoBlock.useGui == 1){
	    refresh_screen();
	};	
	return (unsigned long) 0;
};

/*
?? Pra qu� ??
int messageboxInit()
{}
*/

//
// End.
//

