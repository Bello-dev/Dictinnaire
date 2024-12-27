compile:
	@gcc -o prog *.c && clear && echo "Executable mis à jpur avec succès !"

run:
	@./prog

clean:
	@rm -f ./prog && clear && echo "Executable supprimé avev succès !"