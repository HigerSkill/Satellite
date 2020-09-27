def list_to_file(data: list, filename: str):
    with open(filename, 'w') as file:
        for line in data:
            if '\n' in line:
                line = line.replace(',', ' ')
                file.write(line)
            else:
                file.write(line+'\n')
