#include <coreft.h>

int         ft_is_number(const char *str)
{
    while (*str)
        if(!ft_isdigit(*str++))
            return (0);
    return (1);
}