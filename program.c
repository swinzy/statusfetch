#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINUX_OS_RELEASE        "/etc/os-release"
#define LINUX_NAME_FIELD        "PRETTY_NAME="
#define LINUX_NAME_REGEX        "PRETTY_NAME=\"%127[^\"]\""
#define LINUX_NAME_FIELD_N      12

int main()
{

    FILE *fp = fopen(LINUX_OS_RELEASE, "r");
    if (!fp) 
    {
        perror("Cannot recognise system. No os-release.\n");
        return 1;
    }

    char line[256];
    char name[128] = {0};

    while (fgets(line, sizeof(line), fp))
    {
        // Match OS name property
        if (strncmp(line, LINUX_NAME_FIELD, LINUX_NAME_FIELD_N) == 0)
        {
            sscanf(line, LINUX_NAME_REGEX, name);
        }
    }

    fclose(fp);

    if (!name[0]) 
    {
        perror("Cannot recognise system. No PRETTY_NAME defined.");
        return 1;
    }

    printf("%s\n", name);

    return 0;
}
