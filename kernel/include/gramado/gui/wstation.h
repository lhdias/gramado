/*
 * Arquivo: wstation.h
 *
 * Descri��o:
 *     Window station. 
 *     Esta��o de janelas. 
 *     (Cont�m desktops).
 *
 * Tipos de window station: 
 *     (interactive, non_interactive).
 *
 * OBS:
 *     Cada PROCESSO est� associado � 
 *     uma window station e s� podem rodar l�.
 *     Uma window station tem v�rios desktops.
 *     Os desktops tem v�rias janelas e menus.
 *
 * Vers�o 1.0, 2015.
 */

 
#define WINDOW_STATION_COUNT_MAX 16 
 
 
/*
 * Window Station:
 *
 */ 
typedef struct wstation_d wstation_t; 
struct wstation_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
    int wsId;
	int wsUsed;
	int wsMagic;
	
	int userID;
	
    //@todo: fazer uma lista encadeada. de desktops
	unsigned long desktops[32];    //@todo: usar aloca��o dinamica.
	
	//struct wstation_d *next_wstation;
	
	//struct desktop_d *arrayDesktop; //ponteiro para um array de estruturas de desktop.
	
	//linked list. ( a linked list da window station)
	struct linkedlist_d *linkedlist;	
	
	//section
    struct usession_d *usession;
	
	//next
	struct wstation_d *next;
};
struct wstation_d *CurrentWindowStation;
struct wstation_d *wsDefault;
struct wstation_d *ws0;
struct wstation_d *ws1;
struct wstation_d *ws2;

// Lista encadeada de window stations.
wstation_t *wstation_Conductor2;
wstation_t *wstation_Conductor;
wstation_t *wstation_rootConductor;

unsigned long windowstationList[WINDOW_STATION_COUNT_MAX];


/*
 * Contagem de window stations.
 *
 */
int windowstations_count;  

void init_window_station();
void init_windowstation_list();
int RegisterWindowStation(struct wstation_d *ws);
void set_current_windowstation(struct wstation_d *ws);
void *get_current_windowstation();
void *CreateWindowStation(struct usession_d *s);


//
//fim.
//


