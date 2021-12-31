#ifndef __TABLE_H__
#define __TABLE_H__
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <assert.h>
#include <sys/select.h>
#include <netinet/in.h>


typedef unsigned int long htable_t;
typedef  char* hkey_t;
typedef void* val_t;

typedef struct htable{
        hkey_t key;
        val_t val;

}h_table;



void init_val(void);
int h_set(h_table* htabl);
h_table get_value(hkey_t key);
h_table key_val_delete(hkey_t key);



#endif//__TABLE_H__