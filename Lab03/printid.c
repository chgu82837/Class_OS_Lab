#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    printf("=== printid ===\nRead      UID = %d\nEffective UID = %d\n",getuid(),geteuid());
    return 0;
}
