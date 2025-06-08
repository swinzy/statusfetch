#include <stdio.h>
#include "os.h"

int main()
{
    const char *os = get_os_name();
    
    // Cannot detect os
    if (!os) {
        return 1;
    }

    printf("%s\n", os);
    return 0;
}
