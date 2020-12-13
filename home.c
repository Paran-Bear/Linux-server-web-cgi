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
	mysql_query(&mysql,"select * from book");
	res=mysql_store_result(&mysql);
	fields=mysql_num_fields(res);
	int rows=mysql_num_rows(res);

	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
//자바스크립트
	
	printf("<script language=\"javascript\">");
	
	printf("function mypage(id){");
	printf("var mpg=document.frmPopup;");
	printf("mpg.action='mypage.cgi';");
//	printf("mpg.action='cpa.cgi';");
	printf("mpg.arg0.value=id;");
	printf("mpg.submit();}");


	printf("function order(id,bkn,quan){");//팝업창 오픈 상품 추가.
	
	printf("var frmPop=document.frmPopup;");
	printf("var url='single_order.cgi';");
	printf("window.open('','popupView','width=600,height=500');");
	printf("frmPop.action=url;");
	printf("frmPop.target='popupView';");
	printf("frmPop.arg0.value=id;");
	printf("frmPop.arg1.value=bkn;");
	printf("frmPop.arg2.value=quan;");

	printf("frmPop.submit();window.location.reload();}");//서브밋 url에 전송. 
	//.
	printf("function open_del_pop(num,quan,id){");
	printf("var frmPop=document.frmPopup;");
	printf("var url='put_basket_info.cgi';");
	printf("window.open('','popupView','width=600,height=500');");
	printf("frmPop.action=url;");
	printf("frmPop.target='popupView';");
	printf("frmPop.arg0.value=num;");
	printf("frmPop.quantity0.value=quan;");
	printf("frmPop.arg1.value=id;");
	
	printf("frmPop.submit();window.location.reload();}");
	printf("function create_bask(id){");
	printf("var create = document.create_basket;");
	printf("var url='create_basket.cgi';");
	printf("window.open('','popupView','width=300,height=300');");
	printf("create.action=url;");
	printf("create.target='popupView';");
	printf("create.id.value=id;");
	printf("create.submit();window.location.reload();}");
	printf("</script>");//스크립트 끝*/
	printf("</head><body>");
	//로그인 체크
	int check=0;
	if(mysql_query(&mysql,"select * from user"))
	{
		printf("<p db연결 실패 %s/>",mysql_error(&mysql));
	}
	res=mysql_store_result(&mysql);
	fields=mysql_num_fields(res);
	rows=mysql_num_rows(res);
	while((row=mysql_fetch_row(res)))
	{
		if(strcmp(findEntry("id"),row[0])==0)//아이디 체크
		{
			check++;
			if(strcmp(findEntry("pwd"),row[1])==0){//비밀번호 체크
				check++;	
				break;
			}
		}
		/*else if(strcmp(findEntry("id"),"admin")==0)
		{
			if(strcmp(findEntry("pwd"),row[1])==0){//비밀번호 체크
				check++;
				break;
				check=9999;
			}
		}*/
	}	
	if(check==2&&strcmp(findEntry("id"),"admin")==0)
	{
			check=9999;
	}

	if(check==9999)
	{
		printf("<META http-equiv=\"refresh\" content=\"0; url='admin_page.cgi'\">");
	}
	else if(check==2)
	{	
		//유저 정보		
		//상단메뉴-------------
		printf("<div id=\"nav_menu\">");
		printf("<ul style=\"list-style-type:none border:1px solid black;margin:auto\">");
		printf("<li style=\"display:inline; text-align:center;\">%s님|</li>",findEntry("id"));
		printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("id"));
		
		printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"mypage('%s');\" value=\"마이페이지\" style=\"background-color:#ffffff;border:0\">|</li>",findEntry("id"));
		printf("<li style=\"display:inline; text-align:center;\"><input type=\"button\" onclick=\"window.location.href='/login.html';\" value=\"로그아웃\" style=\"background-color:#ffffff;border:0\">|</li>");
		printf("</ul>\n</div>");
		//------------------------
		mysql_free_result(res);//쿼리 결과 해제.
		if(mysql_query(&mysql,"select * from book"))
			printf("<h1>목록 불러오기실패</h1>");

		else{
		//상품메뉴--------------------------------------
		res=mysql_store_result(&mysql);
		fields=mysql_num_fields(res);
		rows=mysql_num_rows(res);
		printf("<table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:center;\">\n<tbody>");
		printf("<tr><td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\"><input type=\"button\" value=\"새로고침\" onclick=\"javascript:location.reload()\"</td>");
		printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\"></td>");
		printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\"></td>");
		printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\"></td>");

		printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\"></td>");
		printf("<td style=\"border-bottom:1px solid black;padding-left:40;\"> </td>");
		printf("<td style=\"border-bottom:1px solid black;padding-left:20;\"></td></tr>");
		printf("<tr>");
		printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\">상품번호</td>");
		printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\">상품이름</td>");
		printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\">재고</td>");
		printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\">가격</td>");
		printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:40;\">수량</td>");

		printf("<td style=\"border-bottom:1px solid black;padding-left:60;\"></td>");
		printf("<td style=\"border-bottom:1px solid black;padding-right:60;\"></td></tr>");
		int cnt=0;
		printf("<form id=\"frmPopup\" name=\"frmPopup\" method=\"post\" action=\"\">");
		
		while((row=mysql_fetch_row(res)))
		{
			if(atoi(row[2])>0){
			printf("<tr bgcolor=\"#C0C0C0\">");			
			for(int i=0;i<fields;i++)
			{
				printf("<td style=\"border-bottom:1px solid black;\">%s</td>",row[i]);
				if(i==0)
					printf("<input type=\"hidden\"name=\"arg%d\"value=\"%s\">",cnt,row[i]);
			}
			printf("<td style=\"border-bottom:1px solid black;\">");
			printf("<input type=\"number\" value=\"1\" size=\"3\" min=\"1\" max=\"%s\" name=\"quantity%d\"></td>",row[2],cnt);
			printf("<td style=\"border-bottom:1px solid black;\"><input type=\"button\" value=\"구매\" onclick=\"order('%s','%s',quantity%d.value);\"></td>",findEntry("id"),row[0],cnt);
			printf("<td style=\"border-bottom:1px solid black;\"><input type=\"button\" value=\"담기\" onclick=\"open_del_pop('%s',quantity%d.value,'%s');\"></td>",row[0],cnt,findEntry("id"));
			printf("</tr>");
			cnt++;}
		}
		printf("</form>");
		printf("</tbody>\n</table>");
		//---------------------------
		
		}
				
	}
	else if(check==1)
	{
		printf("<h1>비밀번호를 다시 확인하여주세요.</h1>");
	}
	else if(check==0)
	{
		printf("<h1>존재하지 않는 ID입니다.</h1>");
	}
	else
	{
		printf("<h1>알수없는 에러</h1>");
	}

	mysql_free_result(res);//쿼리 결과 해제.
//	free(q);
	mysql_close(&mysql);//쿼리 해제.

	printf("</head></body></html>");//html끝.
}

