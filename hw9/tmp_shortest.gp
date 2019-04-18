set term gif
set output "shortest.gif"
plot "shortest.tsv" u 1:2 with linespoints ls 1