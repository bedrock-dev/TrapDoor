from bz2 import compress
import os
import zipfile

# project_root_dir = 'C:/Users/xhy/dev/TrapDoor/'
project_root_dir = os.path.abspath('../..')+'/'
build_dir = '/build/'
other_files = ['changelog.md',
               'trapdoor-disclaimer.md',
               'LICENSE'
               ]


def get_versions():
    dll_dir = project_root_dir + build_dir
    dll_files = []
    for f in os.listdir(dll_dir):
        if f.endswith('.dll'):
            dll_files.append(f)
    if len(dll_files) == 0:
        input('warning: no valid files')
        exit(0)

    dll_files.sort()
    tips = 'choose one to pack\n'
    index = 0
    for file in reversed(dll_files):
        tips += '[' + str(index) + '] : ' + file+'\n'
        index += 1
 #   print(tips)

    idx = 0
    if len(dll_files) > 1:
        idx = input(tips)
        idx = int(idx)
        if idx < 0 or idx >= len(dll_files):
            input('invalid files\n')
            exit(0)

    return dll_files[len(dll_files)-1-idx]


def pack(dll_file):
    version = dll_file[:-4]
    print('version is '+version)
    print('begin packing...')
    release_zip_file = zipfile.ZipFile(
        version + '.zip', 'w', compresslevel=6, compression=zipfile.ZIP_DEFLATED)
    release_zip_file.write(project_root_dir + build_dir +
                           version + '.dll', arcname=version+'.dll')
    release_zip_file.write(project_root_dir + build_dir +
                           version + '.pdb', arcname=version+'.pdb')
    for other_file in other_files:
        print('pack:  ' + other_file)
        release_zip_file.write(project_root_dir+other_file,
                               arcname='others/'+other_file)
    release_zip_file.close()
    input('success pack release:' + version+'.zip\n')


if __name__ == '__main__':
    pack(get_versions())
