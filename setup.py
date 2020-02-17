#!/usr/bin/python3
# -*- mode: python; coding: utf-8 -*-

import Ice
from distutils.core import setup

__version__ = open('.version').read()

setup(
    name          = 'smart-transducer',
    version       =  __version__,
    description   = "Python library for Smart Transducer interfaces",
    author        = "Arco Group",
    author_email  = "arco.group@gmail.com",
    url           = "https://bitbucket.org/arco_group/smart-transducer/src/master/",
    package_dir   = {'': 'python'},
    py_modules    = ['stlib'],
    data_files    = [
        ('share/slice/st', ['slice/st.ice']),
        ('bin', ['tools/st-client', 'tools/st-link-to']),
    ]
)
