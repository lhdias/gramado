/*
 * File: microkernel\create.c
 *
 * Descri��o:
 *     Rotinas de cria��o de processos e threads.
 *     Faz parte do Process Manager, parte fundamental do Kernel Base.
 *     ?? Criar, cria a estrutura. ??
 *     ?? Inicializar inicializa estrutura passada por argumento. ??
 *
 * @todo: 
 *     Separar as rotinas de cria��o de inicializa��o de threads e processos, 
 * pois assim pode haver algum tipo de reaproveitamento, apenas reinicializando 
 * a thread.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 *     ...
 */

 
#include <kernel.h>

//
// Fun��es importadas.
//

extern unsigned long get_page_dir();



/*
 * KeCreateProcess:
 *     Interface para cria��o de um processo.
 * @todo: 
 *     Erro. Rotinas come�adas com 'Ke_' servem para chamar servi�os de 
 * m�dulos externos.
 */
void *KeCreateProcess( struct wstation_d *window_station,
                       struct desktop_d  *desktop,
                       struct window_d *window,
                       unsigned long init_eip, 
                       unsigned long priority, 
					   int ppid, 
					   char *name )
{
    //
	// @todo: Create some interface routine.
	//
	
	//@todo: Filtros para ponteiros NULL.
	
    //
	// Create process.
	//
    create_process( window_station, desktop, window, init_eip, priority, ppid, name);
	//@todo: Return da fun��o create.
	
done:
    return NULL;
};


/*
 * KeCreateThread:
 *    Interface para cria��o de uma thread.
 * @todo: 
 * #Erro. Rotinas come�adas com 'Ke_' servem para chamar servi�os de 
 * m�dulos externos.
 */
void *KeCreateThread( struct wstation_d *window_station,
                      struct desktop_d  *desktop,
                      struct window_d *window,
                      unsigned long init_eip, 
                      unsigned long priority, 
					  int ppid, 
					  char *name )
{
    //
	// @todo: Create some interface routine.
	//
	
	//@todo filtros, para ponteiros NULL.
	
    //
	// Create thread.
	//
    create_thread( window_station, desktop, window, init_eip, priority, ppid, name);               
    //@todo: return da fun��o create.
	
done:
    return NULL;
};



/*
 * dofork:
 *     Implementa a rotinca de clonagem de processo.
 *     Essa rotina ser� chamada por fork().
 *
 */
//int dofork(); 
//int dofork(){
//	return 0;
//};


/*
 * fork: 
 *
 * @todo:
 *     Semelhante ao unix, isso deve criar um processo filho fazendo uma c�pia 
 * dos par�metros presentes no PCB do processo pai. Um tipo de clonagem. 
 * Depois obviamente a imagem do processo filho ser� carregada em um endere�o 
 * f�sico diferente da imagem do processo pai.
 * Essa n�o precisa ser a rotina, pode ser apenas uma interface, que chama a 
 * rotina dofork() e outras se necess�rio.
 */
int fork()
{  
    //struct process_t *p;
	
	//p = (void *) processList[current_process];
	
	//...
	
	//dofork();
	
done:	
	//return (int) p->pid;
	return (int) 0;    //Ainda n�o implementada. 
};


/*
 * create_task:
 *     @todo: Criar um processo.
 *     Cria tarefas para ring 3.
 *     Seta o contexto dos registradores para a nova tarefa, 
 * atribui id, nome, pilha ...
 *
 * @todo: 
 *     Alocar pilha dinamicamente.
 *     Criar filtro de quantidade de tarefas criadas.
 *     Mudar o nome para createProcess(....);
 * Retorna o id da task.
 * Retorno 0 se falhar.
 *
 */
int create_task( int task_id, 
                 unsigned long *task_eip, 
				 unsigned long *task_stack, 
				 unsigned long prior )
{
    //int ProcessId = task_id;
    
	/*
    create_process( window_station, desktop, window, 
	                init_eip, priority, ppid, name);
	*/
	
done:	
	return (int) 0;
};


