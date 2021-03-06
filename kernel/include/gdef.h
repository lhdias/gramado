/*
 * File: gdef.h
*
* Descri��o:
*     Defini��es globais. 
*     Ser� utilizado por todos os m�dulos. Deve ficar no in�cio.
*     Quando uma defini��o deve ser acessada por todos os m�dulos
*     do kernel base ela deve ficar aqui.
*
* @todo: FAZER O M�XIMO DE COISAS SISTEMICAMENTE N�O-IMPORTANTES PRIMEIRO.
         que n�o comprometam o sistema. como gui.
*/

/*
 * Sobre a GUI:
 * ============
 *     Um grid flutuante de janelas quadradas, 4 janelas.
 *     O message box pode ser um ret�ngulo abaixo do grid.
 *     Uma janela de terminal virtual igual � um celular. 
 * Desse modo, enquanto essas 6 janelas n�o s�o flutuantes, d� pra
 * ir usando elas desenha das no backbuffer mesmo.
 *
 *
 * divis�o da tela:   
 * quatro quadrantes de 10.
 * divide por vinte e multiplica pela quantidade desejada.
 *         (multiplicador*(total/20)) 
 */

/*
 Sobre o banco de dados:
 =======================
 
Tipos de contas:
    aspace e dspace, pessoais e conjuntas.
	
aspace:
    Um Address Space � uma conta de banco de dados em mem�ria. Uma conta 
pode ser do tipo conjunta(Shared) ou  pessoal(Personal). 

dspace:
    Um Disk Space � uma conta de banco de dados em disco. Uma conta pode 
ser do tipo conjunta(Shared) ou  pessoal(Personal). 

Donos das contas:
    Os processos s�o os clientes dos bancos de dados e s�o os donos das 
contas de bancos de dados.

Tipos de bancos:
    Kernel Data Base, Global Data Base e Local Data Base.

KDB:	
    Banco de dados do tipo kernel. � o banco de maior privil�gio, poucos
processos poder�o usar esse banco e as contas presentes nele.

GDB:
    Bancos de dados do tipo global. � o banco das contas conjuntas, para
que os processos possam compartilhar as contas e os dados que elas acessam.

LDB:
    Bancos de dados do tipo pessoal. � o banco das contas pessoais. Um 
processo pode ser dono de uma conta dessas para proteger seus dados
e revogar qualquer tipo de acesso e somente ele ter� acesso aos dados
dessa conta.
	
*/


#define FRONTBUFFER_ADDRESS 0xC0400000
#define BACKBUFFER_ADDRESS  0xC0800000

//#define FRONTBUFFER_VA 0xC0400000
//#define BACKBUFFER_VA  0xC0800000


//#define BIOS_FONT8X8 0x000FFA6E

//using gui flags.
#define GUI_ON   1
#define GUI_OFF  0

/*
 * Os Type:
 *     O sistema operacional pode ser usado como servidor.
 * Radando em uma m�quina real e acessado por um terminal
 * via rede LAN, ou porta serial. TTY.
 *     Qualquer sistema operacional em uma m�quina cliente pode
 * acessar o sistema operacional na maquina servidora. Pra isso
 * tem que ter um programa na m�quina cliente que envie comandos 
 * para a m�quina servidora atrav�s da placa de rede ou da porta 
 * serial.
 *     O sistema pode atuar como cliente.
 */
typedef enum {
	OsTypeClient,
	OsTypeServer,
	OsTypeHeadlessServer,  //Headless Server. ??	
}os_type_t;

//
// Enumerando os tipos de objetos.
// Obs: Deve ser o mesmo que as defini��es acima.
// As estruturas indicam o tipo de objeto que se pode criar.
// o primeiro �tem de uma estrutura deve ser a indica��o do tipo
// de objeto que ela representa.
// @todo: A ORDEM AQUI SEGUIR� A ORDEM DAS CLASSES DO SISTEMA.
//        COME�ANDO DA CLASSE RAM.
//
// Precisa ser uma defini��o global. pois todas estruturas v�o usar.
//
// Obs: Essa lista deve estar sincronizada com alista de fefini��es em object.h
//

