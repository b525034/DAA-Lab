#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp = fopen("moves.dat", "w");

    if(fp == NULL)
    {
        printf("Error creating file!\n");
        return 1;
    }

    for(int n = 1; n <= 10; n++)
    {
        int moves = (1 << n) - 1;
        fprintf(fp, "%d %d\n", n, moves);
    }

    fclose(fp);

    FILE *gnuplot = _popen("gnuplot -persistent", "w");

    if(gnuplot == NULL)
    {
        printf("GNUplot not found!\n");
        return 1;
    }

    fprintf(gnuplot, "set title 'Tower of Hanoi'\n");
    fprintf(gnuplot, "set xlabel 'Number of Disks'\n");
    fprintf(gnuplot, "set ylabel 'Number of Moves'\n");
    fprintf(gnuplot, "plot 'moves.dat' using 1:2 with linespoints linewidth 2 title 'Moves'\n");

    fflush(gnuplot);

    printf("Graph displayed.\n");

    getchar();
    getchar();

    _pclose(gnuplot);

    return 0;
}