all:
	echo "Use a target of: macosx linux clean"

macosx: llama-common.o llama-mmap.o
	ar -qs libllama.a $^

linux: llama-common.o llama-mmap.o
	ar -qs libllama.a $^

llama-common.o: llama-common.c llama.h
	$(CC) -c $(CFLAGS) -o $@ $<

llama-mmap.o: llama-mmap.c llama-internal.h llama.h
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o libllama.a
