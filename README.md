
Amora Kernel
=========

Amora is a simple x86 kernel being developed from scratch as a side project for learning purposes.

Currently the kernel has a booloader written in Assembly which sets the GDT, enters protected mode and load a kernel written in C. The kernel has a simple screen driver and handlers for interrupts and the IRQ, which is partly written in Assembly. The PIT interrupt (IRQ0) has been implemented, giving the kernel a periodic interrupt that will be used by the process scheduler later.

Progress
---------

- [X] Booloader
- [X] Screen driver
- [X] Partial Interrupt handler
- [X] Partial IRQ handler
- [X] Timed interrupt with PIT
- [X] Keyboard Interrupt handler
- [ ] Keyboard driver
- [X] Flat Paging
- [ ] Memory handler
- [ ] Multitasking
- [ ] VFS
- [ ] File system
- [ ] User mode

Compiling and Installing
----------
You just need to run
```
	$ make
```
to compile the code. A file called *os-image* will be created. You can either copy it to a floppy disk or a hard drive with
```
	# dd bs=512 if=os-image of=/dev/sdX
```
where *sdX* is your floppy disk or hard drive device name. However, if you do not have a floppy disk lying around or a spare hard drive, you can run it in *qemu* (assuming you have it installed) with
```
	$ make run
```

Debugging
---------
In order to debug the kernel, we can use *qemu*+*gdb*.
You can run
```
	$ make debug
```
to start *qemu* in debugging mode, with the processor stopped. It will wait for a *gdb* connection, which can be established with `target remote :1234` typed in *gdb*.


License
---------
[The MIT License (MIT)](LICENSE)

Learning Material
---------
- [Operational Systems: Design and Implementation](http://www.amazon.com/Operating-Systems-Design-Implementation-Second/dp/0136386776) by Andrew Tanenbaum
- [Principles of Computer System Design](http://www.amazon.com/Principles-Computer-System-Design-Introduction/dp/0123749573) by Jerome Saltzer
- [MIT Xv6](http://pdos.csail.mit.edu/6.828/2012/xv6.html)
- [Writing a Simple Operational System](http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf) by Nick Blundell
- [James Molloy's Kernel Development Tutorials](http://www.jamesmolloy.co.uk/tutorial_html/index.html)
- [OSDev.org wiki](http://wiki.osdev.org/)
- [Bona fide OS Developer](http://www.osdever.net/tutorials/)

________
###### No penguins were harmed during the development of this kernel