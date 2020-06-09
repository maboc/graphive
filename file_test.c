#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv){
  FILE * fp;

  int n;
  int n2;
  char * t;
  int int_size=sizeof(int);

  printf("Size of an int : %i\n", int_size);
  
  fp=fopen("test_file.dat", "w+");

  for (n2=1; n2<=100; n2++){
    fwrite(&n2, 1, sizeof(int), fp);
  }

  t=malloc(5);
  t=memset(t, 0x61, 1);
  for (n2=1;n2<=20;n2++){
    fwrite(t, 1, strlen(t), fp);
  }

  free(t);

  t=malloc(1);
  t=memset(t, 0x63 ,1);
  if(fseek(fp, 100*int_size, SEEK_SET)==0){
    printf("ZOu moeten werken\n");
  } else {
    printf("NIet als gewenst\n");
  }
  fwrite(t, 1, strlen(t), fp);
  free(t);
  fclose(fp);
  return 0;
}
  
