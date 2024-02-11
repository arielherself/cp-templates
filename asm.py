import time
from ctypes import *
import mmap

buf=mmap.mmap(-1,mmap.PAGESIZE,prot=mmap.PROT_READ|mmap.PROT_WRITE|mmap.PROT_EXEC)
def compile_asm_raw(s,ftype):
    buf.write(s)
    return ftype(addressof(c_void_p.from_buffer(buf)))

#https://gcc.godbolt.org/
#https://defuse.ca/online-x86-assembler.htm
#order: edi,esi,edx,ecx,r8d

asm_solve=compile_asm_raw(b"", CFUNCTYPE(c_void_p, POINTER(c_int), c_int, c_int, POINTER(c_int)))
