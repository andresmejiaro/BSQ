// cambiar las call de printf a ft_putstr
// cambiar las call de strstr a ft_strstr

// funciones que crean memoria read_textfile2, read_textfile (a travez de read_textfile2), linefy


#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


void	find_sol(char **map, int *sz, int *sol);
int		check(char **map, int num, int y, int x);
void	update(char **map, int *sz, int *pos, int *sol);
void 	drawsq(char **map, int *sq);
void	solve(char **map, int *sz);



int	evaluator_function_n(char c)
{
	if (((c >= '0') && (c <= '9')))
		return (1);
	return (0);
}

int	ft_str_is_numeric(char *str)
{
	while (*str != '\0')
	{
		if (!evaluator_function_n   (*str))
			return (0);
		str++;
	}
	return (1);
}

int	check_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	if (c == '\n' || c == '\f' || c == '\r')
		return (1);
	if (c == '-')
		return (2);
	if (c == '+')
		return (3);
	return (0);
}


int	ft_atoi(char *str)
{
	int	cumulative_sign;
	int	cumulative_sum;

	cumulative_sign = 0;
	cumulative_sum = 0;
	while (check_space(*str) == 1)
		str++;
	while (check_space(*str) == 2 || check_space(*str) == 3)
	{
		if (check_space(*str) == 2)
			cumulative_sign++;
		str ++;
	}
	while (*str >= '0' && *str <= '9')
	{
		cumulative_sum = 10 * cumulative_sum + *str - '0';
		str++;
	}
	if (cumulative_sign % 2 == 1)
		cumulative_sum = -cumulative_sum;
	return (cumulative_sum);
}

void	ft_delete_char(char *str)
{
	while (*str != '\0')
	{
		*str = *(str + 1);
		str++;
	}
}

char	*ft_strcat(char *s1, char *s2)
{
	char	*to_return;

	to_return = s1;
	while (*s1 != '\0')
	{
		s1++;
	}
	while (*s2 != '\0')
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = '\0';
	return (to_return);
}

char	*ft_strcpy(char *dest, char *src)
{
	char	*dest_cpy;

	dest_cpy = dest;
	while (1)
	{
		*dest = *src;
		if (*src == '\0')
		{
			return (dest_cpy);
		}
		dest++;
		src++;
	}
}

int	evaluator_function(char c)
{
	if ((c >= ' ') && (c <= '~'))
		return (1);
	return (0);
}

int	ft_str_is_printable(char *str)
{
	while (*str != '\0')
	{
		if (!evaluator_function(*str))
			return (0);
		str++;
	}
	return (1);
}

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
    if (fo <= 0)
        return 0;
    fsize=count_char(fo);
    close(fo);
    fo=open(path, O_RDONLY);
    to_return = read_text_file2(fo,fsize);
    close(fo);
    if (to_return[fsize-2]!='\n')
        return 0;
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
        str2 = ft_strstr(str2,"\n");
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
        str = ft_strstr(str,"\n");
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
			*(*(map +iy) +ix)= c; 
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

void map_error()
{
    ft_putstr("map error\n");
}

int number_from_header(char *str)
{
    int length;
    char *last3;
    char cpy[40000];


    ft_strcpy(cpy,str);
    length = ft_strlen(cpy);
    last3=cpy+(length-3);
    ft_delete_char(last3);
    ft_delete_char(last3);
    ft_delete_char(last3);
    if (ft_str_is_numeric(cpy))
        return(ft_atoi(cpy));
    else
        return(-1);
}   


int check_map2(char *symbols,char **lines, int *size)
{
    if(symbols[3]== symbols[4] || symbols[4]== symbols[5] || symbols[3]== symbols[5])
        return (0);
    if (!ft_str_is_printable(lines[0]))
        return(0);
    if (number_from_header(lines[0])!= size[0])
        return(0);
    return(1);
}

int check_map(char **lines,int *size, char *symbols)
{
    int counter;
    int counter2;

    if(size[0] <= 0 || size[1] <= 0)
        return(0);
    counter=1;
    while (counter < size[0])
    {
        if (ft_strlen(lines[counter]) != size[1])
            return (0);
        counter2=0;
        while(counter2 < size[1])
        {
            if(!(lines[counter][counter2] ==symbols[3] || \
             lines[counter][counter2] ==symbols[4]))
                return (0);
            counter2++;
        }
        counter ++;
    }
    return(check_map2(symbols,lines,size));
}

void map_cicle(char *file_content)
{
    int     size[2];
    char    **lines;
    char    **map;
    char    symbols[6];
    
    lines = linefy(file_content, size);
    get_symbols(lines[0],symbols);
    map = lines_to_map(lines, size[0], symbols);
    size[0]--;
    if (size[0] == 0)
    {
        map_error();
        return ;
    }
    size[1]=ft_strlen(map[1]);
    if (!check_map(lines,size,symbols)){
        map_error();
        return ;   
    }
    get_symbols(lines[0],symbols);
    swap(map,size,symbols,0);
    solve(map,size);
    swap(map,size,symbols,1);
    print_lines(map,size[0]);
    free(file_content);
    free(lines);
    free(map);
}

void map_cicle_from_file(char *path)
{
    int     size[2];
    char    *file_read;
    char     **lines;
    char    **map;
    char    symbols[6];
    
    file_read=read_text_file(path);
    if(file_read == 0){
        map_error();
        return;
    }
    map_cicle(file_read);
}


void	append_nlines(char *bigstr, int nlines, int *nchars)
{
	int		count;
	int		nbytes;
	char	buf[400];
	
	count = 0;
	while (count < nlines)
	{

		nbytes = read(0, buf, 400);
		if (nbytes <= 0)
			return ;
		buf[nbytes] = '\0';
		ft_strcat(bigstr, buf);
		*nchars += ft_strlen(buf);
		count++;
	}
}

char	*std_in_to_str(void)
{
	char	buf[40000];
	int		nchars;
	int		nlines;
	char	*ret;

	nchars = read(0, buf, 400);
	if (nchars <= 0)
		return (NULL);
	buf[nchars - 1] = '\0';
	nlines =  number_from_header(buf);
	ft_strcat(buf, "\n");
	append_nlines(buf, nlines, &nchars);
	ret = malloc(nchars * sizeof(char));
	ft_strcpy(ret, buf);
	return (ret);
}


int main(int argc, char **argv)
{
    int counter;

    //argc=2;
    if (argc >2)
    {
        counter=1;
        while(counter < argc)
        {
            map_cicle_from_file(argv[counter]);
            
            ft_putstr("\n");
            counter++;
        }
    }
    else if (argc ==2)
        map_cicle_from_file(argv[1]);
    else
        map_cicle(std_in_to_str());
    return (0);
}