/*
 * KiFork:
 *    Inicio do m�dulo interno que chama a fun��o fork.
 *    Isso � uma interface para a chamada � rotina fork.
 *    @todo: As fun��es relativas �s rotinas de fork
 *           podem ir para um arquivo que ser� compilado junto com o kernel.
 *           ex: fork.c
 */
int KiFork()
{
	
	//@todo Criar interface
	
	return (int) fork();
};


/*
 * KiCreateTask:
 *     Interface para chamar a rotina que cria um processo.
 *     
 */
int KiCreateProcess(unsigned long type, unsigned long *task_eip)
{
	//@todo:
	
	return (int) 0;
};


/*
 * KiCreateTask:
 *     Interface para chamar a rotina que cria um processo.
 *     @todo: Mudar para KiCreateProcess(...).
 */
int KiCreateTask( int task_id, 
                  unsigned long *task_eip, 
				  unsigned long *task_stack, 
				  unsigned long prior )
{
	
	//@todo: Criar interface e filtrar argumentos.
	
	return (int) KiCreateProcess(0, task_eip);
};

/*
 * CreateSystemTasks:
 *     Cria e inicializa as estruturas dos processos do sistema.
 *     Idle, Shell, Taskmanager.
 *     N�o criar Idle aqui.
 *     @todo: Poderia mudar o nome para createCreateSystemProcesses().
 * Obs:
 *    Funcionou bem a cria��o de processos e treads.
 */
void CreateSystemTasks()
{
	struct process_d *Process;
	struct thread_d *Thread;
	
    printf("CreateSystemTasks: Creating System threads..\n");
	KeCreateShell();
	KeCreateTaskManager();
	//...
	
	//
	// @todo: Testando a cria��o de processos.
	//
		
	//Create Process, test 1.
	Process = (void*) create_process( NULL, NULL, NULL, (unsigned long) 0x00401000, PRIORITY_LOW, 0, "TESTPROCESS");	
	if((void*) Process == NULL){
		printf("CreateSystemTasks fail: Create process.\n");
		refresh_screen();
		while(1){};
	};
	
	
	//
	// @todo: Testando criar threads inicializadas mas n�o prontas pra execu��o.
	//
	//OBS: As threads ser�o criadas depois de ja serem sido criadas as threads do sistema.
	//idle thread eip (unsigned long) 0x00401000.
	

	
	//Create Thread, test 1.
	Thread = (void*) create_thread( NULL, NULL, NULL, (unsigned long) 0x00401000, PRIORITY_LOW, 0, "TESTTHREAD1");	
	if((void*) Thread == NULL){
		printf("CreateSystemTasks fail: Create thread.\n");
		refresh_screen();
		while(1){};
	};
	

	//Create Thread, test 2.
	Thread = (void*) create_thread( NULL, NULL, NULL, (unsigned long) 0x00401000, PRIORITY_LOW, 0, "TESTTHREAD2");	
	if((void*) Thread == NULL){
		printf("CreateSystemTasks fail: Create thread 2.\n");
		refresh_screen();
		while(1){};
	};
	
	
	//@todo: Stress test.
	//debug_test_threads();
	
	
	//...
	
	
done:
    printf("Done.\n");
    return;
};


/*
 * KeCreateKernelProcess:
 *    Criando manualmente o processo do Kernel.
 *    
 * @todo: 
 *     Rever a inicial Ke, pois � usado para chamadas � m�dulos externos.  
 *
 * @todo: 
 *     Mudar o nome para createCreateKernelProcess()
 */