//
//Obs: Esses poderiam ser os principais, e imut�veis
// deichando os vindouros como subsequentes � esses.
//

typedef enum {
	
	// **** EXECUTIVE  ****
	
	//ram
	//Nothing for now.	
    ObjectTypeNull,               //0 Null.
	ObjectTypeASpace,             //1 Address Space. (memory address)
	ObjectTypeDSpace,             //2 Disk Space.
	ObjectTypeBank,               //3 Bank. (banco de dados).
	//sm
	ObjectTypeChannel,            //4 executive sm.
	ObjectTypeDirectory,          //5 diret�rio de arquivos. executive sm.
	ObjectTypeHeap,               //6 heap executive sm
	ObjectTypeIoBuffer,           //7 i/o buffer executive sm
	ObjectTypeIpAddress,          //8 ip address executivesm.
	ObjectTypeProcessMemoryInfo,  //9 process memory info, executive sm.
	ObjectTypePhysicalMemoryInfo, //10 physical memory info, executive sm.
	ObjectTypeMemoryInfo,         //11 memory info, executive sm.
	ObjectTypeMemoryBlock,        //12 ????? @todo: Ver se esse pode ser Criado sem prejudicar a aloca��o din�mica. executive sm mm.	
	ObjectTypePageDirectory,      //13 page directory. executive sm, mm.	
	ObjectTypePageTable,          //14 pagepool , page table, executive ,sm,mm.	
	ObjectTypePageFrame,          //15 page frame ,executive ,sm,mm.
	ObjectTypeFramePool,          //16
	ObjectTypeSocket,             //17 sockets, executive, sm.
    ObjectTypeUserInfo,           //18 userinfo, executive, sm.
	//uigm 
	ObjectTypeDesktop,     //19 desktop, executive,uigm.	
	ObjectTypeMenuItem,        //20 menuitem, executive uigm.
	ObjectTypeMenu,        //21 menu, executive uigm.	
	ObjectTypeUserSession, //22 User session, executive, uigm.	
	ObjectTypeWindowProcedure,  //23 window procedure, executive, uigm.	
	ObjectTypeRectangle,        //24 rectangle, executive, uigm. 	
	ObjectTypeRGBA,             //25 rgba, executive, uigm. 
	ObjectTypeWindow,           //26 window, executive ,uigm.
	ObjectTypeWindowStation,  //27 desktop pool. window station, executive, uigm.
	//uitm.
	ObjectTypeConsole,        //28 console, executive, uitm.
    ObjectTypeLine,           //29 console line, executive, uitm.
	ObjectTypeTerminal,       //30 Terminal, executive, uitm.
	
    // **** MICROKERNEL  ****
	
	//microkernel
	ObjectTypeProcess,  //31 Process, microkernel.
	ObjectTypeSemaphore,  //32 semaphore, microkernel.	
	ObjectTypeThread,     //33 thread, microkernel.
	
	//io 
	//@todo: isso dever� ser criado aqui.
	ObjectTypeCpu,  //34
	ObjectTypeDma,  //35
	
	// **** HAL  ****
	
	ObjectTypeProcessor,  //36 processor, hal (talvez isso devesse ir para io de microkernel.)
	
	//device(unblocked e blocked).
	ObjectTypeDevice,      //37 device, hal
	ObjectTypeDiskInfo,    //38 disk info, hal.
	ObjectTypeProcessorBlock, //39 processor block hal...(pode ir para io,microkernel)
    ObjectTypeHostInfo,  //40 HostInfo, hal. 
	ObjectTypeKeyboard,   //41 keyboard, hal.
	ObjectTypeMacAddress,  //42 MAC Address, hal.
	ObjectTypeMemory,      //43 memory card info, hal.
	ObjectTypePciDevice,   //44 PCI device info, hal.
	ObjectTypePciDeviceDriver,   //45 PCI device driver info, hal.
	ObjectTypePIC, //46 pic controller, hal.
	ObjectTypeRTC, //47 rtc controller, hal.
	ObjectTypeScreen, //48 Screen, hal.
	ObjectTypeTimer,    //49 ?? timer ,hal.	
	ObjectTypeVideo,    //50 video ,hal.
	ObjectTypeVolume,    //51 disk volume ,hal.
	
	//things
	//@todo:
	
	// **** OUTROS  ****
	ObjectTypeCursor,    //52 /include.
	ObjectTypeRequest,   //53 request de kernel /include.
	ObjectTypeSignal,    //54
	ObjectTypeFile,      //55 file, /include. stdio.
	ObjectTypeMetafile, //56 
	ObjectTypeMutex,    //57
	ObjectTypeToken,    //58 Token de acesso � objetos. (access token)
	ObjectTypeFont,    //59
	ObjectTypeIcon,     //60
	ObjectTypePipe,     //61
	
	ObjectTypeGroup,     //62
	ObjectTypeUser,      //63
	
	ObjectTypeComputer,      //64
	ObjectTypeCpuRegister,   //65
	
	
	ObjectTypeDisk,   //66
	ObjectTypeDiskPartition,   //67 //info struct
	ObjectTypeGDT,   //68
	ObjectTypeLDT,   //69
	ObjectTypeIDT,   //70
	ObjectTypeTSS,   //71
	
	ObjectTypePort,  //72 (i/o port)
	ObjectTypeController, //73
	ObjectTypeKM, //74
	ObjectTypeUM, //75
	ObjectTypeColorScheme,  //76
	//...
}object_type_t;

