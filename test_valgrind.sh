#!/bin/bash
echo "Running MLX game test with timeout..."
timeout 5s valgrind --leak-check=full --show-leak-kinds=definite ./Cub3d maps/simple.cub 2>&1 | grep -E "(LEAK SUMMARY|definitely lost|ERROR SUMMARY)" | tail -5
