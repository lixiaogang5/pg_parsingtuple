#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define BUF_SIZE (1024 * 2)
#define MIN(a,b) ((a) < (b) ? (a) : (b))

int get_version_by_conf_file(const char *pFilePath, char *pSoftVerBuf, int iSoftBufSize)
{
	FILE *fp = NULL;
	int iRetVal = 0;
	char szBufSize[BUF_SIZE] = {0};
	static const char *szSoftVersion = "SOFTVERSION";
	
	do 
	{
		if(NULL == pFilePath)
		{
			printf("pFilePath[%p] is empty.\n", pFilePath);
			break;
		}
	
		fp = fopen(pFilePath, "r");
		if(NULL == fp)
		{
			printf("fopen() %s failed. errno[%d] err[%s]\n", pFilePath, errno, strerror(errno));
			break;
		}

		while(NULL != fgets(szBufSize, BUF_SIZE, fp))
		{
			printf("%s", szBufSize);
			if(0 == strncmp(szBufSize, szSoftVersion, strlen(szSoftVersion)))
			{
				char *pSoftVer = strstr(szBufSize, "=");
				if(NULL == pSoftVer)
				{
					printf("strstr() %s failed. errno[%d] err[%s]\n", szBufSize, errno, strerror(errno));
					break;
				}
				pSoftVer += 1;
				
				while(*pSoftVer && isspace(*pSoftVer))  pSoftVer++; 
				puts("--------------------------------------------------------");
				printf("pSoftVer:%s len: %d\n", pSoftVer, strlen(pSoftVer));
				puts("--------------------------------------------------------");
				strncpy(pSoftVerBuf, pSoftVer, MIN(strlen(pSoftVer) - 1, iSoftBufSize));
				break;
			}
		}
		
		iRetVal = 1;
	}while(0);

	if(fp)
	{
		fclose(fp);
		fp = NULL;
	}

	return iRetVal;
}
int main()
{
	const char *pFileFull = "/home/soft/nhzd/pg/test/1213/package.conf";
	char buf[BUF_SIZE] = {0};
	if(0 == get_version_by_conf_file(pFileFull, buf, BUF_SIZE))
		printf("error....\n");
	else 
		printf("succeed. buf[%s]\n", buf);
	
	return 0;
}









