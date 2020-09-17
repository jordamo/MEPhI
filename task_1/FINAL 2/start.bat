@echo off

for %%i in (*.cpp) do (g++ -c %%i)

set mat=
for %%c in (*.o) do (call set "mat=%%mat%% %%c")
g++ %mat:~1%
