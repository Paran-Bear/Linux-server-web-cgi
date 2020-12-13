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
	mysql_query(&mysql,"select * from card_comp");
	res=mysql_store_result(&mysql);
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	printf("<script language=\"javascript\">");
	printf("function winclo(){");
	printf("window.close();");
	printf("opener.location.reload();}");

	printf("function numMax(e){");
	printf("if(e.value.length>e.maxLength){");
	printf("e.value=e.value.slice(0,e.maxLength);");
	printf("}}");
	printf("</script>");

	printf("</head>");
	printf("<h1>신규 카드 등록</h1>");
	printf("<body>");
	printf("<form method=\"post\" action=\"instcard.cgi\">");
	printf("<table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:left;\"><tbody>");
	printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("id"));
	printf("<tr><td style=\"border-bottom:1px solid black;\">카드사\t");
	printf("<select name=\"comp\">");
	while((row=mysql_fetch_row(res)))
	{
		printf("<option value=\"%s\">%s</option>",row[0],row[0]);
	}
	printf("</select></td></tr>");

	printf("<tr><td style=\"border-bottom:1px solid black;\">카드번호 ");
	for(int i=0;i<4;i++)
	{
		printf("<input type=\"number\" name=\"cn%d\" maxlength=\"4\" style=\"width:50px;\"  oninput=\"numMax(this);\" required>",i);
		if(i!=3)
			printf("-");
	}
	printf("</td></tr>");
	printf("<tr><td style=\"border-bottom:1px solid black;\">유효기간 <input type=\"month\" name=\"date\" required></td></tr>");
	printf("<tr><br></tr>");
	printf("<tr><td style=\"border-bottom:1px solid black;\"><input type=\"submit\" value=\"등록\">          <input type=\"button\" value=\"취소\" onclick=\"winclo();\"></td></tr>");
	printf("</tobdy></table>");
	printf("</form>");
	printf("</html>");
}
