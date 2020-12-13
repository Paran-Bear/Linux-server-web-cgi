#include<stdio.h>
#include"/usr/include/mysql/mysql.h"
#include<errno.h>
#include"cgipost.h"
#include<string.h>
#include<stdlib.h>
void main(){
	
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
	char *q=malloc(sizeof(char)*999);
	int err=0;
	strcpy(q,"update border set status='판매완료' where num='");
	strcat(q,findEntry("arg0"));
	strcat(q,"'");
	if(mysql_query(&mysql,q))
	{
		err++;
	}
			
//	res=mysql_store_result(&mysql);

	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	printf("<script language=\"javascript\">");
	printf("function winclo(){");
	printf("window.close();");
	printf("opener.location.reload();}");
	printf("</script>");
	if(err==0){
	printf("<h1>주문해주셔서 감사합니다..</h1>");}
	else{
		printf("<h1>주문취소 오류<h1>");
		printf("<p1>에러:%s",mysql_error(&mysql));
	}
	printf("<input type=\"button\" value=\"확인\" onclick=\"winclo();\">");
	printf("</head></html>");
	free(q);
//	mysql_free_result(res);
}
