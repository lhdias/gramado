/*
 * File: char.c
 *
 * Descri��o:
 *     Constr�i caractere em modo gr�fico.
 *     Desenha o caractere pixel por pixel.
 *     Faz parte do m�dulo Window Manager do tipo MB.
 * Obs: A fonte usada � a fonte 8x8 que est� na ROM BIOS. em 0x000FFA6E.
 *
 * Vers�o 1.0, 2015.
 */

 
#include <kernel.h>


//
// @todo: Criar uma estrutura para o char. entre os elementos
// pode ter os buffer para o char. backbuffer, frontbuffer, dedicatedbuffer.
//
//


//
// charDirectCharBuilt: 
//     Desenha um caractere diretamente no frontbuffer.
//     Obs: Requer sincroniza��o vertical.
//     Obs: A sincroniza��o � feita antes de desenha o caractere e n�o
// a cada pixel enviado.
//
//void charDirectCharBuilt( void* FrontBuffer, unsigned long x, unsigned long y, unsigned long color, unsigned long c);
//void charDirectCharBuilt( void* FrontBuffer, unsigned long x, unsigned long y, unsigned long color, unsigned long c)
//{
//    return; //Ainda n�o implementada.	
//}


/*
 * my_buffer_char_blt:
 *     Constr�i um caractere 8x8 no buffer.
 */
//void charBuiltCharBackBuffer( unsigned long x, unsigned long y, unsigned long color, unsigned long c)
void my_buffer_char_blt( unsigned long x, 
                         unsigned long y, 
						 unsigned long color, 
						 unsigned long c)
{
	int x2;
    int y2;
    unsigned char bit_mask = 0x80;	
    char *work_char;  
    struct window_d *hWindow;			
	  
    //
	// Window Terminal.
	//
	
	/*
	if( VideoBlock.useGui == 1 )
	{
        //se existe um terminal.
		if( (void *) terminal != NULL )
        {
		    if( (void*) terminal->window != NULL )
			{
			    hWindow = (void*) terminal->window;
			
			    x = hWindow->left + x;
			    y = hWindow->top + y;
			};
			
		};		
    };	
	*/
	  
	  
    /*
	 * @todo: 
	 *     +Criar vari�veis internas para tamanho de fonte.
	 *     +Pegar as informa��es em uma estrutura.
	 *     ...
	 */
	 
    //int CharWidth;
	//int CharHeight;  
	  
	  
    /*
	 * Get the font pointer.
	 *
	 * @todo:
     *     usar variavel g8x8fontAddress.	 
	 *     + Criar e usar uma estrutura para fonte.
	 *     + Usar o ponteiro para a fonte atual que foi carregada.
	 *     + Criar um switch para o tamanho da fonte.
	 *     ...
	 */
	 
    if( gfontAddress == 0 || 
	    gcharWidth == 0 || 
		gcharHeight == 0 )
	{
	    gfontAddress = (unsigned long) 0x000FFA6E;    //ROM bios.
		gcharWidth = 8;
		gcharHeight = 8;
	};

 	//
	// O caractere sendo trabalhado.
	// Offset da tabela de chars de altura 8 na ROM.	
    //
	
	work_char = (void *) gfontAddress + (c * gcharHeight);
    //work_char = (void *) 0x000FFA6E + (c * 8);

	//
	// Draw.
	//
	
    for( y2 = 0; y2 < gcharHeight; y2++ )
    {
        bit_mask = 0x80;

        for( x2 = 0; x2 < gcharWidth; x2++ )
        {
			//
			// @todo: o nome dessa rotina de putpixel ser� mudado.
			//
			
            if( (*work_char & bit_mask) )
                my_buffer_put_pixel(color, x + x2, y, 0);  //Put pixel.
                bit_mask = (bit_mask >> 1);                //Rotate bitmask.
        };
		
		y++;            //Pr�xima linha da 8 linhas do caractere.
		work_char++;   
	};
	
	//
	// Algo mais ?
	//
 
done:
    return;  	         	   
};


/*
int charInit()
{}
*/

//
//fim
//

