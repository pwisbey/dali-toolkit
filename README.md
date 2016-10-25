<img src="https://dalihub.github.io/images/DaliLogo320x200.png">

# Build Instructions

## 1. GBS Builds

### NON-SMACK Targets

         $ gbs build -A [TARGET_ARCH]

### SMACK enabled Targets

         $ gbs build -A [TARGET_ARCH] --define "%enable_dali_smack_rules 1"

### DEBUG Builds

         $ gbs build -A [TARGET_ARCH] --define "%enable_debug 1"

## 1. Building for Ubuntu desktop

### Minimum Requirements

 - Ubuntu 14.04
 - Environment created using dali_env script in dali-core repository

### Building the Repository

To build the repository enter the 'build/tizen' folder:

         $ cd dali-toolkit/build/tizen

Then run the following commands:

         $ autoreconf --install
         $ ./configure --prefix=$DESKTOP_PREFIX
         $ make install -j8

### Building and executing test cases

See the README.md in dali-toolkit/automated-tests.
