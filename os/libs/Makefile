all: main

run:
	./main

out:
	mkdir $@

main.o: src/main.c out
	gcc -c $< -o out/$@

hello.o: src/hello.c out
	gcc -c $< -o out/$@

hello.a: hello.o
	ar rcs out/$@ out/$<

world.o: src/world.c out
	gcc -c $< -shared -fpic -o out/$@

libworld.so: world.o
	gcc out/$< -shared -fpic -o out/$@

marks.o: src/marks.c out
	gcc -c $< -shared -fpic -o out/$@

libmarks.so: marks.o
	gcc out/$< -shared -fpic -o out/$@

main: main.o hello.a libworld.so libmarks.so
	gcc -L./out -Wl,-rpath=./out out/$< out/hello.a -o $@ -lworld -ldl

clean:
	rm -f main
	rm -rf out
