/* This is the differente fonction tha we use to add or delete one machine or all   */

#include "table.h"
//#define TAILLE 10

//--------------------------inittalisation values------------------------------------------------------------------------------------------------
//h_table table[TAILLE];
void init_val()
{ // initilisation of values of ours table

        //h_table table[TAILLE]; // create of table struct

        for (int i = 0; i < TAILLE; i++)
        {
                table[i].key = NULL;
                table[i].val = NULL;
                tab_val[i].key = NULL;
                tab_val[i].val = NULL;
               // table[i].suivant = NULL;
                //table[i].next = NULL;
        }
        /* for(int i =0; i<capa_tab; i++){//verification if in set init_val(), table[i]==NULL
                 if(table[i]==NULL)
                    fprintf(stderr," %d ",i+1);
         }*/

}

//------------------------end initialisation-------------------------------------------------------------------------------------------------------

//-----------------------------------add a machine or server---------------------------------------------------------------------------------------
/*int new_taille(int *taille){
       *taille = *taille*2;

       return *taille;z'retre

       
}*/
/*int generate_indix(h_table *htabl, int TAILLE){
         // this fonction we used to add a new machine
      
       htable_t h_indix = hash(htabl->key);
       printf("\nThe key is : %s \n", htabl->key);
       h_indix = h_indix * 5 + 1; // linear generator congruence
       h_indix = h_indix ^ (TAILLE- 1);
       h_indix = h_indix & (TAILLE - 1);
       printf("h_indix = %ld", h_indix);
       int indix = h_indix % (TAILLE);
       printf("\n Dans la fonction SET : indix = %d \n", indix);
       return indix;
}
*/

int h_set(hkey_t key, val_t val){
        htable_t h_indix = hash(key);
        htable_t h_indix_val = hash(val);
        assert(key != NULL);
        assert(val != NULL);
        
//--------------about hash key----------------------------------------------------------

       // printf("\nThe key is : %s \n", htabl->key);
        h_indix = h_indix * 5 + 1; // linear generator congruence
        h_indix = h_indix ^ (TAILLE- 1);
        h_indix = h_indix & (TAILLE - 1);
        //printf("h_indix = %ld", h_indix);
        int indix = h_indix % (TAILLE);
       // printf("\n Dans la fonction SET : indix = %d \n", indix);

     
        /*while(table[indix].key != NULL || table[indix].key !=0)
        {
                indix +=1;

                if(indix > TAILLE)
                {
                        indix = 0;
                }

        } */
        if(table[indix].key != NULL || table[indix].key !=0){
                   tab_l* tab_li = malloc(50*sizeof(tab_l));
                   tab_li[indix].list->key = key;
                   tab_li[indix].list->key = val;
                   tab_li[indix].suivant = NULL;
        }
        else{
               //time_t  hStamp =time(NULL);

                table[indix].key = key;
                table[indix].val = val;
                //struct tm *hInfos = localtime(&hStamp);//we will use the timestamp by struct : struct tm
               //int valH = ((hInfos->tm_min)+(hInfos->tm_mday *24*60)+(hInfos->tm_hour*60));
               //tabHeur[indix]= valH;

        }
        
        
        

       //printf("\n %s : %s\n\n ", htabl->key, (char *)htabl->val);

        for(int i = 0; i < TAILLE; i++ ){
                printf("\n\t%s -----------> %s\n\n",table[i].key, table[i].val);
        }//goto hval;

        //-----------------------------end it----------------------------------------------------

        //-----------------------about hash value------------------------------------------------

      

       /* hval :{
       // printf("\nThe key is : %s \n", htabl->key);
        h_indix_val = h_indix_val * 5 + 1; // linear generator congruence
        h_indix_val = h_indix_val ^ (TAILLE- 1);
        h_indix_val = h_indix_val & (TAILLE - 1);
        //printf("h_indix = %ld", h_indix);
        int indix_val = h_indix_val % (TAILLE);
       // printf("\n Dans la fonction SET : indix = %d \n", indix);

        if(table[indix].val != NULL || table[indix].val !=0){
            tab_l* tab_li = malloc(50*sizeof(tab_l));
            tab_li[indix].list->key = key;
            tab_li[indix].list->key = val;
            tab_li[indix].suivant = NULL;
    }
        /*while(tab_val[indix_val].val != NULL || tab_val[indix_val].val !=0)
        {
                indix_val++;

                if(indix_val > TAILLE)
                {
                        indix_val = 0;
                }

        }
        if(get_key(val) ==1)
        {
                
        }
        else{
                time_t hStamp =time(NULL);
                tab_val[indix_val].key = key;
                tab_val[indix_val].val = val;
                struct tm *hInfos = localtime(&hStamp);//we will use the timestamp by struct : struct tm
                int valH = ((hInfos->tm_min)+(hInfos->tm_mday *24*60)+(hInfos->tm_hour*60));
                tabHeur1[indix]= valH;

        }
         

       //printf("\n %s : %s\n\n ", htabl->key, (char *)htabl->val
        
        for(int i = 0; i < TAILLE; i++ ){
                printf("\n\t%s ---------------------------------------------->%s\n\n",tab_val[i].key, tab_val[i].val);
        }


//-------
        ---------------end it-----------------------------------------------------------
        }
        while (1)
        {
                time_t hStamp =time(NULL);
                struct tm *hInfos = localtime(&hStamp);
                int valh2  = ((hInfos->tm_min)+(hInfos->tm_mday *24*60)+(hInfos->tm_hour*60));
                for(int j=0; j>100; j++){
                        if((valh2 -tabHeur[j]) > 10){
                                tab_val[j].key = 0;
                                tab_val[j].val = 0;
                                table[j].key = 0;
                                table[j].val = 0;


                        }*/
                        //else{

                        //}

                }
                
        }
        

}

