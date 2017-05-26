#!/usr/bin/gnuplot
set terminal png size 800,480 enhanced font 'Arial, 16'
set output "ex3.png"

set style line 1 linecolor rgb 'red' linetype 1 linewidth 2
set style line 2 linecolor rgb 'blue' linetype 5 linewidth 2

set border linewidth 1
set key top left
set grid
set mytics 0
set format y "%.6f"
set xlabel "Number of elements" font "Arial, 16"
set format x "%.0f"
set ylabel "Execution time (sec)" font "Arial, 16"
set xtics font "Arial, 12"
set ytics font "Arial, 12"
set rmargin 4
set tmargin 2
set mxtics

plot "timed.txt" using 1:2 title "MergeSort" with linespoints ls 1,\
"time1d.txt" using 1:2 title "ShellSort" with linespoints ls 2