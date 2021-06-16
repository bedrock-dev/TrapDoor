import builtins
import os
from os import path
import zipfile


build_dir =  '../release'
lang_folders = 'lang/'
rodb_file = 'RoDB.exe'
config_file = 'trapdoor-config.json'
other_files = ['../changelog.md','../README.md','../README_zh.md','../trapdoor-disclaimer.md','../LICENSE']


#get dll files
dll_files = []
for file in os.listdir(build_dir): 
        if file.endswith('.dll'):
            dll_files.append(file)

if len(dll_files) == 0:
    input('warning: no valid files')
    exit(0)
dll_files.sort()
tips = 'choose one to pack\n'
index = 0
for file in  reversed(dll_files):
    tips += '['+ str(index)+  '] : '+ file+'\n'
    index += 1

#choose version
idx = 0
if len(dll_files) > 1: 
    idx  = input(tips)
    idx = int(idx)
    if idx <0 or idx >= len(dll_files):
        input('invalid files\n')
        exit(0)


dll_file = dll_files[len(dll_files)-1-idx]

full_dll_file_path = build_dir+'/'+ dll_file
os.system('upx '+full_dll_file_path)
## check lang and config.json
if not  (path.exists(lang_folders) and  path.exists(config_file) and path.exists(rodb_file)):
    input('can not find land folder or config_file')
    exit(0)

## check other files
for other_file in other_files:
    if not path.exists(other_file):
        input('can not find file'+other_file+'\n')
        exit(0)

#get version
version = dll_file[:-4]
print('version is '+version)
print('begin packing...')

#begin pack
release_zip_file = zipfile.ZipFile(version +'.zip','w')
release_zip_file.write(build_dir+'/'+ dll_file,arcname=dll_file)
print('pack:  ' + dll_file)
for file in os.listdir(lang_folders): 
    if file.endswith('.json'):
        print('pack:  ' + file)
        release_zip_file.write(lang_folders+file)
for other_file in other_files:
    other_file_name = other_file[3:]
    print('pack:  ' + other_file_name)
    release_zip_file.write(other_file,arcname=other_file_name)
release_zip_file.write(config_file)
release_zip_file.write(rodb_file)
release_zip_file.close()
input('success pack release:' + version+'.zip\n')
