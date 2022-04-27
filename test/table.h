#ifndef __TABLE_H__
#define __TABLE_H__
#include <sys/types.h>
#include<stdarg.h>
#include<stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stddef.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#define TAILLE 10
//int TAILLE = 10;

typedef unsigned int long htable_t;
typedef  char*  hkey_t;
typedef char* val_t;

/*typedef struct tabT{
        int index;
        int t;
}tabTime;
*/

typedef struct htable{
        hkey_t key;
        val_t val;
      //  struct htable*next;

}h_table;

//int tabHeur[TAILLE];
h_table table[10];
h_table tab1[10];
h_table tab2[10];
h_table tab3[10];
h_table tab4[10];
h_table tab5[10];
h_table tab6[10];
h_table tab7[10];
h_table tab8[10];
h_table tab9[10];
//h_table tab_val[10];

void init_val();//Initialisation of 
//int new_taille(int* taille); //augment the size when the table is plemty at 1/2
//h_table new_tab(h_table *old_tab);


bool h_set(hkey_t key, val_t val);//add anew table

htable_t hash(hkey_t key);//creation of hash table, used implementation of python

bool key_val_delete(hkey_t key);//for delete the key with the value.
int get_value(hkey_t key);//get key and value
void addr_info(hkey_t key);

#endif//__TABLE_H__
