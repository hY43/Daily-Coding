#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/******************************
+ Struct Detail
- Data: DAT 파일의 데이터를 입력 받아 저장할 구조체
*******************************/

typedef struct Data
{
/*
+ Valuable Detail
- procTime: 처리 시간
- fruitName: 과일 명
- procSort: 처리 구분(1,입고요청 2,입고확인 3,출고처리)
- fruitCount: 과일 수량
- docNum: 전표 번호
*/
	char procTime[10];
	char fruitName[21];
	char procSort;
	char fruitCount[7];
	char docNum[5];

	int proSort_Int;
	int fruitCount_int;
	int docNum_int;
	int proTime_int;
	int procTime_HH;
	int procTime_MM;
	int procTime_SS;
	int procTime_ZZZ;
} DAT;

typedef struct datResult
{
/*
+ Valuable Detail
- inProduct: 입고 수량
- outProduct: 출고 수량
- TotalProduct: 보관 수량
- timeOfIn: 입고 요청 시간
- timeOfCon: 입고 확인 시간
- inFlag: 데이터가 입고 요청이 왔다면 1, 안왔다면 0 -> 결과 값 출력시 사용되지 않은 전표 번호 구분을 위한 변수.

- rProcTime_HH: 시간 저장
- rProcTime_MM: 분 저장
- rProcTime_SS: 초 저장
- rProcTime_ZZZ: 초 저장
*/
	int* inFlag;
	int* inProduct;
	int* outProduct;
	int* TotalProduct;
	int* timeOfIn;
	int* timeOfCon;
	int* rProcTime;

	int* rProcTime_HH;
	int* rProcTime_MM;
	int* rProcTime_SS;
	int* rProcTime_ZZZ;

}DRESULT;

/******************************
+ Function Detail
- sortDat: 데이터를 각 구조체 변수로 저장하기 위한 함수
- createCSVR: 결과 값을 Excel CSV 형식의 파일로 생성하기 위한 함수
- maxDocNum: 최대 전표 번호 값을 구하기 위한 함수
- createCSV: dat 파일의 csv 파일로 변환, 실제 출력 내용을 QC하기 위한 함수
- allocData: 기존의 DRESULT 내의 동적할당된 변수에 대해 최대 전표 번호와 인덱스를 매칭 시킬 배열을 생성시키는 함수
- inDresult: 입력 받은 데이터를 각 조건(입고 요청/입고 확인/출고)에 맞게 연산하기 위한 함수
- showResult: 결과를 콘솔 창에 출력하기 위한 함수
*******************************/
DAT sortDat(char* dat,DAT datStore);
void createCSVR(DRESULT datResult,int i,int hour,int minute,int second,int msecond);
int maxDocNum(FILE* datFile);
DRESULT allocData(int maxDoc,DRESULT datResult);
DRESULT inDresult(DAT datStore, DRESULT datResult);
void showResult(DRESULT datResult,int maxDoc);

int main()
{
/*
+ Valuable Detail
- datFile: 파일을 열기위한 FILE 구조체 변수
- datStore: 파일의 내용을 각 항목별로 저장하기 위한 DAT 구조체 변수
- maxDoc: 최대 전표 번호 저장
- dat: 최초의 Raw Data를 받기 위한 배열
- i: 반복문 용 변수
*/
	FILE *datFile = fopen("Hoa_20151216.dat","r");
	DAT datStore;
	DRESULT datResult;
	char dat[45];
	int i;

	//memset(&datResult,0,sizeof(datResult));
	int maxDoc = maxDocNum(datFile); // 최대 전표 번호를 구한다.
	memset(&datResult,0,sizeof(datResult));
	datResult = allocData(maxDoc,datResult); // 최대 전표 수만큼의 값을 갖는 배열들을 생성, 전표 번호와 인덱스를 일치 시켜 값을 저장하기 위한 용도

	for(i=0;!feof(datFile);i++)
	{
		memset(&datStore,0,sizeof(datStore)); // 구조체 변수 datStore를 사용하기 위한 초기화
		fgets(dat,sizeof(dat)+1,datFile); // dat 파일의 내용을 한줄씩 받아오기 위한 fgets
		dat[strlen(dat)-1] = '\0'; // fgets 함수를 통해 받아온 데이터의 맨 끝의 개행문자를 널문자로 변환
		datStore = sortDat(dat,datStore); // 받아온 데이터를 실제 규격에 맞게 정리
		datResult = inDresult(datStore, datResult); // 규격에 맞춘 데이터를 이용하여 결과 값 연산
	}
	
	showResult(datResult,maxDoc);
	fclose(datFile);
	return 0;
}

DAT sortDat(char* dat,DAT datStore)
{
/*
배열의 내용을 각 구조체 변수에 맞게 입력한 후(memmove), 그 마지막에 NULL 값을 대입해준다.
*/
	int i=0;
	do{
		memcpy(&datStore.procTime, dat, sizeof(datStore.procTime));
		i+=2;

		if(i>=8)
			datStore.procTime[9] = '\0';
		else
			datStore.procTime[i] = '\0';

		if(i<=2)
			datStore.procTime_HH = atoi(&datStore.procTime[i-2]);
		else if(i>2 && i<=4)
			datStore.procTime_MM =  atoi(&datStore.procTime[i-2]);
		else if(i>4 && i<=6)
			datStore.procTime_SS =  atoi(&datStore.procTime[i-2]);
		else
			datStore.procTime_ZZZ =  atoi(&datStore.procTime[i-2]);
	}while(i<8);
	// 시간 값 계산을 위한 반복문

	datStore.proTime_int = (datStore.procTime_HH * 3600 + datStore.procTime_MM * 360 + datStore.procTime_SS)*1000 + datStore.procTime_ZZZ;
	// 입고 요청 시간과 입고 확인 시간간의 차이를 구하기 위해 밀리세컨드 단위로 연산

	memmove(&datStore.fruitName, &dat[9], sizeof(datStore.fruitName));
	datStore.fruitName[20] = '\0';
	memmove(&datStore.procSort, &dat[29], sizeof(datStore.procSort));
	datStore.proSort_Int = atoi(&datStore.procSort);
	memmove(&datStore.fruitCount, &dat[30], sizeof(datStore.fruitCount));
	datStore.fruitCount[6] = '\0';
	datStore.fruitCount_int = atoi(datStore.fruitCount);
	memmove(&datStore.docNum, &dat[36], sizeof(datStore.docNum));
	datStore.docNum[4] = '\0';
	datStore.docNum_int = atoi(datStore.docNum);

	return datStore;
}

