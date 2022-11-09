#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int ls (const char* path, const char* arg) {
	struct dirent* dir_s;
	DIR* dir = opendir(path);
	if(dir == NULL) {
		printf("Invalid directory:%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	while((dir_s = readdir(dir)) != NULL) {
		if(arg == NULL && dir_s->d_name[0] == '.') {
			continue;
		}
		printf("%s ", dir_s->d_name);
	}
	return 1;
}

int main (int argv, char** argc) {
	if (argv == 1) { ls(".", NULL); }
	else if (argv == 2) { ls(argc[1], NULL); }
	else if (argv == 3) { ls(argc[2], argc[1]); }
	else {
		perror("Invalid arguments number");
		exit(EXIT_FAILURE);
	}
}
