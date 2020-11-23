#include "io.h"

int load(char * filename){
  FILE * fp;
  unsigned long long empty_spot;
  unsigned long long cur_pos;
  int t;
  unsigned long long id;
  char status;
  struct base_type * base;
  int base_id;
  unsigned long long node_id;
  unsigned long long relation_id;
  int kl;
  char * k;
  int vl;
  char * v;
  struct attribute_type * attr;
  char * OK_SIGN;
  struct node_type * node;
  
  OK_SIGN=malloc(2);
  bzero(OK_SIGN,2);
  OK_SIGN=strcpy(OK_SIGN, "O");
  
  fp=fopen(filename, "r+");
  //first piece to read : the nexr empty spot
  fseek(fp, 0, SEEK_SET);
  fread(&empty_spot, sizeof(unsigned long long), 1, fp);

  cur_pos=sizeof(unsigned long long);

  while(cur_pos<empty_spot){
    //read the type of the next object
    fread(&t, sizeof(int), 1, fp);

    if(t==1){
      //it 's a base object
      //get the id
      fread(&id, sizeof(int), 1 , fp);
      if(id>scn)scn=id;


      //status stuff
      fread(&status, sizeof(char), 1, fp);
      if (strcmp(OK_SIGN, "O")==0){
      
	// IF the base has status O ...create it. If status  is D, then it is deleted
	  base=base_new_from_load(id, cur_pos);
	  bases=dll_new(bases, base);
	}
	
      //update current position
      cur_pos=ftell(fp);
    } else if ((t==2) || (t==4)){
      // apparently an base attribute

      //let's get the base to which this attr belongs
      fread(&base_id, sizeof(int), 1, fp);
            
      //get the node
      fread(&node_id, sizeof(unsigned long long), 1, fp);
            
      //get the relation 
      fread(&relation_id, sizeof(unsigned long long), 1, fp);
            
      //get the attributes ID
      fread(&id, sizeof(unsigned long long), 1, fp);
      if(id>scn)scn=id;
      
      //key stuff
      fread(&kl, sizeof(int), 1, fp);
      k=malloc(kl)+1;
      bzero(k, kl+1);
      fread(k, kl, 1, fp);

      //value stuff
      fread(&vl, sizeof(int), 1, fp);
      v=malloc(vl)+1;
      bzero(v, vl+1);
      fread(v, vl, 1, fp);

      //status stuff
      fread(&status, sizeof(char), 1, fp);
      if (strcmp(OK_SIGN, "O")==0){
	//IF status==O ...create this attrbute

	//find the base it belongs to (whether the attr belongs to a bas or a node
	base=base_find(base_id);
	
	attr=attribute_new_from_load(id, k, v, cur_pos);
	if (t==2){
	  //it's a bas atrtibute
	  base->attributelist=dll_new(base->attributelist, attr);
	} else if (t==4){
	  node=node_search(base, node_id);
	  node->attributelist=dll_new(node->attributelist, attr);
	}
      }
      //update current position
      cur_pos=ftell(fp);
    } else if(t==3){
      //apparantly a node object
      
      //let's get the base to which this node belongs
      fread(&base_id, sizeof(int), 1, fp);
      
      //get the node ID
      fread(&id, sizeof(unsigned long long), 1, fp);
      if(id>scn)scn=id;
	    
      //status stuff
      fread(&status, sizeof(char), 1, fp);
      if (strcmp(OK_SIGN, "O")==0){
	//IF status==O ...create this node
	base=base_find(base_id);
	node=node_new_from_load(id, cur_pos);
	base->nodelist=dll_new(base->nodelist, node);
      }
      //update current position
      cur_pos=ftell(fp);
    }
  } 
  return 0;
}

int create_file(char * filename){
  int rc=0;
  FILE * fp;
  int n;
  char * buffer;
  unsigned long long pospoi=0;
  
  logger("Create file");
  logger(filename);

  buffer=malloc(1024*1024);
  bzero(buffer,1024*1024);
		
  fp=fopen("graphive.dat", "a+");
  // size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
  n=fwrite(buffer, 1024*1024, 1, fp);
  fflush(fp);
  /* 1 omdat ik fwrite anders niet goed aand e praat krijg */
  if(n!=1) rc=6;
  
  bzero(buffer,1024*1024);
  sprintf(buffer, "%i", n);
  logger(buffer);
  free(buffer);
  
  fflush(fp);  
  fclose(fp);
  
  //Setting the very first entry in the file as the free position pointer
  pospoi=sizeof(unsigned long long);
  set_empty_spot(pospoi);
  
  return rc;
}

