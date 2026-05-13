SHELL := /bin/bash
CXX := g++
CXXFLAGS := -std=c++17 -O2 -pipe -Wall -Wextra
SRC := $(shell find practice -name '*.cpp' 2>/dev/null || true)

.PHONY: all windows linux clean

all: windows linux

windows:
	powershell -ExecutionPolicy Bypass -File scripts/build_all.ps1

linux:
	@mkdir -p bin
	@for src in $(SRC); do \
		outdir=bin/$$(dirname $$src); \
		mkdir -p $$outdir; \
		name=$$(basename $$src .cpp); \
		$(CXX) $(CXXFLAGS) -o $$outdir/$$name $$src || exit 1; \
	done

clean:
	rm -rf bin/*
