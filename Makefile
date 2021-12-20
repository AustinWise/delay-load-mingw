
testdelay.exe: testdelay.c version.lib
	gcc -o test testdelay.c -lversion -L .

version.lib: version.def
	dlltool --input-def version.def --output-delaylib version.lib --dllname version.dll
