#!/usr/bin/env python3

"""
Instaliranje biblioteke:
	sudo apt-get install python3-pil
	
Koriscenje:
	python3 skripta.py imeslike.png
	
Ako skripta pukne, umesto png staviti bmp format	

"""

from PIL import Image
from sys import argv
sprite_name = argv[1] if len(argv) > 1 else input("file name: ")
sprite = Image.open(sprite_name)

def colorMap(rgb):
	return "0x{:02X}{:02X}{:02X}".format(rgb[0], rgb[1], rgb[2])

output = []
for y in range(sprite.size[1]):
    row = [sprite.getpixel((x, y)) for x in range(sprite.size[0])]
    row = [colorMap(rgb) for rgb in row]
    output.append("    " + ", ".join(row))
sprite.close()

sprite_name = sprite_name.split(".")[0]
print("const uint32_t {}[] = {{".format(sprite_name))
print(",\n".join(output))
print("};\n")
