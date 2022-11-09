#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int cat (const char* path) {
	int fd = open(path, O_RDONLY);
	
	if (fd < 0) {
		return -1;
	}

	off_t length = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	char* content = malloc(length * sizeof(char));

	ssize_t status = read(fd, content, length);
	if (status != length) {
		printf("%s %d\n", strerror(errno), errno);
		return -1;
	}

	printf("Path: %s\nContent:\n%s\n", path, content);
	close(fd);
	free(content);
	return 1; 
}

int is_file(const char* path) {
	struct stat st_buf;
	int ret_code = stat(path, &st_buf);
	if(ret_code != 0) { 
		printf("Not a file:%s\n", path);
	}

	if(S_ISREG(st_buf.st_mode)) {
		return 1;
	} else {
		return 0;
	}
}

int show_dir(const char* path) {
	struct dirent *d;
	DIR* dir = opendir(path);
	if(!dir) {
		printf("Invalid path:%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	while((d = readdir(dir)) != NULL) {
		char full_path[250];
		if(d->d_name[0] == '.') { continue; }
		
		
		strcat(full_path, path);
		if(full_path[strlen(path) - 1] != '/') { strcat(full_path, "/"); }
		strcat(full_path, d->d_name);

		if (is_file(full_path) == 1) { cat(full_path); }
		memset(full_path, 0, 250);

	}
}

int main(int argc, char** argv) {
	if (argc != 2) {
		perror("Invalid arguments\n");
		exit(EXIT_FAILURE);
	}
	show_dir(argv[1]);
}
