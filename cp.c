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

int is_dir(const char* path) {
	
    struct stat buf;
    stat(path,&buf);
    if(S_ISDIR(buf.st_mode)) { return 1; }
    return 0;
}


int main (int argc, char **argv){

	if(argc < 3) {
		printf("Command needs more args\n");
		return errno;
	}

	char *src, *dst;

	src = argv[1];
	dst = argv[2];
	
	int src_fd = open(src, O_RDONLY, S_IRWXU);
	
	if (is_dir(dst)) {
		char* name = basename(src);
		if(dst[strlen(dst) - 1] != '/') { strcat(dst, "/"); }
		strcat(dst, name);
	}
	
	int dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (src_fd < 0 || dst_fd < 0) {
		return errno;
	}
	
	off_t length = lseek(src_fd, 0, SEEK_END);
	lseek(src_fd, 0, SEEK_SET);
	char* buf = malloc(length * sizeof(char));
	
	read(src_fd, buf, length);
	write(dst_fd, buf, length);
	close(src_fd);
	close(dst_fd);
	
	
	return 0;
}
