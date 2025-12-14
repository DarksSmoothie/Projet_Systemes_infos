#ifndef _LIBTABLEAUX_H_
#define _LIBTABLEAUX_H_


void arrayInit();


void freeArray();

void insertItem(int item);
void updateItem(int i, int item);
int getItem(int i);
void deleteItem(int item);
void printArray();



//_______________LOGS_____________________
extern char debug_level;

void log_info(char *message,...);
void log_debug(char *message,...);



#endif 
