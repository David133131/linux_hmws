#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int main (){
	int count;
	printf("ENTER THE NUMBER OF FILES(1-99), THEN INPUT THE TEXT\n");
	scanf("%d\n", &count);
	if(count < 0) { return -1; }
	
	char text[50];
	fgets(text, 50, stdin);
	text[strlen(text) - 1] = '\0';	
	char name[50] = "file_";

	for (int i = 0; i < count; ++i) {
		char name_tmp[50];
		strcpy(name_tmp, name);
		printf("%s\n", name_tmp);
		char text_tmp[50];
		strcpy(text_tmp, text);
		
		char num[3];
		int fd_num = i + 1;
		if (!(fd_num / 10)) {
			num[0] = fd_num + '0';
			num[1] = '\0';
		} else {
			int tmp = fd_num / 10;
			num[0] = tmp + '0';
			tmp = fd_num % 10;
			num[1] = tmp + '0';
			num[2] = '\0';			
		}
		
		strcat(name_tmp, num);
		strcat(text_tmp, " ");
		strcat(text_tmp, num);
		strcat(name_tmp, ".txt");
		printf("%s\n", name_tmp);

		int fd = open(name_tmp, O_WRONLY | O_CREAT, S_IRWXU);
		
		if(fd < 0) { return errno; }
	
		write(fd, text_tmp, strlen(text_tmp));
		close(fd);
	}

	return 0;
}
	
