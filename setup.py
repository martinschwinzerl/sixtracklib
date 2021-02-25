import sys

try:
    from skbuild import setup
except ImportError:
    print( "Please update pip version >= 10 or install the requirements\n"
           " listed in pyproject.toml yourself if you have a none PEP 518\n"
           " compilant environment\n", file=sys.stderr, )
    raise

setup(
    name='sixtracklib',
    version="1.0.0",
    author='SixTrack',
    author_email='sixtrack.contact@cern.ch',
    description='Python bindings for SixTrackLib (6D-Tracking Code)',
    packages=[ "sixtracklib" ],
    package_dir = { 'sixtracklib': 'python/sixtracklib' },
    url='https://github.com/SixTrack/sixtracklib',
    zip_safe=False,
    cmake_install_dir="python/sixtracklib",
    install_requires=['numpy', 'scipy', 'toml', 'cobjects>=0.0.4','pysixtrack>=0.0.6','sixtracktools>=0.0.2'],
    cmake_args=['-DCMAKE_BUILD_TYPE=Debug',]
)
