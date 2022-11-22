// cambiar las call de printf a ft_putstr
// cambiar las call de strstr a ft_strstr

// funciones que crean memoria read_textfile2, read_textfile (a travez de read_textfile2), linefy


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


void	find_sol(char **map, int *sz, int *sol);
int		check(char **map, int num, int y, int x);
void	update(char **map, int *sz, int *pos, int *sol);
void 	drawsq(char **map, int *sq);
void	solve(char **map, int *sz);


int	ft_strlen(char *str)
{
	int		counter;

	counter = 0;
	while (*str != '\0')
	{
		str++;
		counter++;
	}
	return (counter);
}

char	*ft_strstr(char *s1, char *s2)
{
	char	*s1_aux;
	char	*s2_aux;

	if (ft_strlen(s2) == 0)
		return (s1);
	while (*s1 != '\0')
	{
		if (*s1 == *s2)
		{
			s1_aux = s1;
			s2_aux = s2;
			while (*s1_aux == *s2_aux)
			{
				s1_aux++;
				s2_aux++;
				if (*s2_aux == '\0')
					return (s1);
				if (*s1_aux == '\0')
					return (0);
			}
		}
		s1++;
	}
	return (0);
}

void	ft_putstr(char *str)
{
	char	*original;
	int		counter;

	original = str;
	counter = 1;
	while (*str != '\0')
	{
		str++;
		counter++;
	}
	write(1, original, counter - 1);
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
    *to_return='\0';
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

void solve(char **map, int *sz)
{
	int sol[3];
	
	find_sol(map, sz, sol);
	if (sol[0] <= 0)
		write(1, "error NO SOLUTION\n", 18);
	else
		drawsq(map, sol);
}

//finds the largest square fitting in map
//(which has sz[0] rows and sz[1] columns) according to the description
//stores the size, row and column of the found square on sol
void	find_sol(char **map, int *sz, int *sol)
{
	int pos[2];
	int max;
	
	sol[0] = -1;
	pos[0] = 0;
	while (pos[0] < sz[0])
	{
		pos[1] = 0;
		while (pos[1] < sz[1])
		{
	 		update(map, sz, pos, sol);
			pos[1]++;
		}
		pos[0]++;
	}
}

//actualiza, si procede el sol observando la casilla pos[0], pos[1]
//updates, if 
void update(char **map, int *sz, int *pos, int *sol)
{
	int max;
	
	max = 0;
	while (pos[0] + max < sz[0] && pos[1] + max < sz[1])
	{
		if (check(map, max + 1, pos[0], pos[1]))
			max++;
		else
			break;
	}
	if (max > sol[0])
	{
		sol[0] = max;
		sol[1] = pos[0];
		sol[2] = pos[1];
	}
}

//returns 1 if it is possible to build a square starting in y,x of side num,
//returns 0 otherwise
//assumes it is possible to build a square of side num -1 on the same place
int	check(char **map, int num, int y, int x)
{
	int count;
	
	count = 0;
	while (count < num)
	{
		if (map[y + num - 1][x + count] == 'o' || 
		map[y + count][x + num - 1] == 'o')
			return (0);
		count++;
	}
	return (1);
}


//draws a square on map of 'x's of size sq[0] 
//whose upper-left corner lays in row sq[1], column sq[2] 
void drawsq(char **map, int *sq)
{
	int iy;
	int ix;
	char c;
	char d;
	c = 'x';
	iy = sq[1];
	while (iy < sq[1] + sq[0])
	{
		ix = sq[2];
		while (ix < sq[2] + sq[0])
		{
			*(*(map +iy) +ix)= c; //NO FUNCIONA ARREGLAR
			ix++;
		}
		iy++;
	}
}


void get_symbols(char *str,char *symbols)
{
    int length;

    length=ft_strlen(str);
    symbols[5]=str[length-1];
    symbols[4]=str[length-2];
    symbols[3]=str[length-3];
    symbols[2]='x';
    symbols[1]='o';
    symbols[0]='.';
}


void	swap_old_new(char **map, int *sz, char *old, char *new);

//wrapper for swap_old_new
void	swap(char **map, int *sz, char *symbols, int mode)
{
	char	dflt[3];
	char	file[3];
	int		count;

	count = 2;
	while (count >= 0)
	{
		dflt[count] = symbols[count];
		file[count] = symbols[count + 3];
		count--;
	}
	if (mode == 0)
		swap_old_new(map, sz, file, dflt);
	else if (mode == 1)
		swap_old_new(map, sz, dflt, file);
	else
		write(1, "\nerror_swap()\n", 14);
}

void	swap_old_new(char **map, int *sz, char *old, char *new)
{
	int		iy;
	int		ix;
	char	*ptr;

	iy = 0;
	while (iy < sz[0])
	{
		ix = 0;
		while (ix < sz[1])
		{
			ptr = &map[iy][ix];
			if (*ptr == old[0])
				*ptr = new[0];
			else if(*ptr == old[1])
				*ptr = new[1];
			else if (*ptr == old[2])
				*ptr = new[2];
			else
			{
				write(1, "\nerror_swap_old_new()\n", 22);
				return ;
			}
			ix++;
		}
		iy++;
	}
}

void map_cicle(char *path)
{
    int     size[2];
    char    *file_read;
    char     **lines;
    char    **map;
    char    symbols[6];
    
    file_read=read_text_file(path);
    lines = linefy(file_read, size);
    get_symbols(lines[0],symbols);
    map = lines_to_map(lines, size[0], symbols);
    size[0]--;
    size[1]=ft_strlen(map[1]);
        //if (!check_map(map,size,symbols)){
    //    print_error()
    //    return ;   
    //}
    get_symbols(lines[0],symbols);
    swap(map,size,symbols,0);
    solve(map,size);
    swap(map,size,symbols,1);
    //swap(map,size,new,old);
    print_lines(map,size[0]);
    ft_putstr("\n");
    free(file_read);
    free(lines);
    free(map);
}

int main(int argc, char **argv)
{
    int counter;

    //argc=2;
    if (argc >1)
    {
        counter=1;
        while(counter < argc)
        {
            map_cicle(argv[counter]);
            //map_cicle("map1.txt");
            counter++;
        }
    }
    return (0);
}
