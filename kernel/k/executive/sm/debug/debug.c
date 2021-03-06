/*
 * File: debug.c
 *
 * Modulo Debug.
 * MB - M�dulos inclu�dos no Kernel Base.
 *	
 * Descri��o:
 *     Kernel Debugger.
 *     Arquivo princial do m�dulo debug do executive do kernel.
 *     Checar se h� falhas no sistema. 
 *     Como um dr watson.
 * 
 * Obs:
 *     As fun��es aqui s�o usadas pelo kernel.
 *     Mas pode haver um aplicativo que utilizem essas fun��es.
 *
 * Obs:
 *     @todo: Come�ar a an�lise pela estrutura 'platform' e todo
 * o que est� dentro dela.
 *
 *
 * Vers�o: 1.0, 2015, 2016.
 */

 
#include <kernel.h>


// Vari�veis internas.
//int debugStatus;
//int debugError;
//...

//
// Estruturas para fases de inicializa��o.
// De uso interno no debug.
// Just for fun.

typedef enum {
   MYTHIC,  	
   ROMANTIC,   
   REALIST,   
   NATURALIST,   
}MindType_t;

typedef struct Mind_d Mind_t;
struct Mind_d
{
    unsigned long Mythic;
	unsigned long Romantic;
	unsigned long Realist;
	unsigned long Naturalist;	
};
Mind_t Mind;




//Internas.
void InitMind();
void SetMind(int Type);



/*
 teste de stress na cria��o de threads.
int debug_test_threads();
int debug_test_threads()
{
	//if( (void*) IdleThread == NULL ){
		//
	//};	
};
*/



//Construtor.
void InitMind()
{
	//if((void*) Mind == NULL)
    //    return;     
			
    Mind.Mythic = 0;
	Mind.Romantic = 0;
	Mind.Realist = 0;
	Mind.Naturalist = 0;	
};


void SetMind(int Type)
{
	//if((void*) Mind == NULL)
    //    return;
		 
    switch(Type)
    {
    	case MYTHIC:     Mind.Mythic = 1;      break;
    	case ROMANTIC:   Mind.Romantic = 1;    break;
		case REALIST:    Mind.Realist = 1;     break;
		case NATURALIST: Mind.Naturalist = 1;  break;
    	
		default:
		    InitMind();
    		break;
	};
};


/*
 * debug_check_inicialization:
 *     Checar se o kernel e os m�dulos foram inicializados.
 *     Checa o valor das flags.
 *     checar todos contextos de tarefas v�lidas.
 */
int debug_check_inicialization()
{
    int Status = 0;
		
	//Check phase.
	if(KeInitPhase != 3){
	   Status = 1;
	   printf("debug_check_inicialization: Initialization fail! fase={%d} \n",KeInitPhase);
	   goto fail;
	};
	SetMind(NATURALIST);
	
	// Executive.
	if(Initialization.executive != 1){
	   Status = 1;
	   printf("debug_check_inicialization: Executive fail!\n");
	   goto fail;
	};
	SetMind(REALIST);
	
	
	// Microkernel.
    if(Initialization.microkernel != 1){
	   Status = 1;
	   printf("debug_check_inicialization: Microkernel fail!\n");
	   goto fail;
	};
	SetMind(ROMANTIC);
	
	// Hal.
    if(Initialization.hal != 1){
	   Status = 1;
	   printf("debug_check_inicialization: Hal fail!\n");
	   goto fail;
	};
	SetMind(MYTHIC);
	
	
	//More?!
	
// Done! 
done:
    return (int) Status;
fail:
	if(VideoBlock.useGui == 1){
	    refresh_screen();
	};
	while(1){}; 
};




/*
 * debug_check_drivers:
 *    Checar se os drivers est�o inicializados.
 */
int debug_check_drivers()
{
	int Status = 0;
    
	if(g_driver_hdd_initialized != 1){
	    //erro
	};
	
	if(g_driver_keyboard_initialized != 1){
	    //erro
	};
	
    if(g_driver_pci_initialized != 1){
	    //erro
	};
	
    if(g_driver_rtc_initialized != 1){
	    //erro
	};
	
    if(g_driver_timer_initialized != 1){
	    //erro
	};
	
done:
    return (int) Status;
};



/*
 * debug_breakpoint:
 *     Para a execu��o do sistema.
 *     @todo: isso pode ir para o arquivo debug.c.
 */
void debug_breakpoint()
{
    printf("debug_breakpoint:");
    if(VideoBlock.useGui == 1){
	    refresh_screen();   
    }; 
	while(1){};
};


//retorna um checksum dado um buffer e um tamanho.
unsigned long debug_compute_checksum( unsigned char *Buffer, unsigned long Lenght)
{
    unsigned long CheckSum = 0;

    while(Lenght > 0){	
		CheckSum = CheckSum + (unsigned long) *Buffer++;
	    Lenght--;	
	};
	return (unsigned long) CheckSum;
};



/*
 * debug:
 *     Checa por falhas depois de cumpridas as tr�s fases de inicializa��o.
 */
int debug()
{   
	int Status;
		
	//printf("debug: Starting..\n");
	
	//Contrutor.
	InitMind();
	
	//
	// Checa inicializa��o. Fases, vari�veis e estruturas.
	//
	
	Status = (int) debug_check_inicialization();
	if(Status == 1){
	   printf("debug fail: Initialization.\n");
	   refresh_screen();
	   while(1){}
	};
	
    // Estrutura 'processor'.	
	if( (void*) processor == NULL ){
	    printf("debug fail: Struct.\n");
		refresh_screen();
		while(1){}
	};

	//Check drivers status. 
	//( Ver se os principais drivers est�o inicializados )
	debug_check_drivers();
	
	
	/*
	 * @todo: 
	 *     Checar se existe componentes do sistema como mbr, root, fat 
	 * e arquivos e programas b�sicos do sistema.
	 *
	 */
	 
	 
	/* 
	 * @todo: 
	 *     Checar por falhas no sistema de arquivos.
	 */
	 
	 
	 
	/*
     * @todo:	
	 *     Checar por falhas nas estruturas de tarefas.
	 */

    //
	// Antes do logon s� tem a Thread idle. 
	// Checar a estrutura da PID 0.
	// 
	 
	if( (void*) threadList[0] == NULL ){
	    printf("debug fail: TID 0!\n");
		refresh_screen();
		while(1){}
	};
	
	

	 
	//
    //
    //
	
	//...

done:
    //printf("debug:OK!\n");
    //printf("debug: Done.\n");	
	return (int) 0; 
};


/*
int debugInit()
{}
*/

//
// End.
//

