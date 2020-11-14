#include<stdio.h>
#include"cgipost.h"
int main()
{
	    int i;

	        printf("Content-type: text/html\n\n");
printf("<meta charset=\"utf-8\">");

		    getPostData();//POST방식으로 전달받은 환경변수를 불러와 구조체에 저장하는 함수.
		    printf("%s님 환영합니다.",findEntry("username"));//특정 name=value의 name의 value를 리턴하는 함수.
		        for(i = 0;i < entry_count;i++){
				       printf(" %d) [%s] = [%s]<br>\n",i, entries[i].name, entries[i].val);
				           }
return 0;
}
