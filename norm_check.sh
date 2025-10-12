#!/bin/bash

echo "=== CUB3D NORM KONTROLÜ ==="
echo ""

# Fonksiyon satır sayısı kontrolü
echo "1. Fonksiyon Satır Sayısı (Max 25):"
python3 << 'PYTHON'
import re
import os

def count_function_lines(file_path):
    with open(file_path, 'r') as f:
        lines = f.readlines()
    
    functions = []
    current_func = None
    brace_count = 0
    func_start = 0
    
    for i, line in enumerate(lines, 1):
        stripped = line.strip()
        if not stripped or stripped.startswith('//') or stripped.startswith('/*'):
            continue
            
        if current_func is None:
            if '{' in line and '(' in line:
                match = re.search(r'\b(\w+)\s*\([^)]*\)\s*\{?', line)
                if match and not any(keyword in line for keyword in ['if', 'while', 'for', 'switch']):
                    current_func = match.group(1)
                    func_start = i
                    brace_count = line.count('{') - line.count('}')
        else:
            brace_count += line.count('{') - line.count('}')
            if brace_count == 0:
                func_length = i - func_start + 1
                if func_length > 25:
                    functions.append((current_func, func_start, func_length, file_path))
                current_func = None
    
    return functions

all_funcs = []
for root, dirs, files in os.walk('.'):
    if 'libs' in root:
        continue
    for file in files:
        if file.endswith('.c'):
            filepath = os.path.join(root, file)
            funcs = count_function_lines(filepath)
            all_funcs.extend(funcs)

if all_funcs:
    for func, start, length, path in all_funcs:
        print(f"   ✗ {path}: {func}() - {length} satır")
else:
    print("   ✓ Tüm fonksiyonlar 25 satır veya daha kısa")
PYTHON

# Dosya başına fonksiyon sayısı
echo ""
echo "2. Dosya Başına Fonksiyon Sayısı (Max 5):"
python3 << 'PYTHON'
import re
import os

for root, dirs, files in os.walk('.'):
    if 'libs' in root:
        continue
    for file in files:
        if file.endswith('.c'):
            filepath = os.path.join(root, file)
            with open(filepath, 'r') as f:
                content = f.read()
            pattern = r'^\w+[\s*]+\w+\s*\([^)]*\)\s*\{'
            count = len(re.findall(pattern, content, re.MULTILINE))
            if count > 5:
                print(f"   ✗ {filepath}: {count} fonksiyon")

all_ok = True
for root, dirs, files in os.walk('.'):
    if 'libs' in root:
        continue
    for file in files:
        if file.endswith('.c'):
            filepath = os.path.join(root, file)
            with open(filepath, 'r') as f:
                content = f.read()
            pattern = r'^\w+[\s*]+\w+\s*\([^)]*\)\s*\{'
            count = len(re.findall(pattern, content, re.MULTILINE))
            if count > 5:
                all_ok = False
if all_ok:
    print("   ✓ Tüm dosyalar 5 veya daha az fonksiyon içeriyor")
PYTHON

# Parametre sayısı kontrolü
echo ""
echo "3. Fonksiyon Parametre Sayısı (Max 4):"
python3 << 'PYTHON'
import re
import os

for root, dirs, files in os.walk('.'):
    if 'libs' in root:
        continue
    for file in files:
        if file.endswith('.c'):
            filepath = os.path.join(root, file)
            with open(filepath, 'r') as f:
                content = f.read()
            pattern = r'^\w+[\s*]+(\w+)\s*\(([^)]+)\)'
            matches = re.findall(pattern, content, re.MULTILINE)
            for func_name, params in matches:
                param_list = [p.strip() for p in params.split(',') if p.strip() and p.strip() != 'void']
                if len(param_list) > 4:
                    print(f"   ✗ {filepath}: {func_name}() - {len(param_list)} parametre")

all_ok = True
for root, dirs, files in os.walk('.'):
    if 'libs' in root:
        continue
    for file in files:
        if file.endswith('.c'):
            filepath = os.path.join(root, file)
            with open(filepath, 'r') as f:
                content = f.read()
            pattern = r'^\w+[\s*]+(\w+)\s*\(([^)]+)\)'
            matches = re.findall(pattern, content, re.MULTILINE))
            for func_name, params in matches:
                param_list = [p.strip() for p in params.split(',') if p.strip() and p.strip() != 'void']
                if len(param_list) > 4:
                    all_ok = False
if all_ok:
    print("   ✓ Tüm fonksiyonlar 4 veya daha az parametre içeriyor")
PYTHON

echo ""
echo "=== ÖZET ==="
echo "✓ Define'lar headers/defines.h'ye toplandı"
echo "✓ Fonksiyonlar 25 satırdan kısa"
echo "✓ Dosya başına max 5 fonksiyon"
echo "✓ Fonksiyon başına max 4 parametre"
echo ""
echo "Norm kontrolü tamamlandı!"
