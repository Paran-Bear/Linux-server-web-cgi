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


	MYSQL_RES* cres;
	MYSQL_ROW crow;
	int cfields;
	
	MYSQL_RES* bres;
	MYSQL_ROW brow;
	int bfields;


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
	/*strcpy(q,"select * from basket  where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	fields=mysql_num_fields(res);
	int rows=mysql_num_rows(res);
*/

	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	printf("<script language=\"javascript\">");

	printf("function myorder(ord,id)\n{\n");
	printf("var mpg=document.my_order;\n");
	printf("window.open('','popupView','width=600,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='detail_order.cgi';\n");
	printf("mpg.arg0.value=ord;\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.submit();\n}\n");

	printf("function order_cancle(ord,id)\n{");
	printf("var mpg=document.my_order;\n");
	printf("window.open('','popupView','width=600,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='order_cancle.cgi';\n");
	printf("mpg.arg0.value=ord;\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.submit();\n}\n");

	printf("function cardmgt(ord,id)\n{");
	printf("var mpg=document.my_order;\n");
	printf("window.open('','popupView','width=600,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='card_mgt.cgi';\n");
	printf("mpg.arg0.value=ord;\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.submit();\n}\n");

	printf("function delvmgt(ord,id)\n{");
	printf("var mpg=document.my_order;\n");
	printf("window.open('','popupView','width=600,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='delv_mgt.cgi';\n");
	printf("mpg.arg0.value=ord;\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.submit();\n}\n");

	printf("function delbsk(ord,id)\n{");
	printf("var mpg=document.my_order;\n");
	printf("window.open('','popupView','width=600,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='drop_basket.cgi';\n");
	printf("mpg.arg0.value=ord;\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.submit();\n}\n");
	
	printf("function go_bsk(ord,id)\n{");
	printf("var mpg=document.my_order;\n");
	//printf("window.open('','popupView','width=600,height=500');\n");
//	printf("mpg.target='popupView';\n");
	printf("mpg.action='bsk_mgt.cgi';\n");
	printf("mpg.arg0.value=ord;\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.submit();\n}\n");

	printf("function go_mypage(ord,id)\n{");
	printf("var mpg=document.my_order;\n");
//	printf("window.open('','popupView','width=600,height=500');\n");
//	printf("mpg.target='popupView';\n");
	printf("mpg.action='mypage.cgi';\n");
	printf("mpg.arg0.value=ord;\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.submit();\n}\n");

	printf("function deletebsk(ord,id)\n{");
	printf("var mpg=document.my_order;\n");
	printf("window.open('','popupView','width=600,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='deletebasket.cgi';\n");
	printf("mpg.arg0.value=ord;\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.submit();\n}\n");


	printf("function bsk_order(ord,id)\n{");
	printf("var mpg=document.my_order;\n");
	printf("window.open('','popupView','width=600,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='basket_order.cgi';\n");
	printf("mpg.arg0.value=ord;\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.submit();\n}\n");
	

	printf("function go_home(id,pwd)\n{");
	printf("var mpg=document.hom;\n");
	printf("mpg.action='home.cgi';\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.pwd.value=pwd;\n");
	printf("mpg.submit();\n}\n");


	printf("</script>");
	printf("</head>");
	printf("<body>");
	strcpy(q,"select pwd from user where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	row=mysql_fetch_row(res);
	printf("<form name=\"hom\" id=\"hom\" method=\"post\" action=\"\">");
	printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("id"));
	printf("<input type=\"hidden\" name=\"pwd\" value=\"%s\">",row[0]);
	printf("</form>");
	printf("<div id=\"nav_menu\">");
	printf("<ul style=\"list-style-type:none border:1px solid black;margin:auto\">");
	printf("<li style=\"display:inline; text-align:center;\">%s님|</li>",findEntry("id"));
	printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"go_home('%s','%s');\" value=\"상품페이지\" style=\"background-color:#ffffff;border:0\">|</li>",findEntry("id"),row[0]);
	printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"window.location.href='/login.html';\" value=\"로그아웃\" style=\"background-color:#ffffff;border:0\">|</li>");
	printf("</ul>\n</div>");

	printf("<br><br>");

	printf("<table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:center;\"><tbody>");
	printf("<tr><td><input type=\"button\" value=\"나의 주문 목록\" onclick=\"go_mypage('%s','%s');\"></td>",findEntry("id"),findEntry("id"));
