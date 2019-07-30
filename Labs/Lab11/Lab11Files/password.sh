#!/bin/sh
# by Krzysztoff Voss
# Nov 2012

# gen_pass generates a new 9-letter password.

gen_pass() {
	local PASS=`python -c "import string
from random import choice
print ''.join([choice(string.letters + string.digits) for i in xrange(9)])"`

	echo "$PASS"
}
