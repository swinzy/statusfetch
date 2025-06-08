#include <stdio.h>
#include <string.h>
#include "os.h"

#define LINUX_OS_RELEASE        "/etc/os-release"
#define LINUX_NAME_FIELD        "PRETTY_NAME="
#define LINUX_NAME_FORMAT       "PRETTY_NAME=\"%127[^\"]\""
#define LINUX_NAME_FIELD_N      12

const char *get_os_name()
{
    FILE *fp = fopen(LINUX_OS_RELEASE, "r");
    if (!fp) 
    {
        perror("Cannot recognise system. No os-release");
        return NULL;
    }

    char line[256];
    static char name[128] = {0};

    while (fgets(line, sizeof(line), fp))
    {
        // Match OS name property
        if (strncmp(line, LINUX_NAME_FIELD, LINUX_NAME_FIELD_N) == 0)
        {
            sscanf(line, LINUX_NAME_FORMAT, name);
        }
    }

    fclose(fp);

    if (!name[0]) 
    {
        fprintf(stderr, "Cannot recognise system. No PRETTY_NAME defined\n");
        return NULL;
    }

    return name;
}

