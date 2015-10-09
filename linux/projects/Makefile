.PHONY: all
all: seminar_0_linux.html seminar_1_linux.html

%.html: %.mkd
	pandoc -t html5 -s -S --toc --template lse.html5 $^ -o $@
