# -*- mode: python; coding: utf-8 -*-

import Ice
import os


SLICE = "../slice/st.ice"
if not os.path.exists(SLICE):
    SLICE = "/usr/share/slice/st/st.ice"

Ice.loadSlice(SLICE)
import st as stslice