htable_t hash(hkey_t key)
{ // creation of hash table, used implementation of python
        unsigned char *p = (unsigned char *)key;
        int long h = *p << 7;
        int long l = 0;
        while (*p)
        {

                h = (1000003 * h) ^ (*p);
                l++;
                p++;
        }

        h ^= l;

        if (h < 0)
                return abs(-h);

        else
                return h;
}

//--------------------------------------end add----------------------------------------------------------------------------------------------------------

//-----------------------------------------------------get value with key-------------------------------------------------------------------------------
int get_value(hkey_t key)
{

        // int h_set(h_table* htabl);//this fonction we used to add a new machine
        // int b=sizeof(h_table);
        
        htable_t h_indix = hash(key);
        h_indix = h_indix * 5 + 1;
        h_indix = h_indix ^(TAILLE - 1); // (sizeof(table) - 1);
        h_indix = h_indix & (TAILLE -1); //(sizeof(table) - 1);
      //  printf("Dant get : H_indix = %ld", h_indix);
        int indix1 = h_indix % TAILLE; // sizeof(table));
      //  printf("\n Dans get : indix = %d \n", indix1);
        int subIndx1 = indix1;
        while(table[indix1].key != NULL || table[indix1].key !=0){

                if(strcmp(key, table[indix1].key)!= 0){
                        indix1++;
                        if(indix1 > TAILLE){
                                indix1 = 0;
                        }

                }
                else{
                        printf("%s\n\n %s",table[indix1].key, table[indix1].val);
                        return 1;
                }
        

                //table[indix] = table[indix]->next;
        }
        // printf("IP : %s, Name : %s",table[indix]->key, (char*)table[indix]->val );

        /* indix++;
         if(indix > sizeof(table)){
                 indix=0;
                 for(int i = 0; i< indix; i++){
                     if(strcmp(key, table[indix].key)==0){
                             //return table[indix];
                              exit(EXIT_SUCCESS);



         }
                     else{
                             // return  gethostbyname(key);
                             printf("No fund name of adrresse");
                              exit(EXIT_SUCCESS);
         }
                     //if(gethostbyname(key)==NULL){
                            //  exit(EXIT_FAILURE);
                // }
         }


         }


         if(gethostbyname(key)==NULL){



                  exit(EXIT_FAILURE);

                  //return  gethostbyname(key);


 }
        // return  gethostbyname(key);
         exit(EXIT_SUCCESS);
//free(table);*/

}
int get_key(val_t val){
        htable_t h_indix_val = hash(val);
        h_indix_val = h_indix_val * 5 + 1; // linear generator congruence
        h_indix_val = h_indix_val ^ (TAILLE- 1);
        h_indix_val = h_indix_val & (TAILLE - 1);
        //printf("h_indix = %ld", h_indix);
        int indix_val = h_indix_val % (TAILLE);
        // printf("\n Dans la fonction SET : indix = %d \n", indix);
         while(table[indix_val].val != NULL || table[indix_val].val !=0){
         if(strcmp(val, table[indix_val].val)!= 0){
                 indix_val++;
                 if(indix_val > TAILLE){
                         indix_val = 0;
                 }
         }
         else{
                 printf("%s\n--->>>\n %s",table[indix_val].key, table[indix_val].val);
                 return 1;
         }
 
         //table[indix] = table[indix]->next;
 }
        
        


}



