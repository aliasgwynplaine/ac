#!/usr/bin/gnuplot

set terminal pngcairo size 1920,1080 enhanced font "Helvetica,20"
set title "Profondeur moyenne vs nombre de noeuds"
set xlabel 'nombre de noeuds'
set ylabel 'profondeur moyenne'
set output "depth_n_height_vs_size.png"
plot "bench_depth_vs_size.data" with lines ls 1 lw 3 t "moyenne", \
     "hauteur_max_vs_size.data" with lines ls 2 lw 3 t "maximum"

set title "Facteur d\'équilibre vs nombre de noeuds"
set xlabel 'nombre de noeuds'
set ylabel "facteur d\'équilibre"
set output "equilibre.png"
plot "bench_equilibre.data" with points ls 1 lw 3 t "moyenne", \
     "bench_equilibre_racine.data" with points ls 2 lw 3 t "racine"

set title "Temps d\'éxecution de l'insertion vs nombre de noeuds"
set xlabel 'nombre de noeuds'
set ylabel "temps"
set output "temps_insertion_vs_size.png"
plot "bench_insertion_time_vs_size.data" with points ls 1 lw 3 notitle


set title "Temps d\'éxecution de l'insertion vs profondeur moyenne"
set xlabel 'profondeur moyenne'
set ylabel "temps"
set output "temps_insertion_vs_profondeur_moyenne.png"
plot "bench_insertion_time_vs_depth_moy.data" with points ls 1 lw 3 notitle