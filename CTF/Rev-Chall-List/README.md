[A set of challenges](https://github.com/N4NU/Reversing-Challenges-List) collected by N4NU.

# Baby

## filechecker

The key function is here:
```c
__int64 __fastcall verify(int idx, unsigned int *pwd)
{
  unsigned int v2; // ecx
  __int64 result; // rax
  int key[15]; // [rsp+10h] [rbp-40h]

  key[0] = 0x12EE;
  key[1] = 0x12E0;
  key[2] = 0x12BC;
  key[3] = 0x12F1;
  key[4] = 0x12EE;
  key[5] = 0x12EB;
  key[6] = 0x12F2;
  key[7] = 0x12D8;
  key[8] = 0x12F4;
  key[9] = 0x12EF;
  key[10] = 0x12D2;
  key[11] = 0x12F4;
  key[12] = 0x12EC;
  key[13] = 0x12D6;
  key[14] = 0x12BA;
  v2 = (signed int)(key[idx] + *pwd) % 0x1337;
  result = v2;
  *pwd = v2;
  return result;
}
```

Basically the program use a set of hardcoded number with numeric operations to check our input. So to recover the key, calculate formula `x + key[idx] = 1337`, x is each byte of our flag.

`IW{FILE_CHeCKa}`

## serverfarm

It will check input, if partially corrects, then outputs corresponding flag section. Simply find out all chars or strings then compose them together.

`IW{S.E.R.V.E.R>=F:A:R:M}`

## SPIM

A challenge requiring us to simulate MIPS, it xor the provided string with corresponding index, simply xor to get result.

## Step

### 1

Okay, the first step can be simply decompiled by IDA: `if ( !strcmp(argv[1], "Much_secure__So_safe__Wow") )`

### 2

Still easy, we just reverse the numeric operation and then can find flag: `Pandi_pandai`

### 3

It uses a set of handler, just decrypt one by one: `Did_you_like_signals?`

## Android App

This becomes slightly more interesting. Use `jadx` to reverse it, we can find that it use a native lib to check input. In the `isCorrect` function, the input key is not encrypted, use it as input and then we get output: `Sharif_CTF{833489ef285e6fa80690099efc5d9c9d}`

## dMd

The comparison is straight forward, but we need to use online md5 cracker to get the input string `grape`.

## Serial

This is a packed program. Use single step to find `cmp` step by step and get the key string...

## SRM

Leak flag through comparison.

## Warmup

Beautify the code and found that `l` is useless, delete it and get flag.

# Easy

