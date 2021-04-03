@echo off
echo                                      ---ORDENACAO---
echo.
echo Defina os parametros para ordenacao
set /p min=O tamanho minimo de entradas:
set /p max=O tamanho maximo de entradas:
set /p di=Digitos por entrada:
set /p re=Repeticoes:
set /p it=Valor das iteracoes das entradas:
set /p se=Seleciton Sort-Opcional:
set /p ord=Vetores Ordenados-Opcional:
projeto "%min%" "%max%" "%di%" "%re%" "%it%" "%se%" "%ord%" > output.txt && gnuplot -c grafico.gp %se% %ord% && pdflatex projeto.tex
pause