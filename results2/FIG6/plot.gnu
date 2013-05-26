

reset

set terminal pngcairo enhanced size 1200, 700; 
set out "FIG2_snr.png";


set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1

set xlabel "{/Symbol s}"
set ylabel "SNR"
plot 'alpha_1.50_beta_-1.00_thr_1.50_results.txt' using 1:2 with linespoints title '{/Symbol b} = -1.0',\
'alpha_1.50_beta_-0.50_thr_1.50_results.txt' using 1:2 with linespoints title '{/Symbol b} = -0.5',\
'alpha_1.50_beta_0.00_thr_1.50_results.txt' using 1:2 with linespoints title '{/Symbol b} = 0.0',\
'alpha_1.50_beta_0.50_thr_1.50_results.txt' using 1:2 with linespoints title '{/Symbol b} = 0.5',\
'alpha_1.50_beta_1.00_thr_1.50_results.txt' using 1:2 with linespoints title '{/Symbol b} = 1.0';


reset

set terminal pngcairo enhanced size 1200, 700; 
set out "FIG2_ampl.png";


set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1

set xlabel "{/Symbol s}"
set ylabel "{/Symbol h}"
plot 'alpha_1.50_beta_-1.00_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol b} = -1.0',\
'alpha_1.50_beta_-0.50_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol b} = -0.5',\
'alpha_1.50_beta_0.00_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol b} = 0.0',\
'alpha_1.50_beta_0.50_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol b} = 0.5',\
'alpha_1.50_beta_1.00_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol b} = 1.0';



reset


set terminal postscript enhanced color; 
set output '| ps2pdf - fig2.pdf'


set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1

set xlabel "{/Symbol s}"
set ylabel "{/Symbol h}"
plot 'alpha_1.50_beta_-1.00_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol b} = -1.0',\
'alpha_1.50_beta_-0.50_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol b} = -0.5',\
'alpha_1.50_beta_0.00_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol b} = 0.0',\
'alpha_1.50_beta_0.50_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol b} = 0.5',\
'alpha_1.50_beta_1.00_thr_1.50_results.txt' using 1:3 with linespoints title '{/Symbol b} = 1.0';