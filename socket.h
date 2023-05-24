#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdio.h>      // 표준입출력 라이브러리
#include <stdlib.h>     // 일반적인 유틸리티 함수 라이브러리
#include <string.h>     // 문자열 처리 함수 라이브러리
#include <unistd.h>     // 유닉스 표준 라이브러리
#include <sys/types.h>  // 시스템 콜과 관련된 자료형 라이브러리
#include <sys/socket.h> // 소켓 프로그래밍 라이브러리
#include <netinet/in.h> // 인터넷 프로토콜 라이브러리
#include <arpa/inet.h>  // 인터넷 주소 변환 라이브러리
#include <pthread.h>    // POSIX 스레드 라이브러리
#include <stdbool.h>
#include "json.h"

#define SERV_PORT 8080 // 서버 포트 번호를 8080으로 정의
#define BACKLOG 10    // 연결 대기 큐의 최대 길이를 10으로 정의
#define BUFFSIZE 512  // 버퍼 크기를 512로 정의
#define CLNT_MAX 2    // 최대 클라이언트 수를 2로 정의

struct Command
{                     // Command 구조체 정의
    int connection;   // 연결된 소켓 파일 디스크립터
    char *command;    // 클라이언트로부터 받은 명령어
    json_object *rootObj;
} typedef getCommand; // 구조체 별칭 getCommand로 정의

void connection(getCommand *getcmd);          // 연결 함수 선언
void socket_connect(getCommand *getcmd);      // 소켓 연결 함수 선언
void client_command(getCommand *getcmd);      // 클라이언트 명령어 처리 함수 선언
void response(char *msg, getCommand *getcmd); // 응답 함수 선언
uint8_t safety(getCommand *getcmd);           // 안전성 검사 함수 선언
int strcmps(char *msg1, char *msg2);          // 문자열 비교 함수
bool checkCommand(json_object *data, const char *command); // JSON 객체와 명령어를 받아 해당 명령어가 있는지 확인하는 함수
#endif

