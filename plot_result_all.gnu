


reset

set terminal pngcairo enhanced size 1200, 700; 
set out "results_all.png";


set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1
set title "{/Symbol a} = 2.0"
set xlabel "{/Symbol s}"
set ylabel "SNR"
plot 'alpha_2.0_beta_0.0_thr_1.0_results.txt' using 1:2 with lp title 'tr=1.0',\
'alpha_2.0_beta_0.0_thr_1.1_results.txt' using 1:2 with lp title 'tr=1.1',\
'alpha_2.0_beta_0.0_thr_1.2_results.txt' using 1:2 with lp title 'tr=1.2',\
'alpha_2.0_beta_0.0_thr_1.5_results.txt' using 1:2 with lp title 'tr=1.5',\
'alpha_2.0_beta_0.0_thr_2.0_results.txt' using 1:2 with lp title 'tr=2.0';

