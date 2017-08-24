// 
//

#include "stdafx.h"
#include "MimeProtocolParsing.h"

char *get_boundary(char *mfd)
{
	char *p, *end;
	char *boundary = NULL;
	int boundary_size;

	if ((p = strstr(mfd, "boundary=")) == NULL) {
		return NULL;
	}

	p += 9;
	if ((end = strstr(p, "\r\n")) == NULL) {
		return NULL;
	}

	boundary_size = end - p + 1;
	boundary = new char[boundary_size];

	strncpy(boundary, p, boundary_size);
	boundary[boundary_size - 1] = 0;

	return boundary;
}

char* memstr(char* full_data, int full_data_len, char* substr)
{
	if (full_data == NULL || full_data_len <= 0 || substr == NULL) {
		return NULL;
	}

	if (*substr == '\0') {
		return NULL;
	}

	int sublen = strlen(substr);

	int i;
	char* cur = full_data;
	int last_possible = full_data_len - sublen + 1;
	for (i = 0; i < last_possible; i++) {
		if (*cur == *substr) {
			//assert(full_data_len - i >= sublen);  
			if (memcmp(cur, substr, sublen) == 0) {
				//found  
				return cur;
			}
		}
		cur++;
	}

	return NULL;
}

char* mutipart_form_data(char *mfd, char *boundary, char **type, char **content, int mfdSize, int& contentLen, int& offsetLen)
{
	char *p, *end;
	int size;
	int boundary_size;
	
	char szBoundary[128] = { 0 };
	sprintf(szBoundary, "--%s", boundary);
	boundary_size = strlen(szBoundary);

	*content = *type = NULL;
	contentLen = offsetLen = 0;
	char* mfdTemp = mfd;
	if ((p = memstr(mfd, mfdSize, szBoundary)) == NULL) {
		return NULL;
	}
	p += (boundary_size + 2);
	
	//½âÎötype
	if ((p = strchr(p, '/')) == NULL) {
		return NULL;
	}
	
	if ((end = strchr(p, '\r')) == NULL) {
		return NULL;
	}

	size = end - p;
	*type = (char*) malloc(size);
	strncpy(*type, (p+1), size);
	(*type)[size - 1] = 0;

	if ((end = memstr(p, mfdSize, "\r\n\r\n")) == NULL) {
		return NULL;
	}

	p = end + 4;

	if ((end = memstr(p, (mfdSize - (p - mfd)), szBoundary)) == NULL) {
		return NULL;
	}

	mfd = end;

	while (*p == '\r' || *p == '\n') {
		p++;
	}

	while (*end == '\r' || *end == '\n') {
		end--;
	}

	if (p > end) {
		return NULL;
	}

	size = end - p - 2;
	*content = (char*)malloc(size+1);
	memcpy(*content, p, size);
	(*content)[size] = 0;
	contentLen = size;
	offsetLen = mfd - mfdTemp;
	return mfd;
}




