# AI Data Generator

An AI training&testing data generator, based on boost serialization. Need dynamic library: `libboost_serialization.so`.

神经网络训练数据生成器

# Build in Windows

1. Check out project from https://github.com/sikkey/AIDataGenerator.git

2. switch platform from "ARM" to "x64"

3. set up remote server address

4. build & run

# Build in Linux (Debian/Ubuntu test)

## install boost

```
sudo apt-get install libboost-all-dev
```

## build cmd

编译时需要链接boost_serialization库

参考命令行:

```
"g++" -W"switch" -W"no-deprecated-declarations" -W"empty-body" -W"conversion" -W"return-type" -W"parentheses" -W"no-pointer-sign" -W"no-format" -W"uninitialized" -W"unreachable-code" -W"unused-function" -W"unused-value" -W"unused-variable" -std=c++11 -Wall -fno-strict-aliasing -g2 -gdwarf-2 "g++" -O0 "3600000" -fthreadsafe-statics -W"switch" -W"no-deprecated-declarations" -W"empty-body" -W"conversion" -W"return-type" -W"parentheses" -W"no-format" -W"uninitialized" -W"unreachable-code" -W"unused-function" -W"unused-value" -W"unused-variable" -frtti -fno-omit-frame-pointer -std=c11 -fexceptions "1" -o "~/project/AIDataGenerator/obj/x64/Debug/%(filename).o" -o"~/project/AIDataGenerator/bin/x64/Debug/AIDataGenerator.out" "3600000" -Wl,-z,relro -Wl,-z,noexecstack -Wl,--no-undefined "g++" -l"boost_serialization" -Wl,-z,now
```

# 运行 `./AIDataGenerator.out`

文本格式：

生成训练文件 train-时间.txt

生成测试文件 test-时间.txt

二进制格式：

生成训练文件 train-时间.dat

生成测试文件 test-时间.dat

# 运行 `./AIDataGenerator.out 文件名前缀`

文本格式：

生成训练文件 文件名前缀-train.txt

生成测试文件 文件名前缀-test.txt

二进制格式：

生成训练文件 文件名前缀-train.dat

生成测试文件 文件名前缀-test.dat
