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
	mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET NAMES utf8");//한글 사용
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><body>");	
	printf("<script language=\"javascript\">");
	printf("function rc(){");
	printf("opener.location.reload();");
	printf("window.close();}</script>");
	if(!mysql_real_connect(&mysql,NULL,"shop","shop1","shopdb",3306,(char *)NULL,0))
	{
		
		printf("DB연결 실패 ");
		
	}
	else
	{               
//		printf("DB연결성공<BR> ");
	}
	if(mysql_query(&mysql,"use shopdb"))
	{
		printf("use test_db 쿼리문은 실패");              
	}
	else
	{
//		printf("use test_db 쿼리문 성공<BR>");
	}
	char *s1="insert into book (num,title,stock,price) values('";//쿼리문 기초
	char *s2=malloc(sizeof(char)*999);//최종 쿼리문
	strcpy(s2,s1);
	for (int i=0;i<entry_count;i++){
		strcat(s2,entries[i].val);
		if(i==entry_count-1)
			strcat(s2,"')");
		else
			strcat(s2,"','");
	}
	if(mysql_query(&mysql,s2))
		printf("등록실패");
	else
		printf("<h1>상품 등록 완료</h1>");
	printf("<input type=\"button\" value=\"확인\" onclick=\"rc()\">");

		

//	res=mysql_store_result(&mysql);//쿼리 결과 저장.
//	fields=mysql_num_fields(res);//쿼리결과의 개수
//	while((row=mysql_fetch_row(res)))//쿼리 결과 탐색.
//	{
//		for(int i=0;i<fields;++i)
//			printf("%s ",row[i]);
//		printf("<br>");
//	}
//	mysql_free_result(res);//쿼리 결과 해제.
	mysql_close(&mysql);//쿼리 해제.
	printf("</body></html>");//html끝.
	free(s2);
}

