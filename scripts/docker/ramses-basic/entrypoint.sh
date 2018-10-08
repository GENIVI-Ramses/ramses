#!/bin/sh

#  -------------------------------------------------------------------------
#  Copyright (C) 2018 BMW Car IT GmbH
#  -------------------------------------------------------------------------
#  This Source Code Form is subject to the terms of the Mozilla Public
#  License, v. 2.0. If a copy of the MPL was not distributed with this
#  file, You can obtain one at https://mozilla.org/MPL/2.0/.
#  -------------------------------------------------------------------------

cd /home/ramses-build

if [ $# -eq 0 ]; then
	# no commands supplied
	exec /bin/bash
else
	# commands supplied
	exec /bin/bash -c "$*"
fi
