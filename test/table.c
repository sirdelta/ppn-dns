/* This is the differente fonction tha we use to add or delete one machine or all   */

#include "table.h"

//--------------------------inittalisation values------------------------------------------------------------------------------------------------
void init_val() { // initilisation of values of ours table
  for (int i = 0; i <TAILLE; i++) {
    table[i].key = "vide";
    tab1[i].key = "vide";
    tab2[i].key = "vide";
    tab3[i].key = "vide";
    tab4[i].key = "vide";
    tab5[i].key = "vide";
    tab6[i].key = "vide";
    tab7[i].key = "vide";
    tab8[i].key = "vide";
    tab9[i].key = "vide";
    table[i].val = "vide";
    tab1[i].val = "vide";
    tab2[i].val = "vide";
    tab3[i].val = "vide";
    tab4[i].val = "vide";
    tab5[i].val = "vide";
    tab6[i].val = "vide";
    tab7[i].val = "vide";
    tab8[i].val = "vide";
    tab9[i].val = "vide";

    //------------------------end initialisation-------------------------------------------------------------------------------------------------------
  }
}
          //-----------------------------------add a machine or server---------------------------------------------------------------------------------------

          bool h_set(hkey_t key, val_t val) {
            htable_t h_indix = hash(key);
           // int indix = 0;
            // htable_t h_indix_val = hash(val);
            assert_non_null(key);
            assert_non_null(val);
            assert(key !=0);
            assert(strcmp(key, "vide") !=0);
            assert(val !=0);
            assert(strcmp(key, "vide") !=0);


            //--------------about hash key----------------------------------------------------------

            // printf("\nThe key is : %s \n", htabl->key);
            h_indix = h_indix * 5 + 1; // linear generator congruence
            h_indix = h_indix ^ (TAILLE - 1);
            h_indix = h_indix & (TAILLE - 1);
            // printf("h_indix = %ld", h_indix);
            int indix = (int)h_indix % (TAILLE);
            // printf("\n Dans la fonction SET : indix = %d \n", indix);

            if(strcmp(table[indix].key, "vide") ==0) {
              table[indix].key = key;
              table[indix].val = val;
              return true;
            }
            else if(strcmp(table[indix].key, "vide") ==0) {

              tab1[indix].key = key;
              tab1[indix].val = val;
              return true;
            }

            else if(strcmp(table[indix].key, "vide") ==0) {

              tab2[indix].key = key;
              tab2[indix].val = val;
              return true;

            }

            else if(strcmp(table[indix].key, "vide") ==0) {

              tab3[indix].key = key;
              tab3[indix].val = val;
              return true;

            }
            else if(strcmp(table[indix].key, "vide") ==0) {

              tab4[indix].key = key;
              tab4[indix].val = val;
              return true;

            }

            else if(strcmp(table[indix].key, "vide") ==0) {

              tab5[indix].key = key;
              tab5[indix].val = val;
              return true;

            }

            else if(strcmp(table[indix].key, "vide") ==0) {

              tab6[indix].key = key;
              tab6[indix].val = val;
              return true;

            }

            else if(strcmp(table[indix].key, "vide") ==0) {

              tab7[indix].key = key;
              tab7[indix].val = val;
              return true;

            }

            else if(strcmp(table[indix].key, "vide") ==0) {

              tab8[indix].key = key;
              tab8[indix].val = val;
              return true;

            }

            else if(strcmp(table[indix].key, "vide") ==0) {

              tab9[indix].key = key;
              tab9[indix].val = val;
              return true;
            }

            // printf("\n %s : %s\n\n ", htabl->key, (char *)htabl->val);
	return true;
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
int get_value(char* key)
{

          htable_t h_indix = hash(key);
          h_indix = h_indix * 5 + 1;
          h_indix = h_indix ^(TAILLE - 1); // (sizeof(table) - 1);
          h_indix = h_indix & (TAILLE -1); //(sizeof(table) - 1);
          //printf("Dant get : H_indix = %ld", h_indix);
          int indix1 = h_indix % TAILLE; // sizeof(table))
      if(strcmp(key,table[indix1].key)==0){
          printf("la cle et valeur :\n %s ============> %s\n",table[indix1].key, table[indix1].val);
          return 1;

      }
      else if(strcmp(key, tab1[indix1].key)==0){
          printf("la cle et valeur :\n %s ============> %s\n",tab1[indix1].key, tab1[indix1].val);
          return 1;

      }
      else if(strcmp(key, tab2[indix1].key)==0){
          printf("la cle et valeur :\n %s ============> %s\n",tab2[indix1].key, tab2[indix1].val);
          return 1;

      }

      else if(strcmp(key, tab3[indix1].key)==0){
          printf("la cle et valeur :\n %s ============> %s\n",tab3[indix1].key, tab3[indix1].val);
          return 1;

      }

      else if(strcmp(key, tab4[indix1].key)==0){
          printf("la cle et valeur :\n %s ============> %s\n",tab4[indix1].key, tab4[indix1].val);
          return 1;

      }

      else if(strcmp(key, tab5[indix1].key)==0){
          printf("la cle et valeur :\n %s ============> %s\n",tab5[indix1].key, tab5[indix1].val);
          return 1;

      }
      else if(strcmp(key, tab6[indix1].key)==0){
          printf("la cle et valeur :\n %s ============> %s\n",tab6[indix1].key, tab6[indix1].val);
          return 1;

      }
      else if(strcmp(key, tab7[indix1].key)==0){
          printf("la cle et valeur :\n %s ============> %s\n",tab7[indix1].key, tab7[indix1].val);
          return 1;

      }

      else if(strcmp(key, tab8[indix1].key)==0){
          printf("la cle et valeur :\n %s ============> %s\n",tab8[indix1].key, tab8[indix1].val);
          return 1;

      }

      else if(strcmp(key, tab9[indix1].key)==0){

          printf("la cle et valeur :\n %s ============> %s\n",tab9[indix1].key, tab9[indix1].val);
          return 1;

      }
      else{

          addr_info(key);
          return 1;

      }






}

//-------------------------------------------delet key with value------------------------------------------------------------------------------------------
bool key_val_delete(hkey_t key)
{
        //h_table *table;
        htable_t h_indix = hash(key);
        h_indix = h_indix * 5 + 1;
        h_indix = h_indix ^ (TAILLE - 1);
        h_indix = h_indix & (TAILLE - 1);
        int indix2 =h_indix % TAILLE;


    if(strcmp(key,table[indix2].key)==0){
        table[indix2].key = "vide";
        table[indix2].val = "vide";
        return true;
    }
    else if(strcmp(key, tab1[indix2].key)==0){
        tab1[indix2].key = "vide";
        tab1[indix2].val = "vide";
        return true;
    }
    else if(strcmp(key, tab2[indix2].key)==0){
        tab2[indix2].key = "vide";
        tab2[indix2].val = "vide";
       return true;
    }

    else if(strcmp(key, tab3[indix2].key)==0){
        tab3[indix2].key = "vide";
        tab3[indix2].val = "vide";
        return true;
    }

    else if(strcmp(key, tab4[indix2].key)==0){
        tab4[indix2].key = "vide";
        tab4[indix2].val = "vide";
        return true;
    }

    else if(strcmp(key, tab5[indix2].key)==0){
        tab5[indix2].key = "vide";
        tab5[indix2].val = "vide";
        return true;
    }
    else if(strcmp(key, tab6[indix2].key)==0){
        tab6[indix2].key = "vide";
        tab6[indix2].val = "vide";
       return true;
    }
    else if(strcmp(key, tab7[indix2].key)==0){
        tab7[indix2].key = "vide";
        tab7[indix2].val = "vide";
        return true;
    }

    else if(strcmp(key, tab8[indix2].key)==0){
        tab8[indix2].key = "vide";
        tab8[indix2].val = "vide";
        return true;
    }

    else if(strcmp(key, tab9[indix2].key)==0){
       tab9[indix2].key = "vide";
       tab9[indix2].val = "vide";
       return true;
    }

return true;
}

void addr_info(hkey_t key){
    struct addrinfo hints;
    struct addrinfo *res, *tmp;
    char host[256];

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (key == 0  || key == NULL) {
        fprintf(stderr, "%s existe pas en addresse hote.\n",key);
        //exit(EXIT_FAILURE);
    }

    int ret = getaddrinfo(key, NULL, &hints, &res);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        exit(EXIT_FAILURE);
    }
    printf("\n\n %s==================>",key);
    for (tmp = res; tmp != NULL; tmp = tmp->ai_next) {
        getnameinfo(tmp->ai_addr, tmp->ai_addrlen, host, sizeof(host), NULL, 0, NI_NUMERICHOST);
        puts(host);
    }
    printf("\n\n");
    free(res);
    //exit(EXIT_SUCCESS);

}


