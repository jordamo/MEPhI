@echo off

for %%i in (*.cpp) do (
    g++ -c %%i
)

set out=
for %%u in (*.o) do (
    call set "out=%%out%% %%u"
)
set out=%out:~1%
g++ %out%
