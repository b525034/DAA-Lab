set terminal pngcairo size 1000,700
set output 'binary_vs_ternary.png'
set title 'Binary Search vs Ternary Search'
set xlabel 'Input Size (n)'
set ylabel 'Number of Comparisons'
set grid
set key top left
plot 'search_data.dat' using 1:2 with linespoints title 'Binary Search', 'search_data.dat' using 1:3 with linespoints title 'Ternary Search'
