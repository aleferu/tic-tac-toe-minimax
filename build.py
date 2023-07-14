#!/usr/bin/env python3


import os
from sys import exit


def execute_command(command: str):
    print(f'Executing: {command}')
    if os.system(command) != 0:
        print('Exiting... Something happened.')
        exit(1)


def add_files_from_path(folder, files):
    for f in os.listdir(folder):
        name = os.path.join(folder, f)
        if os.path.isdir(name):
            add_files_from_path(name, files)
        elif f.endswith('.cpp'):
            files.append(name)


def main():
    cxx = 'g++'
    cflags = '-Wall -Wextra -pedantic -std=c++17'
    includeflags = '-Isrc'
    linkerflags = '-lraylib'

    src_folders = ['src']
    code_files = []
    for folder in src_folders:
        add_files_from_path(folder, code_files)

    obj_folder = 'obj'
    if not os.path.isdir(obj_folder):
        os.mkdir(obj_folder)
    for file in code_files:
        name = os.path.join(obj_folder, file.split(os.sep)[-1][:-4] + '.o')
        execute_command(f'{cxx} {cflags} -c {file} {includeflags} -o {name}')

    target_folder = 'target'
    if not os.path.isdir(target_folder):
        os.mkdir(target_folder)
    program_name = 'tic-tac-toe-minimax'
    execute_command(f'{cxx} {cflags} {os.path.join(obj_folder, "*.o")} {includeflags} -o {os.path.join(target_folder, program_name)} {linkerflags}')


if __name__ == '__main__':
    main()
