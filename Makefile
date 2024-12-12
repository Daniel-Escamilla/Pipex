all:
	@$(MAKE) -C src --no-print-directory

bonus:
	$(MAKE) -C src_bonus --no-print-directory

clean:
	$(MAKE) -C src clean
	$(MAKE) -C src_bonus clean

fclean: clean
	rm -f pipex

re: fclean all
