#!/usr/bin/env python

import sys
import drqueue.base.libdrqueue as drqueue

osMap = {2: 'Linux', 3: 'Windows'}
index = int(sys.argv[1])
computer = drqueue.request_computer_list(drqueue.CLIENT)[index]
print osMap[computer.hwinfo.os]
