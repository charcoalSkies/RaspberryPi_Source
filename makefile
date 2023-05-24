CORSS =
CC=$(CORSS)gcc

# main 실행 파일 이름
EXE=main

# 매크로 정의
DEFINES=

# 링크 플래그 설정
LDFLAGS = -lpthread -lwiringPi -ljson-c

# 컴파일 플래그 설정
CFLAGS=-g -I./include $(DEFINES)

C_SRC=$(wildcard *.c) # 현재 디렉토리에서 .c 파일을 모두 찾아서 C_SRC 변수에 저장
CPP_SRC = $(wildcard *.cpp) # 현재 디렉토리에서 .cpp 파일을 모두 찾아서 CPP_SRC 변수에 저장
CC_SRC = $(wildcard *.cc) # 현재 디렉토리에서 .cc 파일을 모두 찾아서 CC_SRC 변수에 저장
SRC = $(C_SRC) $(CPP_SRC) $(CC_SRC) # 모든 소스 파일을 SRC 변수에 저장
OBJ = $(C_SRC:.c=.o) $(CC_SRC:.cc=.o) $(CPP_SRC:.cpp=.o) # 소스 파일들을 컴파일하여 오브젝트 파일로 만들어 OBJ 변수에 저장

defualt : $(EXE) clean # default 타겟으로 EXE 파일과 clean 타겟을 순차적으로 빌드

all : $(EXE) # all 타겟으로 EXE 파일을 빌드

$(EXE) : $(OBJ) # EXE 파일을 빌드하기 위해 OBJ 파일들이 필요, gcc 컴파일러를 사용하여 EXE 파일을 빌드, 빌드된 EXE 파일을 strip하여 파일 크기를 줄임
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 
	strip $@ 
	
clean: # 현재 디렉토리에서 모든 오브젝트 파일을 삭제
	rm *.o 
