#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE 10000000
//------------The data type----------------------------------------
typedef unsigned int long htable_t;
typedef  char*  hkey_t;
typedef char* val_t;
//-----------------end---------------------------------------------
//-----------------structure of hash table-------------------------
typedef struct htable{
    hkey_t key;
    val_t val;
}h_table;
//--------------------end-------------------------------------------
//-------------------fonction of hash-------------------------------
htable_t hash(hkey_t key)
{ // creation of hash table, used implementation of python
        unsigned char *p = (unsigned char *)key;
        int long h = *p << 7;
        int long l = 0;
        while (*p)
        {

                h = (1000000001 * h) ^ (*p);
                l++;
                p++;
        }

        h ^= l;

        if (h < 0)
        {
            h=abs(h);
            htable_t h_indix = 0 ;
            h_indix = h*5 + 1;
           // h_indix = h_indix ^(TAILLE - 1); // (sizeof(table) - 1);
            //h_indix = h_indix & (TAILLE -1);
            h_indix = h_indix % (TAILLE -1);

            return h_indix;

        }


        else
        {
            htable_t h_indix = 0 ;
            h_indix = h*5 + 1;
            //h_indix = h_indix ^(TAILLE - 1); // (sizeof(table) - 1);
            //h_indix = h_indix & (TAILLE -1);
            h_indix = h_indix % (TAILLE -1);

            return h_indix;

        }

}
//--------------------end----------------------------------------
int main() {
    char str[255];//reate table of content
    int i=0;
    htable_t tab1[2335],ent1;
    FILE* fich3 = fopen("C:/Users/fiacr/Desktop/EXOC/F_test_evo/doc3.csv", "a");// create and write in file the number of collision
    if(!fich3)
    {
        printf("Erreur de creation du fichier N3, Try it");//print it if error
    }

    //fprintf(fich3, "TAILLE          K");

    FILE* fich = fopen("C:/Users/fiacr/Desktop/EXOC/F_test_evo/doc2.txt", "w");// create and write file of integer of the hash
    if(!fich)
    {
        printf("Erreur de creation du fichier N2, Try it");//print it if error
    }
    FILE* fich1 = fopen("C:/Users/fiacr/Desktop/EXOC/F_test_evo/doc1.txt", "r");//read file of data set password
    if(!fich1)
    {
        printf("Erreur de Lecture du Fichier N1");//print if error

    } else
    {
        while(fgets(str,255,fich1)!=NULL)
        {
            tab1[i]= hash(str);

            //fwrite(ent1,strlen(ent1),1, fich);
            //fputs(&tab1[i],fich);
            printf("%d ===> %ld\n",i,tab1[i]);
            fprintf(fich,"%ld \n",tab1[i]);


            i++;
        }
        int tab2[2335];
        for(int a=0; a < 2335; a++)
        {
            tab2[a]=tab1[a];
        }
        int k = 0;
        FILE* fich2 = fopen("C:/Users/fiacr/Desktop/EXOC/F_test_evo/doc2.txt","r");//read file of int of the hast
        if(!fich2)
        {
            printf("La creation du fichier");//print if erreur
        }
        //-------------------------create table and copy element in table and counts colision------
        for(int j = 0; j < 2335; j++)
        {
            for(int v =0; v<2335; v++ )
             {
                if(tab2[j] >= 0)
                {
                    if(j==v)
                    {
                        v = j + 1;
                    }

                    //if(j<1115){//compte k< TAILLE/2 or >


                        if (tab2[j] == tab2[v]) {
                            k++;
                            tab2[v] = -1;
                            //printf("%d =====>%d\n", tab1[j], tab1[v]);
                        }
                   // }//compte k
                }
            }

            //k=0;
        }
        fprintf(fich3, "%d,%d\n",TAILLE, k);
        printf("La valeur de k = %d\n", k);

    }
    //-------------------------------------end-------------------------------------
    fclose(fich1);
    fclose(fich);
    fclose(fich3);
    return 0;
}
