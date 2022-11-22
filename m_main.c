/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momil-vo <momil-vo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:38:51 by momil-vo          #+#    #+#             */
/*   Updated: 2022/11/21 17:43:57 by momil-vo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

void	find_sol(char **map, int *sz, int *sol);
int		check(char **map, int num, int y, int x);
void	update(char **map, int *sz, int *pos, int *sol);
void 	drawsq(char **map, int *sq);
void	solve(char **map, int *sz);

int main()
{
	char	**map;
	int		*sz;
	int		k;
	
	sz = malloc(2);
	sz[0] = 9;
	sz[1] = 27;
	map = (char **) malloc(sz[0]);
	k = 0;
	while (k < sz[0])
	{
		map[k] = (char *) malloc(sz[1] + 1);
		k++;
	}
	map[0] = "...........................";
	map[1] = "....o......................";
	map[2] = "............o..............";
	map[3] = "...........................";
	map[4] = "....o......................";
	map[5] = "...............o...........";
	map[6] = "...........................";
	map[7] = "......o..............o.....";
	map[8] = "..o.......o................";
	solve(map, sz);
	k = 0;
	while (k < sz[0])
	{
		write(1, map[k], sz[1]);
		write(1, "\n", 1);
		k++;
	}
	return (0);
}

//fits into solve the biggest square of 'x's posible
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
	
	c = 'x';
	iy = sq[1];
	while (iy < sq[1] + sq[0])
	{
		ix = sq[2];
		while (ix < sq[2] + sq[0])
		{
			map[iy][ix] = c; //NO FUNCIONA ARREGLAR
			ix++;
		}
		iy++;
	}
}