

reset

set terminal pngcairo enhanced size 1200, 700; 
set out "FIG2_snr.png";


set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1

set xlabel "{/Symbol s}"
set ylabel "SNR"
plot 'alpha_1.10_beta_0.00_thr_1.50_results.txt' using 1:2 with linespoints title '{/Symbol a} = 1.1',\
'alpha_1.40_beta_0.00_thr_1.50_results.txt' using 1:2 with linespoints title '{/Symbol a} = 1.4',\
'alpha_1.70_beta_0.00_thr_1.50_results.txt' using 1:2 with linespoints title '{/Symbol a} = 1.7',\
'alpha_2.00_beta_0.00_thr_1.50_results.txt' using 1:2 with linespoints title '{/Symbol a} = 2.0';



reset

set terminal pngcairo enhanced size 1200, 700; 
set out "FIG2_ampl.png";


set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1

set xlabel "{/Symbol s}"
set ylabel "{/Symbol h}"
plot 'alpha_1.10_beta_0.00_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol a} = 1.1',\
'alpha_1.40_beta_0.00_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol a} = 1.4',\
'alpha_1.70_beta_0.00_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol a} = 1.7',\
'alpha_2.00_beta_0.00_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol a} = 2.0';



reset


set terminal postscript enhanced color; 
set output '| ps2pdf - fig2.pdf'


set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1

set xlabel "{/Symbol s}"
set ylabel "{/Symbol h}"
plot 'alpha_1.10_beta_0.00_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol a} = 1.1',\
'alpha_1.40_beta_0.00_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol a} = 1.4',\
'alpha_1.70_beta_0.00_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol a} = 1.7',\
'alpha_2.00_beta_0.00_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol a} = 2.0';