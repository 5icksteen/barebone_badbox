# barebone

## GCC_ARM
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads  
最新 -> gcc-arm-none-eabi-10-2020-q4-major  

pkgでインストールした場合は  
`$ sudo code ~/.zshrc`  
`export PATH=/Applications/ARM/bin:$PATH`  
`$ source ~/.zshrc`  

homebrewでのインストール  
`$ brew tap ArmMbed/homebrew-formulae`  
`$ brew install arm-none-eabi-gcc`  
