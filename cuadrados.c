
// cambiar las call de printf a ft_putstr
// cambiar las call de strstr a ft_strstr

// funciones que crean memoria read_textfile2, read_textfile (a travez de read_textfile2), linefy


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


int ft_strlen(char *str)
{
    return(strlen(str));
}


char *ft_strstr(char *str, char *to_find)
{
    return(strstr(str,to_find));
}

void ft_putstr(char *str)
{
    printf("%s", str);
}


int count_char(int fo)
{
    int counter;
    int status;
    char c;

    counter = 0;
    status = 1;
    while(status==1)
    {
        status = read(fo,&c,1);
        counter ++;
    }
    return (counter);
}

char *read_text_file2(int fo, int fsize)
{
    int status;
    char c;
    char *to_return;
    char *to_return2;

    to_return=(char *)malloc((fsize+1)*sizeof(char));
    to_return2=to_return;
    status = 1;
    while(status==1)
    {
        status = read(fo,to_return,1);
        to_return++;
    }
    to_return='\0';
    return (to_return2);
}


char *read_text_file(char *path)
{
    int fo;
    char *to_return;
    int fsize;

    fo=open(path, O_RDONLY);
    fsize=count_char(fo);
    close(fo);
    fo=open(path, O_RDONLY);
    to_return = read_text_file2(fo,fsize);
    close(fo);

    return(to_return);

}


int count_lines(char *str)
{
    int counter;
    char *str2;
    counter = 0;

    str2 = str;
    while (str2 !=0)
    {
        str2 = strstr(str2,"\n");
        if (str2 == 0)
            break ;
        str2++;
        counter++;
    }
    return (counter);
}


char **linefy(char *str,int *n_lines)
{
    char **lines;
    int counter;

    *n_lines=count_lines(str);
    lines = (char **)malloc(*n_lines*sizeof(char*));
    counter = 0;
    while(counter < *n_lines)
    {
        *(lines+counter)=str;
        str = strstr(str,"\n");
        if (str != 0)
        {
            *str = '\0';
            str++;
        }
            
        counter++;
    }
    return (lines);

}


void print_lines(char **lines, int n_lines)
{
    int counter;

    counter = 0;
    while(counter < n_lines)
    {
        ft_putstr(lines[counter]);
        ft_putstr("\n");
        counter++;
    }
}


char **lines_to_map(char **lines, int n_lines, char *symbols)
{
    char **map;
    int counter;
    int len_str;

    map = (char **)malloc((n_lines - 1) * sizeof(char*));
    counter = 1;
    while (counter < n_lines)
    {
        *(map+counter -1) = *(lines+counter);
        counter++;
    }
    len_str = ft_strlen(lines[0]);
    symbols[2] = lines[0][len_str - 1];
    symbols[1] = lines[0][len_str - 2];
    symbols[0] = lines[0][len_str - 4];

    return (map);
}




/*
void map_cicle(char *path, int *size, char *codes)
{
    int     n_lines;
    int     **lines;
    int     **map;
    char    symbols[3];
    
    file_read = read_text_file(path);
    lines = linefy(file_read.&n_lines);
    map = lines_to_map(lines, n_lines, &symbols);
    if (!check_map(map,n_lines,symbols)){
        print_error()
        return ;   
    }
    map = solve(map);
    map_to_original(map,symbols);
    print_lines(map, n_lines -1);
    free(file_read);
    free(lines);
    free(map);

}*/


int main(void)
{
    int fo;
    int size;
    char *file_read;
    char **lines;
    char *str;
    char ** map;
    char symbols[3];

    file_read=read_text_file("map1.txt");

    lines = linefy(file_read, &fo);
    
    map = lines_to_map(lines, fo, symbols);
    print_lines(map,fo-1);


    return (0);
}


