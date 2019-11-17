filename=manual

$(filename).pdf: $(filename).ps
	ps2pdf $(filename).ps

$(filename).ps: $(filename).dvi
	dvips -t a4 $(filename).dvi 

$(filename).dvi: $(filename).tex
	latex $(filename).tex

zip: $(filename).tex Makefile
	zip xvasko16-fit.zip $(filename).tex Makefile
