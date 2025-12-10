#!/usr/bin/env python3
"""
Generate content.tex from codes/ directory structure.
Scans category folders and generates LaTeX sections/subsections with markdown and code listings.
"""

import os
from pathlib import Path

CATEGORIES = [
    "data-structures",
    "graphs",
    "dp",
    "trees",
    "classicos",
    "strings",
    "math",
    "geometry"
]

CATEGORY_NAMES = {
    "data-structures": "Data Structures",
    "graphs": "Graphs",
    "dp": "DP",
    "trees": "Trees",
    "classicos": "Problemas clássicos",
    "strings": "Strings",
    "math": "Math",
    "geometry": "Geometry"
}

def format_subsection_name(dirname):
    name = dirname.replace("-", " ").replace("_", " ")
    return " ".join(word.capitalize() for word in name.split())

def find_cpp_files(directory):
    cpp_files = sorted(Path(directory).glob("*.cpp"))
    return [f for f in cpp_files if f.is_file()]

def has_content_recursive(directory):
    if len(find_cpp_files(directory)) > 0 or (directory / "README.md").exists():
        return True
    
    subdirs = [d for d in directory.iterdir() if d.is_dir()]
    return any(has_content_recursive(subdir) for subdir in subdirs)

def process_directory(directory, output_lines, level=0):
    subdirs = sorted([d for d in directory.iterdir() if d.is_dir()])
    cpp_files = find_cpp_files(directory)
    readme_path = directory / "README.md"
    
    has_direct_content = len(cpp_files) > 0 or readme_path.exists()
    
    content_subdirs = [
        subdir for subdir in subdirs
        if has_content_recursive(subdir)
    ]
    has_content_subdirs = len(content_subdirs) > 0
    
    should_generate_header = True
    if readme_path.exists():
        should_generate_header = False
    
    if level > 0 and (has_direct_content or has_content_subdirs) and should_generate_header:
        subsection_name = format_subsection_name(directory.name)
        if level == 1:
            output_lines.append(f"\\subsection{{{subsection_name}}}")
        elif level == 2:
            output_lines.append(f"\\subsubsection{{{subsection_name}}}")
        elif level >= 3:
            output_lines.append(f"\\textbf{{{subsection_name}}}")
            
        output_lines.append("")
    
    if has_direct_content:
        if readme_path.exists():
            rel_path = readme_path.relative_to(Path("."))
            
            shift_amount = level
            if level == 0:
                shift_amount = 1
                
            output_lines.append(f"\\markdownInput[shiftHeadings={shift_amount}]{{{rel_path}}}")
            output_lines.append("")
        
        for cpp_file in cpp_files:
            rel_path = cpp_file.relative_to(Path("."))
            output_lines.append(f"\\lstinputlisting[language=C++]{{{rel_path}}}")
            output_lines.append("")
    
    for subdir in content_subdirs:
        process_directory(subdir, output_lines, level + 1)

def generate_content():
    codes_dir = Path("codes")
    output_lines = []
    
    for category in CATEGORIES:
        category_path = codes_dir / category
        
        if not category_path.exists() or not category_path.is_dir():
            continue
        
        section_name = CATEGORY_NAMES.get(category, category.capitalize())
        output_lines.append(f"\\section{{{section_name}}}")
        output_lines.append("")
        
        process_directory(category_path, output_lines, level=0)
    
    output_content = "\n".join(output_lines)
    with open("content.tex", "w", encoding="utf-8") as f:
        f.write(output_content)
    
    print(f"Generated content.tex with {len(output_lines)} lines")

if __name__ == "__main__":
    generate_content()