//	printf("<form name=\"mgtf\" id=\"mgtf\" method=\"post\" action=\"\">");
//	printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("arg0"));
//	printf("<form>");
	printf("<form name=\"my_order\" id=\"my_order\" method=\"post\" action=\"\">");
        printf("<input type=\"hidden\" name=\"arg0\"value=\"\" >");
	printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("id"));
	printf("<td><input type=\"button\" value=\"결제 카드 관리\" onclick=\"cardmgt('null','%s');\"></td>",findEntry("id"));
	printf("<td><input type=\"button\" value=\"배송지 관리\" onclick=\"delvmgt('null','%s');\"></td>",findEntry("id"));
	printf("<td><input type=\"button\" value=\"내 장바구니\" onclick=\"go_bsk('null','%s');\"></td></tr><tr><td><br></td></tr>",findEntry("id"));
	strcpy(q,"select * from basket  where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	fields=mysql_num_fields(res);
	int rows=mysql_num_rows(res);


	int idxb=1;
	while((row=mysql_fetch_row(res)))
	{
		printf("<tr bgcolor=\"#BDBDBD\"><td style=\"border-bottom:3px solid black;\">%d</td><td style=\"border-bottom:3px solid black;\"></td><td style=\"border-bottom:3px solid black;\">%s</td><td style=\"border-bottom:3px solid black;\"><input type=\"button\"value=\"바구니삭제\"onclick=\"deletebsk('%s','%s');\"></td><td style=\"border-bottom:3px solid black;\"></td><td style=\"border-bottom:3px solid black;\"></td><td style=\"border-bottom:3px solid black;\"></td></tr>",idxb++,row[1],row[1],findEntry("id"));
		strcpy(q,"select putbasket.book_num,book.title,sum(putbasket.quantity), book.price,sum(putbasket.quantity)*book.price from putbasket,book where putbasket.basket_num='");
		strcat(q,row[0]);
		strcat(q,"' and putbasket.book_num=book.num group by book_num");
		mysql_query(&mysql,q);
		cres=mysql_store_result(&mysql);
		int idx=1;
		int tq=0;
		int tp=0;
		while((crow=mysql_fetch_row(cres)))
		{
			printf("<tr bgcolor=\"#E6E6E6\"><td style=\"border-bottom:1px solid black;\">%d</td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\"><input type=\"button\" value=\"삭제\" onclick=\"delbsk('%s','%s');\"></td></tr>",idx++,crow[0],crow[1],crow[3],crow[2],crow[4],row[0],crow[0]);
			tq+=atoi(crow[2]);
			tp+=atoi(crow[4]);
		}
		printf("<tr bgcolor=\"#BDBDBD\"><td style=\"border-top:3px solid black;border-bottom:3px solid black;\">total</td><td style=\"border-top:3px solid black;border-bottom:3px solid black;\"></td><td style=\"border-top:3px solid black;border-bottom:3px solid black;\"></td><td style=\"border-bottom:3px solid black;border-top:3px solid black;\"></td><td style=\"border-bottom:3px solid black;border-top:3px solid black;\">%d개</td><td style=\"border-top:3px solid black;border-bottom:3px solid black;\">%d원</td><td style=\"border-bottom:3px solid black;border-top:3px solid black;\"></td></tr>",tq,tp);
		
		printf("<tr><td></td><td></td><td><input type=\"button\" value=\"장바구니 상품 구매\" onclick=\"bsk_order('%s','%s');\"></tr>",row[0],findEntry("id"));
		printf("<tr><td><br></td></tr>");

	}

		


	


		
	

	printf("</form>");
	printf("</tbody></tabel></body>");
	free(q);
	mysql_free_result(res);
mysql_free_result(row);
	printf("</html>");
}
