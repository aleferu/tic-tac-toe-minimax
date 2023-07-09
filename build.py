#!/usr/bin/env python3


import os
from sys import exit


def execute_command(command: str):
    print(f'Executing: {command}')
    if os.system(command) != 0:
        print('Exiting... Something happened.')
        exit(1)


def add_paths(folder, files):
    for f in os.listdir(folder):
        name = os.path.join(folder, f)
        if os.path.isdir(name):
            add_paths(name, files)
        elif f.endswith('.cpp') or f.endswith('.c'):
            files.append(name)


def main():
    cxx = 'g++'
    cflags = '-Wall -Wextra -pedantic -std=c++17'
    includeflags = '-Isrc'

    linkerflags = '-lraylib'

    src_folders = ['src']
    code_files = []
    for folder in src_folders:
        add_paths(folder, code_files)
    new_code_files = []
    obj_data_file_name = 'obj_data.dat'
    if not os.path.isfile(obj_data_file_name):
        f = open(obj_data_file_name, 'x')
        f.close()
    temp_file_name = 'temp'
    if not os.path.isfile(temp_file_name):
        f = open(temp_file_name, 'x')
        f.close()
    with open(obj_data_file_name, 'r+') as data_file, open(temp_file_name, 'w+') as temp_file:
        lines = data_file.readlines()
        for file_name in code_files:
            found = False
            file_mtime = round(os.path.getmtime(file_name), 6)
            for line in lines:
                line = line.split(',')
                saved_name = line[0]
                saved_mtime = round(float(line[1][:-1]), 6)
                if saved_name == file_name:
                    found = True
                    if saved_mtime != file_mtime:
                        new_code_files.append(file_name)
                        saved_mtime = file_mtime
                    temp_file.write(','.join([saved_name, str(saved_mtime) + '\n']))
                    continue
            if not found:
                new_code_files.append(file_name)
                temp_file.write(','.join([file_name, str(file_mtime) + '\n']))
    code_files = new_code_files

    obj_folder = 'obj'
    if not os.path.isdir(obj_folder):
        os.mkdir(obj_folder)
    for file in code_files:
        offset = 4
        if file.endswith('.c'):
            offset = 2
        name = os.path.join(obj_folder, file.split(os.sep)[-1][:-offset] + '.o')
        execute_command(f'{cxx} {cflags} -c {file} {includeflags} -o {name}')

    target_folder = 'target'
    if not os.path.isdir(target_folder):
        os.mkdir(target_folder)
    program_name = 'tic-tac-toe-minimax'
    execute_command(f'{cxx} {cflags} {os.path.join(obj_folder, "*.o")} {includeflags} -o {os.path.join(target_folder, program_name)} {linkerflags}')
    os.remove(obj_data_file_name)
    os.rename(temp_file_name, obj_data_file_name)


if __name__ == '__main__':
    main()
