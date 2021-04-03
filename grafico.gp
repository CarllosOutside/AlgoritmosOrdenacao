set terminal epslatex
set grid
set style line 1 lc rgb "#78076B" pt 7 ps 0.5
set style line 2 lc rgb "#1A6368" pt 7 ps 0.5
set style line 3 lc rgb "#991229" pt 7 ps 0.5
set key box
set key spacing 1.5
set key samplen 2.5
set xlabel "n"
set ylabel "t(s)"
set key left top

if(ARG1 == 1){
if(ARG2 == 0){
set title "Algoritmos de Ordenacao - Vetores nao ordenados"
set output "qSortXcSortXsSort.tex"}
if(ARG2 == 1){
set title "Algoritmos de Ordenacao - Vetores ordenados"
set output "qSortXcSortXsSortO.tex"
}
plot 'output.txt' using 1:6:7 ls 3 title "Selection Sort" with errorlines , '' using 1:4:5 ls 2 title "Counting Sort" with errorlines, '' using 1:2:3 ls 1 title "qSort" with errorlines
}
if(ARG1 == 0){
if(ARG2 == 0){
set title "QuickSort vs CountingSort - Vetores nao ordenados"
set output "qSortXcSort.tex"
}
if(ARG2 == 1){
set title "QuickSort vs CountingSort - Vetores ordenados"
set output "qSortXcSortO.tex"
}
plot 'output.txt' using 1:2:3 ls 1 title "qSort" with errorlines, '' using 1:4:5 ls 2 title "Counting Sort" with errorlines
}