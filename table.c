
#include "table.h"




      void init_val(void){
             int capa_tab = 17;
             h_table*table[capa_tab]; 

             for(int i =0; i< capa_tab; i++){
                     table[i]=NULL;
             }

             
     }
     int h_set(h_table* htabl){
             int capa_tab=17;
             h_table*table[capa_tab];
             htabl[sizeof(htabl)];
             int hash(hkey_t nam);
             int j = 0;
             
             assert(htabl->key != NULL);

             assert(htabl->val!= NULL);
             htable_t h_indix = hash(htabl->key);

        
             h_indix = h_indix*5 + 1;
             h_indix = h_indix ^(sizeof(table) - 1);
             h_indix = h_indix & (sizeof(table) - 1);
             int indix = h_indix% sizeof(table);
             for(int i= 0; i <sizeof(table);i++){
                     if(table[i]!= NULL){
                             j++;
                     }

             }
             if(j >= (sizeof(htabl))/2){
                     int ncapa_tab = sizeof(table)*2;
                     h_table* gram_t[ncapa_tab];
                     if(ncapa_tab<sizeof(table)){
                             printf("Not Found reallocate, try again\n");
                     }
                     for(int i=0; i<sizeof(table); i++){
                        gram_t[i] = table[i];


                     }



                     free(table);
                     capa_tab = ncapa_tab;
                     table[capa_tab] = gram_t[ncapa_tab];

            
            

             }

             while(table[indix]!=NULL){
                     if(indix>sizeof(table)){indix =0;}
                     indix++;
             }
             table[indix]= htabl;


             


     }

     int  hash(hkey_t nam){//creation of hash table, used implementation of python
         unsigned char *p = (unsigned char*)nam;
         int long h = *p << 7;
        int long l = 0;
         while(*p){
             h = (1000003*h)^(*p);   
             l++;
             p++;

    }

     h ^= l;
     if(h<0){
        return -h;
    }
    else{
        return h;
    }

}

    h_table get_value(hkey_t key){
            h_table*table;
            htable_t h_indix = hash(key);
            h_indix = h_indix*5 + 1;
            h_indix = h_indix ^(sizeof(table) - 1);
            h_indix = h_indix & (sizeof(table) - 1);
            int indix = h_indix% sizeof(table);
            while(table[indix].key != NULL){
                    if(strcmp(key, table[indix].key)==0){
                            return table[indix];
                            exit(EXIT_SUCCESS);


                    }
                    indix++;
                    if(indix > sizeof(table)){
                            indix=0;
                            for(int i = 0; i< indix; i++){
                                if(strcmp(key, table[indix].key)==0){
                                        return table[indix];
                                         exit(EXIT_SUCCESS);


                    }
                                else{
                                        // return  gethostbyname(key);
                                         exit(EXIT_SUCCESS);
                    }
                                if(gethostbyname(key)==NULL){
                                         exit(EXIT_FAILURE);
                            }
                    }
                    
                    
                    }
            }

                    if(gethostbyname(key)==NULL){



                             exit(EXIT_FAILURE);

                             //return  gethostbyname(key);

            
            }
                   // return  gethostbyname(key);
                    exit(EXIT_SUCCESS);
        free(table);
    }

        h_table key_val_delete(hkey_t key){h_table*table;
            htable_t h_indix = hash(key);
            h_indix = h_indix*5 + 1;
            h_indix = h_indix ^(sizeof(table) - 1);
            h_indix = h_indix & (sizeof(table) - 1);
            int indix = h_indix% sizeof(table);
            while(table[indix].key != NULL){
                    if(strcmp(key, table[indix].key)==0){
                            table[indix].key ="=>delecte";
                            table[indix].val = "=>delecte";
                            exit(EXIT_SUCCESS);


                    }

            }






        }
int main(){
    /*   // htable_t hash(hkey_t* key);
   // char c[7]= "pap";
   // int j = hash(c);
   // printf(".%d.",j);
    printf("...%d...",hash("maman3"));
    printf("...%d...",hash("fofo" ));
    printf("...%d...",hash("dada"));
    printf("..%d...",hash("cloclo12"));
    printf("...%d...",hash("fohek1"));
    printf("....%d...",hash("da"));
    printf("..%d...",hash("clc12"));
    printf("...%d...",hash("maman mali3"));
    printf("...%d...",hash("fofo dja" ));
    printf("...%d...",hash("dada yi"));
    printf("...%d...",hash("cloclo va"));
    printf("...%d...",hash("maman"));
    printf("...%d...",hash("foggdnfo" ));
    printf("...%d...",hash("dagagada"));

*/
   

        return 0;
}