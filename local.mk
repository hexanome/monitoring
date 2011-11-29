# Local Makefile for custom rules

default: sim debug

sim:
	@echo "VxWorks sim"
	@node vxworks.js &
