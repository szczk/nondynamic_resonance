
reset

set terminal pngcairo enhanced size 1200, 700; 
set out "results.png";


set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1

set xlabel "{/Symbol s}"
set ylabel "SNR"
plot 'alpha_2.0_beta_0.0_thr_1.0_results.txt' using 1:2 with points notitle lc rgbcolor '#000000';

