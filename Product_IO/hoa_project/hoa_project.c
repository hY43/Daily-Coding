#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/******************************
+ Struct Detail
- Data: DAT ������ �����͸� �Է� �޾� ������ ����ü
*******************************/

typedef struct Data
{
/*
+ Valuable Detail
- procTime: ó�� �ð�
- fruitName: ���� ��
- procSort: ó�� ����(1,�԰��û 2,�԰�Ȯ�� 3,���ó��)
- fruitCount: ���� ����
- docNum: ��ǥ ��ȣ
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
- inProduct: �԰� ����
- outProduct: ��� ����
- TotalProduct: ���� ����
- timeOfIn: �԰� ��û �ð�
- timeOfCon: �԰� Ȯ�� �ð�
- inFlag: �����Ͱ� �԰� ��û�� �Դٸ� 1, �ȿԴٸ� 0 -> ��� �� ��½� ������ ���� ��ǥ ��ȣ ������ ���� ����.

- rProcTime_HH: �ð� ����
- rProcTime_MM: �� ����
- rProcTime_SS: �� ����
- rProcTime_ZZZ: �� ����
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
- sortDat: �����͸� �� ����ü ������ �����ϱ� ���� �Լ�
- createCSVR: ��� ���� Excel CSV ������ ���Ϸ� �����ϱ� ���� �Լ�
- maxDocNum: �ִ� ��ǥ ��ȣ ���� ���ϱ� ���� �Լ�
- createCSV: dat ������ csv ���Ϸ� ��ȯ, ���� ��� ������ QC�ϱ� ���� �Լ�
- allocData: ������ DRESULT ���� �����Ҵ�� ������ ���� �ִ� ��ǥ ��ȣ�� �ε����� ��Ī ��ų �迭�� ������Ű�� �Լ�
- inDresult: �Է� ���� �����͸� �� ����(�԰� ��û/�԰� Ȯ��/���)�� �°� �����ϱ� ���� �Լ�
- showResult: ����� �ܼ� â�� ����ϱ� ���� �Լ�
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
- datFile: ������ �������� FILE ����ü ����
- datStore: ������ ������ �� �׸񺰷� �����ϱ� ���� DAT ����ü ����
- maxDoc: �ִ� ��ǥ ��ȣ ����
- dat: ������ Raw Data�� �ޱ� ���� �迭
- i: �ݺ��� �� ����
*/
	FILE *datFile = fopen("Hoa_20151216.dat","r");
	DAT datStore;
	DRESULT datResult;
	char dat[45];
	int i;

	//memset(&datResult,0,sizeof(datResult));
	int maxDoc = maxDocNum(datFile); // �ִ� ��ǥ ��ȣ�� ���Ѵ�.
	memset(&datResult,0,sizeof(datResult));
	datResult = allocData(maxDoc,datResult); // �ִ� ��ǥ ����ŭ�� ���� ���� �迭���� ����, ��ǥ ��ȣ�� �ε����� ��ġ ���� ���� �����ϱ� ���� �뵵

	for(i=0;!feof(datFile);i++)
	{
		memset(&datStore,0,sizeof(datStore)); // ����ü ���� datStore�� ����ϱ� ���� �ʱ�ȭ
		fgets(dat,sizeof(dat)+1,datFile); // dat ������ ������ ���پ� �޾ƿ��� ���� fgets
		dat[strlen(dat)-1] = '\0'; // fgets �Լ��� ���� �޾ƿ� �������� �� ���� ���๮�ڸ� �ι��ڷ� ��ȯ
		datStore = sortDat(dat,datStore); // �޾ƿ� �����͸� ���� �԰ݿ� �°� ����
		datResult = inDresult(datStore, datResult); // �԰ݿ� ���� �����͸� �̿��Ͽ� ��� �� ����
	}
	
	showResult(datResult,maxDoc);
	fclose(datFile);
	return 0;
}

