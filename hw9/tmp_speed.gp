set term gif
set output "speed.gif"
plot "speed.tsv" u 1:2 with linespoints ls 1