"""Setup for the Applied Parallel Computing LLC software components
 Copyright (C) 2015  Ehsan Azar (dashesy@linux.com)
 Copyright (C) 2019, 2020, 2021  Dmitry Mikushin (dmitry@kernelgen.org)
"""

from ThirdParty.apcllcsetup import apcllcsetup

apcllcsetup.apcllcsetup(
    name="arrsin",
    description='C++ Parallel STL sample package',
    long_description='Sample Python package to demonstrate how C++ Parallel STL can be leveraged from Python',
    author='Dmitry Mikushin',
    author_email='dmitry@kernelgen.org',
    entry_points={},
    #entry_points={'console_scripts': ['example_console = example.console:main']},
)

