@echo off
echo %1 %2
forfiles -p "%1/image/" -s -m *.log -d -%2 -c "cmd /c del @path"
forfiles -p "%1/image/" -s -m *.log -d -%2 -c "cmd /c del @path"