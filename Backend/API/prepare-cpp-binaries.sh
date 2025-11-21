pwd
[ ! -d "cpp-lib-binaries" ] && mkdir cpp-lib-binaries
g++ -fPIC -fpermissive -shared -w -o cpp-lib-binaries/wrapper.so \
                   ../../GenAlgAlgorithms/MathBase/utils/*cpp \
                   ../../GenAlgAlgorithms/MathBase/parse/*cpp \
                   ../../GenAlgAlgorithms/MathBase/merr/*cpp  \
                  ../../GenAlgAlgorithms/MathBase/*cpp 