//void *createCreateKernelProcess() 
void *KeCreateKernelProcess()
{
	struct process_d *p;
	char *ProcessName = "KERNEL PROCESS";
	
	//KernelProcess 
	
	p = (void *) malloc( sizeof(struct process_d) );
	
	if( (void*) p == NULL ){
	    printf("KeCreateKernelProcess:");
		refresh_screen();
		while(1){}
	}else{
		
		//Directory (endere�o f�sico?). (cr3).
		p->Directory = (unsigned long ) KERNEL_PAGEDIRECTORY;
		//p->Directory = (unsigned long ) get_page_dir();
		
		//Inicializando a lista de framepools do processo.
		//@todo: Todo processo deve sr criado com pelo menos um 
		//frame pool, o que � equivalente a 4MB.(uma parti��o)
		//Obs: Um framepool indica onde � a �rea de mem�ria fisica
		//que ser� usada para mapeamento das p�ginas usadas pelo processo.
		p->framepoolListHead = NULL;

		//Heap and Stack. (endere�os f�sicos = endere�os virtuais).
	    //KernelProcess->StackOffset = 0;     // Deslocamento da pilha em rela��o ao in�cio do kernel. 
	    p->Stack       = KERNEL_STACK_START;  // Endere�o do in�cio da Stack do processo.
	    p->StackSize   = KERNEL_STACK_SIZE;   // Tamanho da pilha.	
	    p->Heap        = KERNEL_HEAP_START;   // Endere�o do in�cio do Heap do processo.
	    p->HeapSize    = KERNEL_HEAP_SIZE;    // Tamanho do heap.
	    p->Image       = KERNEL_IMAGE_BASE;   // Base da imagem do processo.
	    //KernelProcess->ImageSize = 0;       // Tamanho da imagem do processo.				
	    
		//Identifications.
		p->pid  = (int) 0;                   //PID.
	    p->ppid = (int) p->pid;  //PPID, Criado por ele mesmo.	 
		p->uid  = (int) GetCurrentUserId();  //UID.
		p->gid  = (int) 0;                   //GID.
		
		p->used = 1;
		p->magic = 1234;	

		p->name_address = (unsigned long) ProcessName;
	    p->iopl = RING0;                        //Kernel mode.
		p->base_priority = PRIORITY_MAX;  //b�sica.
		p->priority = p->base_priority;   //din�mica.
		
		//ppl = K0
		//p->pplK0;
		
		//Lista de threads
		p->threadListHead = NULL;
		
		//Sinal para processo.
		p->signal = 0;
		p->signalMask = 0;
		//Continua ...
		
		
		p->Next = NULL;                         //(void*) KernelProcess;	
		
		
		//
		// @todo: Cuidado com esses ponteiros.
		//
		
		//Atualizando o ponteiro global para estrutura do processo kernel.
		KernelProcess = (void*) p;
		
		processList[0] = (unsigned long) KernelProcess;
		
		//Processor struct. 
		processor->CurrentProcess = (void*) KernelProcess;
		processor->NextProcess    = (void*) KernelProcess;	
	}; 
	
//Done.
done:
    return (void*) KernelProcess;
};


/*
 * KeCreateIdle:
 *     Criando Idle thread manualmente.
 * *IMPORTANTE: Na verdade esse processos e threads devem ser criados 
 * com uma fun�ao que passe os parametros via argumento, tipo 
 * create_process create_thread. Exceto a idle que pode ser feita manualmente. 
 *
 * Obs: Criar idle thread com prioridade alta. TID=0 Idle (RING 3).
 * @todo: Mudar o nome para createCreateIdleThread()
 */
