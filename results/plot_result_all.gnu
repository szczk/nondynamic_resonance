
reset

set terminal pngcairo enhanced size 1200, 700; 
set out "results_a_2.0_b_0.0.png";
set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1
set title "{/Symbol a} = 2.0, {/Symbol b} = 0.0"
set xlabel "{/Symbol s}"
set ylabel "SNR"
plot 'alpha_2.00_beta_0.00_thr_1.00_results.txt' using 1:2 with lp title 'tr=1.0',\
'alpha_2.00_beta_0.00_thr_1.10_results.txt' using 1:2 with lp title 'tr=1.1',\
'alpha_2.00_beta_0.00_thr_1.20_results.txt' using 1:2 with lp title 'tr=1.2',\
'alpha_2.00_beta_0.00_thr_1.30_results.txt' using 1:2 with lp title 'tr=1.3',\
'alpha_2.00_beta_0.00_thr_1.40_results.txt' using 1:2 with lp title 'tr=1.4',\
'alpha_2.00_beta_0.00_thr_1.50_results.txt' using 1:2 with lp title 'tr=1.5',\
'alpha_2.00_beta_0.00_thr_2.00_results.txt' using 1:2 with lp title 'tr=2.0';



reset

set terminal pngcairo enhanced size 1200, 700; 
set out "results_a_1.8_b_0.0.png";
set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1
set title "{/Symbol a} = 1.8, {/Symbol b} = 0.0"
set xlabel "{/Symbol s}"
set ylabel "SNR"
plot 'alpha_1.80_beta_0.00_thr_1.00_results.txt' using 1:2 with lp title 'tr=1.0',\
'alpha_1.80_beta_0.00_thr_1.10_results.txt' using 1:2 with lp title 'tr=1.1',\
'alpha_1.80_beta_0.00_thr_1.20_results.txt' using 1:2 with lp title 'tr=1.2',\
'alpha_1.80_beta_0.00_thr_1.30_results.txt' using 1:2 with lp title 'tr=1.3',\
'alpha_1.80_beta_0.00_thr_1.40_results.txt' using 1:2 with lp title 'tr=1.4',\
'alpha_1.80_beta_0.00_thr_1.50_results.txt' using 1:2 with lp title 'tr=1.5',\
'alpha_1.80_beta_0.00_thr_2.00_results.txt' using 1:2 with lp title 'tr=2.0';


reset

set terminal pngcairo enhanced size 1200, 700; 
set out "results_a_1.6_b_0.0.png";
set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1
set title "{/Symbol a} = 1.6, {/Symbol b} = 0.0"
set xlabel "{/Symbol s}"
set ylabel "SNR"
plot 'alpha_1.60_beta_0.00_thr_1.00_results.txt' using 1:2 with lp title 'tr=1.0',\
'alpha_1.60_beta_0.00_thr_1.10_results.txt' using 1:2 with lp title 'tr=1.1',\
'alpha_1.60_beta_0.00_thr_1.20_results.txt' using 1:2 with lp title 'tr=1.2',\
'alpha_1.60_beta_0.00_thr_1.30_results.txt' using 1:2 with lp title 'tr=1.3',\
'alpha_1.60_beta_0.00_thr_1.40_results.txt' using 1:2 with lp title 'tr=1.4',\
'alpha_1.60_beta_0.00_thr_1.50_results.txt' using 1:2 with lp title 'tr=1.5',\
'alpha_1.60_beta_0.00_thr_2.00_results.txt' using 1:2 with lp title 'tr=2.0';


reset