//
// Enumerando classes de objetos. (categorias)
//
typedef enum {
	ObjectClassKernelObjects,  // Kernel Objects.
	ObjectClassUserObjects,    // User Objects.
	ObjectClassGuiObjects,     // Graphical User Interface Objects.
	ObjectClassCliObjects,     // Command Line Interface Objects.
    //...	
}object_class_t;


/*
 * PPL - (Process Permition Level).
 *
 * Determina as camadas de software que um processo ter� acesso
 * irrestrito.
 *
 * + A permiss�o natural de um processo de usu�rio � K5. Podendo ele
 * utiliza somente os servi�os oferecidos pela camada K5, que � 
 * a mais alta.
 * 
 * + A permiss�o natural dos m�dulos do kernel em user mode podem ser
 *   diferente, variando de K0 � K4. Mas nada impede dos m�dulos
 *   usarem a permiss�o K5. Um m�dulo em kernel mode fabricado por usu�rios
 *   poderiam receber apenas a permiss�o K5. As outras permiss�es
 *   seriam concedidas somente com licensa paga, ou para que fabrica
 * o sistema operacional.
 *
 * + Servidores em user mode poder�o ter qualquer um dos n�veis.
 *   Mas a permiss�o natural seria K5. As licensas para servidores
 * em user mode s�o mais baratas.
 *
 *   Obs: Categorizar os servidores de acordo com o n�vel de permiss�o
 * pode melhorar a organiza��o do sistema, tendo em vista que as permiss�es
 * seguem o padr�o de classes do sistema, que uma interconex�o l�gica
 * de dispositivos.
 */
typedef enum {
	pplK0, //executive, (ram),sm,uigm,uitm.
	pplK1, //microkernel,(io),cpu.
	pplK2, //microkernel,(io),dma.
	pplK3, //hal,(device),unblocked.
	pplK4, //hal,(device),blocked.
	pplK5, //hal,(things).
}process_permition_level_t; 




unsigned long g_backbuffer_address;            //0xC0800000
unsigned long g_frontbuffer_buffer_address;    //LFB. Endere�o f�sico do frontbuffer(mem�ria da placa de v�deo). 
unsigned long g_frontbuffer_buffer_va;    //endere�o l�gico do frontbuffer.





int gNextKeyboardMessage;

//
// End.
//

