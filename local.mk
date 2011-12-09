# Local Makefile for custom rules

default: sim debug

sim:
	@echo "vxworks sim"
	@node vxworks.js > sim.log &
