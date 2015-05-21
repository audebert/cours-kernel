WEB_SRC       = index.mkd
WORKSHOPS_SRC = workshop_0_bootstrap.mkd workshop_1_char_devices.mkd

OUTPUT_SRC    = $(WEB_SRC) $(WORKSHOPS_SRC)
OUTPUT        = $(addprefix build/, $(OUTPUT_SRC:.mkd=.html))

STATIC_SRC    = lse.html5 style.css
STATIC        = $(addprefix build/, $(STATIC_SRC))

.PHONY: all
all: $(OUTPUT) $(STATIC)

build:
	mkdir -p build

build/%: % | build
	cp -f $^ $@

build/%.html: %.mkd | build
	pandoc -t html5 -s -S --toc -c style.css --template lse.html5 $^ -o $@

.PHONY: upload
upload: all
	rsync -Pha --delete build/ halfr.net:/srv/http/sigalarm.eu/

.PHONY: clean
clean:
	$(RM) -r build
