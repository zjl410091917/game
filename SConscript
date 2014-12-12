import os, sys, time
from glob import glob

env = Environment()
ccflags = ['-std=c++11', ]
if ARGUMENTS.get('release', '0') == '0':
  ccflags += ['-O0', '-g3', '-Werror', ]
else:
  ccflags += ['-O3', '-g0', '-Wall', ]
env.Append(CPPFLAGS = ccflags)
env.Append(CPPPATH = ['.', 'socket/src', '/usr/local/include'])

ccdefines = {'_FILE_OFFSET_BITS' : '64', 
'DEBUG' : 1, }
if sys.platform == 'darwin':
  ccdefines['__APPALE__'] = 1 
env.Append(CPPDEFINES=ccdefines)

env.Append(LIBPATH = ['/usr/local/lib',])
libs = ['pthread', 'dl', 'glog', 'protobuf', 'gflags', 'tcmalloc', 'snappy']
if sys.platform != 'darwin':
  libs += ['rt']
env.Append(LIBS=libs)

base_dir='socket/src'
source_files = glob('%s/io/*.cc' % base_dir) + \
               glob('%s/base/*.cc' % base_dir) + \
               glob('%s/util/*.cc' % base_dir) + \
               glob('%s/util/logger/*.cc' % base_dir) + \
               glob('%s/util/compression/*.cc' % base_dir) + \
               glob('*.cc')

if sys.platform != 'darwin':
  source_files += glob('../util/file_system_watcher/*.cc') 

print("souce code list: >>")
for s in source_files:
	print(os.path.realpath(s))
print('')

env.Program('gm', source_files)
