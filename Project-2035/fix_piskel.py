import re
import sys

def shorten_piskel_data(piskel_path):
    # Read the original content of the file
    with open(piskel_path, 'r') as file:
        piskel_data = file.read()
    
    # Use a regular expression to find and modify hex numbers (removing the first two digits after '0x')
    shortened_data = re.sub(r'0x(\w{2})(\w{6})', r'0x\2', piskel_data)

    # Write the modified content back to the same file
    with open(piskel_path, 'w') as file:
        file.write(shortened_data)

# Check if a filename is provided as an argument
if len(sys.argv) != 2:
    print("Usage: python fix_piskel.py <piskel_path>")
else:
    piskel_path = sys.argv[1]
    shorten_piskel_data(piskel_path)