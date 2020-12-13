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
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	printf("<script language=\"javascript\">");
	printf("function winclo(){");
	printf("window.close();");
	printf("opener.location.href=\"/login.html\";}");
	printf("</script>");
	//id중복 검사
	char *q=malloc(sizeof(char)*999);
	int chk=0;
	mysql_query(&mysql,"select id from user");
	res=mysql_store_result(&mysql);
	
	while((row=mysql_fetch_row(res)))
	{
		if(strcmp(row[0],findEntry("id"))==0){
			chk++;
			break;
		}
	}
	if(chk==1)
	{
		printf("<p1>중복된 ID입니다.</p1>");
		printf("<br><input type=\"button\" value=\"닫기\" onclick=\"window.close();\">");
//		printf("<br><input type=\"button\" value=\"닫기\" onclick=\"winclo();\">");
	}
	if(chk==0)
	{
		strcpy(q,"insert into user(name,id,pwd) values('");
		strcat(q,findEntry("name"));
		strcat(q,"','");
		strcat(q,findEntry("id"));
		strcat(q,"','");
		strcat(q,findEntry("pwd"));
		strcat(q,"')");
		if(mysql_query(&mysql,q))
		{
			printf("<p1>Error : %s</p1>",mysql_error(&mysql));
		}
		else
		{
			printf("<h1>가입이 완료되었습니다.</h1>");
		}
		if(strcmp(findEntry("c1"),"0")==0)
		{
			printf("<p1>카드 등록이 완료되지 않았습니다.마이페이지에서 추가하여 주세요.</p1>");
		}
		else
		{
			strcpy(q,"insert into card(id,num,date,comp) values('");
			strcat(q,findEntry("id"));
			strcat(q,"','");
			strcat(q,findEntry("c1"));
			strcat(q,"-");
			strcat(q,findEntry("c2"));
			strcat(q,"-");
			strcat(q,findEntry("c3"));
			strcat(q,"-");
			strcat(q,findEntry("c4"));
			strcat(q,"','");
			strcat(q,findEntry("date"));
			strcat(q,"-01','");
			strcat(q,findEntry("카드사"));
			strcat(q,"')");
			if(mysql_query(&mysql,q))
			{
				printf("<p1>카드 등록 Error :<br> %s<br>마이페이지에서 추가 등록이 가능합니다.</p1>",mysql_error(&mysql));
			}
		}
		strcpy(q,"insert into addr(id,chk,zip,base,detail) values('");
		strcat(q,findEntry("id"));
		strcat(q,"','");
		strcat(q,"자택");
		strcat(q,"','");
		strcat(q,findEntry("zip1집"));
		strcat(q,"-");
		strcat(q,findEntry("zip2집"));
		strcat(q,"','");
		strcat(q,findEntry("base집"));
		strcat(q,"','");
		strcat(q,findEntry("detail집"));
		strcat(q,"')");
		mysql_query(&mysql,q);
		strcpy(q,"insert into addr(id,chk,zip,base,detail) values('");
		strcat(q,findEntry("id"));
		strcat(q,"','");
		strcat(q,"회사");                               
		strcat(q,"','");
		strcat(q,findEntry("zip1회사"));
		strcat(q,"-");
		strcat(q,findEntry("zip2회사"));
		strcat(q,"','");
		strcat(q,findEntry("base회사"));
		strcat(q,"','");                                
		strcat(q,findEntry("detail회사"));
		strcat(q,"')");
		mysql_query(&mysql,q);
		printf("<br><input type=\"button\" value=\"닫기\" onclick=\"winclo();\">");
	}




	printf("</head></html>");
	free(q);
	mysql_free_result(res);
}
