/* -----------------------------------------------------------------------
	cgipost.c

	   This is the public utility header file for HTML form tag ......

   Date		Name		Desc
   -----------	--------------	-----------------------------
   1997. 3.19	Deadfire	Optimize
   ------------------------------------------------------------------------ */
#include "cgipost.h"

char *makeword(line, stop) 
char *line;
char stop;
 {
    int x = 0,y;
    char *word =(char*)malloc(sizeof(char)*(strlen(line)+1));
    for(x=0;((line[x]) && (line[x] != stop));x++)
        word[x] = line[x];
    word[x] = '\0';
    if(line[x]) ++x;
    y=0;
    while(line[y++] = line[x++]);
    return word;
}
char *fmakeword(f,  stop, cl) 
FILE *f; 
char stop; 
int *cl;
 {
    int wsize;
    char *word;
    int ll;
    wsize = 102400;
    ll=0;
    word = (char *) malloc(sizeof(char) * (wsize + 1));
    while(1) {
        word[ll] = (char)fgetc(f);
        if(ll==wsize) {
            word[ll+1] = '\0';
        
    wsize+=102400;
            word = (char *)realloc(word,sizeof(char)*(wsize+1));
        }
        --(*cl);
        if((word[ll] == stop) || (feof(f)) || (!(*cl))) {
            if(word[ll] != stop){
                ll++;
            }
            if(!feof(f)){
                word[ll] = '\0';
            }else{
                word[ll-1] = '\0';
            }
            return word;
        }
        ++ll;
    }
}
char x2c(what) 
char *what;
{
   register char digit;
   digit =(what[0]>='A'?((what[0]&0xdf)-'A')+10:(what[0]-'0'));
   digit *= 16;
   digit +=(what[1]>='A'?((what[1]&0xdf)-'A')+10:(what[1]-'0'));
   return(digit);
}
void unescape_url(url) 
char *url; 
{
    register int x,y;
    for(x=0,y=0;url[y];++x,++y) {
        if((url[x] = url[y]) == '%') {
            url[x] = x2c(&url[y+1]);
            y+=2;
        }
    }
    url[x] = '\0';
}
void plustospace(str) 
char *str;
{
    register int x;
    for(x=0;str[x];x++) if(str[x] == '+') str[x] = ' ';
}
void getPostData()
{
   int i;
   unsigned int cl;

   cl = atol(getenv("CONTENT_LENGTH"));
   for(i = 0; cl&&(!feof(stdin)); i++) {
           entries[i].val = fmakeword(stdin,'&',&cl);
           plustospace(entries[i].val);
           unescape_url(entries[i].val);
           entries[i].name = makeword(entries[i].val,'=');
   }
   entry_count = i;
}
char *findEntry(name)
char *name;
{
   int i;
   for(i = 0;i < entry_count;i++)
	if( strcmp(entries[i].name, name) == 0) 
		return(entries[i].val);
   return 0;	/* null */
}
int findEntryCount(name)
char *name;
{
   int i;
   int cnt = 0;		/* match count */

   for(i = 0;i < entry_count;i++)
	if( strcmp(entries[i].name, name) == 0) 
		cnt++;
   return cnt;
}