# Python script to convert all uppercase letters in a file to lowercase

def convert_to_lowercase(file_path, output_file_path=None):
    try:
        # Open the input file in read mode
        with open(file_path, 'r') as file:
            # Read the entire content of the file
            content = file.read()
        
        # Convert the content to lowercase
        lower_content = content.lower()
        
        # Determine the output file path
        if output_file_path is None:
            output_file_path = file_path  # Overwrite the original file
        
        # Open the output file in write mode
        with open(output_file_path, 'w') as file:
            # Write the lowercase content to the file
            file.write(lower_content)
        
        print(f"Successfully converted {file_path} to lowercase.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
# input_file = 'cub3d.h'  # Replace with your input file path
# output_file = 'cub3d.h'  # Optional: replace with your output file path, or set to None to overwrite the original file

# convert_to_lowercase(input_file, output_file)

import sys

if __name__ == "__main__":
    convert_to_lowercase(sys.argv[1], sys.argv[1])