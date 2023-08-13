#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>

int	main(void)
{
	char		current_dir[PATH_MAX];
	char		archive_name[100];
	char		tar_command[250];
	int			res;
	time_t		current_time ;
	struct tm	*time_info;
	struct stat	st = {0};

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		fprintf(stderr, "Failed to get current working directory: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (stat(".archives", &st) == -1)
	{
		if (mkdir(".archives", 0700) != 0)
		{
			fprintf(stderr, "Failed to create 'archives' folder: %s\n", strerror(errno));
			return (EXIT_FAILURE);
		}
	}
	current_time = time(NULL);
	time_info = localtime(&current_time);
	res = strftime(archive_name, sizeof(archive_name), "archive_%Y_%m_%d_%H_%M_%S.tar.gz", time_info);
	if (res == 0 || (long unsigned int) res > sizeof(archive_name))
	{
		fprintf(stderr, "The archive name was truncated.\n");
		return (EXIT_FAILURE);
	}
	res = snprintf(tar_command, sizeof(tar_command), \
		"/bin/tar --ignore-failed-read -czf %s/.archives/%s --exclude=*.jar --exclude=.archives .",\
			current_dir, archive_name);
	if (res < 0 || (long unsigned int) res > sizeof(tar_command))
	{
		fprintf(stderr, "The tar command was truncated.\n");
		return (EXIT_FAILURE);
	}
	if (system(tar_command) != 0)
		fprintf(stderr, "[BACKUP FAILED] Archive creation failed\n");
	else
		printf("[BACKUP] Archive creation completed successfully\n");
	return (EXIT_SUCCESS);
}
