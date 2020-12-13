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
	if(mysql_query(&mysql,"select num,total,status,id from border order by status"))
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
	printf("function order_mgt(num,code){");
	printf("var frmPop=document.frmPopup;");
	printf("var url='ordermgt.cgi';");
	printf("window.open('','popupView','width=600,height=500');");
	printf("frmPop.action=url;");
	printf("frmPop.target='popupView';");
	printf("frmPop.order_num.value=num;");
	printf("frmPop.code.value=code;");
	printf("frmPop.submit();}");

	printf("function cancle_order(num,code){");
	printf("var frmPop=document.frmPopup;");
	printf("var url='cancle_order.cgi';");
	printf("window.open('','popupView','width=600,height=500');");
	printf("frmPop.action=url;");
	printf("frmPop.target='popupView';");
	printf("frmPop.order_num.value=num;");
	printf("frmPop.code.value=code;");
	printf("frmPop.submit();}");
	
	printf("function del_border(num,code){");
	printf("var frmPop=document.frmPopup;");
	printf("var url='del_border.cgi';");
	printf("window.open('','popupView','width=600,height=500');");
	printf("frmPop.action=url;");
	printf("frmPop.target='popupView';");
	printf("frmPop.order_num.value=num;");
	printf("frmPop.code.value=code;");
	printf("frmPop.submit();}");


	printf("function order_info(num,code){");	  
  	printf("var frmPop=document.frmPopup;");
	printf("var url='order_.cgi';");
	printf("window.open('','popupView','width=600,height=500');");
	printf("frmPop.action=url;");
	printf("frmPop.target='popupView';");
	printf("frmPop.order_num.value=num;");
	printf("frmPop.code.value=code;");
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
	printf("<tr>");	
	printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\">주문 번호</td>");
	printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\">주문 총액</td>");
	printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\">주문 상태</td>");
	printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\">주문 아이디</td>");
//	printf("<td style=\"border-bottom:1px solid black;padding-left:60;\">상품</td>");
	printf("<td style=\"border-bottom:1px solid black;padding-right:60;\"></td></tr>");
	int cnt=0;	
	printf("<form id=\"frmPopup\" name=\"frmPopup\" method=\"post\" action=\"\">");
	printf("<input type=\"hidden\" name=\"order_num\" value=\"\">");
	printf("<input type=\"hidden\" name=\"code\" value=\"\">");
	char *color=malloc(sizeof(char)*99);
	strcpy(color,"bgcolor=\"#A9F5D0\"");
//	row=mysql_fetch_row(res);
//	printf("%s %s %s %s",row[0],row[1],row[2],row[3]);
	while((row=mysql_fetch_row(res)))//쿼리의 결과중 한 줄을  row에 저장. 성공시 true 리턴.
	{	

		if(strcmp(row[2],"신청")==0){
			strcpy(color,"bgcolor=\"#A9F5D0\"");}
		if(strcmp(row[2],"발송")==0){
			strcpy(color,"bgcolor=\"#F3E2A9\"");}
		if(strcmp(row[2],"판매완료")==0){
			strcpy(color,"bgcolor=\"#A9D0F5\"");}
		if(strcmp(row[2],"취소")==0){
			strcpy(color,"bgcolor=\"#FA5858\"");
		}

		printf("<tr %s>",color);
		for(int i=0;i<4;i++)
		{
			printf("<td style=\"border-bottom:1px solid black;\">");
			printf("%s",row[i]);
			printf("</td>");
		}	
//		printf("rows:%d--cnt:%d",rows,cnt);
		//전체
		printf("<td style=\"border-bottom:1px solid black;\">");
		printf("<input type=\"button\" value=\"상세정보\" onclick=\"order_mgt('%s','1');\">",row[0]);
		printf("</td>");
		if(strcmp(row[2],"신청")==0){
		//신청 상태 일때
		printf("<td style=\"border-bottom:1px solid black;\">");
		printf("<input type=\"button\" value=\"발송\" onclick=\"order_mgt('%s','2');\">",row[0]);
		printf("</td>");

		printf("<td style=\"border-bottom:1px solid black;\">");
		printf("<input type=\"button\" value=\"취소\" onclick=\"order_mgt('%s','3');\">",row[0]);
		printf("</td>");
		}
		else
		{
			printf("<td style=\"border-bottom:1px solid black;\">");
			printf("<input type=\"button\"value=\"삭제\"onclick=\"del_border('%s','null');\"></td>",row[0]);
			printf("<td style=\"border-bottom:1px solid black;\"></td>");
		}
		


	
							  
		printf("</tr>");
		cnt++;
	}
	printf("</form>");
	printf("</tbody>\n</table>");
	mysql_free_result(res);//쿼리 결과 해제.
	mysql_close(&mysql);//쿼리 해제.
	printf("</body></html>");//html끝.
}

