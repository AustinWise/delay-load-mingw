
testdelay.exe: testdelay.c version.lib
	gcc -o $@ $< -lversion -L .

version.lib: version.def
	dlltool --input-def $< --output-delaylib $@ --dllname version.dll