//----------------------------------------------end delete---------------------------------------------------------------------------------------------------
/*
int main()
{

        //-----------------------------------------------------test of hash-----------------------------------------------------------------------------------------------
        init_val();
        printf("...%ld...", hash("maman3"));
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

        //----------------------------------------------------test of insert a new machine----------------------------------------------------------------------------------

        h_table jan = {"123.345.456.1", "mahine1"};
        h_table klen = {"123.345.16.1", "mahine123"};

        h_table jonas = {"123.45.46.1", "mahine4"};
        h_table dona = {"123.35.46.1", "mahine189"};

        h_table luc = {"123.3.56.1", "mahine6741"};
        h_table van = {"123.3.6.1", "mahine134"};
        h_table blan = {"3.35.6.1", "78machin"};
        h_table kankun = {"1.35.6.1", "ahine1"};
        h_table didier = {"13.5.56.1", "mahi34"};

        h_set("123.345.456.1","machine1");
        h_set("123.345.456.2","machine2");
        h_set("123.345.456.3","machine3");


       // h_set("123.345.16.4", "machine2");
       // h_set("123.45.46.7","machine3");
       // h_set(&jonas);
       // h_set(&luc);

        //---------------------------------------------------------end insert-------------------------------------------------------------------------------------------------

        //-----------------------------------------------------------------------test of the fonction get----------------------------------------------------------------------
        //key_val_delete("123.345.456.2");

        //get_value("123.345.456.2");
        get_value("google.com");
        return 0;
}
*/
