/*
 * File: shell.h
 *
 * Descri��o:
 *     Header principal do Shell.
 *     SHELL.BIN (32bit User Mode) 
 *
 * Obs: 
 * Para atender os comandos do usu�rio o Shell chamar� v�rios programas, assim 
 * como ter� rotinas internas que atendem os comandos. Para isso, esse 
 * diret�rio deve ter v�rias pastas, uma para cada um dos comandos principais, 
 * como shutdown. Cda pasta � um programa que o Shell vai chamar.
 *
 * Vers�o 1.0, 2016.
 */
 
//
// Defini��es.
//
 
#define SHELL_VERSION  "1.0"
#define SHELL_PROMPT   ">"
//#define SHELL_PROMPT   "$"
//#define SHELL_PROMPT   "shell: " 
//... 
 
 
//
// Macros.
// 
 
//#define DeclareStructHandle(name) struct nameJABUTICABA__ { int unused; }; typedef struct nameJABUTICABA__ *name 
//#define DeclareHandle(name) typedef void* name 
 

//cores do texto. 
unsigned long backgroung_color;  //pano de fundo.
unsigned long foregroung_color;  //texto.
 
 
//
// Usage banner.
//
 
static const char usage[] =
    "Usage: shell [arguments...]\n"
    "       shell -help             Display this help message and exit.\n"
    "       shell -version          Output version information and exit.";
	//...
 
 
//
// Structures.
// 
 

typedef struct shell_hook_d shell_hook_t; 
struct shell_hook_d
{
	int dummy;
	//struct window_d *window;
	//struct rect_d *rect;
}; 
shell_hook_t *ShellHook; 


typedef struct shell_metrics_d shell_metrics_t;
struct shell_metrics_d
{
    int fontWidth;
    int fontHeight;
	int lineMax;
	int colMax;
	//... 
};
shell_metrics_t *ShellMetrics;
//...


//int app_main(int argc, char *argv[]); 

 
//
// End.
//

