#ifndef _CORE_H_
#define _CORE_H_

int countChains(char ** words, int length, char * result[]);

int getLongestWordChain(char ** words, int length, char * result[], char head, 
                        char tail, char ban, bool allow_circle);

int getLongestCharChain(char ** words, int length, char * result[], char head, 
                        char tail, char ban, bool allow_circle);

#endif 
