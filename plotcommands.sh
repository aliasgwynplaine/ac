#!/usr/bin/gnuplot

set terminal pngcairo size 1500,927 enhanced font "Helvetica,20"
set title "Facteur d\'équilibre vs nombre de noeuds"
set xlabel 'nombre de noeuds'
set ylabel "facteur d\'équilibre"
set output "equilibre.png"
plot "bench_equilibre.data" with points ls 1 lw 3 t "moyenne", \
     "bench_equilibre_racine.data" with points ls 2 lw 3 t "racine"

set key left top
set title "Profondeur vs nombre de noeuds"
set xlabel 'nombre de noeuds'
set ylabel 'profondeur'
set output "depth_n_height_vs_size.png"
plot "bench_depth_vs_size.data" with lines ls 1 lw 3 t "moyenne", \
     "bench_hauteur_max_vs_size.data" with lines ls 2 lw 3 t "maximum"


set title "Temps d\'éxecution de l'insertion vs nombre de noeuds"
set xlabel 'nombre de noeuds'
set ylabel "temps"
set output "temps_insertion_vs_size.png"
plot "bench_insertion_time_vs_size.data" with points ls 1 lw 3 notitle

set title "Temps d\'éxecution de la suppression vs nombre de noeuds"
set xlabel 'nombre de noeuds'
set ylabel "temps"
set output "temps_suppression_vs_size.png"
plot "bench_suppresion_time_vs_size.data" with points ls 2 lw 3 notitle


set title "Temps d\'éxecution de la recherche vs nombre de noeuds"
set xlabel 'nombre de noeuds'
set ylabel "temps"
set output "temps_recherche_vs_size.png"
plot "bench_search_time_vs_size.data" with points ls 3 lw 3 notitle


set title "Temps d\'éxecution de l'insertion vs profondeur moyenne"
set xlabel 'profondeur moyenne'
set ylabel "temps"
set output "temps_insertion_vs_profondeur_moyenne.png"
plot "bench_insertion_time_vs_depth_moy.data" with points ls 1 lw 3 notitle
     
set title "Temps d\'éxecution de la suppression vs profondeur moyenne"
set xlabel 'profondeur moyenne'
set ylabel "temps"
set output "temps_suppression_vs_profondeur_moyenne.png"
plot "bench_suppresion_time_vs_depth_moy.data" with points ls 2 lw 3 notitle

set title "Temps d\'éxecution de la recherche vs profondeur moyenne"
set xlabel 'profondeur moyenne'
set ylabel "temps"
set output "temps_recherche_vs_profondeur_moyenne.png"
plot "bench_search_time_vs_depth_moy.data" with points ls 3 lw 3 notitle