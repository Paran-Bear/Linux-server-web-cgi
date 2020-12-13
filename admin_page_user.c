#include<stdio.h>
#include"/usr/include/mysql/mysql.h"
#include<errno.h>
#include"cgipost.h"
#include<string.h>
#include<stdlib.h>
void main(){
	
//	getPostData();
	
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
	//상세페이지 js
	printf("function detail(id){");
	printf("var ff=document.userf;");
	printf("var url='user_detail.cgi';");
	printf("window.open('','popupView','width=650,height=500');");
	printf("ff.action=url;");
	printf("ff.target='popupView';");
	printf("ff.id.value=id;");
	printf("ff.submit();}");

	printf("function sales_history(id){");
	printf("var ff=document.userf;");
	printf("var url='user_history.cgi';");
	printf("window.open('','popupView','width=1000,height=500');");
	printf("ff.action=url;");
	printf("ff.target='popupView';");
	printf("ff.id.value=id;");
	printf("ff.submit();}");









	printf("</script>");
	char *q=malloc(sizeof(char)*999);
	strcpy(q,"select id,name from user where id!='삭제된계정' and id!='admin'");
	mysql_query(&mysql,q);


	//메뉴구성
	printf("<div id=\"nav_menu\">");
	printf("<ul style=\"list-style-type:none border:1px solid black;margin:auto\">");
	printf("<li style=\"display:inline; text-align:center;\">관리자님|</li>");
	printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"window.location.href='admin_page.cgi'\" value=\"상품관리\" style=\"background-color:#ffffff;border:0\">|</li>");
	printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"window.location.href='admin_page_order.cgi'\" value=\"주문관리\" style=\"background-color:#ffffff;border:0\">|</li>");
	printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"window.location.href='admin_page_user.cgi'\" value=\"회원관리\" style=\"background-color:#ffffff;border:0\">|</li>");
	printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"window.location.href='/login.html'\" value=\"로그아웃\" style=\"background-color:#ffffff;border:0\"></li>");
	printf("</ul>\n</div>");
	res=mysql_store_result(&mysql);
	fields=mysql_num_fields(res);
	//테이블 구성
	printf("<table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:left;\">\n<tbody>");
	printf("<tr bgcolor=\"#BDBDBD\"><td style=\"border-bottom:3px solid black;padding-right:40;padding-left:40; text-align:center;\">ID</td><td style=\"border-bottom:3px solid black;padding-rig2ht:40;padding-l2eft:40;text-align:center;\">이름</td><td style=\"border-bottom:3px solid black;adding-r2ight:40;paddi123ng-left:40; text-align:center;\">관리메뉴</td>");

	printf("</tr>");
	printf("<form method=\"post\" action=\"\" name=\"userf\" id=\"userf\">");
	printf("<input type=\"hidden\" name=\"id\" value=\"\">");
	printf("</form>");
	while((row=mysql_fetch_row(res)))
	{
		printf("<tr bgcolor=\"#E6E6E6\">");
		for(int i=0; i<fields;i++)
		{
			printf("<td style=\"border-bottom:1px solid black;padding-left:20;\">");
			printf("%s",row[i]);
			printf("</td>");
		}
		printf("<td style=\"padding-right:20;padding-left:20;border-bottom:1px solid black;\">");
		printf("<input type=\"button\" value=\"상세정보\" onclick=\"detail('%s')\">",row[0]);
/*		printf("</td>");

		printf("<td style=\"padding-right:40;padding-left:20;border-bottom:1px solid black;\">");*/
		printf("<input type=\"button\" value=\"판매이력\" onclick=\"sales_history('%s')\">",row[0]);
		printf("</td>");

		/*printf("<td style=\"padding-right:40;padding-left:20;\">");
		printf("<input type=\"button\" value=\"계정삭제\" onclick=\"del_account('%s')\">",row[0]);
		printf("</td>");*/

		printf("</tr>");
	}




	printf("</tobdy></table>");
	printf("</head></html>");
	free(q);
	mysql_free_result(res);
	mysql_close(&mysql);
}
