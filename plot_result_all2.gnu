

reset

set terminal pngcairo enhanced size 1200, 700; 
set out "results_snr_all.png";


set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1

set xlabel "{/Symbol s}"
set ylabel "SNR"
plot 'alpha_2.00_beta_0.00_thr_2.00_results.txt' using 1:2 with linespoints title 'tr=2.0',\
'alpha_2.00_beta_0.00_thr_1.50_results.txt' using 1:2 with linespoints title 'tr=1.5',\
'alpha_2.00_beta_0.00_thr_1.40_results.txt' using 1:2 with linespoints title 'tr=1.4',\
'alpha_2.00_beta_0.00_thr_1.20_results.txt' using 1:2 with linespoints title 'tr=1.2',\
'alpha_2.00_beta_0.00_thr_1.10_results.txt' using 1:2 with linespoints title 'tr=1.1',\
'alpha_2.00_beta_0.00_thr_1.00_results.txt' using 1:2 with linespoints title 'tr=1.0';
;




reset

set terminal pngcairo enhanced size 1200, 700; 
set out "results_ampl_all.png";


set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1

set xlabel "{/Symbol s}"
set ylabel "{/Symbol h}"
plot 'alpha_2.00_beta_0.00_thr_2.00_results.txt' using 1:3 with linespoints title 'tr=2.0',\
'alpha_2.00_beta_0.00_thr_1.50_results.txt' using 1:3 with linespoints title 'tr=1.5',\
'alpha_2.00_beta_0.00_thr_1.40_results.txt' using 1:3 with linespoints title 'tr=1.4',\
'alpha_2.00_beta_0.00_thr_1.20_results.txt' using 1:3 with linespoints title 'tr=1.2',\
'alpha_2.00_beta_0.00_thr_1.10_results.txt' using 1:3 with linespoints title 'tr=1.1',\
'alpha_2.00_beta_0.00_thr_1.00_results.txt' using 1:3 with linespoints title 'tr=1.0';
;