./bread:./bread.c
	gcc ./bread.c ./compiler.c ./vm.c -o ./bread

run:
	./bread

clean:
	rm ./bread
