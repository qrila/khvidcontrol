from distutils.core import setup, Extension

module = Extension(
    'ATEM',
    extra_compile_args = ['-std=c++14'],
    sources = ['atem.cpp', 'wrapper/IPAddress.cpp', 'wrapper/wrap.cpp', 'skaarhoj/ATEMbase/ATEMbase.cpp', 'skaarhoj/ATEMmax/ATEMmax.cpp'])

setup(name = 'ATEM',
      version = '1.0',
      description = 'Control module for Ethernet connected ATEM switchers',
      ext_modules = [module])

