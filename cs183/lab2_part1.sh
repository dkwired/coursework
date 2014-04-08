#!/bin/sh
cd ..
(find . -name "*.h" | xargs grep -l magic) > ~/myfile.txt
echo "The number of .h files with 'magic' in it is: $(wc -l myfile.txt)"
cd -
