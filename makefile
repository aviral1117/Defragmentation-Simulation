main: driver.o linked_array.o
	@gcc -o exe driver.o linked_array.o
	@./exe
driver.o: driver.c linked_array.h
	@gcc -c driver.c
linked_array.o: linked_array.c linked_array.h 	
	@gcc -c linked_array.c
clean:
	@rm driver.o linked_array.o
