# Local Makefile for custom rules

default: sim debug

sim:
	@echo "simulating monitoring server"
	@node serversim.js &
