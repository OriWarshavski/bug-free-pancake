TESTS = configuration crawl dictionary

check:
	$(foreach T, $(TESTS), $(MAKE) -C $(T) check;)

clean:
	$(foreach T, $(TESTS), $(MAKE) -C $(T) clean;)
