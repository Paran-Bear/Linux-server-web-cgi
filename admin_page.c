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
/*	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");

	printf("<script language=\"javascript\">");
	printf("function open_pop(arg1){");
	printf("var frmPop=document.frmPopup;");
	printf("var url='edit_page.cgi';");
	printf("window.open('','popupView','width=600,height=500');");
	printf("frmPop.action=url;");
	printf("frmPop.target='popupView';");
	for(int i=0;i<fields;i++){
	printf("frmPop.arg%d.value=arg%d;",i);
	}
	printf("frmPop.submit();}");
	printf("</script>");

	printf("</head><body>");*/
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
	if(mysql_query(&mysql,"select * from book"))
	{
		printf("%s",mysql_error(&mysql));
	}
	res=mysql_store_result(&mysql);
	fields=mysql_num_fields(res);
	int rows=mysql_num_rows(res);


	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	
	printf("<script language=\"javascript\">");
	printf("function open_pop(");
	for(int i=0;i<rows;i++)
	{
		if(i==rows-1)
			printf("arg%d){",i);
		else
			printf("arg%d,",i);
	}
		
	printf("var frmPop=document.frmPopup;");
	printf("var url='edit_page.cgi';");
	printf("window.open('','popupView','width=600,height=500');");
	printf("frmPop.action=url;");
	printf("frmPop.target='popupView';");
//	printf("frmPop.arg1.value=arg1;");
	for(int i=0;i<rows;i++)
	{
		printf("frmPop.arg%d.value=arg%d;",i,i);
	}

	printf("frmPop.submit();}");
	
	printf("function open_del_pop(");
	for(int i=0;i<rows;i++)
	{
		if(i==rows-1)
			printf("arg%d){",i);
		else
			printf("arg%d,",i);
	}	
	printf("var frmPop=document.frmPopup;");
	printf("var url='del_book.cgi';");
	printf("window.open('','popupView','width=600,height=500');");
	printf("frmPop.action=url;");
	printf("frmPop.target='popupView';");
//	printf("frmPop.arg1.value=arg1;");
	for(int i=0;i<rows;i++)
	        {
       			printf("frmPop.arg%d.value=arg%d;",i,i);
		}

	printf("frmPop.submit();}");
	

	printf("</script>");
	
	printf("</head><body>");

	printf("<div id=\"nav_menu\">");
	printf("<ul style=\"list-style-type:none border:1px solid black;margin:auto\">");
	printf("<li style=\"display:inline; text-align:center;\">관리자님|</li>");
	printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"window.location.href='admin_page.cgi'\" value=\"상품관리\" style=\"background-color:#ffffff;border:0\">|</li>");
	printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"window.location.href='admin_page_order.cgi'\" value=\"주문관리\" style=\"background-color:#ffffff;border:0\">|</li>");
	printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"window.location.href='admin_page_user.cgi'\" value=\"회원관리\" style=\"background-color:#ffffff;border:0\">|</li>");
	printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"window.location.href='/login.html'\" value=\"로그아웃\" style=\"background-color:#ffffff;border:0\"></li>");
	printf("</ul>\n</div>");
	printf("<table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:center;\">\n<tbody>");
	printf("<tr><td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\"><input type=\"button\" value=\"새로고침\" onclick=\"javascript:location.reload()\"</td><td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\"></td><td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\"></td><td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\"></td><td style=\"border-bottom:1px solid black;padding-left:40;\"></td><td style=\"border-bottom:1px solid black;padding-left:20;\"><input type=\"button\"value=\"상품추가\" onclick=\"window.name='책 추가';window.open('http://34.121.15.144/add_book.html','상품 등록','width=700,height=400,resizable=no,scrollbars=no,status=no');return false;\"></td></tr>");
	printf("<tr>");	
	printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\">상품번호</td>");
	printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\">상품이름</td>");
	printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\">재고</td>");
	printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\">가격</td>");
	printf("<td style=\"border-bottom:1px solid black;padding-left:60;\">상품</td>");
	printf("<td style=\"border-bottom:1px solid black;padding-right:60;\">관리</td></tr>");
	int cnt=0;	
	printf("<form id=\"frmPopup\" name=\"frmPopup\" method=\"post\" action=\"\">");

	while((row=mysql_fetch_row(res)))//쿼리의 결과중 한 줄을  row에 저장. 성공시 true 리턴.
	{	
		printf("<tr bgcolor=\"#C0C0C0\">");
//		printf("<form id=\"frm\" name=\"frm\" method=\"post\" action=\"\">");


		for(int i=0;i<fields;i++)//쿼리 결과의 필드 개수=fields
		{
			printf("<td style=\"border-bottom:1px solid black;\">%s</td>",row[i]);
			if(i==0)
				printf("<input type=\"hidden\"name=\"arg%d\"value=\"%s\">",cnt,row[i]);
		}

	
		printf("<td style=\"border-bottom:1px solid black;\"><input type=\"button\" value=\"수정\" onclick=\"open_pop('%s');\"></td>",row[0]);
		printf("<td style=\"border-bottom:1px solid black;\"><input type=\"button\" value=\"삭제\" onclick=\"open_del_pop(arg%d.value);\"></td>",cnt);
							  
		printf("</tr>");
		cnt++;
	}
	printf("</form>");
	printf("</tbody>\n</table>");
	mysql_free_result(res);//쿼리 결과 해제.
	mysql_close(&mysql);//쿼리 해제.
	printf("</body></html>");//html끝.
}

