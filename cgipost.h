/* -----------------------------------------------------------------------
	cgipost.h

	   This is the public utility header file for HTML form tag ......

   Date		Name		Desc
   -----------	--------------	-----------------------------
   1997. 3.19	Deadfire	Optimize
   ------------------------------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>

#define 	MAXENTRY	1000	/* form entry count */

char *makeword();
char *fmakeword();
char x2c();
void unescape_url(); 
void plustospace();

typedef struct {
	char *name;
	char *val;
}entry;

/** ------------------------ global variable ------------------------------ **/
entry entries[MAXENTRY];
int entry_count;

/** ------------------------ user function -------------------------------- **/

char *findEntry();		/* find val by given name in entries[] */
int findEntryCount();		/* find count by given name in entries[] */
void getPostData();		/* get post data to entries[] from html */
