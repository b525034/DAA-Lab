#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 10000

void generate(FILE *fp, int type, int n)
{
    long long op[7];

    if (type == 1)
    {
        op[0] = n;
        op[1] = 1;
        op[2] = 1;
        op[3] = n;
        op[4] = n;
        op[5] = n;
        op[6] = n;
    }
    else if (type == 2)
    {
        op[0] = ceil(log2(n + 1));
        op[1] = n;
        op[2] = n;
        op[3] = 1;
        op[4] = 1;
        op[5] = 1;
        op[6] = 1;
    }
    else if (type == 3)
    {
        op[0] = n;
        op[1] = 1;
        op[2] = n;
        op[3] = n;
        op[4] = n;
        op[5] = n;
        op[6] = n;
    }
    else if (type == 4)
    {
        op[0] = n;
        op[1] = n;
        op[2] = n;
        op[3] = n;
        op[4] = 1;
        op[5] = n;
        op[6] = 1;
    }
    else if (type == 5)
    {
        op[0] = n;
        op[1] = 1;
        op[2] = 1;
        op[3] = n;
        op[4] = n;
        op[5] = n;
        op[6] = n;
    }
    else
    {
        op[0] = n;
        op[1] = n;
        op[2] = 1;
        op[3] = 1;
        op[4] = 1;
        op[5] = 1;
        op[6] = 1;
    }

    fprintf(fp, "%d", n);

    for (int i = 0; i < 7; i++)
        fprintf(fp, " %lld", op[i]);

    fprintf(fp, "\n");
}

void plot(FILE *g, char *file, char *title)
{
    fprintf(g, "set output '%s.png'\n", file);
    fprintf(g, "set title '%s'\n", title);
    fprintf(g, "set xlabel 'Input Size (n)'\n");
    fprintf(g, "set ylabel 'Operations'\n");
    fprintf(g, "set grid\n");

    fprintf(g,
        "plot '%s.dat' using 1:2 with linespoints title 'Search',"
        "'%s.dat' using 1:3 with linespoints title 'Insert',"
        "'%s.dat' using 1:4 with linespoints title 'Delete',"
        "'%s.dat' using 1:5 with linespoints title 'Maximum',"
        "'%s.dat' using 1:6 with linespoints title 'Minimum',"
        "'%s.dat' using 1:7 with linespoints title 'Predecessor',"
        "'%s.dat' using 1:8 with linespoints title 'Successor'\n",
        file, file, file, file, file, file, file);
}

int main()
{
    FILE *fp[6];
    char *files[] = {
        "unsorted_array",
        "sorted_array",
        "singly_unsorted",
        "singly_sorted",
        "doubly_unsorted",
        "doubly_sorted"
    };

    for (int i = 0; i < 6; i++)
    {
        char name[50];
        sprintf(name, "%s.dat", files[i]);
        fp[i] = fopen(name, "w");
    }

    for (int n = 100; n <= MAXN; n += 100)
    {
        for (int i = 0; i < 6; i++)
            generate(fp[i], i + 1, n);
    }

    for (int i = 0; i < 6; i++)
        fclose(fp[i]);

    FILE *g = _popen("gnuplot", "w");

    if (g == NULL)
    {
        printf("Gnuplot not found.\n");
        return 1;
    }

    fprintf(g, "set terminal pngcairo size 1000,700\n");

    plot(g, "unsorted_array",
         "Dictionary Operations - Unsorted Array");

    plot(g, "sorted_array",
         "Dictionary Operations - Sorted Array");

    plot(g, "singly_unsorted",
         "Dictionary Operations - Singly Linked Unsorted");

    plot(g, "singly_sorted",
         "Dictionary Operations - Singly Linked Sorted");

    plot(g, "doubly_unsorted",
         "Dictionary Operations - Doubly Linked Unsorted");

    plot(g, "doubly_sorted",
         "Dictionary Operations - Doubly Linked Sorted");

    fflush(g);
    _pclose(g);

    printf("All 6 graphs generated successfully.\n");

    return 0;
}