int maxDocNum(FILE* datFile)
{
/*
+ Valuable Detail
- i: for 문을 위한 변수
- buf: 문장의 한줄을 담기 위한 배열
*/
	int i,num = 0;
	char buf[41];
	for(i=0;!feof(datFile);i++) // 해당 파일의 끝까지 동작하는 반복문
	{
		fgets(buf,sizeof(buf), datFile);
		if(num < atoi(&buf[36])) // 해당 전표 번호와 저장된 전표 번호를 비교하여 최대치를 저장
			num = atoi(&buf[36]);
	}
	fseek(datFile, 0, SEEK_SET);
	return num;// 최대 전표 번호 반환
}

DRESULT allocData(int maxDoc,DRESULT datResult)
{
	// 최대 전표 번호를 이용하여 데이터가 입력될 만큼만 동적할당.
	datResult.inFlag = (int*)malloc(sizeof(int)*maxDoc);
	memset(datResult.inFlag,0,sizeof(datResult.inFlag));
	datResult.TotalProduct = (int*)malloc(sizeof(int)*maxDoc);
	datResult.timeOfCon = (int*)malloc(sizeof(int)*maxDoc);
	datResult.timeOfIn = (int*)malloc(sizeof(int)*maxDoc);
	datResult.rProcTime = (int*)malloc(sizeof(int)*maxDoc);
	datResult.inProduct = (int*)malloc(sizeof(int)*maxDoc);;
	datResult.outProduct = (int*)malloc(sizeof(int)*maxDoc);;
		
	return datResult;
}

DRESULT inDresult(DAT datStore, DRESULT datResult)
{
	datResult.TotalProduct[datStore.docNum_int] = 0;
	datResult.inProduct[datStore.docNum_int] = 0;
	datResult.outProduct[datStore.docNum_int] = 0;
	// 과일의 초기 보유량을 0으로 초기화
	memset(datResult.inFlag,0,sizeof(datResult.inFlag));
	// 해당 전표 번호에 대한 데이터 입고 사항을 확인하기 위한 Flag 값 0으로 초기화
	datResult.inFlag[datStore.docNum_int] = 1;
	// 한번 사용된 전표는 Flag를 1로 전환하여 결과 출력 시 대상에 들어감.

	/*
	결과 연산을 위한 switch
	1. 입고 요청 2. 입고 확인 3. 출고 처리으로 분류하여 각 분류에 맞는 연산
	1. 입고 요청
	- 입고 요청 시간 저장
	- 입고 수량 저장
	2. 입고 확인
	- 확인 시간 저장 및 확인 시간과 요청 시간간의 차이 연산.
	3. 출고 처리
	- 현재 보유 과일 수에서 출고 량만큼 제외
	*/
	switch (datStore.proSort_Int)
	{
	case 1:
		datResult.timeOfIn[datStore.docNum_int] = datStore.proTime_int;
		datResult.inProduct[datStore.docNum_int] += datStore.fruitCount_int;
		break;
	case 2:
		datResult.timeOfCon[datStore.docNum_int] = datStore.proTime_int;
		datResult.rProcTime[datStore.docNum_int] = datResult.timeOfCon[datStore.docNum_int] - datResult.timeOfIn[datStore.docNum_int];
		break;
	case 3:
		datResult.TotalProduct[datStore.docNum_int] -= datStore.fruitCount_int;
		break;
	}

	return datResult;
}

void showResult(DRESULT datResult,int maxDoc)
{
	int i;
	int hour,minute,second,msecond;
	printf("전표번호 처리시간     입고수량    출고수량    보관수량\n");
	for(i=1;i<=maxDoc;i++)
	{
		if(datResult.inFlag[i] != 1)
			continue;

		hour = datResult.rProcTime[i]/36000000;
		minute = (datResult.rProcTime[i] - hour)/360000;
		second = (datResult.rProcTime[i] - hour - minute)/1000;
		msecond = (datResult.rProcTime[i] - hour - minute)%1000;

		printf("%8d %02d:%02d:%02d:%03d %8d %8d %8d\n",i,hour,minute,second,msecond, datResult.inProduct[i],datResult.outProduct[i],datResult.inProduct[i] - datResult.outProduct[i]);
		// 결과에 대한 콘솔 화면 출력
		createCSVR(datResult,i, hour,minute,second,msecond);
		// 결과에 대한 Excel CSV 파일 생성
	}
}

void createCSVR(DRESULT datResult,int i,int hour,int minute,int second,int msecond)
{
	FILE* datFile = fopen("result.csv","at");
	fprintf(datFile,"%8d,%02d:%02d:%02d:%03d,%8d,%8d,%8d\n",i,hour,minute,second,msecond, datResult.inProduct[i],datResult.outProduct[i],datResult.inProduct[i] - datResult.outProduct[i]);
	fclose(datFile);
}