set terminal pngcairo enhanced size 1200, 700; 
set out "results_a_1.4_b_0.0.png";
set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1
set title "{/Symbol a} = 1.4, {/Symbol b} = 0.0"
set xlabel "{/Symbol s}"
set ylabel "SNR"
plot 'alpha_1.40_beta_0.00_thr_1.00_results.txt' using 1:2 with lp title 'tr=1.0',\
'alpha_1.40_beta_0.00_thr_1.10_results.txt' using 1:2 with lp title 'tr=1.1',\
'alpha_1.40_beta_0.00_thr_1.20_results.txt' using 1:2 with lp title 'tr=1.2',\
'alpha_1.40_beta_0.00_thr_1.30_results.txt' using 1:2 with lp title 'tr=1.3',\
'alpha_1.40_beta_0.00_thr_1.40_results.txt' using 1:2 with lp title 'tr=1.4',\
'alpha_1.40_beta_0.00_thr_1.50_results.txt' using 1:2 with lp title 'tr=1.5',\
'alpha_1.40_beta_0.00_thr_2.00_results.txt' using 1:2 with lp title 'tr=2.0';





reset

set terminal pngcairo enhanced size 1200, 700; 
set out "results_a_1.2_b_0.0.png";
set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1
set title "{/Symbol a} = 1.2, {/Symbol b} = 0.0"
set xlabel "{/Symbol s}"
set ylabel "SNR"
plot 'alpha_1.20_beta_0.00_thr_1.00_results.txt' using 1:2 with lp title 'tr=1.0',\
'alpha_1.20_beta_0.00_thr_1.10_results.txt' using 1:2 with lp title 'tr=1.1',\
'alpha_1.20_beta_0.00_thr_1.20_results.txt' using 1:2 with lp title 'tr=1.2',\
'alpha_1.20_beta_0.00_thr_1.30_results.txt' using 1:2 with lp title 'tr=1.3',\
'alpha_1.20_beta_0.00_thr_1.40_results.txt' using 1:2 with lp title 'tr=1.4',\
'alpha_1.20_beta_0.00_thr_1.50_results.txt' using 1:2 with lp title 'tr=1.5',\
'alpha_1.20_beta_0.00_thr_2.00_results.txt' using 1:2 with lp title 'tr=2.0';





reset

set terminal pngcairo enhanced size 1200, 700; 
set out "results_a_1.0_b_0.0.png";
set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1
set title "{/Symbol a} = 1.0, {/Symbol b} = 0.0"
set xlabel "{/Symbol s}"
set ylabel "SNR"
plot 'alpha_1.00_beta_0.00_thr_1.00_results.txt' using 1:2 with lp title 'tr=1.0',\
'alpha_1.00_beta_0.00_thr_1.10_results.txt' using 1:2 with lp title 'tr=1.1',\
'alpha_1.00_beta_0.00_thr_1.20_results.txt' using 1:2 with lp title 'tr=1.2',\
'alpha_1.00_beta_0.00_thr_1.30_results.txt' using 1:2 with lp title 'tr=1.3',\
'alpha_1.00_beta_0.00_thr_1.40_results.txt' using 1:2 with lp title 'tr=1.4',\
'alpha_1.00_beta_0.00_thr_1.50_results.txt' using 1:2 with lp title 'tr=1.5',\
'alpha_1.00_beta_0.00_thr_2.00_results.txt' using 1:2 with lp title 'tr=2.0';



reset

set terminal pngcairo enhanced size 1200, 700; 
set out "results_a_0.8_b_0.0.png";
set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1
set title "{/Symbol a} = 0.8, {/Symbol b} = 0.0"
set xlabel "{/Symbol s}"
set ylabel "SNR"
plot 'alpha_0.80_beta_0.00_thr_1.00_results.txt' using 1:2 with lp title 'tr=1.0',\
'alpha_0.80_beta_0.00_thr_1.10_results.txt' using 1:2 with lp title 'tr=1.1',\
'alpha_0.80_beta_0.00_thr_1.20_results.txt' using 1:2 with lp title 'tr=1.2',\
'alpha_0.80_beta_0.00_thr_1.30_results.txt' using 1:2 with lp title 'tr=1.3',\
'alpha_0.80_beta_0.00_thr_1.40_results.txt' using 1:2 with lp title 'tr=1.4',\
'alpha_0.80_beta_0.00_thr_1.50_results.txt' using 1:2 with lp title 'tr=1.5',\
'alpha_0.80_beta_0.00_thr_2.00_results.txt' using 1:2 with lp title 'tr=2.0';
