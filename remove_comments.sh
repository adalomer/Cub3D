#!/bin/bash

# Function to remove comments from a file
remove_comments() {
    file="$1"
    # Create a temporary file
    temp_file=$(mktemp)
    
    # Process the file
    gcc -fpreprocessed -dD -E -P "$file" 2>/dev/null > "$temp_file"
    
    # If gcc preprocessing worked, use it
    if [ -s "$temp_file" ] && [ $? -eq 0 ]; then
        mv "$temp_file" "$file"
    else
        # Fallback: use sed to remove comments more carefully
        sed -i \
            -e ':a' \
            -e '/\/\*/!b' \
            -e ':b' \
            -e '/\*\//!{N;bb;}' \
            -e 's|/\*.*\*/||' \
            -e 't a' \
            -e 's|//.*$||' \
            "$file"
        rm -f "$temp_file"
    fi
}

# Process all .c and .h files (excluding libs)
find . -type f \( -name "*.c" -o -name "*.h" \) ! -path "*/libs/*" | while read file; do
    echo "Processing: $file"
    remove_comments "$file"
done

echo "Done!"
