set -e
pwd
mkdir -p cpp-lib-binaries
g++ -std=c++20 -fPIC -shared -o cpp-lib-binaries/wrapper.so \
  ../../GenAlgAlgorithms/MathBase/utils/*.cpp \
  ../../GenAlgAlgorithms/MathBase/parse/*.cpp \
  ../../GenAlgAlgorithms/MathBase/merr/*.cpp \
  ../../GenAlgAlgorithms/MathBase/*.cpp