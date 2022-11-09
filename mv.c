#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int is_file(const char* path) {
	struct stat st_buf;

	if(S_ISREG(st_buf.st_mode)) {
		return 1;
	} else {
		return 0;
	}
}


int main (int argc,char **argv){

	if(argc < 3) {
		printf("Command needs more args\n");
		return errno;
	}

	char *src, *dst;

	src = argv[1];
	dst = argv[2];

	if(!is_file(dst)) {
		rename(src, dst);
		return 0; 
	}

	char* name = basename(argv[1]);
	if(dst[strlen(dst) - 1] != '/') { strcat(dst, "/"); }
	strcat(dst, name);

	rename(src, dst);
	return 0;
}
