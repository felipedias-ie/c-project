import subprocess
import os

project = 'slither.c'
copyright = '2024'
author = 'Felipe'

extensions = [
    'breathe',
]

breathe_projects = {
    'slither': '_build/doxygen/xml'
}
breathe_default_project = 'slither'

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

html_theme = 'furo'
html_static_path = ['_static']
html_title = 'slither.c'

html_theme_options = {
    "dark_css_variables": {
        "color-brand-primary": "#7dd3fc",
        "color-brand-content": "#7dd3fc",
    },
    "light_css_variables": {
        "color-brand-primary": "#0284c7",
        "color-brand-content": "#0284c7",
    },
}

def run_doxygen(app):
    docs_dir = os.path.dirname(os.path.abspath(__file__))
    subprocess.run(['doxygen', 'Doxyfile'], cwd=docs_dir, check=True)

def setup(app):
    app.connect('builder-inited', run_doxygen)