int regular_file(char * filename){
  struct stat buffer;
  int rc=0;
  int s;
  
  s=stat(filename, &buffer);
  if(S_ISREG(buffer.st_mode)){
    logger("File is a regular file");
    logger(filename);
  } else {
    logger("File is not a regular file");
    logger(filename);
    rc=6;
  }

  return rc;
}

int file_exists(char * filename){
  struct stat buffer;
  int rc = 0;
  int s;
  
  s=stat(filename, &buffer);
  if (s!=0){
    logger("I can not detemine stat for file");
    logger(filename);
    rc=4;
  } else {
    logger("I can determine stat for filename");
    logger(filename);
  }

  return rc;
}
  
/* when starting the initial load there are no bases yet...so no need to supply NULL*/
int initial_load(){
  int rc;
  FILE * fp;

  rc=file_exists("graphive.dat");
  if (rc==0){
    rc=regular_file("graphive.dat");
    if(rc==0){
      rc=load("graphive.dat");
    }
  } else {
    rc=create_file("graphive.dat");
  }

  return rc; 
}

int write_node(struct node_type * node, struct base_type * base){
  char * tmp;
  unsigned long long pos;
  FILE * fp;
  int t=3; //type : node (zie mem_disk.txt)

  /*
  tmp=malloc(100);
  sprintf(tmp, "Write node ID : %i", node->id);
  logger(tmp);
  free(tmp);
  */
  
  if(node->status==2){
    // logger("really...nothing changed");
  } else if(node->status==1){
    // logger("just created");
    
    pos=get_empty_spot();
    fp=fopen("graphive.dat", "r+");
    fseek(fp, pos, SEEK_SET);
    
    fwrite(&t, sizeof(int), 1, fp);
    fwrite(& base->id, sizeof(int), 1, fp);
    fwrite(& node->id, sizeof(unsigned long long), 1, fp);
    fwrite(&"O", sizeof(char),1,fp);
    
    node->file=0;
    node->location=pos;
    node->status=2;
    
    pos=pos+sizeof(int)+sizeof(int)+sizeof(unsigned long long)+ sizeof(char);
    
    set_empty_spot(pos);
    
    fclose(fp);
  }
  
  write_attributes(node->attributelist, base, node);
  
  return 0;
}

int write_nodes(struct dll * list, struct base_type * base){
  struct node_type * node;
  int rc=0;

  if(list==NULL){
    //   logger("No nodes to write");
  } else {
    //  logger("write nodes");
    list=first(list);
    while(list->next!=NULL){
      write_node(list->payload, base);
      list=list->next;
    }
    rc=write_node(list->payload, base);
  }
  return rc;
}

int write_attribute(struct attribute_type * attr, struct base_type * base, struct node_type * node){
  char * tmp;
  int t; //type of the object we are going to write
  unsigned long long pos;
  FILE * fp;
  int kl;
  int vl;
  char * null_char;
  
  tmp=malloc(1000);
  null_char=malloc(1);
  bzero(null_char, 1);

  /*
  if(node==NULL){
    sprintf(tmp, "Base Attribute : ID : %i Key : %s Value : %s", attr->id, attr->key, attr->val);
    logger(tmp);
    free(tmp);
    t=2;  
  } else {
    sprintf(tmp, "Node Attribute : ID : %i Key : %s Value : %s", attr->id, attr->key, attr->val);
    logger(tmp);
    free(tmp);
    t=4;  
  }
  */
  if(attr->status==2){
    //  logger("nothing to write");
  }else if (attr->status==1){
    //logger("Just created");
    
    pos=get_empty_spot();
    
    fp=fopen("graphive.dat", "r+");
    fseek(fp, pos, SEEK_SET);
    fwrite(&t, sizeof(int), 1, fp);//type
    fwrite(&(base->id), sizeof(int), 1, fp); //base
    if(node==NULL){
      fwrite(null_char,sizeof(unsigned long long),1,fp); //node
    }else{
      fwrite(& node->id, sizeof(unsigned long long), 1, fp);
    }
    fwrite(null_char ,sizeof(unsigned long long),1,fp); //relation
    fwrite(&(attr->id), sizeof(unsigned long long), 1, fp); // ID
    kl=strlen(attr->key);
    fwrite(&kl, sizeof(int),1,fp);
    fwrite(attr->key, strlen(attr->key), 1,  fp);
    vl=strlen(attr->val);
    fwrite(&vl, sizeof(int), 1, fp);
    fwrite(attr->val, strlen(attr->val), 1, fp);
    fwrite(&"O", 1, 1, fp);
    
    free(null_char);
    
    fclose(fp);
    
    pos=pos+sizeof(int)+sizeof(int)+sizeof(unsigned long long)+sizeof(unsigned long long)+sizeof(unsigned long long) + sizeof(int)+ strlen(attr->key)+sizeof(int)+strlen(attr->val)+1;
    set_empty_spot(pos);
    
    attr->file=0;
    attr->location=pos;
    attr->status=2;
    
  }
    
  return 0;
}