void *KeCreateIdle()
{
    void *idleStack;                    // Stack pointer.
	char *ThreadName = "idlethread";    // Name.
	
    //Aloca mem�ria mara a estrutura.
	IdleThread = (void*) malloc( sizeof(struct thread_d) );	
	if( (void*) IdleThread == NULL ){
	    printf("KeCreateIdle:\n");
		refresh_screen();
		while(1){}
	}
	else
	{ 
	    //Ver se a estrutura do processo � v�lida.
		if( (void*) KernelProcess == NULL ){
	        printf("KeCreateIdle: Kernel Process was not created.\n");
		    refresh_screen();
		    while(1){}
	    }else{
			//Indica � qual processo a thread pertence.
	        IdleThread->process = (void*) KernelProcess;
		};		
		
	    //Continua...
	};

	//
	// @todo: bugbug; A stack da idle n�o deve ficar no heap do kernel.
	//                Pois a idle est� em user mode e 
	//                deve ter sua stack em user mode
	//                para ter permiss�o de acesso.
	//                Mas ficar� aqui por enquanto.
	//                Obs: Mais abaixo a pilha foi configurada 
	//                     manualmente no lugar certo.
	//
	
	//IdleThread->Heap = ?;
	//IdleThread->HeapSize = ?;
	//IdleThread->Stack = ?;
	//IdleThread->StackSize = ?;	
	
	//Stack.
	//#BugBug.
	idleStack = (void*) malloc(4*1024);
	if( (void*) idleStack == NULL ){
	    printf("KeCreateIdle fail: Stack.\n");
		refresh_screen();
		while(1){}
	};
	
	//
	// @todo: 
	//     � poss�vel usar a fun��o create_thread nesse momento.
	//     Mas � mais veloz fazer o m�ximo em uma fun��o s�.
	//     Mas por enquanto ser�o feitas � m�o essas primeiras threads. 
	//
	
	//Object. @todo: Isso parece ser legal.
	//IdleThread->ObjectType = OBJECT_THREAD;
	
    //Identificadores.
	IdleThread->tid = 0;
	IdleThread->ppid = (int) KernelProcess->pid;  
	IdleThread->used = 1;
	IdleThread->magic = 1234;
	IdleThread->name_address = (unsigned long) ThreadName;   //Funciona.

	IdleThread->process = (void*) KernelProcess;
	//
	// Procedimento de janela.
	//  

    //O procedimento.
	IdleThread->procedure = (unsigned long) &system_procedure;
	
    //Argumentos do procedimento de janela.	
	IdleThread->window = NULL; //window;//arg1.
	IdleThread->msg   = 0;     //arg2.
	IdleThread->long1 = 0;     //arg3.
	IdleThread->long2 = 0;     //arg4.
	
	//Caracter�sticas.
	IdleThread->type  = TYPE_IDLE;    //TYPE_SYSTEM.
	IdleThread->iopl  = RING3;        //Idle thread � uma thread de um processo em user mode.
	IdleThread->state = INITIALIZED;   
	
	IdleThread->base_priority = KernelProcess->base_priority;  //b�sica.   
  	IdleThread->priority = IdleThread->base_priority;          //din�mica.
	
	IdleThread->saved = 0; 
	IdleThread->preempted = UNPREEMPTABLE;    // N�o pode sofrer preemp��o.
	
	//Temporizadores.
	IdleThread->step = 0;
	IdleThread->Quota = 9;           
	IdleThread->quantum       = QUANTUM_BASE;
	IdleThread->quantum_limit = QUANTUM_LIMIT;

	IdleThread->standbyCount = 0;
	IdleThread->runningCount = 0;    //Tempo rodando antes de parar.
	IdleThread->readyCount = 0;      //Tempo de espera para retomar a execu��o.
	IdleThread->ready_limit = READY_LIMIT;
	IdleThread->waitingCount  = 0;
	IdleThread->waiting_limit = WAITING_LIMIT;
	IdleThread->blockedCount = 0;    //Tempo bloqueada.		
	IdleThread->blocked_limit = BLOCKED_LIMIT;
	
	
	IdleThread->ticks_remaining = 1000;
	
	//signal
	//Sinais para threads.
	IdleThread->signal = 0;
	IdleThread->signalMask = 0;
	
	//...
	
	//
	// Obs: Essa parte � dependente da arquitetura, deveria estar em 
	//      uma pasta, por exemplo, microkernel\i386.
	//	
	
	//if(MachineType == i386Type){...};
	
	//Context.
	//@todo: Isso deve ser uma estrutura de contexto.
	IdleThread->ss  = 0x23;                          //RING 3.
	IdleThread->esp = (unsigned long) 0x0044FFF0;    //idleStack; (*** RING 3)
	IdleThread->eflags = 0x3200;
	IdleThread->cs = 0x1B;                                
	IdleThread->eip = (unsigned long) 0x00401000;     	                                               
	IdleThread->ds = 0x23; 
	IdleThread->es = 0x23; 
	IdleThread->fs = 0x23; 
	IdleThread->gs = 0x23; 
	IdleThread->eax = 0;
	IdleThread->ebx = 0;
	IdleThread->ecx = 0;
	IdleThread->edx = 0;
	IdleThread->esi = 0;
	IdleThread->edi = 0;
	IdleThread->ebp = 0;
	

	//CPU configuration.
	//IdleThread->cpuID = 0;              //Qual processador.
	//IdleThread->confined = 1;           //Flag, confinado ou n�o.
	//IdleThread->CurrentProcessor = 0;   //Qual processador.
	//IdleThread->NextProcessor = 0;      //Pr�ximo processador. 
	
	//Coloca na lista de estruturas.
	threadList[0]  = (unsigned long) IdleThread;
	
	//Pr�xima thread.
	IdleThread->Next = NULL;
	//IdleThread->Next = (void*) IdleThread;    //Op��o.
	
    //
	// Running tasks. (Quantas threads est�o rodando).
	//
	
    ProcessorBlock.running_tasks = (int) 1;
	
	//@todo: setar a idle como current.
	
	//if( ProcessorBlock.running_tasks == 1 ){
	//	current_thread = IdleThread->tid;
	//};
	
// Done.	
done:
    queue_insert_data(queue, (unsigned long) IdleThread, QUEUE_INITIALIZED);
    SelectForExecution(IdleThread);    // * MOVEMENT 1 ( Initialized ---> Standby).
   	return (void*) IdleThread;
};



