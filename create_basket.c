#include<stdio.h>
#include"/usr/include/mysql/mysql.h"
#include<errno.h>
#include"cgipost.h"
#include<string.h>
#include<stdlib.h>
#include<time.h>
void main(){
	time_t curr;
	struct tm *d;
	curr=time(NULL);
	d=localtime(&curr);

	getPostData();
	
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	int fields;
	
	mysql_init(&mysql);//객체 초기화
	
	
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET NAMES utf8");//한글 사용*/
	if(!mysql_real_connect(&mysql,NULL,"shop","shop1","shopdb",3306,(char *)NULL,0))
	{
		
		printf("DB연결 실패 ");
		
	}
	else
		
		
		if(mysql_query(&mysql,"use shopdb"))
		{
			printf("use test_db 쿼리문은 실패");
		}
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	
	printf("<script language=\"JavaScript\">");
	printf("function closeWin(){");
	printf("window.history.back();}");
	printf("</script>");
	
	char *q=malloc(sizeof(char)*999);
	strcpy(q,"insert into basket(id) values('");
	strcat(q,findEntry("id"));
	strcat(q,"')");
	if(	mysql_query(&mysql,q) )
	{
		printf("<p>장바구니 생성 실패<br>%s</p1>",mysql_error(&mysql));
	}
	else
		printf("장바구니가 생성 되었습니다.");
	printf("<body onload=\"closeWin();\">");

	printf("</body></head></html>");
}
