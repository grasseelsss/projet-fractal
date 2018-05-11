#include <stdlib.h>
#include <string.h>
#include "fractal.h"
#include <stdio.h>

#include <pthread.h>


struct fractal *fractal_new(const char *name, int width, int height, double a, double b,double mean,int**pix)
{
  struct fractal *new =  (struct fractal*) malloc(sizeof(struct fractal));
  new->a= a;
  new->b=b;
  new->height=height;
  new->width=width;
  new->mean=mean;
  char *realname= (char*) malloc (strlen(name)*sizeof(char));
  strcpy(realname,name);
  new->name =realname;
  int i;
  int j;
  for( i= 0;i<width;i++){
    for( j= 0;j<height;j++){
      pix[j]=malloc(height*(sizeof(width)));
		    
    }
  }
  return new;
  
}

void fractal_free(struct fractal *f)
{
  free( f->pix);
  free(f->name);
  free(f);
   
}

const char *fractal_get_name(const struct fractal *f)
{
  return f->name;
}

int fractal_get_value(const struct fractal *f, int x, int y)
{
  return (f->pix)[x][y];
}

void fractal_set_value(struct fractal *f, int x, int y, int val)
{
  (f->pix)[x][y]= val;
}

int fractal_get_width(const struct fractal *f)
{
  return f->width;
}

int fractal_get_height(const struct fractal *f)
{
  return f->height;
   
}

double fractal_get_a(const struct fractal *f)
{
    
  return f->a;
}

double fractal_get_b(const struct fractal *f)
{
    
  return f->b;
}