DAT sortDat(char* dat,DAT datStore)
{
/*
�迭�� ������ �� ����ü ������ �°� �Է��� ��(memmove), �� �������� NULL ���� �������ش�.
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
	// �ð� �� ����� ���� �ݺ���

	datStore.proTime_int = (datStore.procTime_HH * 3600 + datStore.procTime_MM * 360 + datStore.procTime_SS)*1000 + datStore.procTime_ZZZ;
	// �԰� ��û �ð��� �԰� Ȯ�� �ð����� ���̸� ���ϱ� ���� �и������� ������ ����

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
- i: for ���� ���� ����
- buf: ������ ������ ��� ���� �迭
*/
	int i,num = 0;
	char buf[41];
	for(i=0;!feof(datFile);i++) // �ش� ������ ������ �����ϴ� �ݺ���
	{
		fgets(buf,sizeof(buf), datFile);
		if(num < atoi(&buf[36])) // �ش� ��ǥ ��ȣ�� ����� ��ǥ ��ȣ�� ���Ͽ� �ִ�ġ�� ����
			num = atoi(&buf[36]);
	}
	fseek(datFile, 0, SEEK_SET);
	return num;// �ִ� ��ǥ ��ȣ ��ȯ
}

DRESULT allocData(int maxDoc,DRESULT datResult)
{
	// �ִ� ��ǥ ��ȣ�� �̿��Ͽ� �����Ͱ� �Էµ� ��ŭ�� �����Ҵ�.
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
	// ������ �ʱ� �������� 0���� �ʱ�ȭ
	memset(datResult.inFlag,0,sizeof(datResult.inFlag));
	// �ش� ��ǥ ��ȣ�� ���� ������ �԰� ������ Ȯ���ϱ� ���� Flag �� 0���� �ʱ�ȭ
	datResult.inFlag[datStore.docNum_int] = 1;
	// �ѹ� ���� ��ǥ�� Flag�� 1�� ��ȯ�Ͽ� ��� ��� �� ��� ��.

	/*
	��� ������ ���� switch
	1. �԰� ��û 2. �԰� Ȯ�� 3. ��� ó������ �з��Ͽ� �� �з��� �´� ����
	1. �԰� ��û
	- �԰� ��û �ð� ����
	- �԰� ���� ����
	2. �԰� Ȯ��
	- Ȯ�� �ð� ���� �� Ȯ�� �ð��� ��û �ð����� ���� ����.
	3. ��� ó��
	- ���� ���� ���� ������ ��� ����ŭ ����
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
	printf("��ǥ��ȣ ó���ð�     �԰����    ������    ��������\n");
	for(i=1;i<=maxDoc;i++)
	{
		if(datResult.inFlag[i] != 1)
			continue;

		hour = datResult.rProcTime[i]/36000000;
		minute = (datResult.rProcTime[i] - hour)/360000;
		second = (datResult.rProcTime[i] - hour - minute)/1000;
		msecond = (datResult.rProcTime[i] - hour - minute)%1000;

		printf("%8d %02d:%02d:%02d:%03d %8d %8d %8d\n",i,hour,minute,second,msecond, datResult.inProduct[i],datResult.outProduct[i],datResult.inProduct[i] - datResult.outProduct[i]);
		// ����� ���� �ܼ� ȭ�� ���
		createCSVR(datResult,i, hour,minute,second,msecond);
		// ����� ���� Excel CSV ���� ����
	}
}

void createCSVR(DRESULT datResult,int i,int hour,int minute,int second,int msecond)
{
	FILE* datFile = fopen("result.csv","at");
	fprintf(datFile,"%8d,%02d:%02d:%02d:%03d,%8d,%8d,%8d\n",i,hour,minute,second,msecond, datResult.inProduct[i],datResult.outProduct[i],datResult.inProduct[i] - datResult.outProduct[i]);
	fclose(datFile);
}
