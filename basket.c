#include<stdio.h>
#include"/usr/include/mysql/mysql.h"
#include<errno.h>
#include"cgipost.h"
#include<string.h>
#include<stdlib.h>
void main()
{
	
	getPostData();
	
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	MYSQL_RES* res1;
	MYSQL_ROW row1;
	int fields;
	
	mysql_init(&mysql);//객체 초기화
	
	
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET NAMES utf8");//한글 사용*/
	if(!mysql_real_connect(&mysql,NULL,"shop","shop1","shopdb",3306,(char *)NULL,0))
	{
		
		printf("DB연결 실패 ");
		
	}
	if(mysql_query(&mysql,"use shopdb"))
	{
		printf("use test_db 쿼리문은 실패");
	}
	char *q=malloc(sizeof(char)*999);
	strcpy(q,"select * from basket where num='");
	strcat(q,findEntry("basketnum"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	fields=mysql_num_fields(res);
	row=mysql_fetch_row(res);
	char *basket_name=malloc(sizeof(char)*999);
	strcpy(basket_name,row[1]);
	strcpy(q,"select book_num,sum(quantity) from putbasket where basket_num='");
	strcat(q,findEntry("basketnum"));
	strcat(q,"' group by book_num");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	fields=mysql_num_fields(res);
	int rows=mysql_num_rows(res);
	
	int tq=0;
	int tp=0;
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	printf("<h1>장바구니 %s </h1>",basket_name);

	printf("<script language=\"javascript\">");
	printf("function delbask(bkn,bn){");
	printf("var delbas=document.delf;");
	printf("var url='drop_basket.cgi';");
	printf("window.open('','popupView','width=10,height=10');");
	printf("delbas.action=url;");
	printf("delbas.target='popupView';");
//	printf("delbas.basket_num.value=\"non\";");
//	printf("delbas.book_num.vlaue=\"non\";");
	printf("delbas.arg0.value=bkn;");
	printf("delbas.id.vlaue=bn;");

	printf("delbas.submit();}");
//	printf("window.location.reload();}");
	printf("</script>");
	printf("<table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:center;\"><tbody>");
	printf("<tr><td style=\"border-bottom:3px solid black;border-right:3px solid black;\">상품번호</td><td style=\"border-bottom:3px solid black;border-right:3px solid black;text-align:center;\">타이틀</td><td style=\"border-bottom:3px solid black;border-right:3px solid black;\">수량</td><td style=\"border-bottom:3px solid black;border-right:3px solid black;\">가격</td></tr>");	
	int cnt=0;
//	printf("<form name=\"del\" id=\"del\" method=\"post\" action=\"\">");
	printf("<form name=\"delf\" id=\"delf\" method=\"post\" action=\"\">");
	printf("<input type=\"hidden\" name=\"arg0\" value=\"\">");
	printf("<input type=\"hidden\" name=\"id\" value=\"\">");
	
	while((row=mysql_fetch_row(res)))
	{
		strcpy(q,"select * from book where num='");
		strcat(q,row[0]);
		strcat(q,"'");
		mysql_query(&mysql,q);
		res1=mysql_store_result(&mysql);
		row1=mysql_fetch_row(res1);
		printf("<tr>");
//		printf("<form name=\"del%d\" id=\"del%d\" method=\"post\" action=\"\">",cnt,cnt);
		printf("<td style=\"border-bottom:1px solid black;border-right:3px solid black;\">%s</td><td style=\"border-bottom:1px solid black;border-right:3px solid black;\">%s</td><td style=\"border-bottom:1px solid black;border-right:3px solid black;\">%s</td><td style=\"border-bottom:1px solid black;border-right:3px solid black;\">%s</td>",row1[0],row1[1],row[1],row1[3]);
//		printf("<input type=\"hidden\" name=\"arg0\" value=\"%s\">",findEntry("basketnum"));
//		printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",row1[0]);
//		printf("</form>");
//		printf("<td><input type=\"button\" value=\"삭제\"onclick=\"delbask('%s','%s');\"></td></tr>",findEntry("basketnum"),row1[0]);cnt++;
		int q=0;
		int p=0;
		q=atoi(row[1]);
		p=atoi(row1[3]);
		tq= tq+q;
		tp=tp+(q*p);
	}
	printf("</form>");

	printf("<tr><td style=\"border-bottom:1px solid black;border-right:1px solid black;border-top:3px solid black;\">Total</td><td style=\"border-top:3px solid black;border-bottom:1px solid black;border-right:3px solid black;\"></td><td style=\"border-top:3px solid black;border-bottom:1px solid black;border-right:3px solid black;\">%d 권</td><td style=\"border-top:3px solid black;border-bottom:1px solid black;border-right:3px solid black;\">%d 원</td></tr>",tq,tp);
	printf("</tbody></table>");
	printf("<input type=\"button\" value=\"닫기\" onclick=\"window.close();\">"); 
	printf("</head></html>");
	free(q);
	mysql_free_result(res);
	mysql_free_result(row);
}
