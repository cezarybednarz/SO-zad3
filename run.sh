qemu-system-x86_64 -curses -enable-kvm -drive file=minix.img -rtc base=localtime -net user -net nic,model=virtio -m 1024M
