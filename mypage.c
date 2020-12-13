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
/*	strcpy(q,"select * from border where id='");
	strcat(q,findEntry("arg0"));
	strcat(q,"'");
	strcat(q," order by status asc;");
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

	printf("function get_book(ord,id)\n{");
	printf("var mpg=document.my_order;\n");
	printf("window.open('','popupView','width=600,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='get_book.cgi';\n");
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

	printf("function go_bsk(ord,id)\n{");
	printf("var mpg=document.my_order;\n");
	//printf("window.open('','popupView','width=600,height=500');\n");
//	printf("mpg.target='popupView';\n");
	printf("mpg.action='bsk_mgt.cgi';\n");
	printf("mpg.arg0.value=ord;\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.submit();\n}\n");

	printf("function go_home(id,pwd)\n{");
	printf("var mpg=document.hom;\n");
	printf("mpg.action='home.cgi';\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.pwd.value=pwd;\n");
	printf("mpg.submit();\n}\n");			
	
	printf("function del_acct(id,pwd)\n{");
	printf("var mpg=document.hom;\n");
	printf("window.open('','popupView','width=600,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='del_account.cgi';\n");
	printf("mpg.pwd.value=pwd;\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.submit();\n}\n");

	printf("function change_pwd(id,pwd)\n{");
	printf("var mpg=document.hom;\n");
	printf("window.open('','popupView','width=600,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='change_pwd.cgi';\n");
	printf("mpg.pwd.value=pwd;\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.submit();\n}\n");



	printf("</script>");
	printf("</head>");
	printf("<body>");
	strcpy(q,"select pwd from user where id='");
	strcat(q,findEntry("arg0"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	row=mysql_fetch_row(res);
	printf("<form name=\"hom\" id=\"hom\" method=\"post\" action=\"\">");
	printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("arg0"));
	printf("<input type=\"hidden\" name=\"pwd\" value=\"%s\">",row[0]);
	printf("</form>");
	printf("<div id=\"nav_menu\">");                        
	printf("<ul style=\"list-style-type:none border:1px solid black;margin:auto\">");
	printf("<li style=\"display:inline; text-align:center;\">%s님|</li>",findEntry("arg0")); 
 	printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"go_home('%s','%s');\" value=\"상품페이지\" style=\"background-color:#ffffff;border:0\">|</li>",findEntry("arg0"),row[0]);
	printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"change_pwd('%s','%s');\" value=\"비밀번호 변경\" style=\"background-color:#ffffff;border:0\">|</li>",findEntry("arg0"),row[0]);
	printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"window.location.href='/login.html';\" value=\"로그아웃\" style=\"background-color:#ffffff;border:0\">|</li>");       
       	printf("</ul>\n</div>");
	printf("<table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:center;\"><tbody>");
	printf("<tr><td>나의 주문 목록</td>");
	//	printf("<form name=\"mgtf\" id=\"mgtf\" method=\"post\" action=\"\">");
//	printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("arg0"));
//	printf("<form>");
	printf("<form name=\"my_order\" id=\"my_order\" method=\"post\" action=\"\">");
        printf("<input type=\"hidden\" name=\"arg0\"value=\"\" >");
	printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("arg0"));
	printf("<td><input type=\"button\" value=\"결제 카드 관리\" onclick=\"cardmgt('null','%s');\"></td>",findEntry("arg0"));
	printf("<td><input type=\"button\" value=\"배송지 관리\" onclick=\"delvmgt('null','%s');\"></td>",findEntry("arg0"));
	printf("<td><input type=\"button\" value=\"내 장바구니\" onclick=\"go_bsk('null','%s');\"></td>",findEntry("arg0"));
	printf("<td><input type=\"button\" value=\"회원 탈퇴\" onclick=\"del_acct('%s','%s');\"></td></tr>",findEntry("arg0"),row[0]);
	printf("<tr><td><br></td></tr>");

	strcpy(q,"select * from border where id='");
	        strcat(q,findEntry("arg0"));
		        strcat(q,"'");
			        strcat(q," order by status asc;");

	int idxb=1;
mysql_query(&mysql,q);
		

	
	res=mysql_store_result(&mysql);
	fields=mysql_num_fields(res);
	int rows=mysql_num_rows(res);
	char *color=malloc(sizeof(char)*99);
	while((row=mysql_fetch_row(res)))
	{
		
		if(strcmp(row[3],"신청")==0){
			strcpy(color,"bgcolor=\"#A9F5D0\"");}
		if(strcmp(row[3],"발송")==0){
			strcpy(color,"bgcolor=\"#F3E2A9\"");}
		if(strcmp(row[3],"판매완료")==0){
			strcpy(color,"bgcolor=\"#A9D0F5\"");}
		if(strcmp(row[3],"취소")==0){
			strcpy(color,"bgcolor=\"#FA5858\"");
		}

		printf("<tr %s>",color);
		printf("<td style=\"border-bottom:3px solid black;\">%d</td><td style=\"border-bottom:3px solid black\";>주문번호:%s</td><td style=\"border-bottom:3px solid black\";>상태:%s</td><td style=\"border-bottom:3px solid black;\"><input type=\"button\" value=\"주문상세\" onclick=\"myorder('%s','null');\"></td>",idxb++,row[0],row[3],row[0]);
		if(strcmp(row[3],"발송")==0)
		{
			printf("<td style=\"border-bottom:3px solid black;\"><input type=\"button\" value=\"수취확인\" onclick=\"get_book('%s','null');\" ></td>",row[0]);
		}
		else if(strcmp(row[3],"신청")==0)
		{
			printf("<td style=\"border-bottom:3px solid black;\"><input type=\"button\" value=\"주문취소\" onclick=\"order_cancle('%s','null');\" ></td>",row[0]);
		}
		else
			printf("<td style=\"border-bottom:3px solid black;\"></td>");
		printf("</tr>");
	
		strcpy(q,"select book_num,book.title,quantity,(quantity*book.price) from book,corder where order_num='");
		strcat(q,row[0]);
		strcat(q,"' and book_num=book.num");
		mysql_query(&mysql,q);
		cres=mysql_store_result(&mysql);
		int idx=0;
		while((crow=mysql_fetch_row(cres)))
		{
//			strcpy(q,"select book_num,book.title,quantity,(quantity*book.price) from book,corder where order_num='");
//			strcat(q,crow[0]);
//			strcat(q,"' and book_num=book.num");
//			mysql_query(&mysql,q);
//			bres=mysql_store_result(&mysql);
			printf("<tr bgcolor=\"#E6E6E6\">");
//			while((brow=mysql_fetch_row(bres)))
//			{
//				printf("<tr>");
			printf("<td style=\"border-bottom:1px solid black;\">%d</td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\">%s</td>",++idx,crow[0],crow[1],crow[2],crow[3]);
			printf("</tr>");
		}
			strcpy(q,"select sum(corder.quantity),sum(book.price*corder.quantity) from corder,book where order_num='");
			strcat(q,row[0]);
			strcat(q,"' and corder.book_num=book.num;");
			mysql_query(&mysql,q);
			bres=mysql_store_result(&mysql);
			brow=mysql_fetch_row(bres);
			printf("<tr bgcolor=\"#BDBDBD\"><td style=\"border-bottom:1px solid black;\">total</td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\">%s</td></tr>",brow[0],brow[1]);
//		mysql_free_result(res);mysql_free_result(cres);mysql_free_result(bres);
		printf("<tr><td><br></td></tr>");
		
	}

	printf("</form>");
	printf("</tbody></tabel></body>");
	
	
	free(q);
//	mysql_free_result(res);
//	mysql_free_result(row);
//	mysql_free_result(cres);
//	mysql_free_result(crow);
//	mysql_free_result(bres);
//	mysql_free_result(brow);
	printf("</html>");
}
