all: main.pdf

content.tex: generate.py
	python3 generate.py

main.pdf: main.tex content.tex
	pdflatex -shell-escape main.tex
	pdflatex -shell-escape main.tex

clean:
	rm -f *.aux *.log *.out *.toc *.synctex.gz *.fls *.fdb_latexmk content.tex *.markdown.*
	rm -rf _markdown_*
