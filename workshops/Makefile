WORKSHOPS = index linux_0_bootstrap linux_1_char_devices
OUTPUT    = $(addsuffix .html, $(WORKSHOPS))

.PHONY: all
all: $(OUTPUT) lse.html5 style.css

%.html: %.mkd
	pandoc -t html5 -s -S --toc -c style.css --template lse.html5 $^ -o $@

.PHONY: upload
upload: all
	rsync *.html style.css halfr.net:/srv/http/sigalarm.eu/

.PHONY: clean
clean:
	$(RM) $(OUTPUT)
