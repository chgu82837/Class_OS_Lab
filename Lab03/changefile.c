#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char temp[300];
    sprintf(temp,"=== printid ===\nRead      UID = %d\nEffective UID = %d\n",getuid(),geteuid());
    printf("%s",temp);
    FILE* cptr = fopen("datafile","a");

    if (cptr == NULL)
    {
        printf("Can't open file!!\n");
        return 0;
    }

    fprintf(cptr,"%s",temp);
    fclose(cptr);

    return 0;
}
