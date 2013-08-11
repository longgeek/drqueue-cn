#!/usr/bin/env python

import sys
import drqueue.base.libdrqueue as drqueue

index = int(sys.argv[1])
computer = drqueue.request_computer_list(drqueue.CLIENT)[index]
print computer.hwinfo.name
