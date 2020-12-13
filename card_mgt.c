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
	strcpy(q,"select comp,num,date_format(date,'%y/%m') from card where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");

	printf("<script language=\"javascript\">");
	printf("function inst_card(id,ur,num){");//팝업창 오픈 상품 추가.
	
	printf("var ff=document.cardf;");
	printf("var url=ur;");
	printf("window.open('','popupView','width=600,height=500');");
	printf("ff.action=url;");
	printf("ff.target='popupView';");
	printf("ff.id.value=id;");
	printf("ff.num.value=num;");
	printf("ff.submit();}");//서브밋 url에 전송. 
	printf("</script>");

	printf("<h1>결제 카드 관리</h1>");
	printf("<table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:center;\"><tbody>");
	printf("<tr><td style=\"border-bottom:3px solid black;\"></td><td style=\"border-bottom:3px solid black;\">카드사</td><td style=\"border-bottom:3px solid black;\">카드번호</td><td style=\"border-bottom:3px solid black;\">유효기간</td></tr>");
	int idx=0;
	printf("<form name=\"cardf\" id=\"cardf\" method=\"post\" actino=\"\">");

	printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("id"));
	printf("<input type=\"hidden\" name=\"num\" value=\"%s\"></form>",findEntry("id"));
	while((row=mysql_fetch_row(res))){
		
		printf("<tr><td style=\"border-bottom:1px solid black;\">%d</td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\"><input type=\"button\" value=\"삭제\" onclick=\"inst_card('%s','rm_card.cgi','%s');\"></td></tr>",++idx,row[0],row[1],row[2],findEntry("id"),row[1]);}
	printf("<tr><td><br></td></tr>");
	printf("<tr><td></td><td></td><td><input type=\"button\" value=\"신규 등록\" onclick=\"inst_card('%s','inst_card.cgi','null');\"></td><td><input type=\"button\" value=\"닫기\" onclick=\"window.close();\"></td></tr>",findEntry("id"));
	printf("</head></html>");
}