//---------------------------------------end get value-----------------------------------------------------------------------------------------------------
//-------------------------------------------delet key with value------------------------------------------------------------------------------------------
h_table key_val_delete(hkey_t key)
{
        h_table *table;
        htable_t h_indix = hash(key);
        h_indix = h_indix * 5 + 1;
        h_indix = h_indix ^ (TAILLE - 1);
        h_indix = h_indix & (TAILLE - 1);
        int indix = h_indix % TAILLE;
        while (table[indix].key != NULL || table[indix].key !=0)
        {
                if(strcmp(key, table[indix].key) == 0)
                {
                        table[indix].key = 0; // if this value is null or 0 you can have mistake to
                        table[indix].val = 0; // same
                        exit(EXIT_SUCCESS);
                }

                if(strcmp(key, table[indix].key) !=0 ){
                        indix++;
                        if(indix > TAILLE){
                                indix = 0;
                        }
                }
                
        
        }
}

//----------------------------------------------end delete---------------------------------------------------------------------------------------------------

int main()
{

        //-----------------------------------------------------test of hash-----------------------------------------------------------------------------------------------
        init_val();
     /*   printf("...%ld...", hash("maman3"));
        printf("...%ld...", hash("fofo"));
        printf("...%ld...", hash("dada"));
        printf("..%ld...", hash("cloclo12"));
        printf("...%ld...", hash("fohek1"));
        printf("....%ld...", hash("da"));
        printf("..%ld...", hash("clc12"));
        printf("...%ld...", hash("maman mali3"));
        printf("...%ld...", hash("fofo dja"));
        printf("...%ld...", hash("dada yi"));
        printf("...%ld...", hash("cloclo va"));
        printf("...%ld...", hash("maman"));
        printf("...%ld...", hash("foggdnfo"));
        printf("...%ld...", hash("dagagada"));
        //----------------------------------------------------end test of hash----------------------------------------------------------------------------------------------
*/
        //----------------------------------------------------test of insert a new machine----------------------------------------------------------------------------------

      /*  h_table jan = {"123.345.456.1", "mahine1"};
        h_table klen = {"123.345.16.1", "mahine123"};

        h_table jonas = {"123.45.46.1", "mahine4"};
        h_table dona = {"123.35.46.1", "mahine189"};

        h_table luc = {"123.3.56.1", "mahine6741"};
        h_table van = {"123.3.6.1", "mahine134"};
        h_table blan = {"3.35.6.1", "78machin"};
        h_table kankun = {"1.35.6.1", "ahine1"};
        h_table didier = {"13.5.56.1", "mahi34"};
*/
        h_set("123.345.456.1","mahine1");
        h_set("123.345.456.2","mahine2");
        h_set("123.345.456.3","mahine3");


       // h_set("123.345.16.4", "machine2");
       // h_set("123.45.46.7","machine3");
       // h_set(&jonas);
       // h_set(&luc);

        //---------------------------------------------------------end insert-------------------------------------------------------------------------------------------------

        //-----------------------------------------------------------------------test of the fonction get----------------------------------------------------------------------
       // key_val_delete("123.345.456.1");
        get_value("123.345.456.1");
        
        return 0;
}