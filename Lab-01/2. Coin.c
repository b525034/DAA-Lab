#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    FILE *fp = fopen("coin.dat", "w");

    if(fp == NULL)
    {
        printf("Error creating file!\n");
        return 1;
    }

    for(int n = 100; n <= 1000; n += 100)
    {
        int fairHeads = 0;
        int biasedHeads = 0;

        for(int i = 0; i < n; i++)
        {
            if(rand() % 2 == 0)
                fairHeads++;
        }
     
        for(int i = 0; i < n; i++)
        {
            if(rand() % 100 < 70)
                biasedHeads++;
        }

        double fairProb = (double)fairHeads / n;
        double biasedProb = (double)biasedHeads / n;

        fprintf(fp,"%d %.4f %.4f\n",n,fairProb,biasedProb);
    }

    fclose(fp);

    FILE *gp = _popen("gnuplot -persistent","w");

    if(gp == NULL)
    {
        printf("GNUplot not found!\n");
        return 1;
    }

    fprintf(gp,"set title 'Fair vs Biased Coin Toss'\n");
    fprintf(gp,"set xlabel 'Number of Tosses'\n");
    fprintf(gp,"set ylabel 'Probability of Head'\n");
    fprintf(gp,"set grid\n");
    fprintf(gp,"set yrange [0:1]\n");

    fprintf(gp,
    "plot 'coin.dat' using 1:2 with linespoints lw 2 title 'Fair Coin',"
    "'coin.dat' using 1:3 with linespoints lw 2 title 'Biased Coin'\n");

    fflush(gp);

    printf("Graph displayed successfully!\n");

    getchar();
    getchar();

    _pclose(gp);

    return 0;
}