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

	strcpy(q,"select * from corder where order_num='");
	strcat(q,findEntry("arg0"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	while((row=mysql_fetch_row(res)))
	{
		strcpy(q,"update book set stock=stock+");
		strcat(q,row[2]);
		strcat(q," where num='");
		strcat(q,row[1]);
		strcat(q,"'");
		mysql_query(&mysql,q);
	}
	//주문상태 취소로 바꿈.
	strcpy(q,"update border set status='취소' where num='");
	strcat(q,findEntry("arg0"));                               
	strcat(q,"'");                                          
	if(mysql_query(&mysql,q));
/* 내역 삭제 코드.
	strcpy(q,"delete from corder where order_num='");
	strcat(q,findEntry("arg0"));
	strcat(q,"'");
	int err=0;
	if(mysql_query(&mysql,q))
	{
		err+=100;
	}
	
	strcpy(q,"delete from border where num='");
	strcat(q,findEntry("arg0"));
	strcat(q,"'");
	if(mysql_query(&mysql,q))
	{
		err+=1000;
	}
*/
	int err=0;
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	printf("<script language=\"javascript\">");
	printf("function winclo(){");
	printf("window.close();");
	printf("opener.location.reload();}");
	printf("</script>");
	if(err==0){
	printf("<h1>주문이 취소 되었습니다.</h1>");}
	else{
		printf("<h1>주문취소 오류<h1>");
		printf("<p1>에러코드:%d",err);
	}
	printf("<input type=\"button\" value=\"확인\" onclick=\"winclo();\">");
	printf("</head></html>");
	free(q);
	mysql_free_result(res);
}
