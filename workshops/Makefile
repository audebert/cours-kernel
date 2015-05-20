WORKSHOPS = linux_0_bootstrap
OUTPUT    = $(addsuffix .html, $(WORKSHOPS))

.PHONY: all
all: $(OUTPUT) lse.html5 style.css

%.html: %.mkd
	pandoc -t html5 -s -S --toc -c style.css --template lse.html5 $^ -o $@

.PHONY: clean
clean:
	$(RM) $(OUTPUT)
