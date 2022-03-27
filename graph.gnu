set terminal png
set output "graph.png"

set xrange [0:4]

set yrange [0:16]

set grid

set ylabel "y"

set xlabel "x"

set ytics 1

plot "./output.txt" using 1:2 with lines title "Interpolation"