# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'The Golden Lotus'
copyright = '2025, oxnz'
author = 'Lanling Xiaoxiao Sheng'
release = '1.0'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ['myst_parser']

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

language = 'zh'

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'alabaster'
html_static_path = ['_static']

# -- Options for epub output --------
version = '3.3'

# -- Options for latexpdf output --------
latex_engine = 'xelatex'
latex_elements = {
    'papersize': 'a4paper',
    'passoptionstopackages': r'''
\PassOptionsToPackage{svgnames}{xcolor}
''',
    'fontpkg': r'''
\setCJKmainfont{SimSong}
\setCJKsansfont{Hiragino Sans GB}
\setCJKmonofont{STFangsong}
''',
    'preamble': r'''
\usepackage{xeCJK}
\usepackage[titles]{tocloft}
\cftsetpnumwidth {1.25cm}\cftsetrmarg{1.5cm}
\setlength{\cftchapnumwidth}{0.75cm}
\setlength{\cftsecindent}{\cftchapnumwidth}
\setlength{\cftsecnumwidth}{1.25cm}
\setlength{\headheight}{12.08pt}
''',
    'sphinxsetup': 'TitleColor=DarkGoldenrod',
    'fncychap': r'\usepackage[Glenn]{fncychap}',
    'printindex': r'\footnotesize\raggedright\printindex',
}
latex_show_urls = 'footnote'

