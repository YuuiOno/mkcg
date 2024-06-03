# mkcg
The software making carbon's nano structures for Gromacs.

# Installation
The basic installation command using root privileges is as follows:
```
git clone https://github.com/YuuiOno/mkcg.git
mkdir build
cd build
cmake .. -DCMAKE_BUILD_WITH_INSTALL_RPATH=true
make
sudo make install
```
. If root privileges are not available, use the `-DCMAKE_INSTALL_PREFIX` option to specify a directory where you have permissions.
```
git clone https://github.com/YuuiOno/mkcg.git
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=[A DIRECTORY WHERE YOU HAVE PERMISSIONS] -DCMAKE_BUILD_WITH_INSTALL_RPATH=true
make
make install
```
# Usage
For basic command usage, check with `-h` or `--help`. Setting `-t` or `--target` to `CNT` will generate structural data for a single carbon nanotube (CNT). If set to `CNTGRA`, it will generate structural data of two perforated graphene sheets connected by CNT. Setting it to `GRA` will geberate structural data for graphene sheets (including perforated or/and multilayered structures).
