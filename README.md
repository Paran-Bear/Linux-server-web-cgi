# 리눅스-서버-웹 -cgid
리눅스 우분투에서 아파치/mysql을 사용해서 웹페이지를 구현해야한다.
php로 하려 했으나 교수님이 C로 만들어 보라 하여 C를 사용
C로 어떻게??? 웹페이지는 HTML이 기본 아닌가? php,jsp 뭐가 됬건 html문서로 만들어 져야 하는대
-->내가 찾은 해답은 Apache2의 CGI였다. CGI에 대한 설명은 google에 많으니 패스한다.
CGI를 사용하기 맘먹은 순간부터 애를 먹었다. 리눅스는 설정파일 만지는게 너무 불편하다.
몇시간 동안 시행착오를 거쳐서 알게된 사실들
Apache2의 디렉토리 설정을 해야함.
설정파일은 httpd.conf는 없고 apache2.conf로 통합된듯 하다.
cgi를 디렉터리는 /usr/lib/cgi-bin이다. 
-->이 설정 파일은 
/etc/apache2/conf-available# vim serve-cgi-bin.conf 에 있다.

<IfModule mod_alias.c>
        <IfModule mod_cgi.c>
                Define ENABLE_USR_LIB_CGI_BIN
        </IfModule>

        <IfModule mod_cgid.c>
                Define ENABLE_USR_LIB_CGI_BIN
        </IfModule>

        <IfDefine ENABLE_USR_LIB_CGI_BIN>
                ScriptAlias /cgi-bin/ /usr/lib/cgi-bin/  <--이부분이다.
                <Directory "/usr/lib/cgi-bin">
                        AllowOverride None
                        Options +ExecCGI -MultiViews +SymLinksIfOwnerMatch
                        Require all granted
                </Directory>

                ScriptAlias /cgi-bin/ /var/www/cgi/
                <Directory "/var/www/cgi/">
                        AllowOverride None
                        Options +ExecCGI
                </Directory>
        </IfDefine>
</IfModule>

# vim: syntax=apache ts=4 sw=4 sts=4 sr noet
아파치서버에서 cgi-bin디렉토리에서 파일을 찾고자 하면 자동으로 /usr/lib/cgi-bin/에서 찾게된다.
cgi파일은 /usr/lib/cgi-bin/이곳에 저장한다. 마찬가지로 저곳의 디렉토리를 바꾸면 바꾼 디렉토리에서 찾게된다. 


C로 CGI를 만들려면 C가 출력하는 내용이 HTML문서 형식이어야만 한다. 

아래는 C예제이다.
#include <stdio.h>
int main()
{
                printf("Content-type: text/html%c%c", 10, 10);
                        printf("Hello, World var/www/cgi!");
                                return 0;
}
cgi스크립트의 첫 문장은 반드시 Content-type: text/html이다.


-----------
httpd.conf없다고 apache2재설치를 몇번을 하면서 구글링하고, 디렉토리 설정을 apache2.conf에서 하려니까 안되서 또 구글링에 몇시간 쓰고...
힘들다. 아직 github을 쓰는 방법조차도 제대로 모르겠다. 좀더 연구를 해야겠다.


------------------------------------20202/11/14------------------------------------
cgi프로그램에서 사용자 입력을 받는법을 공부하는데 대략 5시간을 쓴것같다. 아직도 완전히 이해하지는 못했지만 얼추 가닥은 잡은 것 같다.
HTML에서 사용자 입력값을 전달하는데는 2가지가 있다 GET, POST 각각 METHOD=' '로 사용한다.
GET방식은 C에서 QUERY STRING으로 인수를 전달 받는다. argv[]에서 받는것과는 다르다.
POST방식은 stdin방식으로 들어와서 파일과 동일하게 포인터로 처리해주면 된다. 
물론 둘다 들어오는 형식은 name=value이다.

전달받은 인수들을 효율적으로 사용하기 위해서 구조체를 정의하여 저장한다.
typedef struct {
    char *name;
    char *val;
}entry;

entry entries[1000];
int entry_count;
1000개의 인수를 저장 할 수 있다. 각 인수의 길이 제한은 없다. 위 구조체는 POST방식에서 사용된다. GET방식은 다루지 않겠다.
.cgi파일을 컴파일 할 때, 헤더를 포함하거나 명령어에서 같이 컴파일 하면된다.
gcc -o filename.cgi filename.c cgipost.c

[출처 : http://deadfire.net/cgic/cgic14.html] 
구글링하면서 더 복잡하고 좋아보이는 라이브러리도 보았지만, 내가 쓰기엔 이게 더 간단하고 편한것 같다. 내일은 DB를 연동해 로그인 및 회원가입을 구현하


