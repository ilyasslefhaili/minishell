#include "exec.h"
int main(int ac, char **av, char**env)
{
    printf("%s\n", env[0]);
    return (0);
}