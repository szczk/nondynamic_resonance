
reset

set terminal pngcairo enhanced size 1200, 700; 
set out "results_snr.png";


set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1

set xlabel "{/Symbol s}"
set ylabel "SNR"
plot 'alpha_2.00_beta_0.00_thr_1.50_results.txt' using 1:2 with linespoints notitle lc rgbcolor '#000000';




reset

set terminal pngcairo enhanced size 1200, 700; 
set out "results_ampl.png";


set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1

set xlabel "{/Symbol s}"
set ylabel "{/Symbol h}"
plot 'alpha_2.00_beta_0.00_thr_1.50_results.txt' using 1:3 with points notitle lc rgbcolor '#000000';