sudo apt-get install build-essential
sudo apt-get install libc6-dev-i386
sudo apt-get install libc6-dev

sudo apt install ninja-build

echo | gcc -E -Wp,-v -

## debug:
debug 完整os的时候，在本机就可以了，因为gdbserver是本机的qemu启动的


## test on mac:
- screen
    ```bash
    brew install SDL2
    brew install SDL2_image
    brew install SDL2_ttf
    ```
