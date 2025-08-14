#!/bin/bash

mkdir -p textures

# Generate North texture (Red checkerboard) - textures/4.xpm
cat > textures/4.xpm << 'EOF'
/* XPM */
static char *north[] = {
"64 64 2 1",
". c #FF0000",
"# c #800000",
EOF

# Generate 64 lines of 64 characters each for red checkerboard
for i in {0..63}; do
    echo -n '"' >> textures/4.xpm
    for j in {0..63}; do
        if (( (i/8 + j/8) % 2 == 0 )); then
            echo -n '.' >> textures/4.xpm
        else
            echo -n '#' >> textures/4.xpm
        fi
    done
    if [ $i -eq 63 ]; then
        echo '"' >> textures/4.xpm
    else
        echo '",' >> textures/4.xpm
    fi
done

echo '};' >> textures/4.xpm

# Generate South texture (Green stripes) - textures/3.xpm
cat > textures/3.xpm << 'EOF'
/* XPM */
static char *south[] = {
"64 64 2 1",
". c #00FF00",
"# c #008000",
EOF

for i in {0..63}; do
    echo -n '"' >> textures/3.xpm
    for j in {0..63}; do
        if (( i % 8 < 4 )); then
            echo -n '.' >> textures/3.xpm
        else
            echo -n '#' >> textures/3.xpm
        fi
    done
    if [ $i -eq 63 ]; then
        echo '"' >> textures/3.xpm
    else
        echo '",' >> textures/3.xpm
    fi
done

echo '};' >> textures/3.xpm

# Generate West texture (Blue vertical stripes) - textures/2.xpm
cat > textures/2.xpm << 'EOF'
/* XPM */
static char *west[] = {
"64 64 2 1",
". c #0000FF",
"# c #000080",
EOF

for i in {0..63}; do
    echo -n '"' >> textures/2.xpm
    for j in {0..63}; do
        if (( j % 8 < 4 )); then
            echo -n '.' >> textures/2.xpm
        else
            echo -n '#' >> textures/2.xpm
        fi
    done
    if [ $i -eq 63 ]; then
        echo '"' >> textures/2.xpm
    else
        echo '",' >> textures/2.xpm
    fi
done

echo '};' >> textures/2.xpm

# Generate East texture (Yellow diagonal) - textures/1.xpm
cat > textures/1.xpm << 'EOF'
/* XPM */
static char *east[] = {
"64 64 2 1",
". c #FFFF00",
"# c #808000",
EOF

for i in {0..63}; do
    echo -n '"' >> textures/1.xpm
    for j in {0..63}; do
        if (( (i + j) % 16 < 8 )); then
            echo -n '.' >> textures/1.xpm
        else
            echo -n '#' >> textures/1.xpm
        fi
    done
    if [ $i -eq 63 ]; then
        echo '"' >> textures/1.xpm
    else
        echo '",' >> textures/1.xpm
    fi
done

echo '};' >> textures/1.xpm

echo "Generated 64x64 XPM textures:"
echo "- North (4.xpm): Red checkerboard pattern"
echo "- South (3.xpm): Green horizontal stripes"
echo "- West (2.xpm): Blue vertical stripes"
echo "- East (1.xpm): Yellow diagonal pattern"
echo ""

# Verify the files
for file in textures/*.xpm; do
    lines=$(grep -c '^"' "$file")
    first_line_chars=$(grep '^"' "$file" | head -1 | wc -c)
    echo "$file: $lines data lines, first line has $((first_line_chars-3)) characters"
done