#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libfractal/fractal.h"
#include <string.h>
#include <semaphore.h>
#define MAX_LENGTH 1000
#include<pthread.h>
int L ;
int i;
int number; //nombre fractale
int nbfile = 0;
char *STDIN ="stdin";
struct fractal **buffer ;
const char* space ;
double *best_average =0;
int genAll;

typedef struct node {
  struct fractal *f;
  struct  node *next; }
  node;

//-------------methode pour transformer une ligne en fractale------
struct fractal  *lineToFractal(char* line){
  char scan[1]; 
  int w,h;                        
  double a,b;
  char *name = (char*) malloc(sizeof(char));
  int error = sscanf(line,"%s %lf %lf %d %d %s",name,a,b,w,h,scan);
  if(error!=5){
    return NULL;}
  struct fractal *f = fractal_new(name,w,h,a,b,0,NULL);
  free (name);
  return f;
}
//-------------------------------------------------------------------

//initialisation des mutex et semaphores
pthread_mutex_t mutex ;
pthread_mutex_t mutex_buffer;
sem_t full;
sem_t empty;

int main(int argc, char *argv []) {
  int printall;
  const char *file[argc];
  const char *file2 = argv[argc-1];

// checkez les arguments
//regardez si l'argument est -d 
  for (i =1; i<argc-1;i++) {
    if( strcmp(argv[i],"-d") == 0) {
      printall=1;
  } 
    else
      //regardez le nombre max de thread
      if(strcmp(argv[i],"--maxthread") == 0) {
	number = atoi(argv[2]);
	i++;
      }
      else { 
	if (strcmp(argv[i],"-")==0) {
	  file[nbfile] =STDIN;
	  nbfile++;
	}
	else {
	  file[nbfile] =argv[i];
	  nbfile++;
	}
      }
  }
  
  //print 
  printf("Nombre de fichiers : %i\n",nbfile);
  if (printall==1) { 
    printf("Tout va etre imprimer,\n");
  }
  printf("fichier de sortie : %s\n",file2);
  for (i=0 ; i<nbfile;i++){
    printf("file n° %i :%s\n",i+1,file[i]);
  }

  //initialisation du buffer 
  struct fractal **buffer;
  buffer =(struct fractal**)(malloc(number*sizeof(struct fractal*)));
 
  //------------------------- methode pour avancer dans le buffer -----------------------

  node *head =NULL;
  int addFrac(struct fractal*f) {
    struct node *new_queue = malloc(sizeof(struct node));
    if(new_queue == NULL) {
      return -1;
    }
    new_queue->f = f;
    new_queue->next=head;
    head =new_queue;
    return 0;
  }
  //-------------------------------------------------------------------------------------
 

 //------methode pour lire un fichier----------------------------------------------------
  void *readerf(void *namefile) {
    const char *fichier =(char*) namefile;
    char*save;
    FILE* file = NULL ;
    char current;
    file =fopen(fichier ,"r");
    char *line =(char*)malloc(sizeof(char)*MAX_LENGTH);
    if(file==NULL){
      while(fgets(line,MAX_LENGTH,file)!=NULL){
	if(*line !=' '&& *line!='#'){
	  addFrac(lineToFractal(line));
	}
	fclose(file);
      }
      free (line);
      pthread_exit(NULL);
    }
    free (line);
    free(namefile);
    pthread_exit(NULL);
  }
  //- ----------------------------------------------------------------------------------------

  

//creation du producteur
  pthread_t *threadsprod;
 int err;
  for ( i = 0; i< nbfile ;i++) {
    err = pthread_create(&(threadsprod[i]),NULL,readerf,NULL);
  }
 

 //creation du consommateur 
  pthread_t *threadscon;
  struct fractal *pop(){
    struct fractal *f =head->f;
    head=head->next;
    return f;
  }
  void *conso(void *p){
    

 
    }

  //-----------------calculer la valeur de la fractale----------------------     
  int compute_Fractale(struct fractal *f){
    int w = fractal_get_width (f);
    int h = fractal_get_height (f);
    double average = 0 ;
    double total =w*h;
    int x,y  ;
    int sum = 0;
    for(x=0; x<w; x++) {
      for(y=0;y<h;y++){
	fractal_compute_value(f,x,y);
	sum+= fractal_get_value(f,x,y);
      }
    }
    average=sum/(w*h);
    return average;
  }
  //--------------------------------------------------------------------------
  return 0;
}





			  


      



  
 


























































































































































































































