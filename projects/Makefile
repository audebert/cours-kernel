TARGET = seminar_0_linux.html seminar_1_linux.html \
	seminar_0_kernel_from_scratch.html \
	seminar_1_kernel_from_scratch.html \
	seminar_2_kernel_from_scratch.html

.PHONY: all
all: $(TARGET)

%.html: %.md
	pandoc -t html5 -s -S --toc --template lse.html5 $^ -o $@

.PHONY: clean
clean:
	$(RM) $(TARGET)