int write_attributes(struct dll * list, struct base_type * base, struct node_type * node){
  struct attribute_type * attr;

  if (list==NULL){
    //  logger("No attributes to write");
  }else{
    // logger("write attributes");
    
    list=first(list);
    while(list->next!=NULL){
      attr=list->payload;
      write_attribute(attr, base, node);
      list=list->next;
    }
    attr=list->payload;
    write_attribute(attr, base, node);
  }
  return 0;
}

unsigned long long get_empty_spot(){
  unsigned long long p;
  FILE * fp;

  fp=fopen("graphive.dat", "r+");
  fseek(fp, 0, SEEK_SET);
  //  size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
  fread(&p, sizeof(unsigned long long), 1,fp);
  fclose(fp);
  
  return p;
}

void set_empty_spot(unsigned long long p){
  FILE * fp;

  fp=fopen("graphive.dat", "r+");
  fseek(fp, 0, SEEK_SET);
  fwrite(&p, sizeof(unsigned long long), 1, fp);
  fclose(fp);
  
}

int write_base(struct base_type * base){
  char * tmp;
  FILE * fp;
  int t=1; //type is base ...so 1 (zie mem_disk.txt)
  unsigned long long p;
  
  tmp=malloc(100);
  sprintf(tmp, "Write base : %i", base->id);
  logger(tmp);
  free(tmp);

  if(base->status==2){
    //   logger("Did not change");
  } else if(base->status==1){
    unsigned long long p;
    
    logger("Just Created");
    /* file en location zullen nog niet geucvld zijn ....want nieuw */
    /* zoek eerste lege positie in de file graphive.dat */

    p=get_empty_spot();
    base->file=0;
    base->location=p;
    fp=fopen("graphive.dat", "r+");
    fseek(fp, p, SEEK_SET);
    fwrite(&t, sizeof(int), 1, fp); //type of entry
    fwrite(&(base->id), sizeof(int), 1, fp); //base_id
    fwrite(&"O", sizeof(char), 1, fp); //status

    fclose(fp);

    set_empty_spot(p+sizeof(int)+sizeof(int)+sizeof(char));
    
    base->status=2;
    
  }else if (base->status==3){
    logger("Deleted");
  }else if(base->status==4){
    logger("Updated");
  }

  write_attributes(base->attributelist, base, NULL);
  write_nodes(base->nodelist, base);
  
  return 0;
}

int write_bases(struct dll * local_bases){
  int rc;
  if(local_bases==NULL){
    //   logger("No bases to write");
  }else{
    logger("write bases");
    local_bases=first(local_bases);
    while(local_bases->next!=NULL){
      rc=write_base(local_bases->payload);
      local_bases=local_bases->next;
    }
    rc=write_base(local_bases->payload);
  }
  return 0;
}

void * data_writer(void * data_in){
  struct dll * local_bases;
  int rc=0;
  sleep(30);  
  logger("Starting data_writer thread");
  //  sleep(60);
  while(goon==0){
    logger("data_writer sweep");
    local_bases=bases;
    
    write_bases(local_bases);
    
    sleep(60);//just for now....every minute we sweep through the data
  }
  pthread_exit(NULL);
}