/*
 * KeCreateShell:
 *     Criando Thread Shell manualmente.
 * @todo: Mudar o nome para createCreateShellThread()
 */
void *KeCreateShell()
{
    void *shellStack;                    // Stack pointer. 
	struct thread_d *t;
	char *ThreadName = "shellthread";    // Name.


   /*
    *@todo: checar o tipo de processador antes de configurar o contexto.
	*
	*/

   /*
	* PID=1 Shell (RING 3).
	*/  

	 
    //Process.
	/*
	struct process_d *p;
	p = (void*) malloc( sizeof(struct process_d) );	
	if( (void*) p == NULL)
	{
	    printf("KeCreateShell: Process fail.\n");
		refresh_screen();
		while(1){}
	};
	*/
	if( (void*) KernelProcess == NULL ){
	    printf("KeCreateShell: Kernel Process is not created.\n");
		refresh_screen();
		while(1){}
	};	
	
	//Thread.
	t = (void*) malloc( sizeof(struct thread_d) );	
	if( (void*) t == NULL ){
	    printf("KeCreateShell fail: Thread.\n");
		refresh_screen();
		while(1){}
	}
	else
	{  
	    //Indica � qual proesso a thread pertence.
	    t->process = (void*) KernelProcess;
	};

	//Stack.
	shellStack = (void*) malloc(4*1024);
	if( (void*) shellStack == NULL ){
	    printf("KeCreateShell: Stack fail.\n");
		refresh_screen();
		while(1){}
	};

    //Identificadores.       	
	t->tid = 1;     
	t->ppid = (int) KernelProcess->pid;         
	t->used = 1;
	t->magic = 1234;
	t->name_address = (unsigned long) ThreadName;    //Funciona.
	
	t->process = (void*) KernelProcess;
	
	//Procedimento de janela.
	t->procedure = (unsigned long) &system_procedure;
	t->window = NULL;  //window;  //arg1
	t->msg = 0;        //arg2
	t->long1 = 0;      //arg3
	t->long2 = 0;      //arg4	
	
	//Caracteristicas.
	t->state = INITIALIZED;  
	
	t->base_priority = KernelProcess->base_priority;  //b�sica.   
  	t->priority = t->base_priority;                   //din�mica.
	
	t->iopl = RING3;  
	t->type = TYPE_SYSTEM;   
	t->saved = 0;
	t->preempted = PREEMPTABLE;    //PREEMPT_PODE; //pode.
	//t->Heap;
	//t->HeapSize;
	//t->Stack;
	//t->StackSize;
	
	//Temporizadores.
	t->step = 0;
	t->Quota = 9;	
	t->quantum       = QUANTUM_BASE;
	t->quantum_limit = QUANTUM_LIMIT;
	
	
	t->standbyCount = 0;
	t->runningCount = 0;    //Tempo rodando antes de parar.
	t->readyCount = 0;      //Tempo de espera para retomar a execu��o.
	t->ready_limit = READY_LIMIT;
	t->waitingCount  = 0;
	t->waiting_limit = WAITING_LIMIT;
	t->blockedCount = 0;    //Tempo bloqueada.		
	t->blocked_limit = BLOCKED_LIMIT;
	
	
	t->ticks_remaining = 1000;	
	
	//signal
	//Sinais para threads.
	t->signal = 0;
	t->signalMask = 0;


	//Context.
	t->ss  = 0x23;                          //RING 3.
	t->esp = (unsigned long) 0x0049FFF0;    //shellStack;//  //RING 3 (pilha do app2)(shell?). 
	t->eflags = 0x3200;
	t->cs = 0x1B;                                
	t->eip = (unsigned long) 0x00451000;     	                                               
	t->ds = 0x23; 
	t->es = 0x23; 
	t->fs = 0x23; 
	t->gs = 0x23; 
	t->eax = 0;
	t->ebx = 0;
	t->ecx = 0;
	t->edx = 0;
	t->esi = 0;
	t->edi = 0;
	t->ebp = 0;	
	
	//CPU stuffs.
	//t->cpuID = 0;              //Qual processador.
	//t->confined = 1;           //Flag, confinado ou n�o.
	//t->CurrentProcessor = 0;   //Qual processador.
	//t->NextProcessor = 0;      //Pr�ximo processador. 	
	
	//coloca na lista de estruras.
	threadList[1] = (unsigned long) t;
	
	t->Next = NULL;

	

	
	//
	// Running tasks.
	//
	
	ProcessorBlock.running_tasks = 2;

	
// Done.
done:
    queue_insert_data(queue, (unsigned long) t, QUEUE_INITIALIZED);
    SelectForExecution(t);    // * MOVEMENT 1 ( Initialized --> Standby).
    return (void*) t;
};



