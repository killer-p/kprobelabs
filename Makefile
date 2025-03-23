all:
	make -C app all
	make -C driver all
clean:
	make -C app clean
	make -C driver clean