/*
 * KeCreateTaskManager:
 *     Criando thread task manager manualmente.
 * @todo: Mudar o nome para createCreateTaskmanThread()
 */
void *KeCreateTaskManager()
{
    void *taskmanStack;                    // Stack pointer. 	
	struct thread_d *t;
	char *ThreadName = "taskmanthread";    // Name.
	
   /*
    * @todo: 
	*     Checar o tipo de processador antes de configurar o contexto.
	*
	*/


   /*
	* PID=2 taskmanager (RING 3).
	*/  
	
	//Process.
	/*
	struct process_d *p;
	p = (void*) malloc( sizeof(struct process_d) );	
	if( (void*) p == NULL)
	{
	    printf("KeCreateTaskManager: Process fail.\n");
		refresh_screen();
		while(1){}
	};
	*/
	if( (void*) KernelProcess == NULL ){
	    printf("KeCreatetaskManager: Kernel Process not created.\n");
		refresh_screen();
		while(1){}
	};	

    //Thread.
	t = (void*) malloc( sizeof(struct thread_d) );	
	if( (void*) t == NULL ){
	    printf("KeCreateTaskManager: Thread fail.\n");
		refresh_screen();
		while(1){}
	}
	else
	{  
	    //Indica � qual proesso a thread pertence.
	    t->process = (void*) KernelProcess;
	};
	
	//Stack.
	taskmanStack = (void*) malloc(4*1024);
	if( (void*) taskmanStack == NULL ){
	    printf("KeCreateTaskManager: Stack fail.\n");
		refresh_screen();
		while(1){}
	};
  	
    //Identificadores      
	t->tid = 2;     
	t->ppid = (int) KernelProcess->pid;         
	t->used = 1;
	t->magic = 1234;	
	t->name_address = (unsigned long) ThreadName;   //Funciona.
	
	t->process = (void*) KernelProcess;

	//Procedimento de janela.
    t->procedure = (unsigned long) &system_procedure;	
	t->window = NULL;  //window;  //arg1.
	t->msg = 0;        //arg2.
	t->long1 = 0;      //arg3.
	t->long2 = 0;      //arg4.	

    //Caracter�sticas.	
	t->type = TYPE_SYSTEM;  
	t->state = INITIALIZED; 

	t->base_priority = KernelProcess->base_priority;  //b�sica.   
  	t->priority = t->base_priority;                   //din�mica.
	
	t->iopl = RING3;   
	t->saved = 0;
	t->preempted = PREEMPTABLE;    //PREEMPT_NAOPODE; //nao pode.	
	//t->Heap;
	//t->HeapSize;
	//t->Stack;
	//t->StackSize;

	//Temporizadores.
	t->step = 0;
	t->Quota = 9;
	t->quantum       = QUANTUM_BASE;
	t->quantum_limit = QUANTUM_LIMIT;	


	t->standbyCount = 0;
	t->runningCount = 0;    //Tempo rodando antes de parar.
	t->readyCount = 0;      //Tempo de espera para retomar a execu��o.
	t->ready_limit = READY_LIMIT;
	t->waitingCount  = 0;
	t->waiting_limit = WAITING_LIMIT;
	t->blockedCount = 0;    //Tempo bloqueada.		
	t->blocked_limit = BLOCKED_LIMIT;
	

	t->ticks_remaining = 1000;
	
	//signal
	//Sinais para threads.
	t->signal = 0;
	t->signalMask = 0;
	
	//Context.
	t->ss  = 0x23;                          //RING 3.
	t->esp = (unsigned long) 0x004FFFF0;    //taskmanStack;//0x0045FFF0;  //pilha. 
	t->eflags = 0x3200;
	t->cs = 0x1B;                                
	t->eip = (unsigned long) 0x004A1000;     	                                               
	t->ds = 0x23; 
	t->es = 0x23; 
	t->fs = 0x23; 
	t->gs = 0x23; 
	t->eax = 0;
	t->ebx = 0;
	t->ecx = 0;
	t->edx = 0;
	t->esi = 0;
	t->edi = 0;
	t->ebp = 0;	

	//CPU stuffs.
	//t->cpuID = 0;              //Qual processador.
	//t->confined = 1;           //Flag, confinado ou n�o.
	//t->CurrentProcessor = 0;   //Qual processador.
	//t->NextProcessor = 0;      //Pr�ximo processador. 
	
	//Coloca na lista de estruras.
	threadList[2] = (unsigned long) t;
	
	t->Next = NULL;
	
	//
	// Running tasks.
	//
	
	ProcessorBlock.running_tasks = 3;
	
// Done.
done:
    queue_insert_data(queue, (unsigned long) t, QUEUE_INITIALIZED);
    SelectForExecution(t);    // * MOVEMENT 1 ( Initialized --> Standby).
    return (void*) t;
};


//
// Fim.
//
