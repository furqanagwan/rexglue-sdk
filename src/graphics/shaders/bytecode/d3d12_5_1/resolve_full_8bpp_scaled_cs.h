#if 0






































cs_5_1
dcl_globalFlags refactoringAllowed
dcl_constantbuffer CB0[0:0][1], immediateIndexed, space=0
dcl_resource_raw T0[0:0], space=0
dcl_uav_typed_buffer (uint,uint,uint,uint) U0[0:0], space=0
dcl_input vThreadID.xy
dcl_temps 26
dcl_thread_group 8, 8, 1
and r0.xyzw, CB0[0][0].xxzz, l(1023, 0x20000000, 8, 0x01000000)
if_nz r0.y
  ubfe r1.xy, l(2, 2, 0, 0), l(17, 20, 0, 0), CB0[0][0].yyyy
else
  mov r1.xy, l(0,0,0,0)
endif
ubfe r2.xyz, l(3, 3, 11, 0), l(16, 19, 5, 0), CB0[0][0].yyyy
imul null, r0.y, r2.x, r2.z
ushr r3.xyzw, CB0[0][0].ywww, l(4, 10, 20, 24)
uge r0.y, vThreadID.x, r0.y
if_nz r0.y
  ret
endif
ubfe r4.xyzw, l(2, 11, 4, 1), l(10, 13, 24, 28), CB0[0][0].xxxx
mov r5.x, CB0[0][0].y
mov r5.y, r3.x
bfi r1.zw, l(0, 0, 4, 1), l(0, 0, 3, 3), r5.xxxy, l(0, 0, 0, 0)
ibfe r0.y, l(6), l(16), CB0[0][0].z
ishl r0.y, r0.y, l(23)
iadd r0.y, r0.y, l(0x3f800000)
ine r0.w, r0.w, l(0)
bfi r2.z, l(10), l(5), CB0[0][0].w, l(0)
bfi r3.xz, l(4, 0, 4, 0), l(3, 0, 3, 0), r3.zzwz, l(0, 0, 0, 0)
ubfe r5.xyz, l(6, 3, 3, 0), l(7, 13, 28, 0), CB0[0][0].zzwz
ishl r6.x, vThreadID.x, l(3)
ieq r5.xw, r5.xxxy, l(2, 0, 0, 1)
and r2.w, r0.w, r5.x
not r3.w, r2.w
and r5.x, r0.w, r3.w
and r0.w, r4.w, r0.w
ieq r6.w, r4.z, l(1)
and r3.w, r3.w, r6.w
uge r6.w, l(3), r5.z
if_nz r6.w
  mov r7.x, r5.z
else
  ieq r6.w, r5.z, l(5)
  if_nz r6.w
    mov r7.x, l(2)
  else
    mov r7.x, l(0)
  endif
endif
umax r6.y, r1.y, vThreadID.y
imad r6.yw, r1.zzzw, r2.xxxy, r6.xxxy
udiv r8.xy, null, r6.ywyy, r2.xyxx
imad r6.yw, -r8.xxxy, r2.xxxy, r6.yyyw
uge r8.z, r4.x, l(2)
if_nz r8.z
  ushr r7.y, r7.x, l(1)
  ishl r9.xy, r8.xyxx, l(1, 1, 0, 0)
  and r9.xy, r9.xyxx, l(-4, -4, 0, 0)
  bfi r9.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r8.xyxx, r9.xyxx
  bfi r9.zw, l(0, 0, 1, 31), l(0, 0, 1, 1), r7.xxxy, l(0, 0, 0, 0)
  iadd r9.xy, r9.zwzz, r9.xyxx
else
  ieq r8.w, r4.x, l(1)
  if_nz r8.w
    bfi r9.x, l(1), l(1), r7.x, r8.x
    ishl r8.w, r8.y, l(1)
    and r8.w, r8.w, l(-4)
    bfi r8.w, l(1), l(0), r8.y, r8.w
    and r9.z, r8.x, l(2)
    iadd r9.y, r8.w, r9.z
  else
    mov r9.xy, r8.xyxx
  endif
endif
imad r9.xy, r9.xyxx, r2.xyxx, r6.ywyy
imul null, r10.yz, r2.xxyx, l(0, 80, 16, 0)
ushr r10.x, r10.y, r4.w
udiv r9.zw, null, r9.xxxy, r10.xxxz
imad r8.w, r9.w, r0.x, r9.z
iadd r8.w, r4.y, r8.w
imad r9.xy, -r9.zwzz, r10.xzxx, r9.xyxx
imul null, r9.z, r10.z, r10.y
imad r9.x, r9.y, r10.x, r9.x
ishl r9.x, r9.x, r4.w
imad r8.w, r8.w, r9.z, r9.x
ishl r9.x, r9.z, l(11)
udiv null, r11.x, r8.w, r9.x
mov r6.z, vThreadID.y
iadd r12.xy, r6.xzxx, l(1, 0, 0, 0)
umax r12.z, r1.y, r12.y
imad r9.yw, r1.zzzw, r2.xxxy, r12.xxxz
udiv r10.yw, null, r9.yyyw, r2.xxxy
imad r9.yw, -r10.yyyw, r2.xxxy, r9.yyyw
if_nz r8.z
  ushr r7.z, r7.x, l(1)
  ishl r12.xy, r10.ywyy, l(1, 1, 0, 0)
  and r12.xy, r12.xyxx, l(-4, -4, 0, 0)
  bfi r12.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r10.ywyy, r12.xyxx
  bfi r12.zw, l(0, 0, 1, 31), l(0, 0, 1, 1), r7.xxxz, l(0, 0, 0, 0)
  iadd r12.xy, r12.zwzz, r12.xyxx
else
  ieq r7.z, r4.x, l(1)
  if_nz r7.z
    bfi r12.x, l(1), l(1), r7.x, r10.y
    ishl r7.z, r10.w, l(1)
    and r7.z, r7.z, l(-4)
    bfi r7.z, l(1), l(0), r10.w, r7.z
    and r8.w, r10.y, l(2)
    iadd r12.y, r7.z, r8.w
  else
    mov r12.xy, r10.ywyy
  endif
endif
imad r12.xy, r12.xyxx, r2.xyxx, r9.ywyy
udiv r12.zw, null, r12.xxxy, r10.xxxz
imad r7.z, r12.w, r0.x, r12.z
iadd r7.z, r4.y, r7.z
imad r12.xy, -r12.zwzz, r10.xzxx, r12.xyxx
imad r8.w, r12.y, r10.x, r12.x
ishl r8.w, r8.w, r4.w
imad r7.z, r7.z, r9.z, r8.w
udiv null, r11.y, r7.z, r9.x
iadd r12.xy, r6.xzxx, l(2, 0, 0, 0)
umax r12.z, r1.y, r12.y
imad r12.xy, r1.zwzz, r2.xyxx, r12.xzxx
udiv r12.zw, null, r12.xxxy, r2.xxxy
imad r12.xy, -r12.zwzz, r2.xyxx, r12.xyxx
if_nz r8.z
  ushr r7.w, r7.x, l(1)
  ishl r13.xy, r12.zwzz, l(1, 1, 0, 0)
  and r13.xy, r13.xyxx, l(-4, -4, 0, 0)
  bfi r13.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r12.zwzz, r13.xyxx
  bfi r7.zw, l(0, 0, 1, 31), l(0, 0, 1, 1), r7.xxxw, l(0, 0, 0, 0)
  iadd r7.zw, r7.zzzw, r13.xxxy
else
  ieq r8.w, r4.x, l(1)
  if_nz r8.w
    bfi r7.z, l(1), l(1), r7.x, r12.z
    ishl r8.w, r12.w, l(1)
    and r8.w, r8.w, l(-4)
    bfi r8.w, l(1), l(0), r12.w, r8.w
    and r13.x, r12.z, l(2)
    iadd r7.w, r8.w, r13.x
  else
    mov r7.zw, r12.zzzw
  endif
endif
imad r7.zw, r7.zzzw, r2.xxxy, r12.xxxy
udiv r13.xy, null, r7.zwzz, r10.xzxx
imad r8.w, r13.y, r0.x, r13.x
iadd r8.w, r4.y, r8.w
imad r7.zw, -r13.xxxy, r10.xxxz, r7.zzzw
imad r7.z, r7.w, r10.x, r7.z
ishl r7.z, r7.z, r4.w
imad r7.z, r8.w, r9.z, r7.z
udiv null, r11.z, r7.z, r9.x
iadd r13.xy, r6.xzxx, l(3, 0, 0, 0)
umax r13.z, r1.y, r13.y
imad r7.zw, r1.zzzw, r2.xxxy, r13.xxxz
udiv r13.xy, null, r7.zwzz, r2.xyxx
imad r7.zw, -r13.xxxy, r2.xxxy, r7.zzzw
if_nz r8.z
  ushr r7.y, r7.x, l(1)
  ishl r13.zw, r13.xxxy, l(0, 0, 1, 1)
  and r13.zw, r13.zzzw, l(0, 0, -4, -4)
  bfi r13.zw, l(0, 0, 1, 1), l(0, 0, 0, 0), r13.xxxy, r13.zzzw
  bfi r14.xy, l(1, 31, 0, 0), l(1, 1, 0, 0), r7.xyxx, l(0, 0, 0, 0)
  iadd r13.zw, r13.zzzw, r14.xxxy
else
  ieq r8.w, r4.x, l(1)
  if_nz r8.w
    bfi r13.z, l(1), l(1), r7.x, r13.x
    ishl r8.w, r13.y, l(1)
    and r8.w, r8.w, l(-4)
    bfi r8.w, l(1), l(0), r13.y, r8.w
    and r14.x, r13.x, l(2)
    iadd r13.w, r8.w, r14.x
  else
    mov r13.zw, r13.xxxy
  endif
endif
imad r13.zw, r13.zzzw, r2.xxxy, r7.zzzw
udiv r14.xy, null, r13.zwzz, r10.xzxx
imad r8.w, r14.y, r0.x, r14.x
iadd r8.w, r4.y, r8.w
imad r13.zw, -r14.xxxy, r10.xxxz, r13.zzzw
imad r13.z, r13.w, r10.x, r13.z
ishl r13.z, r13.z, r4.w
imad r8.w, r8.w, r9.z, r13.z
udiv null, r11.w, r8.w, r9.x
iadd r11.xyzw, r0.wwww, r11.xyzw
iadd r14.xy, r6.xzxx, l(4, 0, 0, 0)
umax r14.z, r1.y, r14.y
imad r13.zw, r1.zzzw, r2.xxxy, r14.xxxz
udiv r14.xy, null, r13.zwzz, r2.xyxx
imad r13.zw, -r14.xxxy, r2.xxxy, r13.zzzw
if_nz r8.z
  ushr r7.y, r7.x, l(1)
  ishl r14.zw, r14.xxxy, l(0, 0, 1, 1)
  and r14.zw, r14.zzzw, l(0, 0, -4, -4)
  bfi r14.zw, l(0, 0, 1, 1), l(0, 0, 0, 0), r14.xxxy, r14.zzzw
  bfi r15.xy, l(1, 31, 0, 0), l(1, 1, 0, 0), r7.xyxx, l(0, 0, 0, 0)
  iadd r14.zw, r14.zzzw, r15.xxxy
else
  ieq r8.w, r4.x, l(1)
  if_nz r8.w
    bfi r14.z, l(1), l(1), r7.x, r14.x
    ishl r8.w, r14.y, l(1)
    and r8.w, r8.w, l(-4)
    bfi r8.w, l(1), l(0), r14.y, r8.w
    and r15.x, r14.x, l(2)
    iadd r14.w, r8.w, r15.x
  else
    mov r14.zw, r14.xxxy
  endif
endif
imad r14.zw, r14.zzzw, r2.xxxy, r13.zzzw
udiv r15.xy, null, r14.zwzz, r10.xzxx
imad r8.w, r15.y, r0.x, r15.x
iadd r8.w, r4.y, r8.w
imad r14.zw, -r15.xxxy, r10.xxxz, r14.zzzw
imad r14.z, r14.w, r10.x, r14.z
ishl r14.z, r14.z, r4.w
imad r8.w, r8.w, r9.z, r14.z
udiv null, r15.x, r8.w, r9.x
iadd r16.xy, r6.xzxx, l(5, 0, 0, 0)
umax r16.z, r1.y, r16.y
imad r14.zw, r1.zzzw, r2.xxxy, r16.xxxz
udiv r16.xy, null, r14.zwzz, r2.xyxx
imad r14.zw, -r16.xxxy, r2.xxxy, r14.zzzw
if_nz r8.z
  ushr r7.y, r7.x, l(1)
  ishl r16.zw, r16.xxxy, l(0, 0, 1, 1)
  and r16.zw, r16.zzzw, l(0, 0, -4, -4)
  bfi r16.zw, l(0, 0, 1, 1), l(0, 0, 0, 0), r16.xxxy, r16.zzzw
  bfi r17.xy, l(1, 31, 0, 0), l(1, 1, 0, 0), r7.xyxx, l(0, 0, 0, 0)
  iadd r16.zw, r16.zzzw, r17.xxxy
else
  ieq r8.w, r4.x, l(1)
  if_nz r8.w
    bfi r16.z, l(1), l(1), r7.x, r16.x
    ishl r8.w, r16.y, l(1)
    and r8.w, r8.w, l(-4)
    bfi r8.w, l(1), l(0), r16.y, r8.w
    and r17.x, r16.x, l(2)
    iadd r16.w, r8.w, r17.x
  else
    mov r16.zw, r16.xxxy
  endif
endif
imad r16.zw, r16.zzzw, r2.xxxy, r14.zzzw
udiv r17.xy, null, r16.zwzz, r10.xzxx
imad r8.w, r17.y, r0.x, r17.x
iadd r8.w, r4.y, r8.w
imad r16.zw, -r17.xxxy, r10.xxxz, r16.zzzw
imad r16.z, r16.w, r10.x, r16.z
ishl r16.z, r16.z, r4.w
imad r8.w, r8.w, r9.z, r16.z
udiv null, r15.y, r8.w, r9.x
iadd r17.xy, r6.xzxx, l(6, 0, 0, 0)
umax r17.z, r1.y, r17.y
imad r16.zw, r1.zzzw, r2.xxxy, r17.xxxz
udiv r17.xy, null, r16.zwzz, r2.xyxx
imad r16.zw, -r17.xxxy, r2.xxxy, r16.zzzw
if_nz r8.z
  ushr r7.y, r7.x, l(1)
  ishl r17.zw, r17.xxxy, l(0, 0, 1, 1)
  and r17.zw, r17.zzzw, l(0, 0, -4, -4)
  bfi r17.zw, l(0, 0, 1, 1), l(0, 0, 0, 0), r17.xxxy, r17.zzzw
  bfi r18.xy, l(1, 31, 0, 0), l(1, 1, 0, 0), r7.xyxx, l(0, 0, 0, 0)
  iadd r17.zw, r17.zzzw, r18.xxxy
else
  ieq r8.w, r4.x, l(1)
  if_nz r8.w
    bfi r17.z, l(1), l(1), r7.x, r17.x
    ishl r8.w, r17.y, l(1)
    and r8.w, r8.w, l(-4)
    bfi r8.w, l(1), l(0), r17.y, r8.w
    and r18.x, r17.x, l(2)
    iadd r17.w, r8.w, r18.x
  else
    mov r17.zw, r17.xxxy
  endif
endif
imad r17.zw, r17.zzzw, r2.xxxy, r16.zzzw
udiv r18.xy, null, r17.zwzz, r10.xzxx
imad r8.w, r18.y, r0.x, r18.x
iadd r8.w, r4.y, r8.w
imad r17.zw, -r18.xxxy, r10.xxxz, r17.zzzw
imad r17.z, r17.w, r10.x, r17.z
ishl r17.z, r17.z, r4.w
imad r8.w, r8.w, r9.z, r17.z
udiv null, r15.z, r8.w, r9.x
iadd r18.xy, r6.xzxx, l(7, 0, 0, 0)
umax r18.z, r1.y, r18.y
imad r1.yz, r1.zzwz, r2.xxyx, r18.xxzx
udiv r17.zw, null, r1.yyyz, r2.xxxy
imad r1.yz, -r17.zzwz, r2.xxyx, r1.yyzy
if_nz r8.z
  ushr r7.y, r7.x, l(1)
  ishl r18.xy, r17.zwzz, l(1, 1, 0, 0)
  and r18.xy, r18.xyxx, l(-4, -4, 0, 0)
  bfi r18.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r17.zwzz, r18.xyxx
  bfi r18.zw, l(0, 0, 1, 31), l(0, 0, 1, 1), r7.xxxy, l(0, 0, 0, 0)
  iadd r18.xy, r18.zwzz, r18.xyxx
else
  ieq r1.w, r4.x, l(1)
  if_nz r1.w
    bfi r18.x, l(1), l(1), r7.x, r17.z
    ishl r1.w, r17.w, l(1)
    and r1.w, r1.w, l(-4)
    bfi r1.w, l(1), l(0), r17.w, r1.w
    and r7.y, r17.z, l(2)
    iadd r18.y, r1.w, r7.y
  else
    mov r18.xy, r17.zwzz
  endif
endif
imad r18.xy, r18.xyxx, r2.xyxx, r1.yzyy
udiv r18.zw, null, r18.xxxy, r10.xxxz
imad r1.w, r18.w, r0.x, r18.z
iadd r1.w, r1.w, r4.y
imad r18.xy, -r18.zwzz, r10.xzxx, r18.xyxx
imad r7.y, r18.y, r10.x, r18.x
ishl r7.y, r7.y, r4.w
imad r1.w, r1.w, r9.z, r7.y
udiv null, r15.w, r1.w, r9.x
iadd r15.xyzw, r0.wwww, r15.xyzw
ishl r11.xyzw, r11.xyzw, l(2, 2, 2, 2)
ld_raw r18.x, r11.x, T0[0].xxxx
ld_raw r18.y, r11.y, T0[0].xxxx
ld_raw r18.z, r11.z, T0[0].xxxx
ld_raw r18.w, r11.w, T0[0].xxxx
ishl r11.xyzw, r15.xyzw, l(2, 2, 2, 2)
ld_raw r15.x, r11.x, T0[0].xxxx
ld_raw r15.y, r11.y, T0[0].xxxx
ld_raw r15.z, r11.z, T0[0].xxxx
ld_raw r15.w, r11.w, T0[0].xxxx
if_nz r4.w
  switch r4.z
    case l(5)
    and r1.w, r2.w, l(16)
    ushr r11.xyzw, r18.xyzw, r1.wwww
    ibfe r11.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r11.xyzw
    itof r11.xyzw, r11.xyzw
    mul r11.xyzw, r11.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
    max r18.xyzw, r11.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
    ushr r11.xyzw, r15.xyzw, r1.wwww
    ibfe r11.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r11.xyzw
    itof r11.xyzw, r11.xyzw
    mul r11.xyzw, r11.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
    max r15.xyzw, r11.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
    break
    case l(7)
    if_nz r2.w
      ushr r11.xyzw, r18.xyzw, l(16, 16, 16, 16)
      f16tof32 r18.xyzw, r11.xyzw
      ushr r11.xyzw, r15.xyzw, l(16, 16, 16, 16)
      f16tof32 r15.xyzw, r11.xyzw
    else
      f16tof32 r18.xyzw, r18.xyzw
      f16tof32 r15.xyzw, r15.xyzw
    endif
    break
    default
    if_nz r2.w
      mov r18.xyzw, l(1.000000,1.000000,1.000000,1.000000)
      mov r15.xyzw, l(1.000000,1.000000,1.000000,1.000000)
    endif
    break
  endswitch
else
  switch r4.z
    case l(0)
    case l(1)
    and r1.w, r5.x, l(16)
    movc r1.w, r2.w, l(24), r1.w
    ushr r11.xyzw, r18.xyzw, r1.wwww
    and r11.xyzw, r11.xyzw, l(255, 255, 255, 255)
    utof r11.xyzw, r11.xyzw
    mul r18.xyzw, r11.xyzw, l(0.003922, 0.003922, 0.003922, 0.003922)
    ushr r11.xyzw, r15.xyzw, r1.wwww
    and r11.xyzw, r11.xyzw, l(255, 255, 255, 255)
    utof r11.xyzw, r11.xyzw
    mul r15.xyzw, r11.xyzw, l(0.003922, 0.003922, 0.003922, 0.003922)
    break
    case l(2)
    case l(10)
    case l(3)
    case l(12)
    if_nz r2.w
      ushr r11.xyzw, r18.xyzw, l(30, 30, 30, 30)
      utof r11.xyzw, r11.xyzw
      mul r18.xyzw, r11.xyzw, l(0.333333, 0.333333, 0.333333, 0.333333)
      ushr r11.xyzw, r15.xyzw, l(30, 30, 30, 30)
      utof r11.xyzw, r11.xyzw
      mul r15.xyzw, r11.xyzw, l(0.333333, 0.333333, 0.333333, 0.333333)
    else
      and r1.w, r5.x, l(20)
      ieq r11.xy, r4.zzzz, l(2, 10, 0, 0)
      or r7.y, r11.y, r11.x
      if_nz r7.y
        ushr r11.xyzw, r18.xyzw, r1.wwww
        and r11.xyzw, r11.xyzw, l(1023, 1023, 1023, 1023)
        utof r11.xyzw, r11.xyzw
        mul r18.xyzw, r11.xyzw, l(0.000978, 0.000978, 0.000978, 0.000978)
        ushr r11.xyzw, r15.xyzw, r1.wwww
        and r11.xyzw, r11.xyzw, l(1023, 1023, 1023, 1023)
        utof r11.xyzw, r11.xyzw
        mul r15.xyzw, r11.xyzw, l(0.000978, 0.000978, 0.000978, 0.000978)
      else
        ushr r11.xyzw, r18.xyzw, r1.wwww
        and r19.xyzw, r11.xyzw, l(1023, 1023, 1023, 1023)
        and r20.xyzw, r11.xyzw, l(127, 127, 127, 127)
        ubfe r21.xyzw, l(3, 3, 3, 3), l(7, 7, 7, 7), r11.xyzw
        firstbit_hi r22.xyzw, r20.xyzw
        iadd r22.xyzw, r22.xyzw, l(-24, -24, -24, -24)
        movc r22.xyzw, r20.xyzw, r22.xyzw, l(8,8,8,8)
        iadd r23.xyzw, -r22.xyzw, l(1, 1, 1, 1)
        movc r23.xyzw, r21.xyzw, r21.xyzw, r23.xyzw
        bfi r11.xyzw, l(7, 7, 7, 7), r22.xyzw, r11.xyzw, l(0, 0, 0, 0)
        and r11.xyzw, r11.xyzw, l(127, 127, 127, 127)
        movc r11.xyzw, r21.xyzw, r20.xyzw, r11.xyzw
        ishl r20.xyzw, r23.xyzw, l(23, 23, 23, 23)
        iadd r20.xyzw, r20.xyzw, l(0x3e000000, 0x3e000000, 0x3e000000, 0x3e000000)
        ishl r11.xyzw, r11.xyzw, l(16, 16, 16, 16)
        iadd r11.xyzw, r20.xyzw, r11.xyzw
        movc r18.xyzw, r19.xyzw, r11.xyzw, l(0,0,0,0)
        ushr r11.xyzw, r15.xyzw, r1.wwww
        and r19.xyzw, r11.xyzw, l(1023, 1023, 1023, 1023)
        and r20.xyzw, r11.xyzw, l(127, 127, 127, 127)
        ubfe r21.xyzw, l(3, 3, 3, 3), l(7, 7, 7, 7), r11.xyzw
        firstbit_hi r22.xyzw, r20.xyzw
        iadd r22.xyzw, r22.xyzw, l(-24, -24, -24, -24)
        movc r22.xyzw, r20.xyzw, r22.xyzw, l(8,8,8,8)
        iadd r23.xyzw, -r22.xyzw, l(1, 1, 1, 1)
        movc r23.xyzw, r21.xyzw, r21.xyzw, r23.xyzw
        bfi r11.xyzw, l(7, 7, 7, 7), r22.xyzw, r11.xyzw, l(0, 0, 0, 0)
        and r11.xyzw, r11.xyzw, l(127, 127, 127, 127)
        movc r11.xyzw, r21.xyzw, r20.xyzw, r11.xyzw
        ishl r20.xyzw, r23.xyzw, l(23, 23, 23, 23)
        iadd r20.xyzw, r20.xyzw, l(0x3e000000, 0x3e000000, 0x3e000000, 0x3e000000)
        ishl r11.xyzw, r11.xyzw, l(16, 16, 16, 16)
        iadd r11.xyzw, r20.xyzw, r11.xyzw
        movc r15.xyzw, r19.xyzw, r11.xyzw, l(0,0,0,0)
      endif
    endif
    break
    case l(4)
    if_nz r2.w
      mov r18.xyzw, l(1.000000,1.000000,1.000000,1.000000)
      mov r15.xyzw, l(1.000000,1.000000,1.000000,1.000000)
    else
      ibfe r11.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r18.xyzw
      itof r11.xyzw, r11.xyzw
      mul r11.xyzw, r11.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
      max r18.xyzw, r11.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
      ibfe r11.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r15.xyzw
      itof r11.xyzw, r11.xyzw
      mul r11.xyzw, r11.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
      max r15.xyzw, r11.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
    endif
    break
    case l(6)
    if_nz r2.w
      mov r18.xyzw, l(1.000000,1.000000,1.000000,1.000000)
      mov r15.xyzw, l(1.000000,1.000000,1.000000,1.000000)
    else
      f16tof32 r18.xyzw, r18.xyzw
      f16tof32 r15.xyzw, r15.xyzw
    endif
    break
    default
    if_nz r2.w
      mov r18.xyzw, l(1.000000,1.000000,1.000000,1.000000)
      mov r15.xyzw, l(1.000000,1.000000,1.000000,1.000000)
    endif
    break
  endswitch
endif
if_nz r3.w
  mov_sat r18.xyzw, r18.xyzw
  ge r11.xyzw, r18.xyzw, l(0.376471, 0.376471, 0.376471, 0.376471)
  if_nz r11.x
    ge r1.w, r18.x, l(0.752941)
    if_nz r1.w
      mov r1.w, l(0.007812)
      mov r7.y, l(-1024.000000)
    else
      mov r1.w, l(0.003906)
      mov r7.y, l(-256.000000)
    endif
  else
    ge r8.w, r18.x, l(0.250980)
    if_nz r8.w
      mov r1.w, l(0.001953)
      mov r7.y, l(-64.000000)
    else
      mov r1.w, l(0.000977)
      mov r7.y, l(0)
    endif
  endif
  mul r8.w, r1.w, r18.x
  mad r7.y, r8.w, l(261120.000000), r7.y
  mul r1.w, r1.w, r7.y
  round_z r1.w, r1.w
  add r1.w, r1.w, r7.y
  mul r18.x, r1.w, l(0.000978)
  if_nz r11.y
    ge r1.w, r18.y, l(0.752941)
    if_nz r1.w
      mov r1.w, l(0.007812)
      mov r7.y, l(-1024.000000)
    else
      mov r1.w, l(0.003906)
      mov r7.y, l(-256.000000)
    endif
  else
    ge r8.w, r18.y, l(0.250980)
    if_nz r8.w
      mov r1.w, l(0.001953)
      mov r7.y, l(-64.000000)
    else
      mov r1.w, l(0.000977)
      mov r7.y, l(0)
    endif
  endif
  mul r8.w, r1.w, r18.y
  mad r7.y, r8.w, l(261120.000000), r7.y
  mul r1.w, r1.w, r7.y
  round_z r1.w, r1.w
  add r1.w, r1.w, r7.y
  mul r18.y, r1.w, l(0.000978)
  if_nz r11.z
    ge r1.w, r18.z, l(0.752941)
    if_nz r1.w
      mov r1.w, l(0.007812)
      mov r7.y, l(-1024.000000)
    else
      mov r1.w, l(0.003906)
      mov r7.y, l(-256.000000)
    endif
  else
    ge r8.w, r18.z, l(0.250980)
    if_nz r8.w
      mov r1.w, l(0.001953)
      mov r7.y, l(-64.000000)
    else
      mov r1.w, l(0.000977)
      mov r7.y, l(0)
    endif
  endif
  mul r8.w, r1.w, r18.z
  mad r7.y, r8.w, l(261120.000000), r7.y
  mul r1.w, r1.w, r7.y
  round_z r1.w, r1.w
  add r1.w, r1.w, r7.y
  mul r18.z, r1.w, l(0.000978)
  if_nz r11.w
    ge r1.w, r18.w, l(0.752941)
    if_nz r1.w
      mov r1.w, l(0.007812)
      mov r7.y, l(-1024.000000)
    else
      mov r1.w, l(0.003906)
      mov r7.y, l(-256.000000)
    endif
  else
    ge r8.w, r18.w, l(0.250980)
    if_nz r8.w
      mov r1.w, l(0.001953)
      mov r7.y, l(-64.000000)
    else
      mov r1.w, l(0.000977)
      mov r7.y, l(0)
    endif
  endif
  mul r8.w, r1.w, r18.w
  mad r7.y, r8.w, l(261120.000000), r7.y
  mul r1.w, r1.w, r7.y
  round_z r1.w, r1.w
  add r1.w, r1.w, r7.y
  mul r18.w, r1.w, l(0.000978)
  mov_sat r15.xyzw, r15.xyzw
  ge r11.xyzw, r15.xyzw, l(0.376471, 0.376471, 0.376471, 0.376471)
  if_nz r11.x
    ge r1.w, r15.x, l(0.752941)
    if_nz r1.w
      mov r1.w, l(0.007812)
      mov r7.y, l(-1024.000000)
    else
      mov r1.w, l(0.003906)
      mov r7.y, l(-256.000000)
    endif
  else
    ge r8.w, r15.x, l(0.250980)
    if_nz r8.w
      mov r1.w, l(0.001953)
      mov r7.y, l(-64.000000)
    else
      mov r1.w, l(0.000977)
      mov r7.y, l(0)
    endif
  endif
  mul r8.w, r1.w, r15.x
  mad r7.y, r8.w, l(261120.000000), r7.y
  mul r1.w, r1.w, r7.y
  round_z r1.w, r1.w
  add r1.w, r1.w, r7.y
  mul r15.x, r1.w, l(0.000978)
  if_nz r11.y
    ge r1.w, r15.y, l(0.752941)
    if_nz r1.w
      mov r1.w, l(0.007812)
      mov r7.y, l(-1024.000000)
    else
      mov r1.w, l(0.003906)
      mov r7.y, l(-256.000000)
    endif
  else
    ge r8.w, r15.y, l(0.250980)
    if_nz r8.w
      mov r1.w, l(0.001953)
      mov r7.y, l(-64.000000)
    else
      mov r1.w, l(0.000977)
      mov r7.y, l(0)
    endif
  endif
  mul r8.w, r1.w, r15.y
  mad r7.y, r8.w, l(261120.000000), r7.y
  mul r1.w, r1.w, r7.y
  round_z r1.w, r1.w
  add r1.w, r1.w, r7.y
  mul r15.y, r1.w, l(0.000978)
  if_nz r11.z
    ge r1.w, r15.z, l(0.752941)
    if_nz r1.w
      mov r1.w, l(0.007812)
      mov r7.y, l(-1024.000000)
    else
      mov r1.w, l(0.003906)
      mov r7.y, l(-256.000000)
    endif
  else
    ge r8.w, r15.z, l(0.250980)
    if_nz r8.w
      mov r1.w, l(0.001953)
      mov r7.y, l(-64.000000)
    else
      mov r1.w, l(0.000977)
      mov r7.y, l(0)
    endif
  endif
  mul r8.w, r1.w, r15.z
  mad r7.y, r8.w, l(261120.000000), r7.y
  mul r1.w, r1.w, r7.y
  round_z r1.w, r1.w
  add r1.w, r1.w, r7.y
  mul r15.z, r1.w, l(0.000978)
  if_nz r11.w
    ge r1.w, r15.w, l(0.752941)
    if_nz r1.w
      mov r1.w, l(0.007812)
      mov r7.y, l(-1024.000000)
    else
      mov r1.w, l(0.003906)
      mov r7.y, l(-256.000000)
    endif
  else
    ge r8.w, r15.w, l(0.250980)
    if_nz r8.w
      mov r1.w, l(0.001953)
      mov r7.y, l(-64.000000)
    else
      mov r1.w, l(0.000977)
      mov r7.y, l(0)
    endif
  endif
  mul r8.w, r1.w, r15.w
  mad r7.y, r8.w, l(261120.000000), r7.y
  mul r1.w, r1.w, r7.y
  round_z r1.w, r1.w
  add r1.w, r1.w, r7.y
  mul r15.w, r1.w, l(0.000978)
endif
uge r1.w, r5.z, l(4)
if_nz r1.w
  mul r1.w, r0.y, l(0.500000)
  or r11.x, r7.x, l(1)
  if_nz r8.z
    ushr r11.y, r7.x, l(1)
    ishl r19.xy, r8.xyxx, l(1, 1, 0, 0)
    and r19.xy, r19.xyxx, l(-4, -4, 0, 0)
    bfi r19.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r8.xyxx, r19.xyxx
    bfi r19.zw, l(0, 0, 1, 31), l(0, 0, 1, 1), r11.xxxy, l(0, 0, 0, 0)
    iadd r19.xy, r19.zwzz, r19.xyxx
  else
    ieq r7.y, r4.x, l(1)
    if_nz r7.y
      and r19.zw, r8.xxxx, l(0, 0, -3, 2)
      iadd r19.x, r19.z, l(2)
      ishl r7.y, r8.y, l(1)
      and r7.y, r7.y, l(-4)
      bfi r7.y, l(1), l(0), r8.y, r7.y
      iadd r19.y, r19.w, r7.y
    else
      mov r19.xy, r8.xyxx
    endif
  endif
  imad r19.xy, r19.xyxx, r2.xyxx, r6.ywyy
  udiv r19.zw, null, r19.xxxy, r10.xxxz
  imad r7.y, r19.w, r0.x, r19.z
  iadd r7.y, r4.y, r7.y
  imad r19.xy, -r19.zwzz, r10.xzxx, r19.xyxx
  imad r8.w, r19.y, r10.x, r19.x
  ishl r8.w, r8.w, r4.w
  imad r7.y, r7.y, r9.z, r8.w
  udiv null, r19.x, r7.y, r9.x
  if_nz r8.z
    ushr r11.z, r7.x, l(1)
    ishl r20.xy, r10.ywyy, l(1, 1, 0, 0)
    and r20.xy, r20.xyxx, l(-4, -4, 0, 0)
    bfi r20.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r10.ywyy, r20.xyxx
    bfi r20.zw, l(0, 0, 1, 31), l(0, 0, 1, 1), r11.xxxz, l(0, 0, 0, 0)
    iadd r20.xy, r20.zwzz, r20.xyxx
  else
    ieq r7.y, r4.x, l(1)
    if_nz r7.y
      and r20.zw, r10.yyyy, l(0, 0, -3, 2)
      iadd r20.x, r20.z, l(2)
      ishl r7.y, r10.w, l(1)
      and r7.y, r7.y, l(-4)
      bfi r7.y, l(1), l(0), r10.w, r7.y
      iadd r20.y, r20.w, r7.y
    else
      mov r20.xy, r10.ywyy
    endif
  endif
  imad r20.xy, r20.xyxx, r2.xyxx, r9.ywyy
  udiv r20.zw, null, r20.xxxy, r10.xxxz
  imad r7.y, r20.w, r0.x, r20.z
  iadd r7.y, r4.y, r7.y
  imad r20.xy, -r20.zwzz, r10.xzxx, r20.xyxx
  imad r8.w, r20.y, r10.x, r20.x
  ishl r8.w, r8.w, r4.w
  imad r7.y, r7.y, r9.z, r8.w
  udiv null, r19.y, r7.y, r9.x
  if_nz r8.z
    ushr r11.w, r7.x, l(1)
    ishl r20.xy, r12.zwzz, l(1, 1, 0, 0)
    and r20.xy, r20.xyxx, l(-4, -4, 0, 0)
    bfi r20.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r12.zwzz, r20.xyxx
    bfi r11.zw, l(0, 0, 1, 31), l(0, 0, 1, 1), r11.xxxw, l(0, 0, 0, 0)
    iadd r11.zw, r11.zzzw, r20.xxxy
  else
    ieq r7.y, r4.x, l(1)
    if_nz r7.y
      and r20.xy, r12.zzzz, l(-3, 2, 0, 0)
      iadd r11.z, r20.x, l(2)
      ishl r7.y, r12.w, l(1)
      and r7.y, r7.y, l(-4)
      bfi r7.y, l(1), l(0), r12.w, r7.y
      iadd r11.w, r20.y, r7.y
    else
      mov r11.zw, r12.zzzw
    endif
  endif
  imad r11.zw, r11.zzzw, r2.xxxy, r12.xxxy
  udiv r20.xy, null, r11.zwzz, r10.xzxx
  imad r7.y, r20.y, r0.x, r20.x
  iadd r7.y, r4.y, r7.y
  imad r11.zw, -r20.xxxy, r10.xxxz, r11.zzzw
  imad r8.w, r11.w, r10.x, r11.z
  ishl r8.w, r8.w, r4.w
  imad r7.y, r7.y, r9.z, r8.w
  udiv null, r19.z, r7.y, r9.x
  if_nz r8.z
    ushr r11.y, r7.x, l(1)
    ishl r11.zw, r13.xxxy, l(0, 0, 1, 1)
    and r11.zw, r11.zzzw, l(0, 0, -4, -4)
    bfi r11.zw, l(0, 0, 1, 1), l(0, 0, 0, 0), r13.xxxy, r11.zzzw
    bfi r20.xy, l(1, 31, 0, 0), l(1, 1, 0, 0), r11.xyxx, l(0, 0, 0, 0)
    iadd r11.zw, r11.zzzw, r20.xxxy
  else
    ieq r7.y, r4.x, l(1)
    if_nz r7.y
      and r20.xy, r13.xxxx, l(-3, 2, 0, 0)
      iadd r11.z, r20.x, l(2)
      ishl r7.y, r13.y, l(1)
      and r7.y, r7.y, l(-4)
      bfi r7.y, l(1), l(0), r13.y, r7.y
      iadd r11.w, r20.y, r7.y
    else
      mov r11.zw, r13.xxxy
    endif
  endif
  imad r11.zw, r11.zzzw, r2.xxxy, r7.zzzw
  udiv r20.xy, null, r11.zwzz, r10.xzxx
  imad r7.y, r20.y, r0.x, r20.x
  iadd r7.y, r4.y, r7.y
  imad r11.zw, -r20.xxxy, r10.xxxz, r11.zzzw
  imad r8.w, r11.w, r10.x, r11.z
  ishl r8.w, r8.w, r4.w
  imad r7.y, r7.y, r9.z, r8.w
  udiv null, r19.w, r7.y, r9.x
  iadd r19.xyzw, r0.wwww, r19.xyzw
  if_nz r8.z
    ushr r11.y, r7.x, l(1)
    ishl r11.zw, r14.xxxy, l(0, 0, 1, 1)
    and r11.zw, r11.zzzw, l(0, 0, -4, -4)
    bfi r11.zw, l(0, 0, 1, 1), l(0, 0, 0, 0), r14.xxxy, r11.zzzw
    bfi r20.xy, l(1, 31, 0, 0), l(1, 1, 0, 0), r11.xyxx, l(0, 0, 0, 0)
    iadd r11.zw, r11.zzzw, r20.xxxy
  else
    ieq r7.y, r4.x, l(1)
    if_nz r7.y
      and r20.xy, r14.xxxx, l(-3, 2, 0, 0)
      iadd r11.z, r20.x, l(2)
      ishl r7.y, r14.y, l(1)
      and r7.y, r7.y, l(-4)
      bfi r7.y, l(1), l(0), r14.y, r7.y
      iadd r11.w, r20.y, r7.y
    else
      mov r11.zw, r14.xxxy
    endif
  endif
  imad r11.zw, r11.zzzw, r2.xxxy, r13.zzzw
  udiv r20.xy, null, r11.zwzz, r10.xzxx
  imad r7.y, r20.y, r0.x, r20.x
  iadd r7.y, r4.y, r7.y
  imad r11.zw, -r20.xxxy, r10.xxxz, r11.zzzw
  imad r8.w, r11.w, r10.x, r11.z
  ishl r8.w, r8.w, r4.w
  imad r7.y, r7.y, r9.z, r8.w
  udiv null, r20.x, r7.y, r9.x
  if_nz r8.z
    ushr r11.y, r7.x, l(1)
    ishl r11.zw, r16.xxxy, l(0, 0, 1, 1)
    and r11.zw, r11.zzzw, l(0, 0, -4, -4)
    bfi r11.zw, l(0, 0, 1, 1), l(0, 0, 0, 0), r16.xxxy, r11.zzzw
    bfi r21.xy, l(1, 31, 0, 0), l(1, 1, 0, 0), r11.xyxx, l(0, 0, 0, 0)
    iadd r11.zw, r11.zzzw, r21.xxxy
  else
    ieq r7.y, r4.x, l(1)
    if_nz r7.y
      and r21.xy, r16.xxxx, l(-3, 2, 0, 0)
      iadd r11.z, r21.x, l(2)
      ishl r7.y, r16.y, l(1)
      and r7.y, r7.y, l(-4)
      bfi r7.y, l(1), l(0), r16.y, r7.y
      iadd r11.w, r21.y, r7.y
    else
      mov r11.zw, r16.xxxy
    endif
  endif
  imad r11.zw, r11.zzzw, r2.xxxy, r14.zzzw
  udiv r21.xy, null, r11.zwzz, r10.xzxx
  imad r7.y, r21.y, r0.x, r21.x
  iadd r7.y, r4.y, r7.y
  imad r11.zw, -r21.xxxy, r10.xxxz, r11.zzzw
  imad r8.w, r11.w, r10.x, r11.z
  ishl r8.w, r8.w, r4.w
  imad r7.y, r7.y, r9.z, r8.w
  udiv null, r20.y, r7.y, r9.x
  if_nz r8.z
    ushr r11.y, r7.x, l(1)
    ishl r11.zw, r17.xxxy, l(0, 0, 1, 1)
    and r11.zw, r11.zzzw, l(0, 0, -4, -4)
    bfi r11.zw, l(0, 0, 1, 1), l(0, 0, 0, 0), r17.xxxy, r11.zzzw
    bfi r21.xy, l(1, 31, 0, 0), l(1, 1, 0, 0), r11.xyxx, l(0, 0, 0, 0)
    iadd r11.zw, r11.zzzw, r21.xxxy
  else
    ieq r7.y, r4.x, l(1)
    if_nz r7.y
      and r21.xy, r17.xxxx, l(-3, 2, 0, 0)
      iadd r11.z, r21.x, l(2)
      ishl r7.y, r17.y, l(1)
      and r7.y, r7.y, l(-4)
      bfi r7.y, l(1), l(0), r17.y, r7.y
      iadd r11.w, r21.y, r7.y
    else
      mov r11.zw, r17.xxxy
    endif
  endif
  imad r11.zw, r11.zzzw, r2.xxxy, r16.zzzw
  udiv r21.xy, null, r11.zwzz, r10.xzxx
  imad r7.y, r21.y, r0.x, r21.x
  iadd r7.y, r4.y, r7.y
  imad r11.zw, -r21.xxxy, r10.xxxz, r11.zzzw
  imad r8.w, r11.w, r10.x, r11.z
  ishl r8.w, r8.w, r4.w
  imad r7.y, r7.y, r9.z, r8.w
  udiv null, r20.z, r7.y, r9.x
  if_nz r8.z
    ushr r11.y, r7.x, l(1)
    ishl r7.xy, r17.zwzz, l(1, 1, 0, 0)
    and r7.xy, r7.xyxx, l(-4, -4, 0, 0)
    bfi r7.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r17.zwzz, r7.xyxx
    bfi r11.xy, l(1, 31, 0, 0), l(1, 1, 0, 0), r11.xyxx, l(0, 0, 0, 0)
    iadd r7.xy, r7.xyxx, r11.xyxx
  else
    ieq r8.w, r4.x, l(1)
    if_nz r8.w
      and r11.xy, r17.zzzz, l(-3, 2, 0, 0)
      iadd r7.x, r11.x, l(2)
      ishl r8.w, r17.w, l(1)
      and r8.w, r8.w, l(-4)
      bfi r8.w, l(1), l(0), r17.w, r8.w
      iadd r7.y, r11.y, r8.w
    else
      mov r7.xy, r17.zwzz
    endif
  endif
  imad r7.xy, r7.xyxx, r2.xyxx, r1.yzyy
  udiv r11.xy, null, r7.xyxx, r10.xzxx
  imad r8.w, r11.y, r0.x, r11.x
  iadd r8.w, r4.y, r8.w
  imad r7.xy, -r11.xyxx, r10.xzxx, r7.xyxx
  imad r7.x, r7.y, r10.x, r7.x
  ishl r7.x, r7.x, r4.w
  imad r7.x, r8.w, r9.z, r7.x
  udiv null, r20.w, r7.x, r9.x
  iadd r11.xyzw, r0.wwww, r20.xyzw
  ishl r19.xyzw, r19.xyzw, l(2, 2, 2, 2)
  ld_raw r20.x, r19.x, T0[0].xxxx
  ld_raw r20.y, r19.y, T0[0].xxxx
  ld_raw r20.z, r19.z, T0[0].xxxx
  ld_raw r20.w, r19.w, T0[0].xxxx
  ishl r11.xyzw, r11.xyzw, l(2, 2, 2, 2)
  ld_raw r19.x, r11.x, T0[0].xxxx
  ld_raw r19.y, r11.y, T0[0].xxxx
  ld_raw r19.z, r11.z, T0[0].xxxx
  ld_raw r19.w, r11.w, T0[0].xxxx
  if_nz r4.w
    switch r4.z
      case l(5)
      and r7.x, r2.w, l(16)
      ushr r11.xyzw, r20.xyzw, r7.xxxx
      ibfe r11.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r11.xyzw
      itof r11.xyzw, r11.xyzw
      mul r11.xyzw, r11.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
      max r20.xyzw, r11.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
      ushr r11.xyzw, r19.xyzw, r7.xxxx
      ibfe r11.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r11.xyzw
      itof r11.xyzw, r11.xyzw
      mul r11.xyzw, r11.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
      max r19.xyzw, r11.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
      break
      case l(7)
      if_nz r2.w
        ushr r11.xyzw, r20.xyzw, l(16, 16, 16, 16)
        f16tof32 r20.xyzw, r11.xyzw
        ushr r11.xyzw, r19.xyzw, l(16, 16, 16, 16)
        f16tof32 r19.xyzw, r11.xyzw
      else
        f16tof32 r20.xyzw, r20.xyzw
        f16tof32 r19.xyzw, r19.xyzw
      endif
      break
      default
      if_nz r2.w
        mov r20.xyzw, l(1.000000,1.000000,1.000000,1.000000)
        mov r19.xyzw, l(1.000000,1.000000,1.000000,1.000000)
      endif
      break
    endswitch
  else
    switch r4.z
      case l(0)
      case l(1)
      and r7.x, r5.x, l(16)
      movc r7.x, r2.w, l(24), r7.x
      ushr r11.xyzw, r20.xyzw, r7.xxxx
      and r11.xyzw, r11.xyzw, l(255, 255, 255, 255)
      utof r11.xyzw, r11.xyzw
      mul r20.xyzw, r11.xyzw, l(0.003922, 0.003922, 0.003922, 0.003922)
      ushr r11.xyzw, r19.xyzw, r7.xxxx
      and r11.xyzw, r11.xyzw, l(255, 255, 255, 255)
      utof r11.xyzw, r11.xyzw
      mul r19.xyzw, r11.xyzw, l(0.003922, 0.003922, 0.003922, 0.003922)
      break
      case l(2)
      case l(10)
      case l(3)
      case l(12)
      if_nz r2.w
        ushr r11.xyzw, r20.xyzw, l(30, 30, 30, 30)
        utof r11.xyzw, r11.xyzw
        mul r20.xyzw, r11.xyzw, l(0.333333, 0.333333, 0.333333, 0.333333)
        ushr r11.xyzw, r19.xyzw, l(30, 30, 30, 30)
        utof r11.xyzw, r11.xyzw
        mul r19.xyzw, r11.xyzw, l(0.333333, 0.333333, 0.333333, 0.333333)
      else
        and r7.x, r5.x, l(20)
        ieq r11.xy, r4.zzzz, l(2, 10, 0, 0)
        or r7.y, r11.y, r11.x
        if_nz r7.y
          ushr r11.xyzw, r20.xyzw, r7.xxxx
          and r11.xyzw, r11.xyzw, l(1023, 1023, 1023, 1023)
          utof r11.xyzw, r11.xyzw
          mul r20.xyzw, r11.xyzw, l(0.000978, 0.000978, 0.000978, 0.000978)
          ushr r11.xyzw, r19.xyzw, r7.xxxx
          and r11.xyzw, r11.xyzw, l(1023, 1023, 1023, 1023)
          utof r11.xyzw, r11.xyzw
          mul r19.xyzw, r11.xyzw, l(0.000978, 0.000978, 0.000978, 0.000978)
        else
          ushr r11.xyzw, r20.xyzw, r7.xxxx
          and r21.xyzw, r11.xyzw, l(1023, 1023, 1023, 1023)
          and r22.xyzw, r11.xyzw, l(127, 127, 127, 127)
          ubfe r23.xyzw, l(3, 3, 3, 3), l(7, 7, 7, 7), r11.xyzw
          firstbit_hi r24.xyzw, r22.xyzw
          iadd r24.xyzw, r24.xyzw, l(-24, -24, -24, -24)
          movc r24.xyzw, r22.xyzw, r24.xyzw, l(8,8,8,8)
          iadd r25.xyzw, -r24.xyzw, l(1, 1, 1, 1)
          movc r25.xyzw, r23.xyzw, r23.xyzw, r25.xyzw
          bfi r11.xyzw, l(7, 7, 7, 7), r24.xyzw, r11.xyzw, l(0, 0, 0, 0)
          and r11.xyzw, r11.xyzw, l(127, 127, 127, 127)
          movc r11.xyzw, r23.xyzw, r22.xyzw, r11.xyzw
          ishl r22.xyzw, r25.xyzw, l(23, 23, 23, 23)
          iadd r22.xyzw, r22.xyzw, l(0x3e000000, 0x3e000000, 0x3e000000, 0x3e000000)
          ishl r11.xyzw, r11.xyzw, l(16, 16, 16, 16)
          iadd r11.xyzw, r22.xyzw, r11.xyzw
          movc r20.xyzw, r21.xyzw, r11.xyzw, l(0,0,0,0)
          ushr r11.xyzw, r19.xyzw, r7.xxxx
          and r21.xyzw, r11.xyzw, l(1023, 1023, 1023, 1023)
          and r22.xyzw, r11.xyzw, l(127, 127, 127, 127)
          ubfe r23.xyzw, l(3, 3, 3, 3), l(7, 7, 7, 7), r11.xyzw
          firstbit_hi r24.xyzw, r22.xyzw
          iadd r24.xyzw, r24.xyzw, l(-24, -24, -24, -24)
          movc r24.xyzw, r22.xyzw, r24.xyzw, l(8,8,8,8)
          iadd r25.xyzw, -r24.xyzw, l(1, 1, 1, 1)
          movc r25.xyzw, r23.xyzw, r23.xyzw, r25.xyzw
          bfi r11.xyzw, l(7, 7, 7, 7), r24.xyzw, r11.xyzw, l(0, 0, 0, 0)
          and r11.xyzw, r11.xyzw, l(127, 127, 127, 127)
          movc r11.xyzw, r23.xyzw, r22.xyzw, r11.xyzw
          ishl r22.xyzw, r25.xyzw, l(23, 23, 23, 23)
          iadd r22.xyzw, r22.xyzw, l(0x3e000000, 0x3e000000, 0x3e000000, 0x3e000000)
          ishl r11.xyzw, r11.xyzw, l(16, 16, 16, 16)
          iadd r11.xyzw, r22.xyzw, r11.xyzw
          movc r19.xyzw, r21.xyzw, r11.xyzw, l(0,0,0,0)
        endif
      endif
      break
      case l(4)
      if_nz r2.w
        mov r20.xyzw, l(1.000000,1.000000,1.000000,1.000000)
        mov r19.xyzw, l(1.000000,1.000000,1.000000,1.000000)
      else
        ibfe r11.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r20.xyzw
        itof r11.xyzw, r11.xyzw
        mul r11.xyzw, r11.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
        max r20.xyzw, r11.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
        ibfe r11.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r19.xyzw
        itof r11.xyzw, r11.xyzw
        mul r11.xyzw, r11.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
        max r19.xyzw, r11.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
      endif
      break
      case l(6)
      if_nz r2.w
        mov r20.xyzw, l(1.000000,1.000000,1.000000,1.000000)
        mov r19.xyzw, l(1.000000,1.000000,1.000000,1.000000)
      else
        f16tof32 r20.xyzw, r20.xyzw
        f16tof32 r19.xyzw, r19.xyzw
      endif
      break
      default
      if_nz r2.w
        mov r20.xyzw, l(1.000000,1.000000,1.000000,1.000000)
        mov r19.xyzw, l(1.000000,1.000000,1.000000,1.000000)
      endif
      break
    endswitch
  endif
  if_nz r3.w
    mov_sat r20.xyzw, r20.xyzw
    ge r11.xyzw, r20.xyzw, l(0.376471, 0.376471, 0.376471, 0.376471)
    if_nz r11.x
      ge r7.x, r20.x, l(0.752941)
      if_nz r7.x
        mov r7.xy, l(0.007812,-1024.000000,0,0)
      else
        mov r7.xy, l(0.003906,-256.000000,0,0)
      endif
    else
      ge r8.w, r20.x, l(0.250980)
      if_nz r8.w
        mov r7.xy, l(0.001953,-64.000000,0,0)
      else
        mov r7.xy, l(0.000977,0,0,0)
      endif
    endif
    mul r8.w, r7.x, r20.x
    mad r7.y, r8.w, l(261120.000000), r7.y
    mul r7.x, r7.x, r7.y
    round_z r7.x, r7.x
    add r7.x, r7.x, r7.y
    mul r20.x, r7.x, l(0.000978)
    if_nz r11.y
      ge r7.x, r20.y, l(0.752941)
      if_nz r7.x
        mov r7.xy, l(0.007812,-1024.000000,0,0)
      else
        mov r7.xy, l(0.003906,-256.000000,0,0)
      endif
    else
      ge r8.w, r20.y, l(0.250980)
      if_nz r8.w
        mov r7.xy, l(0.001953,-64.000000,0,0)
      else
        mov r7.xy, l(0.000977,0,0,0)
      endif
    endif
    mul r8.w, r7.x, r20.y
    mad r7.y, r8.w, l(261120.000000), r7.y
    mul r7.x, r7.x, r7.y
    round_z r7.x, r7.x
    add r7.x, r7.x, r7.y
    mul r20.y, r7.x, l(0.000978)
    if_nz r11.z
      ge r7.x, r20.z, l(0.752941)
      if_nz r7.x
        mov r7.xy, l(0.007812,-1024.000000,0,0)
      else
        mov r7.xy, l(0.003906,-256.000000,0,0)
      endif
    else
      ge r8.w, r20.z, l(0.250980)
      if_nz r8.w
        mov r7.xy, l(0.001953,-64.000000,0,0)
      else
        mov r7.xy, l(0.000977,0,0,0)
      endif
    endif
    mul r8.w, r7.x, r20.z
    mad r7.y, r8.w, l(261120.000000), r7.y
    mul r7.x, r7.x, r7.y
    round_z r7.x, r7.x
    add r7.x, r7.x, r7.y
    mul r20.z, r7.x, l(0.000978)
    if_nz r11.w
      ge r7.x, r20.w, l(0.752941)
      if_nz r7.x
        mov r7.xy, l(0.007812,-1024.000000,0,0)
      else
        mov r7.xy, l(0.003906,-256.000000,0,0)
      endif
    else
      ge r8.w, r20.w, l(0.250980)
      if_nz r8.w
        mov r7.xy, l(0.001953,-64.000000,0,0)
      else
        mov r7.xy, l(0.000977,0,0,0)
      endif
    endif
    mul r8.w, r7.x, r20.w
    mad r7.y, r8.w, l(261120.000000), r7.y
    mul r7.x, r7.x, r7.y
    round_z r7.x, r7.x
    add r7.x, r7.x, r7.y
    mul r20.w, r7.x, l(0.000978)
    mov_sat r19.xyzw, r19.xyzw
    ge r11.xyzw, r19.xyzw, l(0.376471, 0.376471, 0.376471, 0.376471)
    if_nz r11.x
      ge r7.x, r19.x, l(0.752941)
      if_nz r7.x
        mov r7.xy, l(0.007812,-1024.000000,0,0)
      else
        mov r7.xy, l(0.003906,-256.000000,0,0)
      endif
    else
      ge r8.w, r19.x, l(0.250980)
      if_nz r8.w
        mov r7.xy, l(0.001953,-64.000000,0,0)
      else
        mov r7.xy, l(0.000977,0,0,0)
      endif
    endif
    mul r8.w, r7.x, r19.x
    mad r7.y, r8.w, l(261120.000000), r7.y
    mul r7.x, r7.x, r7.y
    round_z r7.x, r7.x
    add r7.x, r7.x, r7.y
    mul r19.x, r7.x, l(0.000978)
    if_nz r11.y
      ge r7.x, r19.y, l(0.752941)
      if_nz r7.x
        mov r7.xy, l(0.007812,-1024.000000,0,0)
      else
        mov r7.xy, l(0.003906,-256.000000,0,0)
      endif
    else
      ge r8.w, r19.y, l(0.250980)
      if_nz r8.w
        mov r7.xy, l(0.001953,-64.000000,0,0)
      else
        mov r7.xy, l(0.000977,0,0,0)
      endif
    endif
    mul r8.w, r7.x, r19.y
    mad r7.y, r8.w, l(261120.000000), r7.y
    mul r7.x, r7.x, r7.y
    round_z r7.x, r7.x
    add r7.x, r7.x, r7.y
    mul r19.y, r7.x, l(0.000978)
    if_nz r11.z
      ge r7.x, r19.z, l(0.752941)
      if_nz r7.x
        mov r7.xy, l(0.007812,-1024.000000,0,0)
      else
        mov r7.xy, l(0.003906,-256.000000,0,0)
      endif
    else
      ge r8.w, r19.z, l(0.250980)
      if_nz r8.w
        mov r7.xy, l(0.001953,-64.000000,0,0)
      else
        mov r7.xy, l(0.000977,0,0,0)
      endif
    endif
    mul r8.w, r7.x, r19.z
    mad r7.y, r8.w, l(261120.000000), r7.y
    mul r7.x, r7.x, r7.y
    round_z r7.x, r7.x
    add r7.x, r7.x, r7.y
    mul r19.z, r7.x, l(0.000978)
    if_nz r11.w
      ge r7.x, r19.w, l(0.752941)
      if_nz r7.x
        mov r7.xy, l(0.007812,-1024.000000,0,0)
      else
        mov r7.xy, l(0.003906,-256.000000,0,0)
      endif
    else
      ge r8.w, r19.w, l(0.250980)
      if_nz r8.w
        mov r7.xy, l(0.001953,-64.000000,0,0)
      else
        mov r7.xy, l(0.000977,0,0,0)
      endif
    endif
    mul r8.w, r7.x, r19.w
    mad r7.y, r8.w, l(261120.000000), r7.y
    mul r7.x, r7.x, r7.y
    round_z r7.x, r7.x
    add r7.x, r7.x, r7.y
    mul r19.w, r7.x, l(0.000978)
  endif
  add r18.xyzw, r18.xyzw, r20.xyzw
  add r15.xyzw, r15.xyzw, r19.xyzw
  uge r5.z, r5.z, l(6)
  if_nz r5.z
    mul r0.y, r0.y, l(0.250000)
    if_nz r8.z
      ishl r7.xy, r8.xyxx, l(1, 1, 0, 0)
      and r7.xy, r7.xyxx, l(-4, -4, 0, 0)
      bfi r7.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r8.xyxx, r7.xyxx
      iadd r11.xy, r7.xyxx, l(0, 2, 0, 0)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        ishl r5.z, r8.y, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r8.y, r5.z
        and r11.xz, r8.xxxx, l(-3, 0, 2, 0)
        iadd r11.y, r5.z, r11.z
      else
        mov r11.xy, r8.xyxx
      endif
    endif
    imad r7.xy, r11.xyxx, r2.xyxx, r6.ywyy
    udiv r11.xy, null, r7.xyxx, r10.xzxx
    imad r5.z, r11.y, r0.x, r11.x
    iadd r5.z, r4.y, r5.z
    imad r7.xy, -r11.xyxx, r10.xzxx, r7.xyxx
    imad r7.x, r7.y, r10.x, r7.x
    ishl r7.x, r7.x, r4.w
    imad r5.z, r5.z, r9.z, r7.x
    udiv null, r11.x, r5.z, r9.x
    if_nz r8.z
      ishl r7.xy, r10.ywyy, l(1, 1, 0, 0)
      and r7.xy, r7.xyxx, l(-4, -4, 0, 0)
      bfi r7.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r10.ywyy, r7.xyxx
      iadd r19.xy, r7.xyxx, l(0, 2, 0, 0)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        ishl r5.z, r10.w, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r10.w, r5.z
        and r19.xz, r10.yyyy, l(-3, 0, 2, 0)
        iadd r19.y, r5.z, r19.z
      else
        mov r19.xy, r10.ywyy
      endif
    endif
    imad r7.xy, r19.xyxx, r2.xyxx, r9.ywyy
    udiv r19.xy, null, r7.xyxx, r10.xzxx
    imad r5.z, r19.y, r0.x, r19.x
    iadd r5.z, r4.y, r5.z
    imad r7.xy, -r19.xyxx, r10.xzxx, r7.xyxx
    imad r7.x, r7.y, r10.x, r7.x
    ishl r7.x, r7.x, r4.w
    imad r5.z, r5.z, r9.z, r7.x
    udiv null, r11.y, r5.z, r9.x
    if_nz r8.z
      ishl r7.xy, r12.zwzz, l(1, 1, 0, 0)
      and r7.xy, r7.xyxx, l(-4, -4, 0, 0)
      bfi r7.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r12.zwzz, r7.xyxx
      iadd r19.xy, r7.xyxx, l(0, 2, 0, 0)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        ishl r5.z, r12.w, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r12.w, r5.z
        and r19.xz, r12.zzzz, l(-3, 0, 2, 0)
        iadd r19.y, r5.z, r19.z
      else
        mov r19.xy, r12.zwzz
      endif
    endif
    imad r7.xy, r19.xyxx, r2.xyxx, r12.xyxx
    udiv r19.xy, null, r7.xyxx, r10.xzxx
    imad r5.z, r19.y, r0.x, r19.x
    iadd r5.z, r4.y, r5.z
    imad r7.xy, -r19.xyxx, r10.xzxx, r7.xyxx
    imad r7.x, r7.y, r10.x, r7.x
    ishl r7.x, r7.x, r4.w
    imad r5.z, r5.z, r9.z, r7.x
    udiv null, r11.z, r5.z, r9.x
    if_nz r8.z
      ishl r7.xy, r13.xyxx, l(1, 1, 0, 0)
      and r7.xy, r7.xyxx, l(-4, -4, 0, 0)
      bfi r7.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r13.xyxx, r7.xyxx
      iadd r19.xy, r7.xyxx, l(0, 2, 0, 0)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        ishl r5.z, r13.y, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r13.y, r5.z
        and r19.xz, r13.xxxx, l(-3, 0, 2, 0)
        iadd r19.y, r5.z, r19.z
      else
        mov r19.xy, r13.xyxx
      endif
    endif
    imad r7.xy, r19.xyxx, r2.xyxx, r7.zwzz
    udiv r19.xy, null, r7.xyxx, r10.xzxx
    imad r5.z, r19.y, r0.x, r19.x
    iadd r5.z, r4.y, r5.z
    imad r7.xy, -r19.xyxx, r10.xzxx, r7.xyxx
    imad r7.x, r7.y, r10.x, r7.x
    ishl r7.x, r7.x, r4.w
    imad r5.z, r5.z, r9.z, r7.x
    udiv null, r11.w, r5.z, r9.x
    iadd r11.xyzw, r0.wwww, r11.xyzw
    if_nz r8.z
      ishl r7.xy, r14.xyxx, l(1, 1, 0, 0)
      and r7.xy, r7.xyxx, l(-4, -4, 0, 0)
      bfi r7.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r14.xyxx, r7.xyxx
      iadd r19.xy, r7.xyxx, l(0, 2, 0, 0)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        ishl r5.z, r14.y, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r14.y, r5.z
        and r19.xz, r14.xxxx, l(-3, 0, 2, 0)
        iadd r19.y, r5.z, r19.z
      else
        mov r19.xy, r14.xyxx
      endif
    endif
    imad r7.xy, r19.xyxx, r2.xyxx, r13.zwzz
    udiv r19.xy, null, r7.xyxx, r10.xzxx
    imad r5.z, r19.y, r0.x, r19.x
    iadd r5.z, r4.y, r5.z
    imad r7.xy, -r19.xyxx, r10.xzxx, r7.xyxx
    imad r7.x, r7.y, r10.x, r7.x
    ishl r7.x, r7.x, r4.w
    imad r5.z, r5.z, r9.z, r7.x
    udiv null, r19.x, r5.z, r9.x
    if_nz r8.z
      ishl r7.xy, r16.xyxx, l(1, 1, 0, 0)
      and r7.xy, r7.xyxx, l(-4, -4, 0, 0)
      bfi r7.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r16.xyxx, r7.xyxx
      iadd r20.xy, r7.xyxx, l(0, 2, 0, 0)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        ishl r5.z, r16.y, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r16.y, r5.z
        and r20.xz, r16.xxxx, l(-3, 0, 2, 0)
        iadd r20.y, r5.z, r20.z
      else
        mov r20.xy, r16.xyxx
      endif
    endif
    imad r7.xy, r20.xyxx, r2.xyxx, r14.zwzz
    udiv r20.xy, null, r7.xyxx, r10.xzxx
    imad r5.z, r20.y, r0.x, r20.x
    iadd r5.z, r4.y, r5.z
    imad r7.xy, -r20.xyxx, r10.xzxx, r7.xyxx
    imad r7.x, r7.y, r10.x, r7.x
    ishl r7.x, r7.x, r4.w
    imad r5.z, r5.z, r9.z, r7.x
    udiv null, r19.y, r5.z, r9.x
    if_nz r8.z
      ishl r7.xy, r17.xyxx, l(1, 1, 0, 0)
      and r7.xy, r7.xyxx, l(-4, -4, 0, 0)
      bfi r7.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r17.xyxx, r7.xyxx
      iadd r20.xy, r7.xyxx, l(0, 2, 0, 0)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        ishl r5.z, r17.y, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r17.y, r5.z
        and r20.xz, r17.xxxx, l(-3, 0, 2, 0)
        iadd r20.y, r5.z, r20.z
      else
        mov r20.xy, r17.xyxx
      endif
    endif
    imad r7.xy, r20.xyxx, r2.xyxx, r16.zwzz
    udiv r20.xy, null, r7.xyxx, r10.xzxx
    imad r5.z, r20.y, r0.x, r20.x
    iadd r5.z, r4.y, r5.z
    imad r7.xy, -r20.xyxx, r10.xzxx, r7.xyxx
    imad r7.x, r7.y, r10.x, r7.x
    ishl r7.x, r7.x, r4.w
    imad r5.z, r5.z, r9.z, r7.x
    udiv null, r19.z, r5.z, r9.x
    if_nz r8.z
      ishl r7.xy, r17.zwzz, l(1, 1, 0, 0)
      and r7.xy, r7.xyxx, l(-4, -4, 0, 0)
      bfi r7.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r17.zwzz, r7.xyxx
      iadd r20.xy, r7.xyxx, l(0, 2, 0, 0)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        ishl r5.z, r17.w, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r17.w, r5.z
        and r20.xz, r17.zzzz, l(-3, 0, 2, 0)
        iadd r20.y, r5.z, r20.z
      else
        mov r20.xy, r17.zwzz
      endif
    endif
    imad r7.xy, r20.xyxx, r2.xyxx, r1.yzyy
    udiv r20.xy, null, r7.xyxx, r10.xzxx
    imad r5.z, r20.y, r0.x, r20.x
    iadd r5.z, r4.y, r5.z
    imad r7.xy, -r20.xyxx, r10.xzxx, r7.xyxx
    imad r7.x, r7.y, r10.x, r7.x
    ishl r7.x, r7.x, r4.w
    imad r5.z, r5.z, r9.z, r7.x
    udiv null, r19.w, r5.z, r9.x
    iadd r19.xyzw, r0.wwww, r19.xyzw
    ishl r11.xyzw, r11.xyzw, l(2, 2, 2, 2)
    ld_raw r20.x, r11.x, T0[0].xxxx
    ld_raw r20.y, r11.y, T0[0].xxxx
    ld_raw r20.z, r11.z, T0[0].xxxx
    ld_raw r20.w, r11.w, T0[0].xxxx
    ishl r11.xyzw, r19.xyzw, l(2, 2, 2, 2)
    ld_raw r19.x, r11.x, T0[0].xxxx
    ld_raw r19.y, r11.y, T0[0].xxxx
    ld_raw r19.z, r11.z, T0[0].xxxx
    ld_raw r19.w, r11.w, T0[0].xxxx
    if_nz r4.w
      switch r4.z
        case l(5)
        and r5.z, r2.w, l(16)
        ushr r11.xyzw, r20.xyzw, r5.zzzz
        ibfe r11.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r11.xyzw
        itof r11.xyzw, r11.xyzw
        mul r11.xyzw, r11.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
        max r20.xyzw, r11.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
        ushr r11.xyzw, r19.xyzw, r5.zzzz
        ibfe r11.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r11.xyzw
        itof r11.xyzw, r11.xyzw
        mul r11.xyzw, r11.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
        max r19.xyzw, r11.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
        break
        case l(7)
        if_nz r2.w
          ushr r11.xyzw, r20.xyzw, l(16, 16, 16, 16)
          f16tof32 r20.xyzw, r11.xyzw
          ushr r11.xyzw, r19.xyzw, l(16, 16, 16, 16)
          f16tof32 r19.xyzw, r11.xyzw
        else
          f16tof32 r20.xyzw, r20.xyzw
          f16tof32 r19.xyzw, r19.xyzw
        endif
        break
        default
        if_nz r2.w
          mov r20.xyzw, l(1.000000,1.000000,1.000000,1.000000)
          mov r19.xyzw, l(1.000000,1.000000,1.000000,1.000000)
        endif
        break
      endswitch
    else
      switch r4.z
        case l(0)
        case l(1)
        and r5.z, r5.x, l(16)
        movc r5.z, r2.w, l(24), r5.z
        ushr r11.xyzw, r20.xyzw, r5.zzzz
        and r11.xyzw, r11.xyzw, l(255, 255, 255, 255)
        utof r11.xyzw, r11.xyzw
        mul r20.xyzw, r11.xyzw, l(0.003922, 0.003922, 0.003922, 0.003922)
        ushr r11.xyzw, r19.xyzw, r5.zzzz
        and r11.xyzw, r11.xyzw, l(255, 255, 255, 255)
        utof r11.xyzw, r11.xyzw
        mul r19.xyzw, r11.xyzw, l(0.003922, 0.003922, 0.003922, 0.003922)
        break
        case l(2)
        case l(10)
        case l(3)
        case l(12)
        if_nz r2.w
          ushr r11.xyzw, r20.xyzw, l(30, 30, 30, 30)
          utof r11.xyzw, r11.xyzw
          mul r20.xyzw, r11.xyzw, l(0.333333, 0.333333, 0.333333, 0.333333)
          ushr r11.xyzw, r19.xyzw, l(30, 30, 30, 30)
          utof r11.xyzw, r11.xyzw
          mul r19.xyzw, r11.xyzw, l(0.333333, 0.333333, 0.333333, 0.333333)
        else
          and r5.z, r5.x, l(20)
          ieq r7.xy, r4.zzzz, l(2, 10, 0, 0)
          or r7.x, r7.y, r7.x
          if_nz r7.x
            ushr r11.xyzw, r20.xyzw, r5.zzzz
            and r11.xyzw, r11.xyzw, l(1023, 1023, 1023, 1023)
            utof r11.xyzw, r11.xyzw
            mul r20.xyzw, r11.xyzw, l(0.000978, 0.000978, 0.000978, 0.000978)
            ushr r11.xyzw, r19.xyzw, r5.zzzz
            and r11.xyzw, r11.xyzw, l(1023, 1023, 1023, 1023)
            utof r11.xyzw, r11.xyzw
            mul r19.xyzw, r11.xyzw, l(0.000978, 0.000978, 0.000978, 0.000978)
          else
            ushr r11.xyzw, r20.xyzw, r5.zzzz
            and r21.xyzw, r11.xyzw, l(1023, 1023, 1023, 1023)
            and r22.xyzw, r11.xyzw, l(127, 127, 127, 127)
            ubfe r23.xyzw, l(3, 3, 3, 3), l(7, 7, 7, 7), r11.xyzw
            firstbit_hi r24.xyzw, r22.xyzw
            iadd r24.xyzw, r24.xyzw, l(-24, -24, -24, -24)
            movc r24.xyzw, r22.xyzw, r24.xyzw, l(8,8,8,8)
            iadd r25.xyzw, -r24.xyzw, l(1, 1, 1, 1)
            movc r25.xyzw, r23.xyzw, r23.xyzw, r25.xyzw
            bfi r11.xyzw, l(7, 7, 7, 7), r24.xyzw, r11.xyzw, l(0, 0, 0, 0)
            and r11.xyzw, r11.xyzw, l(127, 127, 127, 127)
            movc r11.xyzw, r23.xyzw, r22.xyzw, r11.xyzw
            ishl r22.xyzw, r25.xyzw, l(23, 23, 23, 23)
            iadd r22.xyzw, r22.xyzw, l(0x3e000000, 0x3e000000, 0x3e000000, 0x3e000000)
            ishl r11.xyzw, r11.xyzw, l(16, 16, 16, 16)
            iadd r11.xyzw, r22.xyzw, r11.xyzw
            movc r20.xyzw, r21.xyzw, r11.xyzw, l(0,0,0,0)
            ushr r11.xyzw, r19.xyzw, r5.zzzz
            and r21.xyzw, r11.xyzw, l(1023, 1023, 1023, 1023)
            and r22.xyzw, r11.xyzw, l(127, 127, 127, 127)
            ubfe r23.xyzw, l(3, 3, 3, 3), l(7, 7, 7, 7), r11.xyzw
            firstbit_hi r24.xyzw, r22.xyzw
            iadd r24.xyzw, r24.xyzw, l(-24, -24, -24, -24)
            movc r24.xyzw, r22.xyzw, r24.xyzw, l(8,8,8,8)
            iadd r25.xyzw, -r24.xyzw, l(1, 1, 1, 1)
            movc r25.xyzw, r23.xyzw, r23.xyzw, r25.xyzw
            bfi r11.xyzw, l(7, 7, 7, 7), r24.xyzw, r11.xyzw, l(0, 0, 0, 0)
            and r11.xyzw, r11.xyzw, l(127, 127, 127, 127)
            movc r11.xyzw, r23.xyzw, r22.xyzw, r11.xyzw
            ishl r22.xyzw, r25.xyzw, l(23, 23, 23, 23)
            iadd r22.xyzw, r22.xyzw, l(0x3e000000, 0x3e000000, 0x3e000000, 0x3e000000)
            ishl r11.xyzw, r11.xyzw, l(16, 16, 16, 16)
            iadd r11.xyzw, r22.xyzw, r11.xyzw
            movc r19.xyzw, r21.xyzw, r11.xyzw, l(0,0,0,0)
          endif
        endif
        break
        case l(4)
        if_nz r2.w
          mov r20.xyzw, l(1.000000,1.000000,1.000000,1.000000)
          mov r19.xyzw, l(1.000000,1.000000,1.000000,1.000000)
        else
          ibfe r11.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r20.xyzw
          itof r11.xyzw, r11.xyzw
          mul r11.xyzw, r11.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
          max r20.xyzw, r11.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
          ibfe r11.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r19.xyzw
          itof r11.xyzw, r11.xyzw
          mul r11.xyzw, r11.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
          max r19.xyzw, r11.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
        endif
        break
        case l(6)
        if_nz r2.w
          mov r20.xyzw, l(1.000000,1.000000,1.000000,1.000000)
          mov r19.xyzw, l(1.000000,1.000000,1.000000,1.000000)
        else
          f16tof32 r20.xyzw, r20.xyzw
          f16tof32 r19.xyzw, r19.xyzw
        endif
        break
        default
        if_nz r2.w
          mov r20.xyzw, l(1.000000,1.000000,1.000000,1.000000)
          mov r19.xyzw, l(1.000000,1.000000,1.000000,1.000000)
        endif
        break
      endswitch
    endif
    if_nz r3.w
      mov_sat r20.xyzw, r20.xyzw
      ge r11.xyzw, r20.xyzw, l(0.376471, 0.376471, 0.376471, 0.376471)
      if_nz r11.x
        ge r5.z, r20.x, l(0.752941)
        if_nz r5.z
          mov r5.z, l(0.007812)
          mov r7.x, l(-1024.000000)
        else
          mov r5.z, l(0.003906)
          mov r7.x, l(-256.000000)
        endif
      else
        ge r7.y, r20.x, l(0.250980)
        if_nz r7.y
          mov r5.z, l(0.001953)
          mov r7.x, l(-64.000000)
        else
          mov r5.z, l(0.000977)
          mov r7.x, l(0)
        endif
      endif
      mul r7.y, r5.z, r20.x
      mad r7.x, r7.y, l(261120.000000), r7.x
      mul r5.z, r5.z, r7.x
      round_z r5.z, r5.z
      add r5.z, r5.z, r7.x
      mul r20.x, r5.z, l(0.000978)
      if_nz r11.y
        ge r5.z, r20.y, l(0.752941)
        if_nz r5.z
          mov r5.z, l(0.007812)
          mov r7.x, l(-1024.000000)
        else
          mov r5.z, l(0.003906)
          mov r7.x, l(-256.000000)
        endif
      else
        ge r7.y, r20.y, l(0.250980)
        if_nz r7.y
          mov r5.z, l(0.001953)
          mov r7.x, l(-64.000000)
        else
          mov r5.z, l(0.000977)
          mov r7.x, l(0)
        endif
      endif
      mul r7.y, r5.z, r20.y
      mad r7.x, r7.y, l(261120.000000), r7.x
      mul r5.z, r5.z, r7.x
      round_z r5.z, r5.z
      add r5.z, r5.z, r7.x
      mul r20.y, r5.z, l(0.000978)
      if_nz r11.z
        ge r5.z, r20.z, l(0.752941)
        if_nz r5.z
          mov r5.z, l(0.007812)
          mov r7.x, l(-1024.000000)
        else
          mov r5.z, l(0.003906)
          mov r7.x, l(-256.000000)
        endif
      else
        ge r7.y, r20.z, l(0.250980)
        if_nz r7.y
          mov r5.z, l(0.001953)
          mov r7.x, l(-64.000000)
        else
          mov r5.z, l(0.000977)
          mov r7.x, l(0)
        endif
      endif
      mul r7.y, r5.z, r20.z
      mad r7.x, r7.y, l(261120.000000), r7.x
      mul r5.z, r5.z, r7.x
      round_z r5.z, r5.z
      add r5.z, r5.z, r7.x
      mul r20.z, r5.z, l(0.000978)
      if_nz r11.w
        ge r5.z, r20.w, l(0.752941)
        if_nz r5.z
          mov r5.z, l(0.007812)
          mov r7.x, l(-1024.000000)
        else
          mov r5.z, l(0.003906)
          mov r7.x, l(-256.000000)
        endif
      else
        ge r7.y, r20.w, l(0.250980)
        if_nz r7.y
          mov r5.z, l(0.001953)
          mov r7.x, l(-64.000000)
        else
          mov r5.z, l(0.000977)
          mov r7.x, l(0)
        endif
      endif
      mul r7.y, r5.z, r20.w
      mad r7.x, r7.y, l(261120.000000), r7.x
      mul r5.z, r5.z, r7.x
      round_z r5.z, r5.z
      add r5.z, r5.z, r7.x
      mul r20.w, r5.z, l(0.000978)
      mov_sat r19.xyzw, r19.xyzw
      ge r11.xyzw, r19.xyzw, l(0.376471, 0.376471, 0.376471, 0.376471)
      if_nz r11.x
        ge r5.z, r19.x, l(0.752941)
        if_nz r5.z
          mov r5.z, l(0.007812)
          mov r7.x, l(-1024.000000)
        else
          mov r5.z, l(0.003906)
          mov r7.x, l(-256.000000)
        endif
      else
        ge r7.y, r19.x, l(0.250980)
        if_nz r7.y
          mov r5.z, l(0.001953)
          mov r7.x, l(-64.000000)
        else
          mov r5.z, l(0.000977)
          mov r7.x, l(0)
        endif
      endif
      mul r7.y, r5.z, r19.x
      mad r7.x, r7.y, l(261120.000000), r7.x
      mul r5.z, r5.z, r7.x
      round_z r5.z, r5.z
      add r5.z, r5.z, r7.x
      mul r19.x, r5.z, l(0.000978)
      if_nz r11.y
        ge r5.z, r19.y, l(0.752941)
        if_nz r5.z
          mov r5.z, l(0.007812)
          mov r7.x, l(-1024.000000)
        else
          mov r5.z, l(0.003906)
          mov r7.x, l(-256.000000)
        endif
      else
        ge r7.y, r19.y, l(0.250980)
        if_nz r7.y
          mov r5.z, l(0.001953)
          mov r7.x, l(-64.000000)
        else
          mov r5.z, l(0.000977)
          mov r7.x, l(0)
        endif
      endif
      mul r7.y, r5.z, r19.y
      mad r7.x, r7.y, l(261120.000000), r7.x
      mul r5.z, r5.z, r7.x
      round_z r5.z, r5.z
      add r5.z, r5.z, r7.x
      mul r19.y, r5.z, l(0.000978)
      if_nz r11.z
        ge r5.z, r19.z, l(0.752941)
        if_nz r5.z
          mov r5.z, l(0.007812)
          mov r7.x, l(-1024.000000)
        else
          mov r5.z, l(0.003906)
          mov r7.x, l(-256.000000)
        endif
      else
        ge r7.y, r19.z, l(0.250980)
        if_nz r7.y
          mov r5.z, l(0.001953)
          mov r7.x, l(-64.000000)
        else
          mov r5.z, l(0.000977)
          mov r7.x, l(0)
        endif
      endif
      mul r7.y, r5.z, r19.z
      mad r7.x, r7.y, l(261120.000000), r7.x
      mul r5.z, r5.z, r7.x
      round_z r5.z, r5.z
      add r5.z, r5.z, r7.x
      mul r19.z, r5.z, l(0.000978)
      if_nz r11.w
        ge r5.z, r19.w, l(0.752941)
        if_nz r5.z
          mov r5.z, l(0.007812)
          mov r7.x, l(-1024.000000)
        else
          mov r5.z, l(0.003906)
          mov r7.x, l(-256.000000)
        endif
      else
        ge r7.y, r19.w, l(0.250980)
        if_nz r7.y
          mov r5.z, l(0.001953)
          mov r7.x, l(-64.000000)
        else
          mov r5.z, l(0.000977)
          mov r7.x, l(0)
        endif
      endif
      mul r7.y, r5.z, r19.w
      mad r7.x, r7.y, l(261120.000000), r7.x
      mul r5.z, r5.z, r7.x
      round_z r5.z, r5.z
      add r5.z, r5.z, r7.x
      mul r19.w, r5.z, l(0.000978)
    endif
    add r11.xyzw, r18.xyzw, r20.xyzw
    add r19.xyzw, r15.xyzw, r19.xyzw
    if_nz r8.z
      ishl r7.xy, r8.xyxx, l(1, 1, 0, 0)
      and r7.xy, r7.xyxx, l(-4, -4, 0, 0)
      bfi r7.xy, l(1, 1, 0, 0), l(0, 0, 0, 0), r8.xyxx, r7.xyxx
      iadd r8.xy, r7.xyxx, l(2, 2, 0, 0)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        and r7.xy, r8.xxxx, l(-3, 2, 0, 0)
        iadd r8.x, r7.x, l(2)
        ishl r5.z, r8.y, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r8.y, r5.z
        iadd r8.y, r7.y, r5.z
      endif
    endif
    imad r6.yw, r8.xxxy, r2.xxxy, r6.yyyw
    udiv r7.xy, null, r6.ywyy, r10.xzxx
    imad r5.z, r7.y, r0.x, r7.x
    iadd r5.z, r4.y, r5.z
    imad r6.yw, -r7.xxxy, r10.xxxz, r6.yyyw
    imad r6.y, r6.w, r10.x, r6.y
    ishl r6.y, r6.y, r4.w
    imad r5.z, r5.z, r9.z, r6.y
    udiv null, r20.x, r5.z, r9.x
    if_nz r8.z
      ishl r6.yw, r10.yyyw, l(0, 1, 0, 1)
      and r6.yw, r6.yyyw, l(0, -4, 0, -4)
      bfi r6.yw, l(0, 1, 0, 1), l(0, 0, 0, 0), r10.yyyw, r6.yyyw
      iadd r10.yw, r6.yyyw, l(0, 2, 0, 2)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        and r6.yw, r10.yyyy, l(0, -3, 0, 2)
        iadd r10.y, r6.y, l(2)
        ishl r5.z, r10.w, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r10.w, r5.z
        iadd r10.w, r6.w, r5.z
      endif
    endif
    imad r6.yw, r10.yyyw, r2.xxxy, r9.yyyw
    udiv r7.xy, null, r6.ywyy, r10.xzxx
    imad r5.z, r7.y, r0.x, r7.x
    iadd r5.z, r4.y, r5.z
    imad r6.yw, -r7.xxxy, r10.xxxz, r6.yyyw
    imad r6.y, r6.w, r10.x, r6.y
    ishl r6.y, r6.y, r4.w
    imad r5.z, r5.z, r9.z, r6.y
    udiv null, r20.y, r5.z, r9.x
    if_nz r8.z
      ishl r6.yw, r12.zzzw, l(0, 1, 0, 1)
      and r6.yw, r6.yyyw, l(0, -4, 0, -4)
      bfi r6.yw, l(0, 1, 0, 1), l(0, 0, 0, 0), r12.zzzw, r6.yyyw
      iadd r12.zw, r6.yyyw, l(0, 0, 2, 2)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        and r6.yw, r12.zzzz, l(0, -3, 0, 2)
        iadd r12.z, r6.y, l(2)
        ishl r5.z, r12.w, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r12.w, r5.z
        iadd r12.w, r6.w, r5.z
      endif
    endif
    imad r6.yw, r12.zzzw, r2.xxxy, r12.xxxy
    udiv r7.xy, null, r6.ywyy, r10.xzxx
    imad r5.z, r7.y, r0.x, r7.x
    iadd r5.z, r4.y, r5.z
    imad r6.yw, -r7.xxxy, r10.xxxz, r6.yyyw
    imad r6.y, r6.w, r10.x, r6.y
    ishl r6.y, r6.y, r4.w
    imad r5.z, r5.z, r9.z, r6.y
    udiv null, r20.z, r5.z, r9.x
    if_nz r8.z
      ishl r6.yw, r13.xxxy, l(0, 1, 0, 1)
      and r6.yw, r6.yyyw, l(0, -4, 0, -4)
      bfi r6.yw, l(0, 1, 0, 1), l(0, 0, 0, 0), r13.xxxy, r6.yyyw
      iadd r13.xy, r6.ywyy, l(2, 2, 0, 0)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        and r6.yw, r13.xxxx, l(0, -3, 0, 2)
        iadd r13.x, r6.y, l(2)
        ishl r5.z, r13.y, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r13.y, r5.z
        iadd r13.y, r6.w, r5.z
      endif
    endif
    imad r6.yw, r13.xxxy, r2.xxxy, r7.zzzw
    udiv r7.xy, null, r6.ywyy, r10.xzxx
    imad r5.z, r7.y, r0.x, r7.x
    iadd r5.z, r4.y, r5.z
    imad r6.yw, -r7.xxxy, r10.xxxz, r6.yyyw
    imad r6.y, r6.w, r10.x, r6.y
    ishl r6.y, r6.y, r4.w
    imad r5.z, r5.z, r9.z, r6.y
    udiv null, r20.w, r5.z, r9.x
    iadd r7.xyzw, r0.wwww, r20.xyzw
    if_nz r8.z
      ishl r6.yw, r14.xxxy, l(0, 1, 0, 1)
      and r6.yw, r6.yyyw, l(0, -4, 0, -4)
      bfi r6.yw, l(0, 1, 0, 1), l(0, 0, 0, 0), r14.xxxy, r6.yyyw
      iadd r14.xy, r6.ywyy, l(2, 2, 0, 0)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        and r6.yw, r14.xxxx, l(0, -3, 0, 2)
        iadd r14.x, r6.y, l(2)
        ishl r5.z, r14.y, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r14.y, r5.z
        iadd r14.y, r6.w, r5.z
      endif
    endif
    imad r6.yw, r14.xxxy, r2.xxxy, r13.zzzw
    udiv r8.xy, null, r6.ywyy, r10.xzxx
    imad r5.z, r8.y, r0.x, r8.x
    iadd r5.z, r4.y, r5.z
    imad r6.yw, -r8.xxxy, r10.xxxz, r6.yyyw
    imad r6.y, r6.w, r10.x, r6.y
    ishl r6.y, r6.y, r4.w
    imad r5.z, r5.z, r9.z, r6.y
    udiv null, r12.x, r5.z, r9.x
    if_nz r8.z
      ishl r6.yw, r16.xxxy, l(0, 1, 0, 1)
      and r6.yw, r6.yyyw, l(0, -4, 0, -4)
      bfi r6.yw, l(0, 1, 0, 1), l(0, 0, 0, 0), r16.xxxy, r6.yyyw
      iadd r16.xy, r6.ywyy, l(2, 2, 0, 0)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        and r6.yw, r16.xxxx, l(0, -3, 0, 2)
        iadd r16.x, r6.y, l(2)
        ishl r5.z, r16.y, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r16.y, r5.z
        iadd r16.y, r6.w, r5.z
      endif
    endif
    imad r6.yw, r16.xxxy, r2.xxxy, r14.zzzw
    udiv r8.xy, null, r6.ywyy, r10.xzxx
    imad r5.z, r8.y, r0.x, r8.x
    iadd r5.z, r4.y, r5.z
    imad r6.yw, -r8.xxxy, r10.xxxz, r6.yyyw
    imad r6.y, r6.w, r10.x, r6.y
    ishl r6.y, r6.y, r4.w
    imad r5.z, r5.z, r9.z, r6.y
    udiv null, r12.y, r5.z, r9.x
    if_nz r8.z
      ishl r6.yw, r17.xxxy, l(0, 1, 0, 1)
      and r6.yw, r6.yyyw, l(0, -4, 0, -4)
      bfi r6.yw, l(0, 1, 0, 1), l(0, 0, 0, 0), r17.xxxy, r6.yyyw
      iadd r17.xy, r6.ywyy, l(2, 2, 0, 0)
    else
      ieq r5.z, r4.x, l(1)
      if_nz r5.z
        and r6.yw, r17.xxxx, l(0, -3, 0, 2)
        iadd r17.x, r6.y, l(2)
        ishl r5.z, r17.y, l(1)
        and r5.z, r5.z, l(-4)
        bfi r5.z, l(1), l(0), r17.y, r5.z
        iadd r17.y, r6.w, r5.z
      endif
    endif
    imad r6.yw, r17.xxxy, r2.xxxy, r16.zzzw
    udiv r8.xy, null, r6.ywyy, r10.xzxx
    imad r5.z, r8.y, r0.x, r8.x
    iadd r5.z, r4.y, r5.z
    imad r6.yw, -r8.xxxy, r10.xxxz, r6.yyyw
    imad r6.y, r6.w, r10.x, r6.y
    ishl r6.y, r6.y, r4.w
    imad r5.z, r5.z, r9.z, r6.y
    udiv null, r12.z, r5.z, r9.x
    if_nz r8.z
      ishl r6.yw, r17.zzzw, l(0, 1, 0, 1)
      and r6.yw, r6.yyyw, l(0, -4, 0, -4)
      bfi r6.yw, l(0, 1, 0, 1), l(0, 0, 0, 0), r17.zzzw, r6.yyyw
      iadd r17.zw, r6.yyyw, l(0, 0, 2, 2)
    else
      ieq r4.x, r4.x, l(1)
      if_nz r4.x
        and r6.yw, r17.zzzz, l(0, -3, 0, 2)
        iadd r17.z, r6.y, l(2)
        ishl r4.x, r17.w, l(1)
        and r4.x, r4.x, l(-4)
        bfi r4.x, l(1), l(0), r17.w, r4.x
        iadd r17.w, r6.w, r4.x
      endif
    endif
    imad r1.yz, r17.zzwz, r2.xxyx, r1.yyzy
    udiv r6.yw, null, r1.yyyz, r10.xxxz
    imad r0.x, r6.w, r0.x, r6.y
    iadd r0.x, r0.x, r4.y
    imad r1.yz, -r6.yywy, r10.xxzx, r1.yyzy
    imad r1.y, r1.z, r10.x, r1.y
    ishl r1.y, r1.y, r4.w
    imad r0.x, r0.x, r9.z, r1.y
    udiv null, r12.w, r0.x, r9.x
    iadd r8.xyzw, r0.wwww, r12.xyzw
    ishl r7.xyzw, r7.xyzw, l(2, 2, 2, 2)
    ld_raw r9.x, r7.x, T0[0].xxxx
    ld_raw r9.y, r7.y, T0[0].xxxx
    ld_raw r9.z, r7.z, T0[0].xxxx
    ld_raw r9.w, r7.w, T0[0].xxxx
    ishl r7.xyzw, r8.xyzw, l(2, 2, 2, 2)
    ld_raw r8.x, r7.x, T0[0].xxxx
    ld_raw r8.y, r7.y, T0[0].xxxx
    ld_raw r8.z, r7.z, T0[0].xxxx
    ld_raw r8.w, r7.w, T0[0].xxxx
    if_nz r4.w
      switch r4.z
        case l(5)
        and r0.x, r2.w, l(16)
        ushr r7.xyzw, r9.xyzw, r0.xxxx
        ibfe r7.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r7.xyzw
        itof r7.xyzw, r7.xyzw
        mul r7.xyzw, r7.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
        max r9.xyzw, r7.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
        ushr r7.xyzw, r8.xyzw, r0.xxxx
        ibfe r7.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r7.xyzw
        itof r7.xyzw, r7.xyzw
        mul r7.xyzw, r7.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
        max r8.xyzw, r7.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
        break
        case l(7)
        if_nz r2.w
          ushr r7.xyzw, r9.xyzw, l(16, 16, 16, 16)
          f16tof32 r9.xyzw, r7.xyzw
          ushr r7.xyzw, r8.xyzw, l(16, 16, 16, 16)
          f16tof32 r8.xyzw, r7.xyzw
        else
          f16tof32 r9.xyzw, r9.xyzw
          f16tof32 r8.xyzw, r8.xyzw
        endif
        break
        default
        if_nz r2.w
          mov r9.xyzw, l(1.000000,1.000000,1.000000,1.000000)
          mov r8.xyzw, l(1.000000,1.000000,1.000000,1.000000)
        endif
        break
      endswitch
    else
      switch r4.z
        case l(0)
        case l(1)
        and r0.x, r5.x, l(16)
        movc r0.x, r2.w, l(24), r0.x
        ushr r7.xyzw, r9.xyzw, r0.xxxx
        and r7.xyzw, r7.xyzw, l(255, 255, 255, 255)
        utof r7.xyzw, r7.xyzw
        mul r9.xyzw, r7.xyzw, l(0.003922, 0.003922, 0.003922, 0.003922)
        ushr r7.xyzw, r8.xyzw, r0.xxxx
        and r7.xyzw, r7.xyzw, l(255, 255, 255, 255)
        utof r7.xyzw, r7.xyzw
        mul r8.xyzw, r7.xyzw, l(0.003922, 0.003922, 0.003922, 0.003922)
        break
        case l(2)
        case l(10)
        case l(3)
        case l(12)
        if_nz r2.w
          ushr r7.xyzw, r9.xyzw, l(30, 30, 30, 30)
          utof r7.xyzw, r7.xyzw
          mul r9.xyzw, r7.xyzw, l(0.333333, 0.333333, 0.333333, 0.333333)
          ushr r7.xyzw, r8.xyzw, l(30, 30, 30, 30)
          utof r7.xyzw, r7.xyzw
          mul r8.xyzw, r7.xyzw, l(0.333333, 0.333333, 0.333333, 0.333333)
        else
          and r0.x, r5.x, l(20)
          ieq r1.yz, r4.zzzz, l(0, 2, 10, 0)
          or r0.w, r1.z, r1.y
          if_nz r0.w
            ushr r4.xyzw, r9.xyzw, r0.xxxx
            and r4.xyzw, r4.xyzw, l(1023, 1023, 1023, 1023)
            utof r4.xyzw, r4.xyzw
            mul r9.xyzw, r4.xyzw, l(0.000978, 0.000978, 0.000978, 0.000978)
            ushr r4.xyzw, r8.xyzw, r0.xxxx
            and r4.xyzw, r4.xyzw, l(1023, 1023, 1023, 1023)
            utof r4.xyzw, r4.xyzw
            mul r8.xyzw, r4.xyzw, l(0.000978, 0.000978, 0.000978, 0.000978)
          else
            ushr r4.xyzw, r9.xyzw, r0.xxxx
            and r7.xyzw, r4.xyzw, l(1023, 1023, 1023, 1023)
            and r10.xyzw, r4.xyzw, l(127, 127, 127, 127)
            ubfe r12.xyzw, l(3, 3, 3, 3), l(7, 7, 7, 7), r4.xyzw
            firstbit_hi r13.xyzw, r10.xyzw
            iadd r13.xyzw, r13.xyzw, l(-24, -24, -24, -24)
            movc r13.xyzw, r10.xyzw, r13.xyzw, l(8,8,8,8)
            iadd r14.xyzw, -r13.xyzw, l(1, 1, 1, 1)
            movc r14.xyzw, r12.xyzw, r12.xyzw, r14.xyzw
            bfi r4.xyzw, l(7, 7, 7, 7), r13.xyzw, r4.xyzw, l(0, 0, 0, 0)
            and r4.xyzw, r4.xyzw, l(127, 127, 127, 127)
            movc r4.xyzw, r12.xyzw, r10.xyzw, r4.xyzw
            ishl r10.xyzw, r14.xyzw, l(23, 23, 23, 23)
            iadd r10.xyzw, r10.xyzw, l(0x3e000000, 0x3e000000, 0x3e000000, 0x3e000000)
            ishl r4.xyzw, r4.xyzw, l(16, 16, 16, 16)
            iadd r4.xyzw, r10.xyzw, r4.xyzw
            movc r9.xyzw, r7.xyzw, r4.xyzw, l(0,0,0,0)
            ushr r4.xyzw, r8.xyzw, r0.xxxx
            and r7.xyzw, r4.xyzw, l(1023, 1023, 1023, 1023)
            and r10.xyzw, r4.xyzw, l(127, 127, 127, 127)
            ubfe r12.xyzw, l(3, 3, 3, 3), l(7, 7, 7, 7), r4.xyzw
            firstbit_hi r13.xyzw, r10.xyzw
            iadd r13.xyzw, r13.xyzw, l(-24, -24, -24, -24)
            movc r13.xyzw, r10.xyzw, r13.xyzw, l(8,8,8,8)
            iadd r14.xyzw, -r13.xyzw, l(1, 1, 1, 1)
            movc r14.xyzw, r12.xyzw, r12.xyzw, r14.xyzw
            bfi r4.xyzw, l(7, 7, 7, 7), r13.xyzw, r4.xyzw, l(0, 0, 0, 0)
            and r4.xyzw, r4.xyzw, l(127, 127, 127, 127)
            movc r4.xyzw, r12.xyzw, r10.xyzw, r4.xyzw
            ishl r10.xyzw, r14.xyzw, l(23, 23, 23, 23)
            iadd r10.xyzw, r10.xyzw, l(0x3e000000, 0x3e000000, 0x3e000000, 0x3e000000)
            ishl r4.xyzw, r4.xyzw, l(16, 16, 16, 16)
            iadd r4.xyzw, r10.xyzw, r4.xyzw
            movc r8.xyzw, r7.xyzw, r4.xyzw, l(0,0,0,0)
          endif
        endif
        break
        case l(4)
        if_nz r2.w
          mov r9.xyzw, l(1.000000,1.000000,1.000000,1.000000)
          mov r8.xyzw, l(1.000000,1.000000,1.000000,1.000000)
        else
          ibfe r4.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r9.xyzw
          itof r4.xyzw, r4.xyzw
          mul r4.xyzw, r4.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
          max r9.xyzw, r4.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
          ibfe r4.xyzw, l(16, 16, 16, 16), l(0, 0, 0, 0), r8.xyzw
          itof r4.xyzw, r4.xyzw
          mul r4.xyzw, r4.xyzw, l(0.000977, 0.000977, 0.000977, 0.000977)
          max r8.xyzw, r4.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
        endif
        break
        case l(6)
        if_nz r2.w
          mov r9.xyzw, l(1.000000,1.000000,1.000000,1.000000)
          mov r8.xyzw, l(1.000000,1.000000,1.000000,1.000000)
        else
          f16tof32 r9.xyzw, r9.xyzw
          f16tof32 r8.xyzw, r8.xyzw
        endif
        break
        default
        if_nz r2.w
          mov r9.xyzw, l(1.000000,1.000000,1.000000,1.000000)
          mov r8.xyzw, l(1.000000,1.000000,1.000000,1.000000)
        endif
        break
      endswitch
    endif
    if_nz r3.w
      mov_sat r9.xyzw, r9.xyzw
      ge r4.xyzw, r9.xyzw, l(0.376471, 0.376471, 0.376471, 0.376471)
      if_nz r4.x
        ge r0.x, r9.x, l(0.752941)
        if_nz r0.x
          mov r0.xw, l(0.007812,0,0,-1024.000000)
        else
          mov r0.xw, l(0.003906,0,0,-256.000000)
        endif
      else
        ge r1.y, r9.x, l(0.250980)
        if_nz r1.y
          mov r0.xw, l(0.001953,0,0,-64.000000)
        else
          mov r0.xw, l(0.000977,0,0,0)
        endif
      endif
      mul r1.y, r0.x, r9.x
      mad r0.w, r1.y, l(261120.000000), r0.w
      mul r0.x, r0.x, r0.w
      round_z r0.x, r0.x
      add r0.x, r0.x, r0.w
      mul r9.x, r0.x, l(0.000978)
      if_nz r4.y
        ge r0.x, r9.y, l(0.752941)
        if_nz r0.x
          mov r0.xw, l(0.007812,0,0,-1024.000000)
        else
          mov r0.xw, l(0.003906,0,0,-256.000000)
        endif
      else
        ge r1.y, r9.y, l(0.250980)
        if_nz r1.y
          mov r0.xw, l(0.001953,0,0,-64.000000)
        else
          mov r0.xw, l(0.000977,0,0,0)
        endif
      endif
      mul r1.y, r0.x, r9.y
      mad r0.w, r1.y, l(261120.000000), r0.w
      mul r0.x, r0.x, r0.w
      round_z r0.x, r0.x
      add r0.x, r0.x, r0.w
      mul r9.y, r0.x, l(0.000978)
      if_nz r4.z
        ge r0.x, r9.z, l(0.752941)
        if_nz r0.x
          mov r0.xw, l(0.007812,0,0,-1024.000000)
        else
          mov r0.xw, l(0.003906,0,0,-256.000000)
        endif
      else
        ge r1.y, r9.z, l(0.250980)
        if_nz r1.y
          mov r0.xw, l(0.001953,0,0,-64.000000)
        else
          mov r0.xw, l(0.000977,0,0,0)
        endif
      endif
      mul r1.y, r0.x, r9.z
      mad r0.w, r1.y, l(261120.000000), r0.w
      mul r0.x, r0.x, r0.w
      round_z r0.x, r0.x
      add r0.x, r0.x, r0.w
      mul r9.z, r0.x, l(0.000978)
      if_nz r4.w
        ge r0.x, r9.w, l(0.752941)
        if_nz r0.x
          mov r0.xw, l(0.007812,0,0,-1024.000000)
        else
          mov r0.xw, l(0.003906,0,0,-256.000000)
        endif
      else
        ge r1.y, r9.w, l(0.250980)
        if_nz r1.y
          mov r0.xw, l(0.001953,0,0,-64.000000)
        else
          mov r0.xw, l(0.000977,0,0,0)
        endif
      endif
      mul r1.y, r0.x, r9.w
      mad r0.w, r1.y, l(261120.000000), r0.w
      mul r0.x, r0.x, r0.w
      round_z r0.x, r0.x
      add r0.x, r0.x, r0.w
      mul r9.w, r0.x, l(0.000978)
      mov_sat r8.xyzw, r8.xyzw
      ge r4.xyzw, r8.xyzw, l(0.376471, 0.376471, 0.376471, 0.376471)
      if_nz r4.x
        ge r0.x, r8.x, l(0.752941)
        if_nz r0.x
          mov r0.xw, l(0.007812,0,0,-1024.000000)
        else
          mov r0.xw, l(0.003906,0,0,-256.000000)
        endif
      else
        ge r1.y, r8.x, l(0.250980)
        if_nz r1.y
          mov r0.xw, l(0.001953,0,0,-64.000000)
        else
          mov r0.xw, l(0.000977,0,0,0)
        endif
      endif
      mul r1.y, r0.x, r8.x
      mad r0.w, r1.y, l(261120.000000), r0.w
      mul r0.x, r0.x, r0.w
      round_z r0.x, r0.x
      add r0.x, r0.x, r0.w
      mul r8.x, r0.x, l(0.000978)
      if_nz r4.y
        ge r0.x, r8.y, l(0.752941)
        if_nz r0.x
          mov r0.xw, l(0.007812,0,0,-1024.000000)
        else
          mov r0.xw, l(0.003906,0,0,-256.000000)
        endif
      else
        ge r1.y, r8.y, l(0.250980)
        if_nz r1.y
          mov r0.xw, l(0.001953,0,0,-64.000000)
        else
          mov r0.xw, l(0.000977,0,0,0)
        endif
      endif
      mul r1.y, r0.x, r8.y
      mad r0.w, r1.y, l(261120.000000), r0.w
      mul r0.x, r0.x, r0.w
      round_z r0.x, r0.x
      add r0.x, r0.x, r0.w
      mul r8.y, r0.x, l(0.000978)
      if_nz r4.z
        ge r0.x, r8.z, l(0.752941)
        if_nz r0.x
          mov r0.xw, l(0.007812,0,0,-1024.000000)
        else
          mov r0.xw, l(0.003906,0,0,-256.000000)
        endif
      else
        ge r1.y, r8.z, l(0.250980)
        if_nz r1.y
          mov r0.xw, l(0.001953,0,0,-64.000000)
        else
          mov r0.xw, l(0.000977,0,0,0)
        endif
      endif
      mul r1.y, r0.x, r8.z
      mad r0.w, r1.y, l(261120.000000), r0.w
      mul r0.x, r0.x, r0.w
      round_z r0.x, r0.x
      add r0.x, r0.x, r0.w
      mul r8.z, r0.x, l(0.000978)
      if_nz r4.w
        ge r0.x, r8.w, l(0.752941)
        if_nz r0.x
          mov r0.xw, l(0.007812,0,0,-1024.000000)
        else
          mov r0.xw, l(0.003906,0,0,-256.000000)
        endif
      else
        ge r1.y, r8.w, l(0.250980)
        if_nz r1.y
          mov r0.xw, l(0.001953,0,0,-64.000000)
        else
          mov r0.xw, l(0.000977,0,0,0)
        endif
      endif
      mul r1.y, r0.x, r8.w
      mad r0.w, r1.y, l(261120.000000), r0.w
      mul r0.x, r0.x, r0.w
      round_z r0.x, r0.x
      add r0.x, r0.x, r0.w
      mul r8.w, r0.x, l(0.000978)
    endif
    add r18.xyzw, r9.xyzw, r11.xyzw
    add r15.xyzw, r8.xyzw, r19.xyzw
  else
    mov r0.y, r1.w
  endif
endif
mul r4.xyzw, r0.yyyy, r18.xyzw
mul r7.xyzw, r0.yyyy, r15.xyzw
ieq r0.x, r6.x, l(0)
ine r0.y, r1.x, l(0)
and r0.x, r0.y, r0.x
if_nz r0.x
  uge r0.x, r1.x, l(2)
  if_nz r0.x
    uge r0.x, r1.x, l(3)
    if_nz r0.x
      mov r4.z, r4.w
    endif
    mov r4.y, r4.z
  endif
  mov r4.x, r4.y
endif
imad r1.yz, r3.xxzx, r2.xxyx, r6.xxzx
ushr r1.x, r1.y, l(3)
udiv r0.xy, null, r1.xzxx, r2.xyxx
if_nz r0.z
  ubfe r0.z, l(3), l(4), CB0[0][0].z
  ishl r0.w, r3.y, l(5)
  ishr r1.yw, r0.yyyy, l(0, 4, 0, 3)
  ishr r2.w, r0.z, l(2)
  ushr r0.w, r0.w, l(4)
  and r0.w, r0.w, l(2046)
  imad r0.w, r2.w, r0.w, r1.y
  ushr r1.y, r2.z, l(5)
  ibfe r3.xy, l(27, 29, 0, 0), l(2, 0, 0, 0), r0.xxxx
  imad r0.w, r0.w, r1.y, r3.x
  ishl r1.y, r0.y, l(8)
  ishr r1.y, r1.y, l(6)
  iadd r1.w, r1.w, r2.w
  bfi r2.w, l(1), l(1), r1.w, l(0)
  iadd r2.w, r2.w, r3.y
  bfi r2.w, l(2), l(1), r2.w, l(0)
  bfi r1.w, l(1), l(0), r1.w, r2.w
  and r3.xy, r1.yyyy, l(16, 8, 0, 0)
  bfi r3.zw, l(0, 0, 22, 22), l(0, 0, 8, 11), r0.wwww, l(0, 0, 0, 0)
  imad r3.xz, r3.xxxx, l(2, 0, 16, 0), r3.zzwz
  bfi r3.xy, l(5, 5, 0, 0), l(0, 3, 0, 0), r3.yyyy, r3.xzxx
  bfi r0.zw, l(0, 0, 2, 2), l(0, 0, 6, 9), r0.zzzz, r3.xxxy
  ubfe r1.y, l(3), l(6), r0.z
  and r2.w, r1.w, l(6)
  bfi r1.w, l(1), l(8), r1.w, l(0)
  imad r1.y, r1.y, l(32), r1.w
  imad r1.y, r2.w, l(4), r1.y
  bfi r0.zw, l(0, 0, 1, 1), l(0, 0, 4, 7), r0.yyyy, r0.zzzw
  bfi r0.w, l(9), l(3), r1.y, r0.w
  bfi r0.z, l(6), l(0), r0.z, r0.w
else
  ibfe r1.yw, l(0, 27, 0, 29), l(0, 2, 0, 0), r0.xxxx
  ishr r3.xy, r0.yyyy, l(5, 2, 0, 0)
  ushr r0.w, r2.z, l(5)
  imad r0.w, r3.x, r0.w, r1.y
  ishl r2.zw, r0.yyyy, l(0, 0, 2, 7)
  ishl r1.y, r2.z, l(1)
  and r1.y, r1.y, l(96)
  bfi r3.x, l(25), l(7), r0.w, r1.y
  and r2.zw, r2.zzzw, l(0, 0, 8, 2048)
  iadd r3.x, r3.x, r2.z
  ishl r3.zw, r1.yyyy, l(0, 0, 3, 2)
  bfi r3.zw, l(0, 0, 25, 25), l(0, 0, 10, 9), r0.wwww, r3.zzzw
  imad r3.zw, r2.zzzz, l(0, 0, 8, 4), r3.zzzw
  bfi r3.xzw, l(1, 0, 1, 1), l(4, 0, 7, 6), r0.yyyy, r3.xxzw
  bfi r0.w, l(12), l(0), r2.w, r3.z
  and r1.y, r3.w, l(1792)
  iadd r0.w, r0.w, r1.y
  and r1.y, r3.y, l(2)
  iadd r1.y, r1.w, r1.y
  bfi r1.y, l(2), l(6), r1.y, l(0)
  iadd r0.w, r0.w, r1.y
  bfi r0.z, l(6), l(0), r3.x, r0.w
endif
imad r0.xy, -r0.xyxx, r2.xyxx, r1.xzxx
imul null, r0.w, r2.y, r2.x
imad r0.x, r0.x, r2.y, r0.y
ishl r0.x, r0.x, l(3)
imad r0.x, r0.z, r0.w, r0.x
ushr r0.x, r0.x, l(3)
if_nz r5.w
  max r0.y, r4.x, l(-1.000000)
  min r0.y, r0.y, l(1.000000)
  ge r0.z, r4.x, l(0.000000)
  movc r0.z, r0.z, l(0.500000), l(-0.500000)
  mad r0.y, r0.y, l(127.000000), r0.z
  ftoi r0.y, r0.y
  max r0.w, r4.y, l(-1.000000)
  min r0.w, r0.w, l(1.000000)
  ge r1.x, r4.y, l(0.000000)
  movc r1.x, r1.x, l(0.500000), l(-0.500000)
  mad r0.w, r0.w, l(127.000000), r1.x
  ftoi r0.w, r0.w
  max r1.x, r4.z, l(-1.000000)
  min r1.x, r1.x, l(1.000000)
  ge r1.y, r4.z, l(0.000000)
  movc r1.y, r1.y, l(0.500000), l(-0.500000)
  mad r1.x, r1.x, l(127.000000), r1.y
  ftoi r1.x, r1.x
  max r1.y, r4.w, l(-1.000000)
  min r1.y, r1.y, l(1.000000)
  ge r1.z, r4.w, l(0.000000)
  movc r1.z, r1.z, l(0.500000), l(-0.500000)
  mad r1.y, r1.y, l(127.000000), r1.z
  ftoi r1.y, r1.y
else
  ieq r0.z, r5.y, l(2)
  if_nz r0.z
    max r0.w, r4.x, l(0.000000)
    min r0.w, r0.w, l(255.000000)
    add r0.w, r0.w, l(0.500000)
    ftou r0.y, r0.w
  else
    ieq r0.w, r5.y, l(3)
    if_nz r0.w
      max r0.w, r4.x, l(-128.000000)
      min r0.w, r0.w, l(127.000000)
      ge r1.x, r4.x, l(0.000000)
      movc r1.x, r1.x, l(0.500000), l(-0.500000)
      add r0.w, r0.w, r1.x
      ftoi r0.y, r0.w
    else
      mov_sat r4.x, r4.x
      mad r0.w, r4.x, l(255.000000), l(0.500000)
      ftou r0.y, r0.w
    endif
  endif
  if_nz r0.z
    max r1.x, r4.y, l(0.000000)
    min r1.x, r1.x, l(255.000000)
    add r1.x, r1.x, l(0.500000)
    ftou r0.w, r1.x
  else
    ieq r1.x, r5.y, l(3)
    if_nz r1.x
      max r1.x, r4.y, l(-128.000000)
      min r1.x, r1.x, l(127.000000)
      ge r1.y, r4.y, l(0.000000)
      movc r1.y, r1.y, l(0.500000), l(-0.500000)
      add r1.x, r1.y, r1.x
      ftoi r0.w, r1.x
    else
      mov_sat r4.y, r4.y
      mad r1.x, r4.y, l(255.000000), l(0.500000)
      ftou r0.w, r1.x
    endif
  endif
  if_nz r0.z
    max r1.y, r4.z, l(0.000000)
    min r1.y, r1.y, l(255.000000)
    add r1.y, r1.y, l(0.500000)
    ftou r1.x, r1.y
  else
    ieq r1.y, r5.y, l(3)
    if_nz r1.y
      max r1.y, r4.z, l(-128.000000)
      min r1.y, r1.y, l(127.000000)
      ge r1.z, r4.z, l(0.000000)
      movc r1.z, r1.z, l(0.500000), l(-0.500000)
      add r1.y, r1.z, r1.y
      ftoi r1.x, r1.y
    else
      mov_sat r4.z, r4.z
      mad r1.y, r4.z, l(255.000000), l(0.500000)
      ftou r1.x, r1.y
    endif
  endif
  if_nz r0.z
    max r0.z, r4.w, l(0.000000)
    min r0.z, r0.z, l(255.000000)
    add r0.z, r0.z, l(0.500000)
    ftou r1.y, r0.z
  else
    ieq r0.z, r5.y, l(3)
    if_nz r0.z
      max r0.z, r4.w, l(-128.000000)
      min r0.z, r0.z, l(127.000000)
      ge r1.z, r4.w, l(0.000000)
      movc r1.z, r1.z, l(0.500000), l(-0.500000)
      add r0.z, r0.z, r1.z
      ftoi r1.y, r0.z
    else
      mov_sat r4.w, r4.w
      mad r0.z, r4.w, l(255.000000), l(0.500000)
      ftou r1.y, r0.z
    endif
  endif
endif
bfi r0.z, l(8), l(8), r0.w, l(0)
bfi r0.y, l(8), l(0), r0.y, r0.z
bfi r0.z, l(8), l(16), r1.x, l(0)
iadd r0.y, r0.z, r0.y
bfi r1.xzw, l(8, 0, 8, 8), l(24, 0, 24, 24), r1.yyyy, r0.yyyy
if_nz r5.w
  max r2.xyzw, r7.xyzw, l(-1.000000, -1.000000, -1.000000, -1.000000)
  min r2.xyzw, r2.xyzw, l(1.000000, 1.000000, 1.000000, 1.000000)
  ge r3.xyzw, r7.xyzw, l(0.000000, 0.000000, 0.000000, 0.000000)
  movc r3.xyzw, r3.xyzw, l(0.500000,0.500000,0.500000,0.500000), l(-0.500000,-0.500000,-0.500000,-0.500000)
  mad r2.xyzw, r2.xyzw, l(127.000000, 127.000000, 127.000000, 127.000000), r3.xyzw
  ftoi r2.xyzw, r2.xyzw
else
  ieq r0.y, r5.y, l(2)
  if_nz r0.y
    max r0.z, r7.x, l(0.000000)
    min r0.z, r0.z, l(255.000000)
    add r0.z, r0.z, l(0.500000)
    ftou r2.x, r0.z
  else
    ieq r0.z, r5.y, l(3)
    if_nz r0.z
      max r0.z, r7.x, l(-128.000000)
      min r0.z, r0.z, l(127.000000)
      ge r0.w, r7.x, l(0.000000)
      movc r0.w, r0.w, l(0.500000), l(-0.500000)
      add r0.z, r0.w, r0.z
      ftoi r2.x, r0.z
    else
      mov_sat r7.x, r7.x
      mad r0.z, r7.x, l(255.000000), l(0.500000)
      ftou r2.x, r0.z
    endif
  endif
  if_nz r0.y
    max r0.z, r7.y, l(0.000000)
    min r0.z, r0.z, l(255.000000)
    add r0.z, r0.z, l(0.500000)
    ftou r2.y, r0.z
  else
    ieq r0.z, r5.y, l(3)
    if_nz r0.z
      max r0.z, r7.y, l(-128.000000)
      min r0.z, r0.z, l(127.000000)
      ge r0.w, r7.y, l(0.000000)
      movc r0.w, r0.w, l(0.500000), l(-0.500000)
      add r0.z, r0.w, r0.z
      ftoi r2.y, r0.z
    else
      mov_sat r7.y, r7.y
      mad r0.z, r7.y, l(255.000000), l(0.500000)
      ftou r2.y, r0.z
    endif
  endif
  if_nz r0.y
    max r0.z, r7.z, l(0.000000)
    min r0.z, r0.z, l(255.000000)
    add r0.z, r0.z, l(0.500000)
    ftou r2.z, r0.z
  else
    ieq r0.z, r5.y, l(3)
    if_nz r0.z
      max r0.z, r7.z, l(-128.000000)
      min r0.z, r0.z, l(127.000000)
      ge r0.w, r7.z, l(0.000000)
      movc r0.w, r0.w, l(0.500000), l(-0.500000)
      add r0.z, r0.w, r0.z
      ftoi r2.z, r0.z
    else
      mov_sat r7.z, r7.z
      mad r0.z, r7.z, l(255.000000), l(0.500000)
      ftou r2.z, r0.z
    endif
  endif
  if_nz r0.y
    max r0.y, r7.w, l(0.000000)
    min r0.y, r0.y, l(255.000000)
    add r0.y, r0.y, l(0.500000)
    ftou r2.w, r0.y
  else
    ieq r0.y, r5.y, l(3)
    if_nz r0.y
      max r0.y, r7.w, l(-128.000000)
      min r0.y, r0.y, l(127.000000)
      ge r0.z, r7.w, l(0.000000)
      movc r0.z, r0.z, l(0.500000), l(-0.500000)
      add r0.y, r0.z, r0.y
      ftoi r2.w, r0.y
    else
      mov_sat r7.w, r7.w
      mad r0.y, r7.w, l(255.000000), l(0.500000)
      ftou r2.w, r0.y
    endif
  endif
endif
bfi r0.yz, l(0, 8, 8, 0), l(0, 8, 16, 0), r2.yyzy, l(0, 0, 0, 0)
bfi r0.y, l(8), l(0), r2.x, r0.y
iadd r0.y, r0.z, r0.y
bfi r1.y, l(8), l(24), r2.w, r0.y
store_uav_typed U0[0].xyzw, r0.xxxx, r1.xyzw
ret

#endif

const BYTE resolve_full_8bpp_scaled_cs[] = {
    68,  88,  66,  67,  251, 38,  112, 251, 226, 193, 69,  215, 174, 47,  92,  15,  154, 103, 165,
    207, 1,   0,   0,   0,   44,  12,  1,   0,   5,   0,   0,   0,   52,  0,   0,   0,   144, 2,
    0,   0,   160, 2,   0,   0,   176, 2,   0,   0,   144, 11,  1,   0,   82,  68,  69,  70,  84,
    2,   0,   0,   1,   0,   0,   0,   228, 0,   0,   0,   3,   0,   0,   0,   60,  0,   0,   0,
    1,   5,   83,  67,  0,   5,   0,   0,   44,  2,   0,   0,   19,  19,  68,  37,  60,  0,   0,
    0,   24,  0,   0,   0,   40,  0,   0,   0,   40,  0,   0,   0,   36,  0,   0,   0,   12,  0,
    0,   0,   0,   0,   0,   0,   180, 0,   0,   0,   7,   0,   0,   0,   6,   0,   0,   0,   1,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   197, 0,   0,   0,   4,   0,   0,   0,   4,   0,   0,
    0,   1,   0,   0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   1,   0,   0,   0,   4,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   213, 0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,
    1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   120, 101, 95,  114, 101, 115, 111,
    108, 118, 101, 95,  101, 100, 114, 97,  109, 0,   120, 101, 95,  114, 101, 115, 111, 108, 118,
    101, 95,  100, 101, 115, 116, 0,   112, 117, 115, 104, 95,  99,  111, 110, 115, 116, 115, 95,
    120, 101, 0,   213, 0,   0,   0,   4,   0,   0,   0,   252, 0,   0,   0,   16,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   156, 1,   0,   0,   0,   0,   0,   0,   4,   0,   0,
    0,   2,   0,   0,   0,   184, 1,   0,   0,   0,   0,   0,   0,   255, 255, 255, 255, 0,   0,
    0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   220, 1,   0,   0,   4,   0,   0,   0,   4,
    0,   0,   0,   2,   0,   0,   0,   184, 1,   0,   0,   0,   0,   0,   0,   255, 255, 255, 255,
    0,   0,   0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   247, 1,   0,   0,   8,   0,   0,
    0,   4,   0,   0,   0,   2,   0,   0,   0,   184, 1,   0,   0,   0,   0,   0,   0,   255, 255,
    255, 255, 0,   0,   0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   12,  2,   0,   0,   12,
    0,   0,   0,   4,   0,   0,   0,   2,   0,   0,   0,   184, 1,   0,   0,   0,   0,   0,   0,
    255, 255, 255, 255, 0,   0,   0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   120, 101, 95,
    114, 101, 115, 111, 108, 118, 101, 95,  101, 100, 114, 97,  109, 95,  105, 110, 102, 111, 0,
    100, 119, 111, 114, 100, 0,   0,   0,   19,  0,   1,   0,   1,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    178, 1,   0,   0,   120, 101, 95,  114, 101, 115, 111, 108, 118, 101, 95,  99,  111, 111, 114,
    100, 105, 110, 97,  116, 101, 95,  105, 110, 102, 111, 0,   120, 101, 95,  114, 101, 115, 111,
    108, 118, 101, 95,  100, 101, 115, 116, 95,  105, 110, 102, 111, 0,   120, 101, 95,  114, 101,
    115, 111, 108, 118, 101, 95,  100, 101, 115, 116, 95,  99,  111, 111, 114, 100, 105, 110, 97,
    116, 101, 95,  105, 110, 102, 111, 0,   77,  105, 99,  114, 111, 115, 111, 102, 116, 32,  40,
    82,  41,  32,  72,  76,  83,  76,  32,  83,  104, 97,  100, 101, 114, 32,  67,  111, 109, 112,
    105, 108, 101, 114, 32,  49,  48,  46,  49,  0,   73,  83,  71,  78,  8,   0,   0,   0,   0,
    0,   0,   0,   8,   0,   0,   0,   79,  83,  71,  78,  8,   0,   0,   0,   0,   0,   0,   0,
    8,   0,   0,   0,   83,  72,  69,  88,  216, 8,   1,   0,   81,  0,   5,   0,   54,  66,  0,
    0,   106, 8,   0,   1,   89,  0,   0,   7,   70,  142, 48,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   161, 0,   0,   6,   70,
    126, 48,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    156, 8,   0,   7,   70,  238, 49,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   68,  68,  0,   0,   0,   0,   0,   0,   95,  0,   0,   2,   50,  0,   2,   0,   104, 0,
    0,   2,   26,  0,   0,   0,   155, 0,   0,   4,   8,   0,   0,   0,   8,   0,   0,   0,   1,
    0,   0,   0,   1,   0,   0,   12,  242, 0,   16,  0,   0,   0,   0,   0,   6,   138, 48,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   255, 3,   0,
    0,   0,   0,   0,   32,  8,   0,   0,   0,   0,   0,   0,   1,   31,  0,   4,   3,   26,  0,
    16,  0,   0,   0,   0,   0,   138, 0,   0,   17,  50,  0,   16,  0,   1,   0,   0,   0,   2,
    64,  0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    2,   64,  0,   0,   17,  0,   0,   0,   20,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   86,  133, 48,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   18,  0,
    0,   1,   54,  0,   0,   8,   50,  0,   16,  0,   1,   0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   1,
    138, 0,   0,   17,  114, 0,   16,  0,   2,   0,   0,   0,   2,   64,  0,   0,   3,   0,   0,
    0,   3,   0,   0,   0,   11,  0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   16,  0,
    0,   0,   19,  0,   0,   0,   5,   0,   0,   0,   0,   0,   0,   0,   86,  133, 48,  0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   38,  0,   0,   8,   0,   208, 0,   0,
    34,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   2,   0,   0,   0,   42,  0,   16,
    0,   2,   0,   0,   0,   85,  0,   0,   12,  242, 0,   16,  0,   3,   0,   0,   0,   214, 143,
    48,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   4,
    0,   0,   0,   10,  0,   0,   0,   20,  0,   0,   0,   24,  0,   0,   0,   80,  0,   0,   6,
    34,  0,   16,  0,   0,   0,   0,   0,   10,  0,   2,   0,   26,  0,   16,  0,   0,   0,   0,
    0,   31,  0,   4,   3,   26,  0,   16,  0,   0,   0,   0,   0,   62,  0,   0,   1,   21,  0,
    0,   1,   138, 0,   0,   17,  242, 0,   16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   2,
    0,   0,   0,   11,  0,   0,   0,   4,   0,   0,   0,   1,   0,   0,   0,   2,   64,  0,   0,
    10,  0,   0,   0,   13,  0,   0,   0,   24,  0,   0,   0,   28,  0,   0,   0,   6,   128, 48,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   54,  0,   0,   7,   18,  0,
    16,  0,   5,   0,   0,   0,   26,  128, 48,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   54,  0,   0,   5,   34,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,
    3,   0,   0,   0,   140, 0,   0,   20,  194, 0,   16,  0,   1,   0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   4,   0,   0,   0,   1,   0,   0,   0,   2,   64,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   6,
    4,   16,  0,   5,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   139, 0,   0,   11,  34,  0,   16,  0,   0,   0,   0,
    0,   1,   64,  0,   0,   6,   0,   0,   0,   1,   64,  0,   0,   16,  0,   0,   0,   42,  128,
    48,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   41,  0,   0,   7,   34,
    0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,
    23,  0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,
    0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 63,  39,  0,   0,   7,   130, 0,
    16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   0,   0,   140, 0,   0,   13,  66,  0,   16,  0,   2,   0,   0,   0,   1,   64,  0,   0,
    10,  0,   0,   0,   1,   64,  0,   0,   5,   0,   0,   0,   58,  128, 48,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   140, 0,
    0,   20,  82,  0,   16,  0,   3,   0,   0,   0,   2,   64,  0,   0,   4,   0,   0,   0,   0,
    0,   0,   0,   4,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   3,   0,   0,   0,
    0,   0,   0,   0,   3,   0,   0,   0,   0,   0,   0,   0,   166, 11,  16,  0,   3,   0,   0,
    0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   138, 0,   0,   17,  114, 0,   16,  0,   5,   0,   0,   0,   2,   64,  0,   0,   6,
    0,   0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,
    7,   0,   0,   0,   13,  0,   0,   0,   28,  0,   0,   0,   0,   0,   0,   0,   166, 139, 48,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   41,  0,   0,   6,   18,  0,
    16,  0,   6,   0,   0,   0,   10,  0,   2,   0,   1,   64,  0,   0,   3,   0,   0,   0,   32,
    0,   0,   10,  146, 0,   16,  0,   5,   0,   0,   0,   6,   4,   16,  0,   5,   0,   0,   0,
    2,   64,  0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,
    0,   1,   0,   0,   7,   130, 0,   16,  0,   2,   0,   0,   0,   58,  0,   16,  0,   0,   0,
    0,   0,   10,  0,   16,  0,   5,   0,   0,   0,   59,  0,   0,   5,   130, 0,   16,  0,   3,
    0,   0,   0,   58,  0,   16,  0,   2,   0,   0,   0,   1,   0,   0,   7,   18,  0,   16,  0,
    5,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   3,   0,   0,
    0,   1,   0,   0,   7,   130, 0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   4,   0,
    0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   32,  0,   0,   7,   130, 0,   16,  0,   6,
    0,   0,   0,   42,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,
    1,   0,   0,   7,   130, 0,   16,  0,   3,   0,   0,   0,   58,  0,   16,  0,   3,   0,   0,
    0,   58,  0,   16,  0,   6,   0,   0,   0,   80,  0,   0,   7,   130, 0,   16,  0,   6,   0,
    0,   0,   1,   64,  0,   0,   3,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   31,
    0,   4,   3,   58,  0,   16,  0,   6,   0,   0,   0,   54,  0,   0,   5,   18,  0,   16,  0,
    7,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   18,  0,   0,   1,   32,  0,   0,
    7,   130, 0,   16,  0,   6,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,
    0,   0,   5,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   6,   0,   0,   0,   54,
    0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,
    18,  0,   0,   1,   54,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   83,  0,   0,   6,   34,  0,
    16,  0,   6,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   26,  0,   2,   0,   35,
    0,   0,   9,   162, 0,   16,  0,   6,   0,   0,   0,   166, 14,  16,  0,   1,   0,   0,   0,
    6,   4,   16,  0,   2,   0,   0,   0,   6,   4,   16,  0,   6,   0,   0,   0,   78,  0,   0,
    8,   50,  0,   16,  0,   8,   0,   0,   0,   0,   208, 0,   0,   214, 5,   16,  0,   6,   0,
    0,   0,   70,  0,   16,  0,   2,   0,   0,   0,   35,  0,   0,   10,  162, 0,   16,  0,   6,
    0,   0,   0,   6,   4,   16,  128, 65,  0,   0,   0,   8,   0,   0,   0,   6,   4,   16,  0,
    2,   0,   0,   0,   86,  13,  16,  0,   6,   0,   0,   0,   80,  0,   0,   7,   66,  0,   16,
    0,   8,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   2,   0,
    0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,   0,   85,  0,   0,   7,   34,
    0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,
    1,   0,   0,   0,   41,  0,   0,   10,  50,  0,   16,  0,   9,   0,   0,   0,   70,  0,   16,
    0,   8,   0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   1,   0,   0,   10,  50,  0,   16,  0,   9,   0,   0,   0,   70,
    0,   16,  0,   9,   0,   0,   0,   2,   64,  0,   0,   252, 255, 255, 255, 252, 255, 255, 255,
    0,   0,   0,   0,   0,   0,   0,   0,   140, 0,   0,   17,  50,  0,   16,  0,   9,   0,   0,
    0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   70,  0,   16,  0,   8,   0,   0,   0,   70,  0,   16,  0,   9,   0,   0,   0,
    140, 0,   0,   20,  194, 0,   16,  0,   9,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   0,   0,   0,   31,  0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   6,   4,   16,  0,   7,
    0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   30,  0,   0,   7,   50,  0,   16,  0,   9,   0,   0,   0,   230, 10,  16,
    0,   9,   0,   0,   0,   70,  0,   16,  0,   9,   0,   0,   0,   18,  0,   0,   1,   32,  0,
    0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,
    64,  0,   0,   1,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   8,   0,   0,   0,
    140, 0,   0,   11,  18,  0,   16,  0,   9,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,
    0,   1,   64,  0,   0,   1,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   10,  0,
    16,  0,   8,   0,   0,   0,   41,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   26,
    0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,
    130, 0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,
    0,   252, 255, 255, 255, 140, 0,   0,   11,  130, 0,   16,  0,   8,   0,   0,   0,   1,   64,
    0,   0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   26,  0,   16,  0,   8,
    0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   1,   0,   0,   7,   66,  0,   16,  0,
    9,   0,   0,   0,   10,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   2,   0,   0,
    0,   30,  0,   0,   7,   34,  0,   16,  0,   9,   0,   0,   0,   58,  0,   16,  0,   8,   0,
    0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   5,   50,
    0,   16,  0,   9,   0,   0,   0,   70,  0,   16,  0,   8,   0,   0,   0,   21,  0,   0,   1,
    21,  0,   0,   1,   35,  0,   0,   9,   50,  0,   16,  0,   9,   0,   0,   0,   70,  0,   16,
    0,   9,   0,   0,   0,   70,  0,   16,  0,   2,   0,   0,   0,   214, 5,   16,  0,   6,   0,
    0,   0,   38,  0,   0,   11,  0,   208, 0,   0,   98,  0,   16,  0,   10,  0,   0,   0,   6,
    1,   16,  0,   2,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   80,  0,   0,   0,
    16,  0,   0,   0,   0,   0,   0,   0,   85,  0,   0,   7,   18,  0,   16,  0,   10,  0,   0,
    0,   26,  0,   16,  0,   10,  0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   78,  0,
    0,   8,   194, 0,   16,  0,   9,   0,   0,   0,   0,   208, 0,   0,   6,   4,   16,  0,   9,
    0,   0,   0,   6,   8,   16,  0,   10,  0,   0,   0,   35,  0,   0,   9,   130, 0,   16,  0,
    8,   0,   0,   0,   58,  0,   16,  0,   9,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,
    0,   42,  0,   16,  0,   9,   0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   8,   0,
    0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   35,
    0,   0,   10,  50,  0,   16,  0,   9,   0,   0,   0,   230, 10,  16,  128, 65,  0,   0,   0,
    9,   0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   70,  0,   16,  0,   9,   0,   0,
    0,   38,  0,   0,   8,   0,   208, 0,   0,   66,  0,   16,  0,   9,   0,   0,   0,   42,  0,
    16,  0,   10,  0,   0,   0,   26,  0,   16,  0,   10,  0,   0,   0,   35,  0,   0,   9,   18,
    0,   16,  0,   9,   0,   0,   0,   26,  0,   16,  0,   9,   0,   0,   0,   10,  0,   16,  0,
    10,  0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   41,  0,   0,   7,   18,  0,   16,
    0,   9,   0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   58,  0,   16,  0,   4,   0,
    0,   0,   35,  0,   0,   9,   130, 0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   8,
    0,   0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,
    41,  0,   0,   7,   18,  0,   16,  0,   9,   0,   0,   0,   42,  0,   16,  0,   9,   0,   0,
    0,   1,   64,  0,   0,   11,  0,   0,   0,   78,  0,   0,   8,   0,   208, 0,   0,   18,  0,
    16,  0,   11,  0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   9,
    0,   0,   0,   54,  0,   0,   4,   66,  0,   16,  0,   6,   0,   0,   0,   26,  0,   2,   0,
    30,  0,   0,   10,  50,  0,   16,  0,   12,  0,   0,   0,   134, 0,   16,  0,   6,   0,   0,
    0,   2,   64,  0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   83,  0,   0,   7,   66,  0,   16,  0,   12,  0,   0,   0,   26,  0,   16,  0,   1,
    0,   0,   0,   26,  0,   16,  0,   12,  0,   0,   0,   35,  0,   0,   9,   162, 0,   16,  0,
    9,   0,   0,   0,   166, 14,  16,  0,   1,   0,   0,   0,   6,   4,   16,  0,   2,   0,   0,
    0,   6,   8,   16,  0,   12,  0,   0,   0,   78,  0,   0,   8,   162, 0,   16,  0,   10,  0,
    0,   0,   0,   208, 0,   0,   86,  13,  16,  0,   9,   0,   0,   0,   6,   4,   16,  0,   2,
    0,   0,   0,   35,  0,   0,   10,  162, 0,   16,  0,   9,   0,   0,   0,   86,  13,  16,  128,
    65,  0,   0,   0,   10,  0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   86,  13,  16,
    0,   9,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,   0,   85,  0,
    0,   7,   66,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   1,
    64,  0,   0,   1,   0,   0,   0,   41,  0,   0,   10,  50,  0,   16,  0,   12,  0,   0,   0,
    214, 5,   16,  0,   10,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   10,  50,  0,   16,  0,   12,  0,
    0,   0,   70,  0,   16,  0,   12,  0,   0,   0,   2,   64,  0,   0,   252, 255, 255, 255, 252,
    255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   140, 0,   0,   17,  50,  0,   16,  0,
    12,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   214, 5,   16,  0,   10,  0,   0,   0,   70,  0,   16,  0,   12,
    0,   0,   0,   140, 0,   0,   20,  194, 0,   16,  0,   12,  0,   0,   0,   2,   64,  0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   31,  0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   6,   8,
    16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   50,  0,   16,  0,   12,  0,   0,   0,
    230, 10,  16,  0,   12,  0,   0,   0,   70,  0,   16,  0,   12,  0,   0,   0,   18,  0,   0,
    1,   32,  0,   0,   7,   66,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   4,   0,
    0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   7,
    0,   0,   0,   140, 0,   0,   11,  18,  0,   16,  0,   12,  0,   0,   0,   1,   64,  0,   0,
    1,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,
    0,   26,  0,   16,  0,   10,  0,   0,   0,   41,  0,   0,   7,   66,  0,   16,  0,   7,   0,
    0,   0,   58,  0,   16,  0,   10,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,
    0,   0,   7,   66,  0,   16,  0,   7,   0,   0,   0,   42,  0,   16,  0,   7,   0,   0,   0,
    1,   64,  0,   0,   252, 255, 255, 255, 140, 0,   0,   11,  66,  0,   16,  0,   7,   0,   0,
    0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   58,  0,
    16,  0,   10,  0,   0,   0,   42,  0,   16,  0,   7,   0,   0,   0,   1,   0,   0,   7,   130,
    0,   16,  0,   8,   0,   0,   0,   26,  0,   16,  0,   10,  0,   0,   0,   1,   64,  0,   0,
    2,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   12,  0,   0,   0,   42,  0,   16,
    0,   7,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   18,  0,   0,   1,   54,  0,
    0,   5,   50,  0,   16,  0,   12,  0,   0,   0,   214, 5,   16,  0,   10,  0,   0,   0,   21,
    0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   50,  0,   16,  0,   12,  0,   0,   0,
    70,  0,   16,  0,   12,  0,   0,   0,   70,  0,   16,  0,   2,   0,   0,   0,   214, 5,   16,
    0,   9,   0,   0,   0,   78,  0,   0,   8,   194, 0,   16,  0,   12,  0,   0,   0,   0,   208,
    0,   0,   6,   4,   16,  0,   12,  0,   0,   0,   6,   8,   16,  0,   10,  0,   0,   0,   35,
    0,   0,   9,   66,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   12,  0,   0,   0,
    10,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   12,  0,   0,   0,   30,  0,   0,
    7,   66,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   42,  0,
    16,  0,   7,   0,   0,   0,   35,  0,   0,   10,  50,  0,   16,  0,   12,  0,   0,   0,   230,
    10,  16,  128, 65,  0,   0,   0,   12,  0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,
    70,  0,   16,  0,   12,  0,   0,   0,   35,  0,   0,   9,   130, 0,   16,  0,   8,   0,   0,
    0,   26,  0,   16,  0,   12,  0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   10,  0,
    16,  0,   12,  0,   0,   0,   41,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   58,
    0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,   9,
    66,  0,   16,  0,   7,   0,   0,   0,   42,  0,   16,  0,   7,   0,   0,   0,   42,  0,   16,
    0,   9,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   78,  0,   0,   8,   0,   208,
    0,   0,   34,  0,   16,  0,   11,  0,   0,   0,   42,  0,   16,  0,   7,   0,   0,   0,   10,
    0,   16,  0,   9,   0,   0,   0,   30,  0,   0,   10,  50,  0,   16,  0,   12,  0,   0,   0,
    134, 0,   16,  0,   6,   0,   0,   0,   2,   64,  0,   0,   2,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   83,  0,   0,   7,   66,  0,   16,  0,   12,  0,
    0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   12,  0,   0,   0,   35,
    0,   0,   9,   50,  0,   16,  0,   12,  0,   0,   0,   230, 10,  16,  0,   1,   0,   0,   0,
    70,  0,   16,  0,   2,   0,   0,   0,   134, 0,   16,  0,   12,  0,   0,   0,   78,  0,   0,
    8,   194, 0,   16,  0,   12,  0,   0,   0,   0,   208, 0,   0,   6,   4,   16,  0,   12,  0,
    0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   35,  0,   0,   10,  50,  0,   16,  0,   12,
    0,   0,   0,   230, 10,  16,  128, 65,  0,   0,   0,   12,  0,   0,   0,   70,  0,   16,  0,
    2,   0,   0,   0,   70,  0,   16,  0,   12,  0,   0,   0,   31,  0,   4,   3,   42,  0,   16,
    0,   8,   0,   0,   0,   85,  0,   0,   7,   130, 0,   16,  0,   7,   0,   0,   0,   10,  0,
    16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   41,  0,   0,   10,  50,
    0,   16,  0,   13,  0,   0,   0,   230, 10,  16,  0,   12,  0,   0,   0,   2,   64,  0,   0,
    1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,
    10,  50,  0,   16,  0,   13,  0,   0,   0,   70,  0,   16,  0,   13,  0,   0,   0,   2,   64,
    0,   0,   252, 255, 255, 255, 252, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   140,
    0,   0,   17,  50,  0,   16,  0,   13,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,
    1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   230, 10,  16,  0,   12,  0,
    0,   0,   70,  0,   16,  0,   13,  0,   0,   0,   140, 0,   0,   20,  194, 0,   16,  0,   7,
    0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,
    31,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,
    0,   1,   0,   0,   0,   6,   12,  16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   194,
    0,   16,  0,   7,   0,   0,   0,   166, 14,  16,  0,   7,   0,   0,   0,   6,   4,   16,  0,
    13,  0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,
    0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,
    4,   3,   58,  0,   16,  0,   8,   0,   0,   0,   140, 0,   0,   11,  66,  0,   16,  0,   7,
    0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,
    10,  0,   16,  0,   7,   0,   0,   0,   42,  0,   16,  0,   12,  0,   0,   0,   41,  0,   0,
    7,   130, 0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   12,  0,   0,   0,   1,   64,
    0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   58,
    0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255, 140, 0,   0,   11,
    130, 0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   0,   0,   58,  0,   16,  0,   12,  0,   0,   0,   58,  0,   16,  0,   8,   0,
    0,   0,   1,   0,   0,   7,   18,  0,   16,  0,   13,  0,   0,   0,   42,  0,   16,  0,   12,
    0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,
    7,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   13,  0,   0,
    0,   18,  0,   0,   1,   54,  0,   0,   5,   194, 0,   16,  0,   7,   0,   0,   0,   166, 14,
    16,  0,   12,  0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   194,
    0,   16,  0,   7,   0,   0,   0,   166, 14,  16,  0,   7,   0,   0,   0,   6,   4,   16,  0,
    2,   0,   0,   0,   6,   4,   16,  0,   12,  0,   0,   0,   78,  0,   0,   8,   50,  0,   16,
    0,   13,  0,   0,   0,   0,   208, 0,   0,   230, 10,  16,  0,   7,   0,   0,   0,   134, 0,
    16,  0,   10,  0,   0,   0,   35,  0,   0,   9,   130, 0,   16,  0,   8,   0,   0,   0,   26,
    0,   16,  0,   13,  0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,
    13,  0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   26,  0,   16,
    0,   4,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   35,  0,   0,   10,  194, 0,
    16,  0,   7,   0,   0,   0,   6,   4,   16,  128, 65,  0,   0,   0,   13,  0,   0,   0,   6,
    8,   16,  0,   10,  0,   0,   0,   166, 14,  16,  0,   7,   0,   0,   0,   35,  0,   0,   9,
    66,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,
    0,   10,  0,   0,   0,   42,  0,   16,  0,   7,   0,   0,   0,   41,  0,   0,   7,   66,  0,
    16,  0,   7,   0,   0,   0,   42,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   4,
    0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,
    8,   0,   0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   42,  0,   16,  0,   7,   0,   0,
    0,   78,  0,   0,   8,   0,   208, 0,   0,   66,  0,   16,  0,   11,  0,   0,   0,   42,  0,
    16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   30,  0,   0,   10,  50,
    0,   16,  0,   13,  0,   0,   0,   134, 0,   16,  0,   6,   0,   0,   0,   2,   64,  0,   0,
    3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   83,  0,   0,
    7,   66,  0,   16,  0,   13,  0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   26,  0,
    16,  0,   13,  0,   0,   0,   35,  0,   0,   9,   194, 0,   16,  0,   7,   0,   0,   0,   166,
    14,  16,  0,   1,   0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   6,   8,   16,  0,
    13,  0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   13,  0,   0,   0,   0,   208, 0,
    0,   230, 10,  16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   2,   0,   0,   0,   35,  0,
    0,   10,  194, 0,   16,  0,   7,   0,   0,   0,   6,   4,   16,  128, 65,  0,   0,   0,   13,
    0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   166, 14,  16,  0,   7,   0,   0,   0,
    31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,   0,   85,  0,   0,   7,   34,  0,   16,
    0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,
    0,   0,   41,  0,   0,   10,  194, 0,   16,  0,   13,  0,   0,   0,   6,   4,   16,  0,   13,
    0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,
    1,   0,   0,   0,   1,   0,   0,   10,  194, 0,   16,  0,   13,  0,   0,   0,   166, 14,  16,
    0,   13,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   252, 255,
    255, 255, 252, 255, 255, 255, 140, 0,   0,   17,  194, 0,   16,  0,   13,  0,   0,   0,   2,
    64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
    2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   6,   4,   16,  0,   13,  0,   0,   0,   166, 14,  16,  0,   13,  0,   0,   0,   140, 0,
    0,   20,  50,  0,   16,  0,   14,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   31,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,
    1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  0,   16,  0,   7,   0,   0,
    0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   30,  0,   0,   7,   194, 0,   16,  0,   13,  0,   0,   0,   166, 14,  16,  0,   13,
    0,   0,   0,   6,   4,   16,  0,   14,  0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,
    130, 0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,
    0,   1,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   8,   0,   0,   0,   140, 0,
    0,   11,  66,  0,   16,  0,   13,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,
    64,  0,   0,   1,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,
    13,  0,   0,   0,   41,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   26,  0,   16,
    0,   13,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   130, 0,
    16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   252,
    255, 255, 255, 140, 0,   0,   11,  130, 0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,
    1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   26,  0,   16,  0,   13,  0,   0,
    0,   58,  0,   16,  0,   8,   0,   0,   0,   1,   0,   0,   7,   18,  0,   16,  0,   14,  0,
    0,   0,   10,  0,   16,  0,   13,  0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,   30,
    0,   0,   7,   130, 0,   16,  0,   13,  0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,
    10,  0,   16,  0,   14,  0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   5,   194, 0,   16,
    0,   13,  0,   0,   0,   6,   4,   16,  0,   13,  0,   0,   0,   21,  0,   0,   1,   21,  0,
    0,   1,   35,  0,   0,   9,   194, 0,   16,  0,   13,  0,   0,   0,   166, 14,  16,  0,   13,
    0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   166, 14,  16,  0,   7,   0,   0,   0,
    78,  0,   0,   8,   50,  0,   16,  0,   14,  0,   0,   0,   0,   208, 0,   0,   230, 10,  16,
    0,   13,  0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   35,  0,   0,   9,   130, 0,
    16,  0,   8,   0,   0,   0,   26,  0,   16,  0,   14,  0,   0,   0,   10,  0,   16,  0,   0,
    0,   0,   0,   10,  0,   16,  0,   14,  0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,
    8,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,
    0,   35,  0,   0,   10,  194, 0,   16,  0,   13,  0,   0,   0,   6,   4,   16,  128, 65,  0,
    0,   0,   14,  0,   0,   0,   6,   8,   16,  0,   10,  0,   0,   0,   166, 14,  16,  0,   13,
    0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,   13,  0,   0,   0,   58,  0,   16,  0,
    13,  0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   42,  0,   16,  0,   13,  0,   0,
    0,   41,  0,   0,   7,   66,  0,   16,  0,   13,  0,   0,   0,   42,  0,   16,  0,   13,  0,
    0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,   9,   130, 0,   16,  0,   8,
    0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   42,  0,   16,  0,   9,   0,   0,   0,
    42,  0,   16,  0,   13,  0,   0,   0,   78,  0,   0,   8,   0,   208, 0,   0,   130, 0,   16,
    0,   11,  0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   9,   0,
    0,   0,   30,  0,   0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   246, 15,  16,  0,   0,
    0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   30,  0,   0,   10,  50,  0,   16,  0,
    14,  0,   0,   0,   134, 0,   16,  0,   6,   0,   0,   0,   2,   64,  0,   0,   4,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   83,  0,   0,   7,   66,  0,
    16,  0,   14,  0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   14,
    0,   0,   0,   35,  0,   0,   9,   194, 0,   16,  0,   13,  0,   0,   0,   166, 14,  16,  0,
    1,   0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   6,   8,   16,  0,   14,  0,   0,
    0,   78,  0,   0,   8,   50,  0,   16,  0,   14,  0,   0,   0,   0,   208, 0,   0,   230, 10,
    16,  0,   13,  0,   0,   0,   70,  0,   16,  0,   2,   0,   0,   0,   35,  0,   0,   10,  194,
    0,   16,  0,   13,  0,   0,   0,   6,   4,   16,  128, 65,  0,   0,   0,   14,  0,   0,   0,
    6,   4,   16,  0,   2,   0,   0,   0,   166, 14,  16,  0,   13,  0,   0,   0,   31,  0,   4,
    3,   42,  0,   16,  0,   8,   0,   0,   0,   85,  0,   0,   7,   34,  0,   16,  0,   7,   0,
    0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   41,
    0,   0,   10,  194, 0,   16,  0,   14,  0,   0,   0,   6,   4,   16,  0,   14,  0,   0,   0,
    2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,
    0,   1,   0,   0,   10,  194, 0,   16,  0,   14,  0,   0,   0,   166, 14,  16,  0,   14,  0,
    0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   252, 255, 255, 255, 252,
    255, 255, 255, 140, 0,   0,   17,  194, 0,   16,  0,   14,  0,   0,   0,   2,   64,  0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   4,
    16,  0,   14,  0,   0,   0,   166, 14,  16,  0,   14,  0,   0,   0,   140, 0,   0,   20,  50,
    0,   16,  0,   15,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   31,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,
    0,   0,   7,   194, 0,   16,  0,   14,  0,   0,   0,   166, 14,  16,  0,   14,  0,   0,   0,
    6,   4,   16,  0,   15,  0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   130, 0,   16,
    0,   8,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,
    0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   8,   0,   0,   0,   140, 0,   0,   11,  66,
    0,   16,  0,   14,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,   0,
    1,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   14,  0,   0,
    0,   41,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   26,  0,   16,  0,   14,  0,
    0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   130, 0,   16,  0,   8,
    0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255,
    140, 0,   0,   11,  130, 0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   0,   0,   26,  0,   16,  0,   14,  0,   0,   0,   58,  0,
    16,  0,   8,   0,   0,   0,   1,   0,   0,   7,   18,  0,   16,  0,   15,  0,   0,   0,   10,
    0,   16,  0,   14,  0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,   30,  0,   0,   7,
    130, 0,   16,  0,   14,  0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   10,  0,   16,
    0,   15,  0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   5,   194, 0,   16,  0,   14,  0,
    0,   0,   6,   4,   16,  0,   14,  0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   35,
    0,   0,   9,   194, 0,   16,  0,   14,  0,   0,   0,   166, 14,  16,  0,   14,  0,   0,   0,
    6,   4,   16,  0,   2,   0,   0,   0,   166, 14,  16,  0,   13,  0,   0,   0,   78,  0,   0,
    8,   50,  0,   16,  0,   15,  0,   0,   0,   0,   208, 0,   0,   230, 10,  16,  0,   14,  0,
    0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   35,  0,   0,   9,   130, 0,   16,  0,   8,
    0,   0,   0,   26,  0,   16,  0,   15,  0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,
    10,  0,   16,  0,   15,  0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,
    0,   26,  0,   16,  0,   4,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   35,  0,
    0,   10,  194, 0,   16,  0,   14,  0,   0,   0,   6,   4,   16,  128, 65,  0,   0,   0,   15,
    0,   0,   0,   6,   8,   16,  0,   10,  0,   0,   0,   166, 14,  16,  0,   14,  0,   0,   0,
    35,  0,   0,   9,   66,  0,   16,  0,   14,  0,   0,   0,   58,  0,   16,  0,   14,  0,   0,
    0,   10,  0,   16,  0,   10,  0,   0,   0,   42,  0,   16,  0,   14,  0,   0,   0,   41,  0,
    0,   7,   66,  0,   16,  0,   14,  0,   0,   0,   42,  0,   16,  0,   14,  0,   0,   0,   58,
    0,   16,  0,   4,   0,   0,   0,   35,  0,   0,   9,   130, 0,   16,  0,   8,   0,   0,   0,
    58,  0,   16,  0,   8,   0,   0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   42,  0,   16,
    0,   14,  0,   0,   0,   78,  0,   0,   8,   0,   208, 0,   0,   18,  0,   16,  0,   15,  0,
    0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   30,
    0,   0,   10,  50,  0,   16,  0,   16,  0,   0,   0,   134, 0,   16,  0,   6,   0,   0,   0,
    2,   64,  0,   0,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   83,  0,   0,   7,   66,  0,   16,  0,   16,  0,   0,   0,   26,  0,   16,  0,   1,   0,
    0,   0,   26,  0,   16,  0,   16,  0,   0,   0,   35,  0,   0,   9,   194, 0,   16,  0,   14,
    0,   0,   0,   166, 14,  16,  0,   1,   0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,
    6,   8,   16,  0,   16,  0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   16,  0,   0,
    0,   0,   208, 0,   0,   230, 10,  16,  0,   14,  0,   0,   0,   70,  0,   16,  0,   2,   0,
    0,   0,   35,  0,   0,   10,  194, 0,   16,  0,   14,  0,   0,   0,   6,   4,   16,  128, 65,
    0,   0,   0,   16,  0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   166, 14,  16,  0,
    14,  0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,   0,   85,  0,   0,
    7,   34,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   1,   64,
    0,   0,   1,   0,   0,   0,   41,  0,   0,   10,  194, 0,   16,  0,   16,  0,   0,   0,   6,
    4,   16,  0,   16,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   10,  194, 0,   16,  0,   16,  0,   0,
    0,   166, 14,  16,  0,   16,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   252, 255, 255, 255, 252, 255, 255, 255, 140, 0,   0,   17,  194, 0,   16,  0,   16,
    0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,
    1,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   6,   4,   16,  0,   16,  0,   0,   0,   166, 14,  16,  0,   16,  0,
    0,   0,   140, 0,   0,   20,  50,  0,   16,  0,   17,  0,   0,   0,   2,   64,  0,   0,   1,
    0,   0,   0,   31,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,
    1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  0,   16,
    0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   194, 0,   16,  0,   16,  0,   0,   0,   166,
    14,  16,  0,   16,  0,   0,   0,   6,   4,   16,  0,   17,  0,   0,   0,   18,  0,   0,   1,
    32,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,
    0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   8,   0,
    0,   0,   140, 0,   0,   11,  66,  0,   16,  0,   16,  0,   0,   0,   1,   64,  0,   0,   1,
    0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,
    10,  0,   16,  0,   16,  0,   0,   0,   41,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,
    0,   26,  0,   16,  0,   16,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,
    0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   1,
    64,  0,   0,   252, 255, 255, 255, 140, 0,   0,   11,  130, 0,   16,  0,   8,   0,   0,   0,
    1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   26,  0,   16,
    0,   16,  0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   1,   0,   0,   7,   18,  0,
    16,  0,   17,  0,   0,   0,   10,  0,   16,  0,   16,  0,   0,   0,   1,   64,  0,   0,   2,
    0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   16,  0,   0,   0,   58,  0,   16,  0,
    8,   0,   0,   0,   10,  0,   16,  0,   17,  0,   0,   0,   18,  0,   0,   1,   54,  0,   0,
    5,   194, 0,   16,  0,   16,  0,   0,   0,   6,   4,   16,  0,   16,  0,   0,   0,   21,  0,
    0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   194, 0,   16,  0,   16,  0,   0,   0,   166,
    14,  16,  0,   16,  0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   166, 14,  16,  0,
    14,  0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   17,  0,   0,   0,   0,   208, 0,
    0,   230, 10,  16,  0,   16,  0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   35,  0,
    0,   9,   130, 0,   16,  0,   8,   0,   0,   0,   26,  0,   16,  0,   17,  0,   0,   0,   10,
    0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   17,  0,   0,   0,   30,  0,   0,   7,
    130, 0,   16,  0,   8,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   58,  0,   16,
    0,   8,   0,   0,   0,   35,  0,   0,   10,  194, 0,   16,  0,   16,  0,   0,   0,   6,   4,
    16,  128, 65,  0,   0,   0,   17,  0,   0,   0,   6,   8,   16,  0,   10,  0,   0,   0,   166,
    14,  16,  0,   16,  0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,   16,  0,   0,   0,
    58,  0,   16,  0,   16,  0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   42,  0,   16,
    0,   16,  0,   0,   0,   41,  0,   0,   7,   66,  0,   16,  0,   16,  0,   0,   0,   42,  0,
    16,  0,   16,  0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,   9,   130,
    0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   42,  0,   16,  0,
    9,   0,   0,   0,   42,  0,   16,  0,   16,  0,   0,   0,   78,  0,   0,   8,   0,   208, 0,
    0,   34,  0,   16,  0,   15,  0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   10,  0,
    16,  0,   9,   0,   0,   0,   30,  0,   0,   10,  50,  0,   16,  0,   17,  0,   0,   0,   134,
    0,   16,  0,   6,   0,   0,   0,   2,   64,  0,   0,   6,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   83,  0,   0,   7,   66,  0,   16,  0,   17,  0,   0,
    0,   26,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   17,  0,   0,   0,   35,  0,
    0,   9,   194, 0,   16,  0,   16,  0,   0,   0,   166, 14,  16,  0,   1,   0,   0,   0,   6,
    4,   16,  0,   2,   0,   0,   0,   6,   8,   16,  0,   17,  0,   0,   0,   78,  0,   0,   8,
    50,  0,   16,  0,   17,  0,   0,   0,   0,   208, 0,   0,   230, 10,  16,  0,   16,  0,   0,
    0,   70,  0,   16,  0,   2,   0,   0,   0,   35,  0,   0,   10,  194, 0,   16,  0,   16,  0,
    0,   0,   6,   4,   16,  128, 65,  0,   0,   0,   17,  0,   0,   0,   6,   4,   16,  0,   2,
    0,   0,   0,   166, 14,  16,  0,   16,  0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,
    8,   0,   0,   0,   85,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,
    0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   41,  0,   0,   10,  194, 0,
    16,  0,   17,  0,   0,   0,   6,   4,   16,  0,   17,  0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   10,
    194, 0,   16,  0,   17,  0,   0,   0,   166, 14,  16,  0,   17,  0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   252, 255, 255, 255, 252, 255, 255, 255, 140, 0,
    0,   17,  194, 0,   16,  0,   17,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   4,   16,  0,   17,  0,   0,
    0,   166, 14,  16,  0,   17,  0,   0,   0,   140, 0,   0,   20,  50,  0,   16,  0,   18,  0,
    0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   31,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   194, 0,
    16,  0,   17,  0,   0,   0,   166, 14,  16,  0,   17,  0,   0,   0,   6,   4,   16,  0,   18,
    0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,
    10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,   4,
    3,   58,  0,   16,  0,   8,   0,   0,   0,   140, 0,   0,   11,  66,  0,   16,  0,   17,  0,
    0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   10,
    0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   17,  0,   0,   0,   41,  0,   0,   7,
    130, 0,   16,  0,   8,   0,   0,   0,   26,  0,   16,  0,   17,  0,   0,   0,   1,   64,  0,
    0,   1,   0,   0,   0,   1,   0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   58,  0,
    16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255, 140, 0,   0,   11,  130,
    0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   0,   0,   26,  0,   16,  0,   17,  0,   0,   0,   58,  0,   16,  0,   8,   0,   0,
    0,   1,   0,   0,   7,   18,  0,   16,  0,   18,  0,   0,   0,   10,  0,   16,  0,   17,  0,
    0,   0,   1,   64,  0,   0,   2,   0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   17,
    0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   18,  0,   0,   0,
    18,  0,   0,   1,   54,  0,   0,   5,   194, 0,   16,  0,   17,  0,   0,   0,   6,   4,   16,
    0,   17,  0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   194, 0,
    16,  0,   17,  0,   0,   0,   166, 14,  16,  0,   17,  0,   0,   0,   6,   4,   16,  0,   2,
    0,   0,   0,   166, 14,  16,  0,   16,  0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,
    18,  0,   0,   0,   0,   208, 0,   0,   230, 10,  16,  0,   17,  0,   0,   0,   134, 0,   16,
    0,   10,  0,   0,   0,   35,  0,   0,   9,   130, 0,   16,  0,   8,   0,   0,   0,   26,  0,
    16,  0,   18,  0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   18,
    0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   26,  0,   16,  0,
    4,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   35,  0,   0,   10,  194, 0,   16,
    0,   17,  0,   0,   0,   6,   4,   16,  128, 65,  0,   0,   0,   18,  0,   0,   0,   6,   8,
    16,  0,   10,  0,   0,   0,   166, 14,  16,  0,   17,  0,   0,   0,   35,  0,   0,   9,   66,
    0,   16,  0,   17,  0,   0,   0,   58,  0,   16,  0,   17,  0,   0,   0,   10,  0,   16,  0,
    10,  0,   0,   0,   42,  0,   16,  0,   17,  0,   0,   0,   41,  0,   0,   7,   66,  0,   16,
    0,   17,  0,   0,   0,   42,  0,   16,  0,   17,  0,   0,   0,   58,  0,   16,  0,   4,   0,
    0,   0,   35,  0,   0,   9,   130, 0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   8,
    0,   0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   42,  0,   16,  0,   17,  0,   0,   0,
    78,  0,   0,   8,   0,   208, 0,   0,   66,  0,   16,  0,   15,  0,   0,   0,   58,  0,   16,
    0,   8,   0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   30,  0,   0,   10,  50,  0,
    16,  0,   18,  0,   0,   0,   134, 0,   16,  0,   6,   0,   0,   0,   2,   64,  0,   0,   7,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   83,  0,   0,   7,
    66,  0,   16,  0,   18,  0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,
    0,   18,  0,   0,   0,   35,  0,   0,   9,   98,  0,   16,  0,   1,   0,   0,   0,   166, 11,
    16,  0,   1,   0,   0,   0,   6,   1,   16,  0,   2,   0,   0,   0,   6,   2,   16,  0,   18,
    0,   0,   0,   78,  0,   0,   8,   194, 0,   16,  0,   17,  0,   0,   0,   0,   208, 0,   0,
    86,  9,   16,  0,   1,   0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   35,  0,   0,
    10,  98,  0,   16,  0,   1,   0,   0,   0,   166, 11,  16,  128, 65,  0,   0,   0,   17,  0,
    0,   0,   6,   1,   16,  0,   2,   0,   0,   0,   86,  6,   16,  0,   1,   0,   0,   0,   31,
    0,   4,   3,   42,  0,   16,  0,   8,   0,   0,   0,   85,  0,   0,   7,   34,  0,   16,  0,
    7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,
    0,   41,  0,   0,   10,  50,  0,   16,  0,   18,  0,   0,   0,   230, 10,  16,  0,   17,  0,
    0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   1,   0,   0,   10,  50,  0,   16,  0,   18,  0,   0,   0,   70,  0,   16,  0,
    18,  0,   0,   0,   2,   64,  0,   0,   252, 255, 255, 255, 252, 255, 255, 255, 0,   0,   0,
    0,   0,   0,   0,   0,   140, 0,   0,   17,  50,  0,   16,  0,   18,  0,   0,   0,   2,   64,
    0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,
    64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    230, 10,  16,  0,   17,  0,   0,   0,   70,  0,   16,  0,   18,  0,   0,   0,   140, 0,   0,
    20,  194, 0,   16,  0,   18,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   1,   0,   0,   0,   31,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   6,   4,   16,  0,   7,   0,   0,   0,
    2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   30,  0,   0,   7,   50,  0,   16,  0,   18,  0,   0,   0,   230, 10,  16,  0,   18,  0,
    0,   0,   70,  0,   16,  0,   18,  0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   130,
    0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,
    1,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   1,   0,   0,   0,   140, 0,   0,
    11,  18,  0,   16,  0,   18,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,
    0,   0,   1,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   42,  0,   16,  0,   17,
    0,   0,   0,   41,  0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,
    17,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   130, 0,   16,
    0,   1,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   252, 255,
    255, 255, 140, 0,   0,   11,  130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   1,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   58,  0,   16,  0,   17,  0,   0,   0,
    58,  0,   16,  0,   1,   0,   0,   0,   1,   0,   0,   7,   34,  0,   16,  0,   7,   0,   0,
    0,   42,  0,   16,  0,   17,  0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,   30,  0,
    0,   7,   34,  0,   16,  0,   18,  0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   26,
    0,   16,  0,   7,   0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   5,   50,  0,   16,  0,
    18,  0,   0,   0,   230, 10,  16,  0,   17,  0,   0,   0,   21,  0,   0,   1,   21,  0,   0,
    1,   35,  0,   0,   9,   50,  0,   16,  0,   18,  0,   0,   0,   70,  0,   16,  0,   18,  0,
    0,   0,   70,  0,   16,  0,   2,   0,   0,   0,   150, 5,   16,  0,   1,   0,   0,   0,   78,
    0,   0,   8,   194, 0,   16,  0,   18,  0,   0,   0,   0,   208, 0,   0,   6,   4,   16,  0,
    18,  0,   0,   0,   6,   8,   16,  0,   10,  0,   0,   0,   35,  0,   0,   9,   130, 0,   16,
    0,   1,   0,   0,   0,   58,  0,   16,  0,   18,  0,   0,   0,   10,  0,   16,  0,   0,   0,
    0,   0,   42,  0,   16,  0,   18,  0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   1,
    0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,
    35,  0,   0,   10,  50,  0,   16,  0,   18,  0,   0,   0,   230, 10,  16,  128, 65,  0,   0,
    0,   18,  0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   70,  0,   16,  0,   18,  0,
    0,   0,   35,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   18,
    0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   10,  0,   16,  0,   18,  0,   0,   0,
    41,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,
    0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,   9,   130, 0,   16,  0,   1,   0,
    0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   26,
    0,   16,  0,   7,   0,   0,   0,   78,  0,   0,   8,   0,   208, 0,   0,   130, 0,   16,  0,
    15,  0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   9,   0,   0,
    0,   30,  0,   0,   7,   242, 0,   16,  0,   15,  0,   0,   0,   246, 15,  16,  0,   0,   0,
    0,   0,   70,  14,  16,  0,   15,  0,   0,   0,   41,  0,   0,   10,  242, 0,   16,  0,   11,
    0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   2,   0,   0,   0,
    2,   0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   165, 0,   0,   8,   18,  0,   16,
    0,   18,  0,   0,   0,   10,  0,   16,  0,   11,  0,   0,   0,   6,   112, 32,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   165, 0,   0,   8,   34,  0,   16,  0,   18,  0,   0,   0,   26,
    0,   16,  0,   11,  0,   0,   0,   6,   112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    165, 0,   0,   8,   66,  0,   16,  0,   18,  0,   0,   0,   42,  0,   16,  0,   11,  0,   0,
    0,   6,   112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   165, 0,   0,   8,   130, 0,
    16,  0,   18,  0,   0,   0,   58,  0,   16,  0,   11,  0,   0,   0,   6,   112, 32,  0,   0,
    0,   0,   0,   0,   0,   0,   0,   41,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,
    70,  14,  16,  0,   15,  0,   0,   0,   2,   64,  0,   0,   2,   0,   0,   0,   2,   0,   0,
    0,   2,   0,   0,   0,   2,   0,   0,   0,   165, 0,   0,   8,   18,  0,   16,  0,   15,  0,
    0,   0,   10,  0,   16,  0,   11,  0,   0,   0,   6,   112, 32,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   165, 0,   0,   8,   34,  0,   16,  0,   15,  0,   0,   0,   26,  0,   16,  0,
    11,  0,   0,   0,   6,   112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   165, 0,   0,
    8,   66,  0,   16,  0,   15,  0,   0,   0,   42,  0,   16,  0,   11,  0,   0,   0,   6,   112,
    32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   165, 0,   0,   8,   130, 0,   16,  0,   15,
    0,   0,   0,   58,  0,   16,  0,   11,  0,   0,   0,   6,   112, 32,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   4,   0,   0,   0,   76,  0,   0,
    3,   42,  0,   16,  0,   4,   0,   0,   0,   6,   0,   0,   3,   1,   64,  0,   0,   5,   0,
    0,   0,   1,   0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   2,
    0,   0,   0,   1,   64,  0,   0,   16,  0,   0,   0,   85,  0,   0,   7,   242, 0,   16,  0,
    11,  0,   0,   0,   70,  14,  16,  0,   18,  0,   0,   0,   246, 15,  16,  0,   1,   0,   0,
    0,   139, 0,   0,   15,  242, 0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   16,  0,
    0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  14,  16,  0,
    11,  0,   0,   0,   43,  0,   0,   5,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,
    0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,
    16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   1,   128, 58,  0,   1,   128, 58,  0,
    1,   128, 58,  0,   1,   128, 58,  52,  0,   0,   10,  242, 0,   16,  0,   18,  0,   0,   0,
    70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 191, 0,   0,   128,
    191, 0,   0,   128, 191, 0,   0,   128, 191, 85,  0,   0,   7,   242, 0,   16,  0,   11,  0,
    0,   0,   70,  14,  16,  0,   15,  0,   0,   0,   246, 15,  16,  0,   1,   0,   0,   0,   139,
    0,   0,   15,  242, 0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   16,  0,   0,   0,
    16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  14,  16,  0,   11,  0,
    0,   0,   43,  0,   0,   5,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,
    0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,
    11,  0,   0,   0,   2,   64,  0,   0,   0,   1,   128, 58,  0,   1,   128, 58,  0,   1,   128,
    58,  0,   1,   128, 58,  52,  0,   0,   10,  242, 0,   16,  0,   15,  0,   0,   0,   70,  14,
    16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 191, 0,   0,   128, 191, 0,
    0,   128, 191, 0,   0,   128, 191, 2,   0,   0,   1,   6,   0,   0,   3,   1,   64,  0,   0,
    7,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   2,   0,   0,   0,   85,  0,   0,
    10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   18,  0,   0,   0,   2,   64,
    0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   131,
    0,   0,   5,   242, 0,   16,  0,   18,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,
    85,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   15,  0,   0,
    0,   2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,
    0,   0,   131, 0,   0,   5,   242, 0,   16,  0,   15,  0,   0,   0,   70,  14,  16,  0,   11,
    0,   0,   0,   18,  0,   0,   1,   131, 0,   0,   5,   242, 0,   16,  0,   18,  0,   0,   0,
    70,  14,  16,  0,   18,  0,   0,   0,   131, 0,   0,   5,   242, 0,   16,  0,   15,  0,   0,
    0,   70,  14,  16,  0,   15,  0,   0,   0,   21,  0,   0,   1,   2,   0,   0,   1,   10,  0,
    0,   1,   31,  0,   4,   3,   58,  0,   16,  0,   2,   0,   0,   0,   54,  0,   0,   8,   242,
    0,   16,  0,   18,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,
    0,   0,   128, 63,  0,   0,   128, 63,  54,  0,   0,   8,   242, 0,   16,  0,   15,  0,   0,
    0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,
    128, 63,  21,  0,   0,   1,   2,   0,   0,   1,   23,  0,   0,   1,   18,  0,   0,   1,   76,
    0,   0,   3,   42,  0,   16,  0,   4,   0,   0,   0,   6,   0,   0,   3,   1,   64,  0,   0,
    0,   0,   0,   0,   6,   0,   0,   3,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,
    7,   130, 0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   5,   0,   0,   0,   1,   64,
    0,   0,   16,  0,   0,   0,   55,  0,   0,   9,   130, 0,   16,  0,   1,   0,   0,   0,   58,
    0,   16,  0,   2,   0,   0,   0,   1,   64,  0,   0,   24,  0,   0,   0,   58,  0,   16,  0,
    1,   0,   0,   0,   85,  0,   0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,
    0,   18,  0,   0,   0,   246, 15,  16,  0,   1,   0,   0,   0,   1,   0,   0,   10,  242, 0,
    16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   255,
    0,   0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   86,  0,   0,   5,
    242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,
    10,  242, 0,   16,  0,   18,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,
    0,   0,   129, 128, 128, 59,  129, 128, 128, 59,  129, 128, 128, 59,  129, 128, 128, 59,  85,
    0,   0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   15,  0,   0,   0,
    246, 15,  16,  0,   1,   0,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   11,  0,   0,
    0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   255, 0,   0,   0,   255, 0,
    0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   86,  0,   0,   5,   242, 0,   16,  0,   11,
    0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,
    15,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   129, 128, 128,
    59,  129, 128, 128, 59,  129, 128, 128, 59,  129, 128, 128, 59,  2,   0,   0,   1,   6,   0,
    0,   3,   1,   64,  0,   0,   2,   0,   0,   0,   6,   0,   0,   3,   1,   64,  0,   0,   10,
    0,   0,   0,   6,   0,   0,   3,   1,   64,  0,   0,   3,   0,   0,   0,   6,   0,   0,   3,
    1,   64,  0,   0,   12,  0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   2,   0,   0,
    0,   85,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   18,  0,
    0,   0,   2,   64,  0,   0,   30,  0,   0,   0,   30,  0,   0,   0,   30,  0,   0,   0,   30,
    0,   0,   0,   86,  0,   0,   5,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,
    11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   18,  0,   0,   0,   70,  14,  16,
    0,   11,  0,   0,   0,   2,   64,  0,   0,   171, 170, 170, 62,  171, 170, 170, 62,  171, 170,
    170, 62,  171, 170, 170, 62,  85,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,
    14,  16,  0,   15,  0,   0,   0,   2,   64,  0,   0,   30,  0,   0,   0,   30,  0,   0,   0,
    30,  0,   0,   0,   30,  0,   0,   0,   86,  0,   0,   5,   242, 0,   16,  0,   11,  0,   0,
    0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   15,  0,
    0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   171, 170, 170, 62,  171,
    170, 170, 62,  171, 170, 170, 62,  171, 170, 170, 62,  18,  0,   0,   1,   1,   0,   0,   7,
    130, 0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,
    0,   20,  0,   0,   0,   32,  0,   0,   10,  50,  0,   16,  0,   11,  0,   0,   0,   166, 10,
    16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   2,   0,   0,   0,   10,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   60,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,
    26,  0,   16,  0,   11,  0,   0,   0,   10,  0,   16,  0,   11,  0,   0,   0,   31,  0,   4,
    3,   26,  0,   16,  0,   7,   0,   0,   0,   85,  0,   0,   7,   242, 0,   16,  0,   11,  0,
    0,   0,   70,  14,  16,  0,   18,  0,   0,   0,   246, 15,  16,  0,   1,   0,   0,   0,   1,
    0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,
    2,   64,  0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,
    0,   86,  0,   0,   5,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,
    0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   18,  0,   0,   0,   70,  14,  16,  0,   11,
    0,   0,   0,   2,   64,  0,   0,   8,   32,  128, 58,  8,   32,  128, 58,  8,   32,  128, 58,
    8,   32,  128, 58,  85,  0,   0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,
    0,   15,  0,   0,   0,   246, 15,  16,  0,   1,   0,   0,   0,   1,   0,   0,   10,  242, 0,
    16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   255,
    3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   86,  0,   0,   5,
    242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,
    10,  242, 0,   16,  0,   15,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,
    0,   0,   8,   32,  128, 58,  8,   32,  128, 58,  8,   32,  128, 58,  8,   32,  128, 58,  18,
    0,   0,   1,   85,  0,   0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,
    18,  0,   0,   0,   246, 15,  16,  0,   1,   0,   0,   0,   1,   0,   0,   10,  242, 0,   16,
    0,   19,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   255, 3,
    0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   1,   0,   0,   10,  242,
    0,   16,  0,   20,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,
    127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   138, 0,   0,
    15,  242, 0,   16,  0,   21,  0,   0,   0,   2,   64,  0,   0,   3,   0,   0,   0,   3,   0,
    0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   2,   64,  0,   0,   7,   0,   0,   0,   7,
    0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,
    135, 0,   0,   5,   242, 0,   16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,
    0,   30,  0,   0,   10,  242, 0,   16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   22,  0,
    0,   0,   2,   64,  0,   0,   232, 255, 255, 255, 232, 255, 255, 255, 232, 255, 255, 255, 232,
    255, 255, 255, 55,  0,   0,   12,  242, 0,   16,  0,   22,  0,   0,   0,   70,  14,  16,  0,
    20,  0,   0,   0,   70,  14,  16,  0,   22,  0,   0,   0,   2,   64,  0,   0,   8,   0,   0,
    0,   8,   0,   0,   0,   8,   0,   0,   0,   8,   0,   0,   0,   30,  0,   0,   11,  242, 0,
    16,  0,   23,  0,   0,   0,   70,  14,  16,  128, 65,  0,   0,   0,   22,  0,   0,   0,   2,
    64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
    55,  0,   0,   9,   242, 0,   16,  0,   23,  0,   0,   0,   70,  14,  16,  0,   21,  0,   0,
    0,   70,  14,  16,  0,   21,  0,   0,   0,   70,  14,  16,  0,   23,  0,   0,   0,   140, 0,
    0,   17,  242, 0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   7,   0,   0,   0,   7,
    0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   70,  14,  16,  0,   22,  0,   0,   0,
    70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   11,  0,
    0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   127, 0,   0,   0,   127,
    0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   55,  0,   0,   9,   242, 0,   16,  0,
    11,  0,   0,   0,   70,  14,  16,  0,   21,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,
    0,   70,  14,  16,  0,   11,  0,   0,   0,   41,  0,   0,   10,  242, 0,   16,  0,   20,  0,
    0,   0,   70,  14,  16,  0,   23,  0,   0,   0,   2,   64,  0,   0,   23,  0,   0,   0,   23,
    0,   0,   0,   23,  0,   0,   0,   23,  0,   0,   0,   30,  0,   0,   10,  242, 0,   16,  0,
    20,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,
    62,  0,   0,   0,   62,  0,   0,   0,   62,  0,   0,   0,   62,  41,  0,   0,   10,  242, 0,
    16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   16,
    0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   30,  0,   0,   7,
    242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   70,  14,  16,
    0,   11,  0,   0,   0,   55,  0,   0,   12,  242, 0,   16,  0,   18,  0,   0,   0,   70,  14,
    16,  0,   19,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   85,  0,   0,   7,
    242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   15,  0,   0,   0,   246, 15,  16,
    0,   1,   0,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   19,  0,   0,   0,   70,  14,
    16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255,
    3,   0,   0,   255, 3,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   20,  0,   0,   0,
    70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   127, 0,   0,   0,   127, 0,   0,
    0,   127, 0,   0,   0,   127, 0,   0,   0,   138, 0,   0,   15,  242, 0,   16,  0,   21,  0,
    0,   0,   2,   64,  0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   3,
    0,   0,   0,   2,   64,  0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,
    7,   0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   135, 0,   0,   5,   242, 0,   16,
    0,   22,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   30,  0,   0,   10,  242, 0,
    16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   22,  0,   0,   0,   2,   64,  0,   0,   232,
    255, 255, 255, 232, 255, 255, 255, 232, 255, 255, 255, 232, 255, 255, 255, 55,  0,   0,   12,
    242, 0,   16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   70,  14,  16,
    0,   22,  0,   0,   0,   2,   64,  0,   0,   8,   0,   0,   0,   8,   0,   0,   0,   8,   0,
    0,   0,   8,   0,   0,   0,   30,  0,   0,   11,  242, 0,   16,  0,   23,  0,   0,   0,   70,
    14,  16,  128, 65,  0,   0,   0,   22,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,
    1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   55,  0,   0,   9,   242, 0,   16,
    0,   23,  0,   0,   0,   70,  14,  16,  0,   21,  0,   0,   0,   70,  14,  16,  0,   21,  0,
    0,   0,   70,  14,  16,  0,   23,  0,   0,   0,   140, 0,   0,   17,  242, 0,   16,  0,   11,
    0,   0,   0,   2,   64,  0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,
    7,   0,   0,   0,   70,  14,  16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,
    0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,
    0,   0,   0,   2,   64,  0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,
    127, 0,   0,   0,   55,  0,   0,   9,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,
    0,   21,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   70,  14,  16,  0,   11,  0,
    0,   0,   41,  0,   0,   10,  242, 0,   16,  0,   20,  0,   0,   0,   70,  14,  16,  0,   23,
    0,   0,   0,   2,   64,  0,   0,   23,  0,   0,   0,   23,  0,   0,   0,   23,  0,   0,   0,
    23,  0,   0,   0,   30,  0,   0,   10,  242, 0,   16,  0,   20,  0,   0,   0,   70,  14,  16,
    0,   20,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   62,  0,   0,   0,   62,  0,   0,
    0,   62,  0,   0,   0,   62,  41,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,
    14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,
    16,  0,   0,   0,   16,  0,   0,   0,   30,  0,   0,   7,   242, 0,   16,  0,   11,  0,   0,
    0,   70,  14,  16,  0,   20,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   55,  0,
    0,   12,  242, 0,   16,  0,   15,  0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   70,
    14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   2,   0,   0,
    1,   6,   0,   0,   3,   1,   64,  0,   0,   4,   0,   0,   0,   31,  0,   4,   3,   58,  0,
    16,  0,   2,   0,   0,   0,   54,  0,   0,   8,   242, 0,   16,  0,   18,  0,   0,   0,   2,
    64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,
    54,  0,   0,   8,   242, 0,   16,  0,   15,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128,
    63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  18,  0,   0,   1,   139, 0,
    0,   15,  242, 0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   16,  0,   0,   0,   16,
    0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  14,  16,  0,   18,  0,   0,
    0,   43,  0,   0,   5,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,
    0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,
    0,   0,   0,   2,   64,  0,   0,   0,   1,   128, 58,  0,   1,   128, 58,  0,   1,   128, 58,
    0,   1,   128, 58,  52,  0,   0,   10,  242, 0,   16,  0,   18,  0,   0,   0,   70,  14,  16,
    0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 191, 0,   0,   128, 191, 0,   0,
    128, 191, 0,   0,   128, 191, 139, 0,   0,   15,  242, 0,   16,  0,   11,  0,   0,   0,   2,
    64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,
    2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   70,  14,  16,  0,   15,  0,   0,   0,   43,  0,   0,   5,   242, 0,   16,  0,   11,  0,
    0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   11,
    0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   1,   128, 58,
    0,   1,   128, 58,  0,   1,   128, 58,  0,   1,   128, 58,  52,  0,   0,   10,  242, 0,   16,
    0,   15,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,
    128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 21,  0,   0,   1,   2,
    0,   0,   1,   6,   0,   0,   3,   1,   64,  0,   0,   6,   0,   0,   0,   31,  0,   4,   3,
    58,  0,   16,  0,   2,   0,   0,   0,   54,  0,   0,   8,   242, 0,   16,  0,   18,  0,   0,
    0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,
    128, 63,  54,  0,   0,   8,   242, 0,   16,  0,   15,  0,   0,   0,   2,   64,  0,   0,   0,
    0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  18,  0,   0,   1,
    131, 0,   0,   5,   242, 0,   16,  0,   18,  0,   0,   0,   70,  14,  16,  0,   18,  0,   0,
    0,   131, 0,   0,   5,   242, 0,   16,  0,   15,  0,   0,   0,   70,  14,  16,  0,   15,  0,
    0,   0,   21,  0,   0,   1,   2,   0,   0,   1,   10,  0,   0,   1,   31,  0,   4,   3,   58,
    0,   16,  0,   2,   0,   0,   0,   54,  0,   0,   8,   242, 0,   16,  0,   18,  0,   0,   0,
    2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128,
    63,  54,  0,   0,   8,   242, 0,   16,  0,   15,  0,   0,   0,   2,   64,  0,   0,   0,   0,
    128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  21,  0,   0,   1,   2,
    0,   0,   1,   23,  0,   0,   1,   21,  0,   0,   1,   31,  0,   4,   3,   58,  0,   16,  0,
    3,   0,   0,   0,   54,  32,  0,   5,   242, 0,   16,  0,   18,  0,   0,   0,   70,  14,  16,
    0,   18,  0,   0,   0,   29,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,
    16,  0,   18,  0,   0,   0,   2,   64,  0,   0,   193, 192, 192, 62,  193, 192, 192, 62,  193,
    192, 192, 62,  193, 192, 192, 62,  31,  0,   4,   3,   10,  0,   16,  0,   11,  0,   0,   0,
    29,  0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   18,  0,   0,
    0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,   58,  0,   16,  0,   1,   0,
    0,   0,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   0,   60,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   128, 196, 18,  0,   0,   1,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   128, 59,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   128, 195, 21,  0,   0,   1,   18,  0,   0,   1,   29,
    0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   18,  0,   0,   0,
    1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,   58,  0,   16,  0,   8,   0,   0,
    0,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,
    0,   59,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   128, 194, 18,  0,   0,   1,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,
    1,   64,  0,   0,   0,   0,   128, 58,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,
    0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   10,
    0,   16,  0,   18,  0,   0,   0,   50,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,
    58,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  26,  0,   16,
    0,   7,   0,   0,   0,   56,  0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,   58,  0,
    16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   67,  0,   0,   5,   130,
    0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   0,   0,   0,   7,
    130, 0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,
    0,   7,   0,   0,   0,   56,  0,   0,   7,   18,  0,   16,  0,   18,  0,   0,   0,   58,  0,
    16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   8,   32,  128, 58,  31,  0,   4,   3,   26,
    0,   16,  0,   11,  0,   0,   0,   29,  0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,
    26,  0,   16,  0,   18,  0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,
    3,   58,  0,   16,  0,   1,   0,   0,   0,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   0,   60,  54,  0,   0,   5,   34,  0,   16,  0,   7,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 196, 18,  0,   0,   1,   54,  0,   0,   5,
    130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 59,  54,  0,   0,
    5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 195, 21,  0,
    0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   26,
    0,   16,  0,   18,  0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,
    58,  0,   16,  0,   8,   0,   0,   0,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   0,   59,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   128, 194, 18,  0,   0,   1,   54,  0,   0,   5,   130,
    0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 58,  54,  0,   0,   5,
    34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   21,  0,   0,
    1,   21,  0,   0,   1,   56,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   58,  0,
    16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   18,  0,   0,   0,   50,  0,   0,   9,   34,
    0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   127, 72,  26,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   130, 0,   16,
    0,   1,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   7,   0,
    0,   0,   67,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   1,
    0,   0,   0,   0,   0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,
    1,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   34,  0,   16,
    0,   18,  0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   8,   32,
    128, 58,  31,  0,   4,   3,   42,  0,   16,  0,   11,  0,   0,   0,   29,  0,   0,   7,   130,
    0,   16,  0,   1,   0,   0,   0,   42,  0,   16,  0,   18,  0,   0,   0,   1,   64,  0,   0,
    193, 192, 64,  63,  31,  0,   4,   3,   58,  0,   16,  0,   1,   0,   0,   0,   54,  0,   0,
    5,   130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   60,  54,  0,
    0,   5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 196, 18,
    0,   0,   1,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   128, 59,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   128, 195, 21,  0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   130, 0,
    16,  0,   8,   0,   0,   0,   42,  0,   16,  0,   18,  0,   0,   0,   1,   64,  0,   0,   129,
    128, 128, 62,  31,  0,   4,   3,   58,  0,   16,  0,   8,   0,   0,   0,   54,  0,   0,   5,
    130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   59,  54,  0,   0,
    5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 194, 18,  0,
    0,   1,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   128, 58,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   130, 0,   16,
    0,   8,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   42,  0,   16,  0,   18,  0,
    0,   0,   50,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   8,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  26,  0,   16,  0,   7,   0,   0,   0,
    56,  0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,
    0,   26,  0,   16,  0,   7,   0,   0,   0,   67,  0,   0,   5,   130, 0,   16,  0,   1,   0,
    0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   0,   0,   0,   7,   130, 0,   16,  0,   1,
    0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,
    56,  0,   0,   7,   66,  0,   16,  0,   18,  0,   0,   0,   58,  0,   16,  0,   1,   0,   0,
    0,   1,   64,  0,   0,   8,   32,  128, 58,  31,  0,   4,   3,   58,  0,   16,  0,   11,  0,
    0,   0,   29,  0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   18,
    0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,   58,  0,   16,  0,
    1,   0,   0,   0,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   0,   60,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,
    0,   0,   0,   0,   128, 196, 18,  0,   0,   1,   54,  0,   0,   5,   130, 0,   16,  0,   1,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 59,  54,  0,   0,   5,   34,  0,   16,  0,
    7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 195, 21,  0,   0,   1,   18,  0,   0,
    1,   29,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   18,  0,
    0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,   58,  0,   16,  0,   8,
    0,   0,   0,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   0,   59,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   128, 194, 18,  0,   0,   1,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   128, 58,  54,  0,   0,   5,   34,  0,   16,  0,   7,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,
    56,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,
    0,   58,  0,   16,  0,   18,  0,   0,   0,   50,  0,   0,   9,   34,  0,   16,  0,   7,   0,
    0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  26,
    0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,
    58,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   67,  0,   0,
    5,   130, 0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   0,   0,
    0,   7,   130, 0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   26,
    0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   130, 0,   16,  0,   18,  0,   0,   0,
    58,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   8,   32,  128, 58,  54,  32,  0,
    5,   242, 0,   16,  0,   15,  0,   0,   0,   70,  14,  16,  0,   15,  0,   0,   0,   29,  0,
    0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   15,  0,   0,   0,   2,
    64,  0,   0,   193, 192, 192, 62,  193, 192, 192, 62,  193, 192, 192, 62,  193, 192, 192, 62,
    31,  0,   4,   3,   10,  0,   16,  0,   11,  0,   0,   0,   29,  0,   0,   7,   130, 0,   16,
    0,   1,   0,   0,   0,   10,  0,   16,  0,   15,  0,   0,   0,   1,   64,  0,   0,   193, 192,
    64,  63,  31,  0,   4,   3,   58,  0,   16,  0,   1,   0,   0,   0,   54,  0,   0,   5,   130,
    0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   60,  54,  0,   0,   5,
    34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 196, 18,  0,   0,
    1,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,
    128, 59,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   128, 195, 21,  0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   130, 0,   16,  0,
    8,   0,   0,   0,   10,  0,   16,  0,   15,  0,   0,   0,   1,   64,  0,   0,   129, 128, 128,
    62,  31,  0,   4,   3,   58,  0,   16,  0,   8,   0,   0,   0,   54,  0,   0,   5,   130, 0,
    16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   59,  54,  0,   0,   5,   34,
    0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 194, 18,  0,   0,   1,
    54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128,
    58,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,
    0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   130, 0,   16,  0,   8,
    0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   15,  0,   0,   0,
    50,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   127, 72,  26,  0,   16,  0,   7,   0,   0,   0,   56,  0,
    0,   7,   130, 0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   26,
    0,   16,  0,   7,   0,   0,   0,   67,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,
    58,  0,   16,  0,   1,   0,   0,   0,   0,   0,   0,   7,   130, 0,   16,  0,   1,   0,   0,
    0,   58,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   56,  0,
    0,   7,   18,  0,   16,  0,   15,  0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   1,
    64,  0,   0,   8,   32,  128, 58,  31,  0,   4,   3,   26,  0,   16,  0,   11,  0,   0,   0,
    29,  0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   15,  0,   0,
    0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,   58,  0,   16,  0,   1,   0,
    0,   0,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   0,   60,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   128, 196, 18,  0,   0,   1,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   128, 59,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   128, 195, 21,  0,   0,   1,   18,  0,   0,   1,   29,
    0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   26,  0,   16,  0,   15,  0,   0,   0,
    1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,   58,  0,   16,  0,   8,   0,   0,
    0,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,
    0,   59,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   128, 194, 18,  0,   0,   1,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,
    1,   64,  0,   0,   0,   0,   128, 58,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,
    0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   26,
    0,   16,  0,   15,  0,   0,   0,   50,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,
    58,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  26,  0,   16,
    0,   7,   0,   0,   0,   56,  0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,   58,  0,
    16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   67,  0,   0,   5,   130,
    0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   0,   0,   0,   7,
    130, 0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,
    0,   7,   0,   0,   0,   56,  0,   0,   7,   34,  0,   16,  0,   15,  0,   0,   0,   58,  0,
    16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   8,   32,  128, 58,  31,  0,   4,   3,   42,
    0,   16,  0,   11,  0,   0,   0,   29,  0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,
    42,  0,   16,  0,   15,  0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,
    3,   58,  0,   16,  0,   1,   0,   0,   0,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   0,   60,  54,  0,   0,   5,   34,  0,   16,  0,   7,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 196, 18,  0,   0,   1,   54,  0,   0,   5,
    130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 59,  54,  0,   0,
    5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 195, 21,  0,
    0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   42,
    0,   16,  0,   15,  0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,
    58,  0,   16,  0,   8,   0,   0,   0,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   0,   59,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   128, 194, 18,  0,   0,   1,   54,  0,   0,   5,   130,
    0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 58,  54,  0,   0,   5,
    34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   21,  0,   0,
    1,   21,  0,   0,   1,   56,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   58,  0,
    16,  0,   1,   0,   0,   0,   42,  0,   16,  0,   15,  0,   0,   0,   50,  0,   0,   9,   34,
    0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   127, 72,  26,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   130, 0,   16,
    0,   1,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   7,   0,
    0,   0,   67,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   1,
    0,   0,   0,   0,   0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,
    1,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   66,  0,   16,
    0,   15,  0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   8,   32,
    128, 58,  31,  0,   4,   3,   58,  0,   16,  0,   11,  0,   0,   0,   29,  0,   0,   7,   130,
    0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   15,  0,   0,   0,   1,   64,  0,   0,
    193, 192, 64,  63,  31,  0,   4,   3,   58,  0,   16,  0,   1,   0,   0,   0,   54,  0,   0,
    5,   130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   60,  54,  0,
    0,   5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 196, 18,
    0,   0,   1,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   128, 59,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   128, 195, 21,  0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   130, 0,
    16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   15,  0,   0,   0,   1,   64,  0,   0,   129,
    128, 128, 62,  31,  0,   4,   3,   58,  0,   16,  0,   8,   0,   0,   0,   54,  0,   0,   5,
    130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   59,  54,  0,   0,
    5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 194, 18,  0,
    0,   1,   54,  0,   0,   5,   130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   128, 58,  54,  0,   0,   5,   34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   130, 0,   16,
    0,   8,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   15,  0,
    0,   0,   50,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   8,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  26,  0,   16,  0,   7,   0,   0,   0,
    56,  0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,
    0,   26,  0,   16,  0,   7,   0,   0,   0,   67,  0,   0,   5,   130, 0,   16,  0,   1,   0,
    0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   0,   0,   0,   7,   130, 0,   16,  0,   1,
    0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,
    56,  0,   0,   7,   130, 0,   16,  0,   15,  0,   0,   0,   58,  0,   16,  0,   1,   0,   0,
    0,   1,   64,  0,   0,   8,   32,  128, 58,  21,  0,   0,   1,   80,  0,   0,   7,   130, 0,
    16,  0,   1,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   4,
    0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   1,   0,   0,   0,   56,  0,   0,   7,
    130, 0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   0,   63,  60,  0,   0,   7,   18,  0,   16,  0,   11,  0,   0,   0,   10,  0,
    16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,   4,   3,   42,
    0,   16,  0,   8,   0,   0,   0,   85,  0,   0,   7,   34,  0,   16,  0,   11,  0,   0,   0,
    10,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   41,  0,   0,
    10,  50,  0,   16,  0,   19,  0,   0,   0,   70,  0,   16,  0,   8,   0,   0,   0,   2,   64,
    0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,
    0,   0,   10,  50,  0,   16,  0,   19,  0,   0,   0,   70,  0,   16,  0,   19,  0,   0,   0,
    2,   64,  0,   0,   252, 255, 255, 255, 252, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,
    0,   140, 0,   0,   17,  50,  0,   16,  0,   19,  0,   0,   0,   2,   64,  0,   0,   1,   0,
    0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  0,   16,  0,
    8,   0,   0,   0,   70,  0,   16,  0,   19,  0,   0,   0,   140, 0,   0,   20,  194, 0,   16,
    0,   19,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,
    0,   0,   31,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,
    0,   0,   0,   1,   0,   0,   0,   6,   4,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,
    7,   50,  0,   16,  0,   19,  0,   0,   0,   230, 10,  16,  0,   19,  0,   0,   0,   70,  0,
    16,  0,   19,  0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   34,  0,   16,  0,   7,
    0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,
    31,  0,   4,   3,   26,  0,   16,  0,   7,   0,   0,   0,   1,   0,   0,   10,  194, 0,   16,
    0,   19,  0,   0,   0,   6,   0,   16,  0,   8,   0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   253, 255, 255, 255, 2,   0,   0,   0,   30,  0,   0,   7,   18,
    0,   16,  0,   19,  0,   0,   0,   42,  0,   16,  0,   19,  0,   0,   0,   1,   64,  0,   0,
    2,   0,   0,   0,   41,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,
    0,   8,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   34,  0,
    16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   252,
    255, 255, 255, 140, 0,   0,   11,  34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,
    1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   26,  0,   16,  0,   8,   0,   0,
    0,   26,  0,   16,  0,   7,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   19,  0,
    0,   0,   58,  0,   16,  0,   19,  0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   18,
    0,   0,   1,   54,  0,   0,   5,   50,  0,   16,  0,   19,  0,   0,   0,   70,  0,   16,  0,
    8,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   50,  0,   16,
    0,   19,  0,   0,   0,   70,  0,   16,  0,   19,  0,   0,   0,   70,  0,   16,  0,   2,   0,
    0,   0,   214, 5,   16,  0,   6,   0,   0,   0,   78,  0,   0,   8,   194, 0,   16,  0,   19,
    0,   0,   0,   0,   208, 0,   0,   6,   4,   16,  0,   19,  0,   0,   0,   6,   8,   16,  0,
    10,  0,   0,   0,   35,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,
    0,   19,  0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   19,  0,
    0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   4,
    0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   35,  0,   0,   10,  50,  0,   16,  0,
    19,  0,   0,   0,   230, 10,  16,  128, 65,  0,   0,   0,   19,  0,   0,   0,   134, 0,   16,
    0,   10,  0,   0,   0,   70,  0,   16,  0,   19,  0,   0,   0,   35,  0,   0,   9,   130, 0,
    16,  0,   8,   0,   0,   0,   26,  0,   16,  0,   19,  0,   0,   0,   10,  0,   16,  0,   10,
    0,   0,   0,   10,  0,   16,  0,   19,  0,   0,   0,   41,  0,   0,   7,   130, 0,   16,  0,
    8,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,
    0,   35,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,
    0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   78,
    0,   0,   8,   0,   208, 0,   0,   18,  0,   16,  0,   19,  0,   0,   0,   26,  0,   16,  0,
    7,   0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,
    0,   8,   0,   0,   0,   85,  0,   0,   7,   66,  0,   16,  0,   11,  0,   0,   0,   10,  0,
    16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   41,  0,   0,   10,  50,
    0,   16,  0,   20,  0,   0,   0,   214, 5,   16,  0,   10,  0,   0,   0,   2,   64,  0,   0,
    1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,
    10,  50,  0,   16,  0,   20,  0,   0,   0,   70,  0,   16,  0,   20,  0,   0,   0,   2,   64,
    0,   0,   252, 255, 255, 255, 252, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   140,
    0,   0,   17,  50,  0,   16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,
    1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   214, 5,   16,  0,   10,  0,
    0,   0,   70,  0,   16,  0,   20,  0,   0,   0,   140, 0,   0,   20,  194, 0,   16,  0,   20,
    0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,
    31,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,
    0,   1,   0,   0,   0,   6,   8,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   50,
    0,   16,  0,   20,  0,   0,   0,   230, 10,  16,  0,   20,  0,   0,   0,   70,  0,   16,  0,
    20,  0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,
    0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,
    4,   3,   26,  0,   16,  0,   7,   0,   0,   0,   1,   0,   0,   10,  194, 0,   16,  0,   20,
    0,   0,   0,   86,  5,   16,  0,   10,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   253, 255, 255, 255, 2,   0,   0,   0,   30,  0,   0,   7,   18,  0,   16,
    0,   20,  0,   0,   0,   42,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,   0,   2,   0,
    0,   0,   41,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   10,
    0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   34,  0,   16,  0,
    7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255,
    255, 140, 0,   0,   11,  34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   58,  0,   16,  0,   10,  0,   0,   0,   26,
    0,   16,  0,   7,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   20,  0,   0,   0,
    58,  0,   16,  0,   20,  0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   18,  0,   0,
    1,   54,  0,   0,   5,   50,  0,   16,  0,   20,  0,   0,   0,   214, 5,   16,  0,   10,  0,
    0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   50,  0,   16,  0,   20,
    0,   0,   0,   70,  0,   16,  0,   20,  0,   0,   0,   70,  0,   16,  0,   2,   0,   0,   0,
    214, 5,   16,  0,   9,   0,   0,   0,   78,  0,   0,   8,   194, 0,   16,  0,   20,  0,   0,
    0,   0,   208, 0,   0,   6,   4,   16,  0,   20,  0,   0,   0,   6,   8,   16,  0,   10,  0,
    0,   0,   35,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   20,
    0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   20,  0,   0,   0,
    30,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,
    0,   26,  0,   16,  0,   7,   0,   0,   0,   35,  0,   0,   10,  50,  0,   16,  0,   20,  0,
    0,   0,   230, 10,  16,  128, 65,  0,   0,   0,   20,  0,   0,   0,   134, 0,   16,  0,   10,
    0,   0,   0,   70,  0,   16,  0,   20,  0,   0,   0,   35,  0,   0,   9,   130, 0,   16,  0,
    8,   0,   0,   0,   26,  0,   16,  0,   20,  0,   0,   0,   10,  0,   16,  0,   10,  0,   0,
    0,   10,  0,   16,  0,   20,  0,   0,   0,   41,  0,   0,   7,   130, 0,   16,  0,   8,   0,
    0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,
    0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,
    42,  0,   16,  0,   9,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   78,  0,   0,
    8,   0,   208, 0,   0,   34,  0,   16,  0,   19,  0,   0,   0,   26,  0,   16,  0,   7,   0,
    0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   8,
    0,   0,   0,   85,  0,   0,   7,   130, 0,   16,  0,   11,  0,   0,   0,   10,  0,   16,  0,
    7,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   41,  0,   0,   10,  50,  0,   16,
    0,   20,  0,   0,   0,   230, 10,  16,  0,   12,  0,   0,   0,   2,   64,  0,   0,   1,   0,
    0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   10,  50,
    0,   16,  0,   20,  0,   0,   0,   70,  0,   16,  0,   20,  0,   0,   0,   2,   64,  0,   0,
    252, 255, 255, 255, 252, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   140, 0,   0,
    17,  50,  0,   16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   230, 10,  16,  0,   12,  0,   0,   0,
    70,  0,   16,  0,   20,  0,   0,   0,   140, 0,   0,   20,  194, 0,   16,  0,   11,  0,   0,
    0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   31,  0,
    0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,
    0,   0,   0,   6,   12,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   194, 0,   16,
    0,   11,  0,   0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   6,   4,   16,  0,   20,  0,
    0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   10,
    0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,   4,   3,
    26,  0,   16,  0,   7,   0,   0,   0,   1,   0,   0,   10,  50,  0,   16,  0,   20,  0,   0,
    0,   166, 10,  16,  0,   12,  0,   0,   0,   2,   64,  0,   0,   253, 255, 255, 255, 2,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   66,  0,   16,  0,   11,
    0,   0,   0,   10,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,
    41,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   12,  0,   0,
    0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   34,  0,   16,  0,   7,   0,
    0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255, 140,
    0,   0,   11,  34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,
    1,   64,  0,   0,   0,   0,   0,   0,   58,  0,   16,  0,   12,  0,   0,   0,   26,  0,   16,
    0,   7,   0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   11,  0,   0,   0,   26,  0,
    16,  0,   20,  0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   18,  0,   0,   1,   54,
    0,   0,   5,   194, 0,   16,  0,   11,  0,   0,   0,   166, 14,  16,  0,   12,  0,   0,   0,
    21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   194, 0,   16,  0,   11,  0,   0,
    0,   166, 14,  16,  0,   11,  0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   6,   4,
    16,  0,   12,  0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   20,  0,   0,   0,   0,
    208, 0,   0,   230, 10,  16,  0,   11,  0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,
    35,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   20,  0,   0,
    0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   20,  0,   0,   0,   30,  0,
    0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   26,
    0,   16,  0,   7,   0,   0,   0,   35,  0,   0,   10,  194, 0,   16,  0,   11,  0,   0,   0,
    6,   4,   16,  128, 65,  0,   0,   0,   20,  0,   0,   0,   6,   8,   16,  0,   10,  0,   0,
    0,   166, 14,  16,  0,   11,  0,   0,   0,   35,  0,   0,   9,   130, 0,   16,  0,   8,   0,
    0,   0,   58,  0,   16,  0,   11,  0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   42,
    0,   16,  0,   11,  0,   0,   0,   41,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,
    58,  0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,
    9,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   42,  0,
    16,  0,   9,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   78,  0,   0,   8,   0,
    208, 0,   0,   66,  0,   16,  0,   19,  0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,
    10,  0,   16,  0,   9,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,
    0,   85,  0,   0,   7,   34,  0,   16,  0,   11,  0,   0,   0,   10,  0,   16,  0,   7,   0,
    0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   41,  0,   0,   10,  194, 0,   16,  0,   11,
    0,   0,   0,   6,   4,   16,  0,   13,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   10,  194, 0,   16,
    0,   11,  0,   0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   252, 255, 255, 255, 252, 255, 255, 255, 140, 0,   0,   17,  194,
    0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    1,   0,   0,   0,   1,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   4,   16,  0,   13,  0,   0,   0,   166, 14,
    16,  0,   11,  0,   0,   0,   140, 0,   0,   20,  50,  0,   16,  0,   20,  0,   0,   0,   2,
    64,  0,   0,   1,   0,   0,   0,   31,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   70,  0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   194, 0,   16,  0,   11,
    0,   0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   6,   4,   16,  0,   20,  0,   0,   0,
    18,  0,   0,   1,   32,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,
    0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,   4,   3,   26,  0,
    16,  0,   7,   0,   0,   0,   1,   0,   0,   10,  50,  0,   16,  0,   20,  0,   0,   0,   6,
    0,   16,  0,   13,  0,   0,   0,   2,   64,  0,   0,   253, 255, 255, 255, 2,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   66,  0,   16,  0,   11,  0,   0,
    0,   10,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,   41,  0,
    0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   13,  0,   0,   0,   1,
    64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,
    26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255, 140, 0,   0,
    11,  34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,
    0,   0,   0,   0,   0,   0,   26,  0,   16,  0,   13,  0,   0,   0,   26,  0,   16,  0,   7,
    0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   11,  0,   0,   0,   26,  0,   16,  0,
    20,  0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   18,  0,   0,   1,   54,  0,   0,
    5,   194, 0,   16,  0,   11,  0,   0,   0,   6,   4,   16,  0,   13,  0,   0,   0,   21,  0,
    0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   194, 0,   16,  0,   11,  0,   0,   0,   166,
    14,  16,  0,   11,  0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   166, 14,  16,  0,
    7,   0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   20,  0,   0,   0,   0,   208, 0,
    0,   230, 10,  16,  0,   11,  0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   35,  0,
    0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   20,  0,   0,   0,   10,
    0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   20,  0,   0,   0,   30,  0,   0,   7,
    34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   26,  0,   16,
    0,   7,   0,   0,   0,   35,  0,   0,   10,  194, 0,   16,  0,   11,  0,   0,   0,   6,   4,
    16,  128, 65,  0,   0,   0,   20,  0,   0,   0,   6,   8,   16,  0,   10,  0,   0,   0,   166,
    14,  16,  0,   11,  0,   0,   0,   35,  0,   0,   9,   130, 0,   16,  0,   8,   0,   0,   0,
    58,  0,   16,  0,   11,  0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   42,  0,   16,
    0,   11,  0,   0,   0,   41,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   58,  0,
    16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,   9,   34,
    0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   42,  0,   16,  0,
    9,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   78,  0,   0,   8,   0,   208, 0,
    0,   130, 0,   16,  0,   19,  0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   10,  0,
    16,  0,   9,   0,   0,   0,   30,  0,   0,   7,   242, 0,   16,  0,   19,  0,   0,   0,   246,
    15,  16,  0,   0,   0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   31,  0,   4,   3,
    42,  0,   16,  0,   8,   0,   0,   0,   85,  0,   0,   7,   34,  0,   16,  0,   11,  0,   0,
    0,   10,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   41,  0,
    0,   10,  194, 0,   16,  0,   11,  0,   0,   0,   6,   4,   16,  0,   14,  0,   0,   0,   2,
    64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
    1,   0,   0,   10,  194, 0,   16,  0,   11,  0,   0,   0,   166, 14,  16,  0,   11,  0,   0,
    0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   252, 255, 255, 255, 252, 255,
    255, 255, 140, 0,   0,   17,  194, 0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   2,   64,  0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   4,   16,
    0,   14,  0,   0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   140, 0,   0,   20,  50,  0,
    16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   31,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   70,  0,   16,  0,   11,  0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,
    0,   7,   194, 0,   16,  0,   11,  0,   0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   6,
    4,   16,  0,   20,  0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   34,  0,   16,  0,
    7,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,
    0,   31,  0,   4,   3,   26,  0,   16,  0,   7,   0,   0,   0,   1,   0,   0,   10,  50,  0,
    16,  0,   20,  0,   0,   0,   6,   0,   16,  0,   14,  0,   0,   0,   2,   64,  0,   0,   253,
    255, 255, 255, 2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,
    66,  0,   16,  0,   11,  0,   0,   0,   10,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,
    0,   2,   0,   0,   0,   41,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,
    16,  0,   14,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   34,
    0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,
    252, 255, 255, 255, 140, 0,   0,   11,  34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,
    0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   26,  0,   16,  0,   14,  0,
    0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   11,
    0,   0,   0,   26,  0,   16,  0,   20,  0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,
    18,  0,   0,   1,   54,  0,   0,   5,   194, 0,   16,  0,   11,  0,   0,   0,   6,   4,   16,
    0,   14,  0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   194, 0,
    16,  0,   11,  0,   0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   6,   4,   16,  0,   2,
    0,   0,   0,   166, 14,  16,  0,   13,  0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,
    20,  0,   0,   0,   0,   208, 0,   0,   230, 10,  16,  0,   11,  0,   0,   0,   134, 0,   16,
    0,   10,  0,   0,   0,   35,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,
    16,  0,   20,  0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   20,
    0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,
    4,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   35,  0,   0,   10,  194, 0,   16,
    0,   11,  0,   0,   0,   6,   4,   16,  128, 65,  0,   0,   0,   20,  0,   0,   0,   6,   8,
    16,  0,   10,  0,   0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   35,  0,   0,   9,   130,
    0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   11,  0,   0,   0,   10,  0,   16,  0,
    10,  0,   0,   0,   42,  0,   16,  0,   11,  0,   0,   0,   41,  0,   0,   7,   130, 0,   16,
    0,   8,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   4,   0,
    0,   0,   35,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,
    0,   0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,
    78,  0,   0,   8,   0,   208, 0,   0,   18,  0,   16,  0,   20,  0,   0,   0,   26,  0,   16,
    0,   7,   0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   31,  0,   4,   3,   42,  0,
    16,  0,   8,   0,   0,   0,   85,  0,   0,   7,   34,  0,   16,  0,   11,  0,   0,   0,   10,
    0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   41,  0,   0,   10,
    194, 0,   16,  0,   11,  0,   0,   0,   6,   4,   16,  0,   16,  0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,
    0,   10,  194, 0,   16,  0,   11,  0,   0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   2,
    64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   252, 255, 255, 255, 252, 255, 255, 255,
    140, 0,   0,   17,  194, 0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   4,   16,  0,   16,
    0,   0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   140, 0,   0,   20,  50,  0,   16,  0,
    21,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   31,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   70,  0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,
    194, 0,   16,  0,   11,  0,   0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   6,   4,   16,
    0,   21,  0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   34,  0,   16,  0,   7,   0,
    0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,
    0,   4,   3,   26,  0,   16,  0,   7,   0,   0,   0,   1,   0,   0,   10,  50,  0,   16,  0,
    21,  0,   0,   0,   6,   0,   16,  0,   16,  0,   0,   0,   2,   64,  0,   0,   253, 255, 255,
    255, 2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   66,  0,
    16,  0,   11,  0,   0,   0,   10,  0,   16,  0,   21,  0,   0,   0,   1,   64,  0,   0,   2,
    0,   0,   0,   41,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,
    16,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   34,  0,   16,
    0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   252, 255,
    255, 255, 140, 0,   0,   11,  34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   1,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   26,  0,   16,  0,   16,  0,   0,   0,
    26,  0,   16,  0,   7,   0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   11,  0,   0,
    0,   26,  0,   16,  0,   21,  0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   18,  0,
    0,   1,   54,  0,   0,   5,   194, 0,   16,  0,   11,  0,   0,   0,   6,   4,   16,  0,   16,
    0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   194, 0,   16,  0,
    11,  0,   0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   6,   4,   16,  0,   2,   0,   0,
    0,   166, 14,  16,  0,   14,  0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   21,  0,
    0,   0,   0,   208, 0,   0,   230, 10,  16,  0,   11,  0,   0,   0,   134, 0,   16,  0,   10,
    0,   0,   0,   35,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,
    21,  0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   21,  0,   0,
    0,   30,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   4,   0,
    0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   35,  0,   0,   10,  194, 0,   16,  0,   11,
    0,   0,   0,   6,   4,   16,  128, 65,  0,   0,   0,   21,  0,   0,   0,   6,   8,   16,  0,
    10,  0,   0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   35,  0,   0,   9,   130, 0,   16,
    0,   8,   0,   0,   0,   58,  0,   16,  0,   11,  0,   0,   0,   10,  0,   16,  0,   10,  0,
    0,   0,   42,  0,   16,  0,   11,  0,   0,   0,   41,  0,   0,   7,   130, 0,   16,  0,   8,
    0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,
    35,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,
    0,   42,  0,   16,  0,   9,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   78,  0,
    0,   8,   0,   208, 0,   0,   34,  0,   16,  0,   20,  0,   0,   0,   26,  0,   16,  0,   7,
    0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,
    8,   0,   0,   0,   85,  0,   0,   7,   34,  0,   16,  0,   11,  0,   0,   0,   10,  0,   16,
    0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   41,  0,   0,   10,  194, 0,
    16,  0,   11,  0,   0,   0,   6,   4,   16,  0,   17,  0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   10,
    194, 0,   16,  0,   11,  0,   0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   252, 255, 255, 255, 252, 255, 255, 255, 140, 0,
    0,   17,  194, 0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   4,   16,  0,   17,  0,   0,
    0,   166, 14,  16,  0,   11,  0,   0,   0,   140, 0,   0,   20,  50,  0,   16,  0,   21,  0,
    0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   31,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   70,  0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   194, 0,
    16,  0,   11,  0,   0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   6,   4,   16,  0,   21,
    0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,
    10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,   4,
    3,   26,  0,   16,  0,   7,   0,   0,   0,   1,   0,   0,   10,  50,  0,   16,  0,   21,  0,
    0,   0,   6,   0,   16,  0,   17,  0,   0,   0,   2,   64,  0,   0,   253, 255, 255, 255, 2,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   66,  0,   16,  0,
    11,  0,   0,   0,   10,  0,   16,  0,   21,  0,   0,   0,   1,   64,  0,   0,   2,   0,   0,
    0,   41,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   17,  0,
    0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   34,  0,   16,  0,   7,
    0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255,
    140, 0,   0,   11,  34,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   0,   0,   26,  0,   16,  0,   17,  0,   0,   0,   26,  0,
    16,  0,   7,   0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   11,  0,   0,   0,   26,
    0,   16,  0,   21,  0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   18,  0,   0,   1,
    54,  0,   0,   5,   194, 0,   16,  0,   11,  0,   0,   0,   6,   4,   16,  0,   17,  0,   0,
    0,   21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   194, 0,   16,  0,   11,  0,
    0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   166,
    14,  16,  0,   16,  0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   21,  0,   0,   0,
    0,   208, 0,   0,   230, 10,  16,  0,   11,  0,   0,   0,   134, 0,   16,  0,   10,  0,   0,
    0,   35,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   21,  0,
    0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   21,  0,   0,   0,   30,
    0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,
    26,  0,   16,  0,   7,   0,   0,   0,   35,  0,   0,   10,  194, 0,   16,  0,   11,  0,   0,
    0,   6,   4,   16,  128, 65,  0,   0,   0,   21,  0,   0,   0,   6,   8,   16,  0,   10,  0,
    0,   0,   166, 14,  16,  0,   11,  0,   0,   0,   35,  0,   0,   9,   130, 0,   16,  0,   8,
    0,   0,   0,   58,  0,   16,  0,   11,  0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,
    42,  0,   16,  0,   11,  0,   0,   0,   41,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,
    0,   58,  0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,
    0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   42,
    0,   16,  0,   9,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   78,  0,   0,   8,
    0,   208, 0,   0,   66,  0,   16,  0,   20,  0,   0,   0,   26,  0,   16,  0,   7,   0,   0,
    0,   10,  0,   16,  0,   9,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   8,   0,
    0,   0,   85,  0,   0,   7,   34,  0,   16,  0,   11,  0,   0,   0,   10,  0,   16,  0,   7,
    0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   41,  0,   0,   10,  50,  0,   16,  0,
    7,   0,   0,   0,   230, 10,  16,  0,   17,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,
    0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   10,  50,  0,
    16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   252,
    255, 255, 255, 252, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   140, 0,   0,   17,
    50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   230, 10,  16,  0,   17,  0,   0,   0,   70,
    0,   16,  0,   7,   0,   0,   0,   140, 0,   0,   20,  50,  0,   16,  0,   11,  0,   0,   0,
    2,   64,  0,   0,   1,   0,   0,   0,   31,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   70,  0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   50,  0,   16,  0,
    7,   0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   11,  0,   0,
    0,   18,  0,   0,   1,   32,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   10,  0,
    16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,   4,   3,   58,
    0,   16,  0,   8,   0,   0,   0,   1,   0,   0,   10,  50,  0,   16,  0,   11,  0,   0,   0,
    166, 10,  16,  0,   17,  0,   0,   0,   2,   64,  0,   0,   253, 255, 255, 255, 2,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   18,  0,   16,  0,   7,   0,
    0,   0,   10,  0,   16,  0,   11,  0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,   41,
    0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   58,  0,   16,  0,   17,  0,   0,   0,
    1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   130, 0,   16,  0,   8,   0,   0,
    0,   58,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255, 140, 0,
    0,   11,  130, 0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,
    64,  0,   0,   0,   0,   0,   0,   58,  0,   16,  0,   17,  0,   0,   0,   58,  0,   16,  0,
    8,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,
    0,   11,  0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   18,  0,   0,   1,   54,  0,
    0,   5,   50,  0,   16,  0,   7,   0,   0,   0,   230, 10,  16,  0,   17,  0,   0,   0,   21,
    0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   50,  0,   16,  0,   7,   0,   0,   0,
    70,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   2,   0,   0,   0,   150, 5,   16,
    0,   1,   0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   11,  0,   0,   0,   0,   208,
    0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   35,
    0,   0,   9,   130, 0,   16,  0,   8,   0,   0,   0,   26,  0,   16,  0,   11,  0,   0,   0,
    10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   11,  0,   0,   0,   30,  0,   0,
    7,   130, 0,   16,  0,   8,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   58,  0,
    16,  0,   8,   0,   0,   0,   35,  0,   0,   10,  50,  0,   16,  0,   7,   0,   0,   0,   70,
    0,   16,  128, 65,  0,   0,   0,   11,  0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,
    70,  0,   16,  0,   7,   0,   0,   0,   35,  0,   0,   9,   18,  0,   16,  0,   7,   0,   0,
    0,   26,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   10,  0,
    16,  0,   7,   0,   0,   0,   41,  0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,
    0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,   9,
    18,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   42,  0,   16,
    0,   9,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   78,  0,   0,   8,   0,   208,
    0,   0,   130, 0,   16,  0,   20,  0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   10,
    0,   16,  0,   9,   0,   0,   0,   30,  0,   0,   7,   242, 0,   16,  0,   11,  0,   0,   0,
    246, 15,  16,  0,   0,   0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   41,  0,   0,
    10,  242, 0,   16,  0,   19,  0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   2,   64,
    0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   165,
    0,   0,   8,   18,  0,   16,  0,   20,  0,   0,   0,   10,  0,   16,  0,   19,  0,   0,   0,
    6,   112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   165, 0,   0,   8,   34,  0,   16,
    0,   20,  0,   0,   0,   26,  0,   16,  0,   19,  0,   0,   0,   6,   112, 32,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   165, 0,   0,   8,   66,  0,   16,  0,   20,  0,   0,   0,   42,
    0,   16,  0,   19,  0,   0,   0,   6,   112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    165, 0,   0,   8,   130, 0,   16,  0,   20,  0,   0,   0,   58,  0,   16,  0,   19,  0,   0,
    0,   6,   112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   41,  0,   0,   10,  242, 0,
    16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   2,
    0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   165, 0,   0,   8,
    18,  0,   16,  0,   19,  0,   0,   0,   10,  0,   16,  0,   11,  0,   0,   0,   6,   112, 32,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   165, 0,   0,   8,   34,  0,   16,  0,   19,  0,
    0,   0,   26,  0,   16,  0,   11,  0,   0,   0,   6,   112, 32,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   165, 0,   0,   8,   66,  0,   16,  0,   19,  0,   0,   0,   42,  0,   16,  0,
    11,  0,   0,   0,   6,   112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   165, 0,   0,
    8,   130, 0,   16,  0,   19,  0,   0,   0,   58,  0,   16,  0,   11,  0,   0,   0,   6,   112,
    32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   4,
    0,   0,   0,   76,  0,   0,   3,   42,  0,   16,  0,   4,   0,   0,   0,   6,   0,   0,   3,
    1,   64,  0,   0,   5,   0,   0,   0,   1,   0,   0,   7,   18,  0,   16,  0,   7,   0,   0,
    0,   58,  0,   16,  0,   2,   0,   0,   0,   1,   64,  0,   0,   16,  0,   0,   0,   85,  0,
    0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   6,
    0,   16,  0,   7,   0,   0,   0,   139, 0,   0,   15,  242, 0,   16,  0,   11,  0,   0,   0,
    2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,
    0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   43,  0,   0,   5,   242, 0,   16,  0,   11,
    0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,
    11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   1,   128,
    58,  0,   1,   128, 58,  0,   1,   128, 58,  0,   1,   128, 58,  52,  0,   0,   10,  242, 0,
    16,  0,   20,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,
    0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 85,  0,   0,   7,
    242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   6,   0,   16,
    0,   7,   0,   0,   0,   139, 0,   0,   15,  242, 0,   16,  0,   11,  0,   0,   0,   2,   64,
    0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   2,
    64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    70,  14,  16,  0,   11,  0,   0,   0,   43,  0,   0,   5,   242, 0,   16,  0,   11,  0,   0,
    0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   11,  0,
    0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   1,   128, 58,  0,
    1,   128, 58,  0,   1,   128, 58,  0,   1,   128, 58,  52,  0,   0,   10,  242, 0,   16,  0,
    19,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128,
    191, 0,   0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 2,   0,   0,   1,   6,   0,
    0,   3,   1,   64,  0,   0,   7,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   2,
    0,   0,   0,   85,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,
    20,  0,   0,   0,   2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,
    0,   16,  0,   0,   0,   131, 0,   0,   5,   242, 0,   16,  0,   20,  0,   0,   0,   70,  14,
    16,  0,   11,  0,   0,   0,   85,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,
    14,  16,  0,   19,  0,   0,   0,   2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,
    16,  0,   0,   0,   16,  0,   0,   0,   131, 0,   0,   5,   242, 0,   16,  0,   19,  0,   0,
    0,   70,  14,  16,  0,   11,  0,   0,   0,   18,  0,   0,   1,   131, 0,   0,   5,   242, 0,
    16,  0,   20,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   131, 0,   0,   5,   242,
    0,   16,  0,   19,  0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   21,  0,   0,   1,
    2,   0,   0,   1,   10,  0,   0,   1,   31,  0,   4,   3,   58,  0,   16,  0,   2,   0,   0,
    0,   54,  0,   0,   8,   242, 0,   16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   0,   0,
    128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  54,  0,   0,   8,   242,
    0,   16,  0,   19,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,
    0,   0,   128, 63,  0,   0,   128, 63,  21,  0,   0,   1,   2,   0,   0,   1,   23,  0,   0,
    1,   18,  0,   0,   1,   76,  0,   0,   3,   42,  0,   16,  0,   4,   0,   0,   0,   6,   0,
    0,   3,   1,   64,  0,   0,   0,   0,   0,   0,   6,   0,   0,   3,   1,   64,  0,   0,   1,
    0,   0,   0,   1,   0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,
    5,   0,   0,   0,   1,   64,  0,   0,   16,  0,   0,   0,   55,  0,   0,   9,   18,  0,   16,
    0,   7,   0,   0,   0,   58,  0,   16,  0,   2,   0,   0,   0,   1,   64,  0,   0,   24,  0,
    0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   85,  0,   0,   7,   242, 0,   16,  0,   11,
    0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   6,   0,   16,  0,   7,   0,   0,   0,
    1,   0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,
    0,   2,   64,  0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   255, 0,
    0,   0,   86,  0,   0,   5,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,
    0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   20,  0,   0,   0,   70,  14,  16,  0,
    11,  0,   0,   0,   2,   64,  0,   0,   129, 128, 128, 59,  129, 128, 128, 59,  129, 128, 128,
    59,  129, 128, 128, 59,  85,  0,   0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,
    16,  0,   19,  0,   0,   0,   6,   0,   16,  0,   7,   0,   0,   0,   1,   0,   0,   10,  242,
    0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,
    255, 0,   0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   86,  0,   0,
    5,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,
    0,   10,  242, 0,   16,  0,   19,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,
    64,  0,   0,   129, 128, 128, 59,  129, 128, 128, 59,  129, 128, 128, 59,  129, 128, 128, 59,
    2,   0,   0,   1,   6,   0,   0,   3,   1,   64,  0,   0,   2,   0,   0,   0,   6,   0,   0,
    3,   1,   64,  0,   0,   10,  0,   0,   0,   6,   0,   0,   3,   1,   64,  0,   0,   3,   0,
    0,   0,   6,   0,   0,   3,   1,   64,  0,   0,   12,  0,   0,   0,   31,  0,   4,   3,   58,
    0,   16,  0,   2,   0,   0,   0,   85,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,
    70,  14,  16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   30,  0,   0,   0,   30,  0,   0,
    0,   30,  0,   0,   0,   30,  0,   0,   0,   86,  0,   0,   5,   242, 0,   16,  0,   11,  0,
    0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   20,
    0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   171, 170, 170, 62,
    171, 170, 170, 62,  171, 170, 170, 62,  171, 170, 170, 62,  85,  0,   0,   10,  242, 0,   16,
    0,   11,  0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   2,   64,  0,   0,   30,  0,
    0,   0,   30,  0,   0,   0,   30,  0,   0,   0,   30,  0,   0,   0,   86,  0,   0,   5,   242,
    0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,   10,
    242, 0,   16,  0,   19,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,
    0,   171, 170, 170, 62,  171, 170, 170, 62,  171, 170, 170, 62,  171, 170, 170, 62,  18,  0,
    0,   1,   1,   0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   5,
    0,   0,   0,   1,   64,  0,   0,   20,  0,   0,   0,   32,  0,   0,   10,  50,  0,   16,  0,
    11,  0,   0,   0,   166, 10,  16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   2,   0,   0,
    0,   10,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   60,  0,   0,   7,   34,  0,
    16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   11,  0,   0,   0,   10,  0,   16,  0,   11,
    0,   0,   0,   31,  0,   4,   3,   26,  0,   16,  0,   7,   0,   0,   0,   85,  0,   0,   7,
    242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   6,   0,   16,
    0,   7,   0,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,
    16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255,
    3,   0,   0,   255, 3,   0,   0,   86,  0,   0,   5,   242, 0,   16,  0,   11,  0,   0,   0,
    70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   20,  0,   0,
    0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   8,   32,  128, 58,  8,   32,
    128, 58,  8,   32,  128, 58,  8,   32,  128, 58,  85,  0,   0,   7,   242, 0,   16,  0,   11,
    0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   6,   0,   16,  0,   7,   0,   0,   0,
    1,   0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,
    0,   2,   64,  0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,
    0,   0,   86,  0,   0,   5,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,
    0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   19,  0,   0,   0,   70,  14,  16,  0,
    11,  0,   0,   0,   2,   64,  0,   0,   8,   32,  128, 58,  8,   32,  128, 58,  8,   32,  128,
    58,  8,   32,  128, 58,  18,  0,   0,   1,   85,  0,   0,   7,   242, 0,   16,  0,   11,  0,
    0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   6,   0,   16,  0,   7,   0,   0,   0,   1,
    0,   0,   10,  242, 0,   16,  0,   21,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,
    2,   64,  0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,
    0,   1,   0,   0,   10,  242, 0,   16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   11,  0,
    0,   0,   2,   64,  0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   127,
    0,   0,   0,   138, 0,   0,   15,  242, 0,   16,  0,   23,  0,   0,   0,   2,   64,  0,   0,
    3,   0,   0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   2,   64,  0,
    0,   7,   0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   70,  14,
    16,  0,   11,  0,   0,   0,   135, 0,   0,   5,   242, 0,   16,  0,   24,  0,   0,   0,   70,
    14,  16,  0,   22,  0,   0,   0,   30,  0,   0,   10,  242, 0,   16,  0,   24,  0,   0,   0,
    70,  14,  16,  0,   24,  0,   0,   0,   2,   64,  0,   0,   232, 255, 255, 255, 232, 255, 255,
    255, 232, 255, 255, 255, 232, 255, 255, 255, 55,  0,   0,   12,  242, 0,   16,  0,   24,  0,
    0,   0,   70,  14,  16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   24,  0,   0,   0,   2,
    64,  0,   0,   8,   0,   0,   0,   8,   0,   0,   0,   8,   0,   0,   0,   8,   0,   0,   0,
    30,  0,   0,   11,  242, 0,   16,  0,   25,  0,   0,   0,   70,  14,  16,  128, 65,  0,   0,
    0,   24,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,
    0,   0,   1,   0,   0,   0,   55,  0,   0,   9,   242, 0,   16,  0,   25,  0,   0,   0,   70,
    14,  16,  0,   23,  0,   0,   0,   70,  14,  16,  0,   23,  0,   0,   0,   70,  14,  16,  0,
    25,  0,   0,   0,   140, 0,   0,   17,  242, 0,   16,  0,   11,  0,   0,   0,   2,   64,  0,
    0,   7,   0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   70,  14,
    16,  0,   24,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   10,
    242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,
    0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   55,  0,
    0,   9,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   23,  0,   0,   0,   70,
    14,  16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   41,  0,   0,   10,
    242, 0,   16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   25,  0,   0,   0,   2,   64,  0,
    0,   23,  0,   0,   0,   23,  0,   0,   0,   23,  0,   0,   0,   23,  0,   0,   0,   30,  0,
    0,   10,  242, 0,   16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   22,  0,   0,   0,   2,
    64,  0,   0,   0,   0,   0,   62,  0,   0,   0,   62,  0,   0,   0,   62,  0,   0,   0,   62,
    41,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,
    0,   2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,
    0,   0,   30,  0,   0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   22,
    0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   55,  0,   0,   12,  242, 0,   16,  0,
    20,  0,   0,   0,   70,  14,  16,  0,   21,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,
    0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   85,  0,   0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   19,
    0,   0,   0,   6,   0,   16,  0,   7,   0,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,
    21,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   255, 3,   0,
    0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   1,   0,   0,   10,  242, 0,
    16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   127,
    0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   138, 0,   0,   15,
    242, 0,   16,  0,   23,  0,   0,   0,   2,   64,  0,   0,   3,   0,   0,   0,   3,   0,   0,
    0,   3,   0,   0,   0,   3,   0,   0,   0,   2,   64,  0,   0,   7,   0,   0,   0,   7,   0,
    0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   135,
    0,   0,   5,   242, 0,   16,  0,   24,  0,   0,   0,   70,  14,  16,  0,   22,  0,   0,   0,
    30,  0,   0,   10,  242, 0,   16,  0,   24,  0,   0,   0,   70,  14,  16,  0,   24,  0,   0,
    0,   2,   64,  0,   0,   232, 255, 255, 255, 232, 255, 255, 255, 232, 255, 255, 255, 232, 255,
    255, 255, 55,  0,   0,   12,  242, 0,   16,  0,   24,  0,   0,   0,   70,  14,  16,  0,   22,
    0,   0,   0,   70,  14,  16,  0,   24,  0,   0,   0,   2,   64,  0,   0,   8,   0,   0,   0,
    8,   0,   0,   0,   8,   0,   0,   0,   8,   0,   0,   0,   30,  0,   0,   11,  242, 0,   16,
    0,   25,  0,   0,   0,   70,  14,  16,  128, 65,  0,   0,   0,   24,  0,   0,   0,   2,   64,
    0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   55,
    0,   0,   9,   242, 0,   16,  0,   25,  0,   0,   0,   70,  14,  16,  0,   23,  0,   0,   0,
    70,  14,  16,  0,   23,  0,   0,   0,   70,  14,  16,  0,   25,  0,   0,   0,   140, 0,   0,
    17,  242, 0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   7,   0,   0,   0,   7,   0,
    0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   70,  14,  16,  0,   24,  0,   0,   0,   70,
    14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   11,  0,   0,
    0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   127, 0,   0,   0,   127, 0,
    0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   55,  0,   0,   9,   242, 0,   16,  0,   11,
    0,   0,   0,   70,  14,  16,  0,   23,  0,   0,   0,   70,  14,  16,  0,   22,  0,   0,   0,
    70,  14,  16,  0,   11,  0,   0,   0,   41,  0,   0,   10,  242, 0,   16,  0,   22,  0,   0,
    0,   70,  14,  16,  0,   25,  0,   0,   0,   2,   64,  0,   0,   23,  0,   0,   0,   23,  0,
    0,   0,   23,  0,   0,   0,   23,  0,   0,   0,   30,  0,   0,   10,  242, 0,   16,  0,   22,
    0,   0,   0,   70,  14,  16,  0,   22,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   62,
    0,   0,   0,   62,  0,   0,   0,   62,  0,   0,   0,   62,  41,  0,   0,   10,  242, 0,   16,
    0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   16,  0,
    0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   30,  0,   0,   7,   242,
    0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   22,  0,   0,   0,   70,  14,  16,  0,
    11,  0,   0,   0,   55,  0,   0,   12,  242, 0,   16,  0,   19,  0,   0,   0,   70,  14,  16,
    0,   21,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   21,
    0,   0,   1,   2,   0,   0,   1,   6,   0,   0,   3,   1,   64,  0,   0,   4,   0,   0,   0,
    31,  0,   4,   3,   58,  0,   16,  0,   2,   0,   0,   0,   54,  0,   0,   8,   242, 0,   16,
    0,   20,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,
    128, 63,  0,   0,   128, 63,  54,  0,   0,   8,   242, 0,   16,  0,   19,  0,   0,   0,   2,
    64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,
    18,  0,   0,   1,   139, 0,   0,   15,  242, 0,   16,  0,   11,  0,   0,   0,   2,   64,  0,
    0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   2,   64,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,
    14,  16,  0,   20,  0,   0,   0,   43,  0,   0,   5,   242, 0,   16,  0,   11,  0,   0,   0,
    70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,
    0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   1,   128, 58,  0,   1,
    128, 58,  0,   1,   128, 58,  0,   1,   128, 58,  52,  0,   0,   10,  242, 0,   16,  0,   20,
    0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 191,
    0,   0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 139, 0,   0,   15,  242, 0,   16,
    0,   11,  0,   0,   0,   2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,
    0,   0,   16,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   43,  0,   0,   5,
    242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,
    10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,
    0,   0,   0,   1,   128, 58,  0,   1,   128, 58,  0,   1,   128, 58,  0,   1,   128, 58,  52,
    0,   0,   10,  242, 0,   16,  0,   19,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,
    2,   64,  0,   0,   0,   0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 0,   0,   128,
    191, 21,  0,   0,   1,   2,   0,   0,   1,   6,   0,   0,   3,   1,   64,  0,   0,   6,   0,
    0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   2,   0,   0,   0,   54,  0,   0,   8,   242,
    0,   16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,
    0,   0,   128, 63,  0,   0,   128, 63,  54,  0,   0,   8,   242, 0,   16,  0,   19,  0,   0,
    0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,
    128, 63,  18,  0,   0,   1,   131, 0,   0,   5,   242, 0,   16,  0,   20,  0,   0,   0,   70,
    14,  16,  0,   20,  0,   0,   0,   131, 0,   0,   5,   242, 0,   16,  0,   19,  0,   0,   0,
    70,  14,  16,  0,   19,  0,   0,   0,   21,  0,   0,   1,   2,   0,   0,   1,   10,  0,   0,
    1,   31,  0,   4,   3,   58,  0,   16,  0,   2,   0,   0,   0,   54,  0,   0,   8,   242, 0,
    16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,
    0,   128, 63,  0,   0,   128, 63,  54,  0,   0,   8,   242, 0,   16,  0,   19,  0,   0,   0,
    2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128,
    63,  21,  0,   0,   1,   2,   0,   0,   1,   23,  0,   0,   1,   21,  0,   0,   1,   31,  0,
    4,   3,   58,  0,   16,  0,   3,   0,   0,   0,   54,  32,  0,   5,   242, 0,   16,  0,   20,
    0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   29,  0,   0,   10,  242, 0,   16,  0,
    11,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   193, 192, 192,
    62,  193, 192, 192, 62,  193, 192, 192, 62,  193, 192, 192, 62,  31,  0,   4,   3,   10,  0,
    16,  0,   11,  0,   0,   0,   29,  0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,
    0,   16,  0,   20,  0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,
    10,  0,   16,  0,   7,   0,   0,   0,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,
    0,   2,   64,  0,   0,   0,   0,   0,   60,  0,   0,   128, 196, 0,   0,   0,   0,   0,   0,
    0,   0,   18,  0,   0,   1,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   2,
    64,  0,   0,   0,   0,   128, 59,  0,   0,   128, 195, 0,   0,   0,   0,   0,   0,   0,   0,
    21,  0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,
    0,   10,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,
    4,   3,   58,  0,   16,  0,   8,   0,   0,   0,   54,  0,   0,   8,   50,  0,   16,  0,   7,
    0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   59,  0,   0,   128, 194, 0,   0,   0,   0,
    0,   0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,
    0,   2,   64,  0,   0,   0,   0,   128, 58,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   130, 0,   16,  0,   8,
    0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   20,  0,   0,   0,
    50,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   127, 72,  26,  0,   16,  0,   7,   0,   0,   0,   56,  0,
    0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   26,
    0,   16,  0,   7,   0,   0,   0,   67,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,
    10,  0,   16,  0,   7,   0,   0,   0,   0,   0,   0,   7,   18,  0,   16,  0,   7,   0,   0,
    0,   10,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   56,  0,
    0,   7,   18,  0,   16,  0,   20,  0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   1,
    64,  0,   0,   8,   32,  128, 58,  31,  0,   4,   3,   26,  0,   16,  0,   11,  0,   0,   0,
    29,  0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   20,  0,   0,
    0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,   10,  0,   16,  0,   7,   0,
    0,   0,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   60,  0,   0,   128, 196, 0,   0,   0,   0,   0,   0,   0,   0,   18,  0,   0,   1,
    54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128,
    59,  0,   0,   128, 195, 0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   18,  0,
    0,   1,   29,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   26,  0,   16,  0,   20,
    0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,   58,  0,   16,  0,
    8,   0,   0,   0,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   59,  0,   0,   128, 194, 0,   0,   0,   0,   0,   0,   0,   0,   18,  0,
    0,   1,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,
    0,   128, 58,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   1,
    21,  0,   0,   1,   56,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   10,  0,   16,
    0,   7,   0,   0,   0,   26,  0,   16,  0,   20,  0,   0,   0,   50,  0,   0,   9,   34,  0,
    16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   127, 72,  26,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   18,  0,   16,  0,
    7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,
    0,   67,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,
    0,   0,   0,   0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,
    0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   34,  0,   16,  0,
    20,  0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   8,   32,  128,
    58,  31,  0,   4,   3,   42,  0,   16,  0,   11,  0,   0,   0,   29,  0,   0,   7,   18,  0,
    16,  0,   7,   0,   0,   0,   42,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,   0,   193,
    192, 64,  63,  31,  0,   4,   3,   10,  0,   16,  0,   7,   0,   0,   0,   54,  0,   0,   8,
    50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   60,  0,   0,   128,
    196, 0,   0,   0,   0,   0,   0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   8,   50,  0,
    16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 59,  0,   0,   128, 195, 0,
    0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,
    130, 0,   16,  0,   8,   0,   0,   0,   42,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,
    0,   129, 128, 128, 62,  31,  0,   4,   3,   58,  0,   16,  0,   8,   0,   0,   0,   54,  0,
    0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   59,  0,
    0,   128, 194, 0,   0,   0,   0,   0,   0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   8,
    50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 58,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,
    0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   42,
    0,   16,  0,   20,  0,   0,   0,   50,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,
    58,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  26,  0,   16,
    0,   7,   0,   0,   0,   56,  0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,
    16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   67,  0,   0,   5,   18,
    0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   0,   0,   0,   7,
    18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,
    0,   7,   0,   0,   0,   56,  0,   0,   7,   66,  0,   16,  0,   20,  0,   0,   0,   10,  0,
    16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   8,   32,  128, 58,  31,  0,   4,   3,   58,
    0,   16,  0,   11,  0,   0,   0,   29,  0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,
    58,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,
    3,   10,  0,   16,  0,   7,   0,   0,   0,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,
    0,   0,   2,   64,  0,   0,   0,   0,   0,   60,  0,   0,   128, 196, 0,   0,   0,   0,   0,
    0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,
    2,   64,  0,   0,   0,   0,   128, 59,  0,   0,   128, 195, 0,   0,   0,   0,   0,   0,   0,
    0,   21,  0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   130, 0,   16,  0,   8,   0,
    0,   0,   58,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,
    0,   4,   3,   58,  0,   16,  0,   8,   0,   0,   0,   54,  0,   0,   8,   50,  0,   16,  0,
    7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   59,  0,   0,   128, 194, 0,   0,   0,
    0,   0,   0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,
    0,   0,   2,   64,  0,   0,   0,   0,   128, 58,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   130, 0,   16,  0,
    8,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   20,  0,   0,
    0,   50,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   8,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  26,  0,   16,  0,   7,   0,   0,   0,   56,
    0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,
    26,  0,   16,  0,   7,   0,   0,   0,   67,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,
    0,   10,  0,   16,  0,   7,   0,   0,   0,   0,   0,   0,   7,   18,  0,   16,  0,   7,   0,
    0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   56,
    0,   0,   7,   130, 0,   16,  0,   20,  0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,
    1,   64,  0,   0,   8,   32,  128, 58,  54,  32,  0,   5,   242, 0,   16,  0,   19,  0,   0,
    0,   70,  14,  16,  0,   19,  0,   0,   0,   29,  0,   0,   10,  242, 0,   16,  0,   11,  0,
    0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   2,   64,  0,   0,   193, 192, 192, 62,  193,
    192, 192, 62,  193, 192, 192, 62,  193, 192, 192, 62,  31,  0,   4,   3,   10,  0,   16,  0,
    11,  0,   0,   0,   29,  0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,
    0,   19,  0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,   10,  0,
    16,  0,   7,   0,   0,   0,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   2,
    64,  0,   0,   0,   0,   0,   60,  0,   0,   128, 196, 0,   0,   0,   0,   0,   0,   0,   0,
    18,  0,   0,   1,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,
    0,   0,   0,   128, 59,  0,   0,   128, 195, 0,   0,   0,   0,   0,   0,   0,   0,   21,  0,
    0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   10,
    0,   16,  0,   19,  0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,
    58,  0,   16,  0,   8,   0,   0,   0,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,
    0,   2,   64,  0,   0,   0,   0,   0,   59,  0,   0,   128, 194, 0,   0,   0,   0,   0,   0,
    0,   0,   18,  0,   0,   1,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   2,
    64,  0,   0,   0,   0,   128, 58,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    21,  0,   0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,
    0,   10,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   19,  0,   0,   0,   50,  0,
    0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   1,
    64,  0,   0,   0,   0,   127, 72,  26,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,
    18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,
    0,   7,   0,   0,   0,   67,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,
    16,  0,   7,   0,   0,   0,   0,   0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,
    0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,
    18,  0,   16,  0,   19,  0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,
    0,   8,   32,  128, 58,  31,  0,   4,   3,   26,  0,   16,  0,   11,  0,   0,   0,   29,  0,
    0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   19,  0,   0,   0,   1,
    64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,   10,  0,   16,  0,   7,   0,   0,   0,
    54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,
    60,  0,   0,   128, 196, 0,   0,   0,   0,   0,   0,   0,   0,   18,  0,   0,   1,   54,  0,
    0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 59,  0,
    0,   128, 195, 0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   18,  0,   0,   1,
    29,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   26,  0,   16,  0,   19,  0,   0,
    0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,   58,  0,   16,  0,   8,   0,
    0,   0,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   59,  0,   0,   128, 194, 0,   0,   0,   0,   0,   0,   0,   0,   18,  0,   0,   1,
    54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128,
    58,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,
    0,   1,   56,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   7,
    0,   0,   0,   26,  0,   16,  0,   19,  0,   0,   0,   50,  0,   0,   9,   34,  0,   16,  0,
    7,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127,
    72,  26,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   18,  0,   16,  0,   7,   0,
    0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   67,
    0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,
    0,   0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,
    0,   26,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   34,  0,   16,  0,   19,  0,
    0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   8,   32,  128, 58,  31,
    0,   4,   3,   42,  0,   16,  0,   11,  0,   0,   0,   29,  0,   0,   7,   18,  0,   16,  0,
    7,   0,   0,   0,   42,  0,   16,  0,   19,  0,   0,   0,   1,   64,  0,   0,   193, 192, 64,
    63,  31,  0,   4,   3,   10,  0,   16,  0,   7,   0,   0,   0,   54,  0,   0,   8,   50,  0,
    16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   60,  0,   0,   128, 196, 0,
    0,   0,   0,   0,   0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   8,   50,  0,   16,  0,
    7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 59,  0,   0,   128, 195, 0,   0,   0,
    0,   0,   0,   0,   0,   21,  0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   130, 0,
    16,  0,   8,   0,   0,   0,   42,  0,   16,  0,   19,  0,   0,   0,   1,   64,  0,   0,   129,
    128, 128, 62,  31,  0,   4,   3,   58,  0,   16,  0,   8,   0,   0,   0,   54,  0,   0,   8,
    50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   59,  0,   0,   128,
    194, 0,   0,   0,   0,   0,   0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   8,   50,  0,
    16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 58,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,   0,   7,
    130, 0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   42,  0,   16,
    0,   19,  0,   0,   0,   50,  0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   58,  0,
    16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  26,  0,   16,  0,   7,
    0,   0,   0,   56,  0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,
    7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   67,  0,   0,   5,   18,  0,   16,
    0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   0,   0,   0,   7,   18,  0,
    16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,
    0,   0,   0,   56,  0,   0,   7,   66,  0,   16,  0,   19,  0,   0,   0,   10,  0,   16,  0,
    7,   0,   0,   0,   1,   64,  0,   0,   8,   32,  128, 58,  31,  0,   4,   3,   58,  0,   16,
    0,   11,  0,   0,   0,   29,  0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   58,  0,
    16,  0,   19,  0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,   10,
    0,   16,  0,   7,   0,   0,   0,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,
    2,   64,  0,   0,   0,   0,   0,   60,  0,   0,   128, 196, 0,   0,   0,   0,   0,   0,   0,
    0,   18,  0,   0,   1,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   2,   64,
    0,   0,   0,   0,   128, 59,  0,   0,   128, 195, 0,   0,   0,   0,   0,   0,   0,   0,   21,
    0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   130, 0,   16,  0,   8,   0,   0,   0,
    58,  0,   16,  0,   19,  0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,
    3,   58,  0,   16,  0,   8,   0,   0,   0,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,
    0,   0,   2,   64,  0,   0,   0,   0,   0,   59,  0,   0,   128, 194, 0,   0,   0,   0,   0,
    0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,
    2,   64,  0,   0,   0,   0,   128, 58,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   130, 0,   16,  0,   8,   0,
    0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   19,  0,   0,   0,   50,
    0,   0,   9,   34,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,
    1,   64,  0,   0,   0,   0,   127, 72,  26,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,
    7,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   26,  0,
    16,  0,   7,   0,   0,   0,   67,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   10,
    0,   16,  0,   7,   0,   0,   0,   0,   0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,
    10,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,
    7,   130, 0,   16,  0,   19,  0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   1,   64,
    0,   0,   8,   32,  128, 58,  21,  0,   0,   1,   0,   0,   0,   7,   242, 0,   16,  0,   18,
    0,   0,   0,   70,  14,  16,  0,   18,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,
    0,   0,   0,   7,   242, 0,   16,  0,   15,  0,   0,   0,   70,  14,  16,  0,   15,  0,   0,
    0,   70,  14,  16,  0,   19,  0,   0,   0,   80,  0,   0,   7,   66,  0,   16,  0,   5,   0,
    0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   6,   0,   0,   0,   31,
    0,   4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   56,  0,   0,   7,   34,  0,   16,  0,
    0,   0,   0,   0,   26,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128,
    62,  31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,   0,   41,  0,   0,   10,  50,  0,
    16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   8,   0,   0,   0,   2,   64,  0,   0,   1,
    0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   10,
    50,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,
    0,   252, 255, 255, 255, 252, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   140, 0,
    0,   17,  50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  0,   16,  0,   8,   0,   0,
    0,   70,  0,   16,  0,   7,   0,   0,   0,   30,  0,   0,   10,  50,  0,   16,  0,   11,  0,
    0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   2,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,
    66,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,
    0,   1,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   41,  0,
    0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   8,   0,   0,   0,   1,
    64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,
    42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255, 140, 0,   0,
    11,  66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,
    0,   0,   0,   0,   0,   0,   26,  0,   16,  0,   8,   0,   0,   0,   42,  0,   16,  0,   5,
    0,   0,   0,   1,   0,   0,   10,  82,  0,   16,  0,   11,  0,   0,   0,   6,   0,   16,  0,
    8,   0,   0,   0,   2,   64,  0,   0,   253, 255, 255, 255, 0,   0,   0,   0,   2,   0,   0,
    0,   0,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   11,  0,   0,   0,   42,  0,
    16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   11,  0,   0,   0,   18,  0,   0,   1,   54,
    0,   0,   5,   50,  0,   16,  0,   11,  0,   0,   0,   70,  0,   16,  0,   8,   0,   0,   0,
    21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   50,  0,   16,  0,   7,   0,   0,
    0,   70,  0,   16,  0,   11,  0,   0,   0,   70,  0,   16,  0,   2,   0,   0,   0,   214, 5,
    16,  0,   6,   0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   11,  0,   0,   0,   0,
    208, 0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,
    35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   11,  0,   0,
    0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   11,  0,   0,   0,   30,  0,
    0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   42,
    0,   16,  0,   5,   0,   0,   0,   35,  0,   0,   10,  50,  0,   16,  0,   7,   0,   0,   0,
    70,  0,   16,  128, 65,  0,   0,   0,   11,  0,   0,   0,   134, 0,   16,  0,   10,  0,   0,
    0,   70,  0,   16,  0,   7,   0,   0,   0,   35,  0,   0,   9,   18,  0,   16,  0,   7,   0,
    0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   10,
    0,   16,  0,   7,   0,   0,   0,   41,  0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,
    10,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,
    9,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   42,  0,
    16,  0,   9,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   78,  0,   0,   8,   0,
    208, 0,   0,   18,  0,   16,  0,   11,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,
    10,  0,   16,  0,   9,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,
    0,   41,  0,   0,   10,  50,  0,   16,  0,   7,   0,   0,   0,   214, 5,   16,  0,   10,  0,
    0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   1,   0,   0,   10,  50,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,
    7,   0,   0,   0,   2,   64,  0,   0,   252, 255, 255, 255, 252, 255, 255, 255, 0,   0,   0,
    0,   0,   0,   0,   0,   140, 0,   0,   17,  50,  0,   16,  0,   7,   0,   0,   0,   2,   64,
    0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,
    64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    214, 5,   16,  0,   10,  0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   30,  0,   0,
    10,  50,  0,   16,  0,   19,  0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,
    0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   18,
    0,   0,   1,   32,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,
    4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,
    0,   5,   0,   0,   0,   41,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   58,  0,
    16,  0,   10,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   66,
    0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,
    252, 255, 255, 255, 140, 0,   0,   11,  66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,
    0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   58,  0,   16,  0,   10,  0,
    0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   0,   0,   10,  82,  0,   16,  0,   19,
    0,   0,   0,   86,  5,   16,  0,   10,  0,   0,   0,   2,   64,  0,   0,   253, 255, 255, 255,
    0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,
    0,   19,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   19,  0,
    0,   0,   18,  0,   0,   1,   54,  0,   0,   5,   50,  0,   16,  0,   19,  0,   0,   0,   214,
    5,   16,  0,   10,  0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,
    50,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   19,  0,   0,   0,   70,  0,   16,
    0,   2,   0,   0,   0,   214, 5,   16,  0,   9,   0,   0,   0,   78,  0,   0,   8,   50,  0,
    16,  0,   19,  0,   0,   0,   0,   208, 0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   134,
    0,   16,  0,   10,  0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,
    26,  0,   16,  0,   19,  0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,
    0,   19,  0,   0,   0,   30,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,
    16,  0,   4,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   35,  0,   0,   10,  50,
    0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  128, 65,  0,   0,   0,   19,  0,   0,   0,
    134, 0,   16,  0,   10,  0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   35,  0,   0,
    9,   18,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   10,  0,
    16,  0,   10,  0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   41,  0,   0,   7,   18,
    0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,
    4,   0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,
    0,   5,   0,   0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   10,  0,   16,  0,   7,   0,
    0,   0,   78,  0,   0,   8,   0,   208, 0,   0,   34,  0,   16,  0,   11,  0,   0,   0,   42,
    0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   31,  0,   4,   3,
    42,  0,   16,  0,   8,   0,   0,   0,   41,  0,   0,   10,  50,  0,   16,  0,   7,   0,   0,
    0,   230, 10,  16,  0,   12,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   10,  50,  0,   16,  0,   7,
    0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   252, 255, 255, 255,
    252, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   140, 0,   0,   17,  50,  0,   16,
    0,   7,   0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   230, 10,  16,  0,   12,  0,   0,   0,   70,  0,   16,  0,
    7,   0,   0,   0,   30,  0,   0,   10,  50,  0,   16,  0,   19,  0,   0,   0,   70,  0,   16,
    0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   66,  0,   16,  0,   5,
    0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,
    31,  0,   4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   41,  0,   0,   7,   66,  0,   16,
    0,   5,   0,   0,   0,   58,  0,   16,  0,   12,  0,   0,   0,   1,   64,  0,   0,   1,   0,
    0,   0,   1,   0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,
    0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255, 140, 0,   0,   11,  66,  0,   16,  0,
    5,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,
    0,   58,  0,   16,  0,   12,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   0,
    0,   10,  82,  0,   16,  0,   19,  0,   0,   0,   166, 10,  16,  0,   12,  0,   0,   0,   2,
    64,  0,   0,   253, 255, 255, 255, 0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,
    30,  0,   0,   7,   34,  0,   16,  0,   19,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,
    0,   42,  0,   16,  0,   19,  0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   5,   50,  0,
    16,  0,   19,  0,   0,   0,   230, 10,  16,  0,   12,  0,   0,   0,   21,  0,   0,   1,   21,
    0,   0,   1,   35,  0,   0,   9,   50,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,
    19,  0,   0,   0,   70,  0,   16,  0,   2,   0,   0,   0,   70,  0,   16,  0,   12,  0,   0,
    0,   78,  0,   0,   8,   50,  0,   16,  0,   19,  0,   0,   0,   0,   208, 0,   0,   70,  0,
    16,  0,   7,   0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   35,  0,   0,   9,   66,
    0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   19,  0,   0,   0,   10,  0,   16,  0,
    0,   0,   0,   0,   10,  0,   16,  0,   19,  0,   0,   0,   30,  0,   0,   7,   66,  0,   16,
    0,   5,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   42,  0,   16,  0,   5,   0,
    0,   0,   35,  0,   0,   10,  50,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  128, 65,
    0,   0,   0,   19,  0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   70,  0,   16,  0,
    7,   0,   0,   0,   35,  0,   0,   9,   18,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,
    0,   7,   0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   10,  0,   16,  0,   7,   0,
    0,   0,   41,  0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,
    0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,
    5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   9,   0,   0,
    0,   10,  0,   16,  0,   7,   0,   0,   0,   78,  0,   0,   8,   0,   208, 0,   0,   66,  0,
    16,  0,   11,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   9,
    0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,   0,   41,  0,   0,   10,
    50,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   13,  0,   0,   0,   2,   64,  0,
    0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,
    0,   10,  50,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,
    64,  0,   0,   252, 255, 255, 255, 252, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,
    140, 0,   0,   17,  50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   1,   0,   0,
    0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  0,   16,  0,   13,
    0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   30,  0,   0,   10,  50,  0,   16,  0,
    19,  0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,
    0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   18,  0,   0,   1,   32,  0,
    0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,
    64,  0,   0,   1,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   5,   0,   0,   0,
    41,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   13,  0,   0,
    0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   66,  0,   16,  0,   5,   0,
    0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255, 140,
    0,   0,   11,  66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,
    1,   64,  0,   0,   0,   0,   0,   0,   26,  0,   16,  0,   13,  0,   0,   0,   42,  0,   16,
    0,   5,   0,   0,   0,   1,   0,   0,   10,  82,  0,   16,  0,   19,  0,   0,   0,   6,   0,
    16,  0,   13,  0,   0,   0,   2,   64,  0,   0,   253, 255, 255, 255, 0,   0,   0,   0,   2,
    0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   19,  0,   0,   0,
    42,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   19,  0,   0,   0,   18,  0,   0,
    1,   54,  0,   0,   5,   50,  0,   16,  0,   19,  0,   0,   0,   70,  0,   16,  0,   13,  0,
    0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   50,  0,   16,  0,   7,
    0,   0,   0,   70,  0,   16,  0,   19,  0,   0,   0,   70,  0,   16,  0,   2,   0,   0,   0,
    230, 10,  16,  0,   7,   0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   19,  0,   0,
    0,   0,   208, 0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   134, 0,   16,  0,   10,  0,
    0,   0,   35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   19,
    0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   19,  0,   0,   0,
    30,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,
    0,   42,  0,   16,  0,   5,   0,   0,   0,   35,  0,   0,   10,  50,  0,   16,  0,   7,   0,
    0,   0,   70,  0,   16,  128, 65,  0,   0,   0,   19,  0,   0,   0,   134, 0,   16,  0,   10,
    0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   35,  0,   0,   9,   18,  0,   16,  0,
    7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   10,  0,   0,
    0,   10,  0,   16,  0,   7,   0,   0,   0,   41,  0,   0,   7,   18,  0,   16,  0,   7,   0,
    0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,
    0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,
    42,  0,   16,  0,   9,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   78,  0,   0,
    8,   0,   208, 0,   0,   130, 0,   16,  0,   11,  0,   0,   0,   42,  0,   16,  0,   5,   0,
    0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   30,  0,   0,   7,   242, 0,   16,  0,   11,
    0,   0,   0,   246, 15,  16,  0,   0,   0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,
    31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,   0,   41,  0,   0,   10,  50,  0,   16,
    0,   7,   0,   0,   0,   70,  0,   16,  0,   14,  0,   0,   0,   2,   64,  0,   0,   1,   0,
    0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   10,  50,
    0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,
    252, 255, 255, 255, 252, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   140, 0,   0,
    17,  50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  0,   16,  0,   14,  0,   0,   0,
    70,  0,   16,  0,   7,   0,   0,   0,   30,  0,   0,   10,  50,  0,   16,  0,   19,  0,   0,
    0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   2,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   66,
    0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,
    1,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   41,  0,   0,
    7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   14,  0,   0,   0,   1,   64,
    0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,
    0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255, 140, 0,   0,   11,
    66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   0,   0,   26,  0,   16,  0,   14,  0,   0,   0,   42,  0,   16,  0,   5,   0,
    0,   0,   1,   0,   0,   10,  82,  0,   16,  0,   19,  0,   0,   0,   6,   0,   16,  0,   14,
    0,   0,   0,   2,   64,  0,   0,   253, 255, 255, 255, 0,   0,   0,   0,   2,   0,   0,   0,
    0,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   19,  0,   0,   0,   42,  0,   16,
    0,   5,   0,   0,   0,   42,  0,   16,  0,   19,  0,   0,   0,   18,  0,   0,   1,   54,  0,
    0,   5,   50,  0,   16,  0,   19,  0,   0,   0,   70,  0,   16,  0,   14,  0,   0,   0,   21,
    0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   50,  0,   16,  0,   7,   0,   0,   0,
    70,  0,   16,  0,   19,  0,   0,   0,   70,  0,   16,  0,   2,   0,   0,   0,   230, 10,  16,
    0,   13,  0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   19,  0,   0,   0,   0,   208,
    0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   35,
    0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   19,  0,   0,   0,
    10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   19,  0,   0,   0,   30,  0,   0,
    7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   42,  0,
    16,  0,   5,   0,   0,   0,   35,  0,   0,   10,  50,  0,   16,  0,   7,   0,   0,   0,   70,
    0,   16,  128, 65,  0,   0,   0,   19,  0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,
    70,  0,   16,  0,   7,   0,   0,   0,   35,  0,   0,   9,   18,  0,   16,  0,   7,   0,   0,
    0,   26,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   10,  0,
    16,  0,   7,   0,   0,   0,   41,  0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,
    0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,   9,
    66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,
    0,   9,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   78,  0,   0,   8,   0,   208,
    0,   0,   18,  0,   16,  0,   19,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   10,
    0,   16,  0,   9,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,   0,
    41,  0,   0,   10,  50,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   16,  0,   0,
    0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   1,   0,   0,   10,  50,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   7,
    0,   0,   0,   2,   64,  0,   0,   252, 255, 255, 255, 252, 255, 255, 255, 0,   0,   0,   0,
    0,   0,   0,   0,   140, 0,   0,   17,  50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,
    0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,
    0,   16,  0,   16,  0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   30,  0,   0,   10,
    50,  0,   16,  0,   20,  0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   18,  0,
    0,   1,   32,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   4,
    0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,
    5,   0,   0,   0,   41,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,
    0,   16,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   66,  0,
    16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   252,
    255, 255, 255, 140, 0,   0,   11,  66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,
    1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   26,  0,   16,  0,   16,  0,   0,
    0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   0,   0,   10,  82,  0,   16,  0,   20,  0,
    0,   0,   6,   0,   16,  0,   16,  0,   0,   0,   2,   64,  0,   0,   253, 255, 255, 255, 0,
    0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,
    20,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   20,  0,   0,
    0,   18,  0,   0,   1,   54,  0,   0,   5,   50,  0,   16,  0,   20,  0,   0,   0,   70,  0,
    16,  0,   16,  0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   50,
    0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   20,  0,   0,   0,   70,  0,   16,  0,
    2,   0,   0,   0,   230, 10,  16,  0,   14,  0,   0,   0,   78,  0,   0,   8,   50,  0,   16,
    0,   20,  0,   0,   0,   0,   208, 0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   134, 0,
    16,  0,   10,  0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   26,
    0,   16,  0,   20,  0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,
    20,  0,   0,   0,   30,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,
    0,   4,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   35,  0,   0,   10,  50,  0,
    16,  0,   7,   0,   0,   0,   70,  0,   16,  128, 65,  0,   0,   0,   20,  0,   0,   0,   134,
    0,   16,  0,   10,  0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   35,  0,   0,   9,
    18,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,
    0,   10,  0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   41,  0,   0,   7,   18,  0,
    16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   4,
    0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,
    5,   0,   0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,
    0,   78,  0,   0,   8,   0,   208, 0,   0,   34,  0,   16,  0,   19,  0,   0,   0,   42,  0,
    16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   31,  0,   4,   3,   42,
    0,   16,  0,   8,   0,   0,   0,   41,  0,   0,   10,  50,  0,   16,  0,   7,   0,   0,   0,
    70,  0,   16,  0,   17,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   10,  50,  0,   16,  0,   7,   0,
    0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   252, 255, 255, 255, 252,
    255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   140, 0,   0,   17,  50,  0,   16,  0,
    7,   0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   70,  0,   16,  0,   17,  0,   0,   0,   70,  0,   16,  0,   7,
    0,   0,   0,   30,  0,   0,   10,  50,  0,   16,  0,   20,  0,   0,   0,   70,  0,   16,  0,
    7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   66,  0,   16,  0,   5,   0,
    0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,
    0,   4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   41,  0,   0,   7,   66,  0,   16,  0,
    5,   0,   0,   0,   26,  0,   16,  0,   17,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,
    0,   1,   0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,
    0,   0,   1,   64,  0,   0,   252, 255, 255, 255, 140, 0,   0,   11,  66,  0,   16,  0,   5,
    0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,
    26,  0,   16,  0,   17,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   0,   0,
    10,  82,  0,   16,  0,   20,  0,   0,   0,   6,   0,   16,  0,   17,  0,   0,   0,   2,   64,
    0,   0,   253, 255, 255, 255, 0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   30,
    0,   0,   7,   34,  0,   16,  0,   20,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,
    42,  0,   16,  0,   20,  0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   5,   50,  0,   16,
    0,   20,  0,   0,   0,   70,  0,   16,  0,   17,  0,   0,   0,   21,  0,   0,   1,   21,  0,
    0,   1,   35,  0,   0,   9,   50,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   20,
    0,   0,   0,   70,  0,   16,  0,   2,   0,   0,   0,   230, 10,  16,  0,   16,  0,   0,   0,
    78,  0,   0,   8,   50,  0,   16,  0,   20,  0,   0,   0,   0,   208, 0,   0,   70,  0,   16,
    0,   7,   0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   35,  0,   0,   9,   66,  0,
    16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   20,  0,   0,   0,   10,  0,   16,  0,   0,
    0,   0,   0,   10,  0,   16,  0,   20,  0,   0,   0,   30,  0,   0,   7,   66,  0,   16,  0,
    5,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,
    0,   35,  0,   0,   10,  50,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  128, 65,  0,
    0,   0,   20,  0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   70,  0,   16,  0,   7,
    0,   0,   0,   35,  0,   0,   9,   18,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,
    7,   0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   10,  0,   16,  0,   7,   0,   0,
    0,   41,  0,   0,   7,   18,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   7,   0,
    0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,   5,
    0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   9,   0,   0,   0,
    10,  0,   16,  0,   7,   0,   0,   0,   78,  0,   0,   8,   0,   208, 0,   0,   66,  0,   16,
    0,   19,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   9,   0,
    0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,   0,   41,  0,   0,   10,  50,
    0,   16,  0,   7,   0,   0,   0,   230, 10,  16,  0,   17,  0,   0,   0,   2,   64,  0,   0,
    1,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,
    10,  50,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,
    0,   0,   252, 255, 255, 255, 252, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   140,
    0,   0,   17,  50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,
    1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   230, 10,  16,  0,   17,  0,
    0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   30,  0,   0,   10,  50,  0,   16,  0,   20,
    0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,
    2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   18,  0,   0,   1,   32,  0,   0,
    7,   66,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,
    0,   0,   1,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   41,
    0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   58,  0,   16,  0,   17,  0,   0,   0,
    1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   66,  0,   16,  0,   5,   0,   0,
    0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255, 140, 0,
    0,   11,  66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,
    64,  0,   0,   0,   0,   0,   0,   58,  0,   16,  0,   17,  0,   0,   0,   42,  0,   16,  0,
    5,   0,   0,   0,   1,   0,   0,   10,  82,  0,   16,  0,   20,  0,   0,   0,   166, 10,  16,
    0,   17,  0,   0,   0,   2,   64,  0,   0,   253, 255, 255, 255, 0,   0,   0,   0,   2,   0,
    0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   20,  0,   0,   0,   42,
    0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   20,  0,   0,   0,   18,  0,   0,   1,
    54,  0,   0,   5,   50,  0,   16,  0,   20,  0,   0,   0,   230, 10,  16,  0,   17,  0,   0,
    0,   21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   50,  0,   16,  0,   7,   0,
    0,   0,   70,  0,   16,  0,   20,  0,   0,   0,   70,  0,   16,  0,   2,   0,   0,   0,   150,
    5,   16,  0,   1,   0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   20,  0,   0,   0,
    0,   208, 0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   134, 0,   16,  0,   10,  0,   0,
    0,   35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   20,  0,
    0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   20,  0,   0,   0,   30,
    0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,
    42,  0,   16,  0,   5,   0,   0,   0,   35,  0,   0,   10,  50,  0,   16,  0,   7,   0,   0,
    0,   70,  0,   16,  128, 65,  0,   0,   0,   20,  0,   0,   0,   134, 0,   16,  0,   10,  0,
    0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   35,  0,   0,   9,   18,  0,   16,  0,   7,
    0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,
    10,  0,   16,  0,   7,   0,   0,   0,   41,  0,   0,   7,   18,  0,   16,  0,   7,   0,   0,
    0,   10,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,
    0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   42,
    0,   16,  0,   9,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   78,  0,   0,   8,
    0,   208, 0,   0,   130, 0,   16,  0,   19,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,
    0,   10,  0,   16,  0,   9,   0,   0,   0,   30,  0,   0,   7,   242, 0,   16,  0,   19,  0,
    0,   0,   246, 15,  16,  0,   0,   0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   41,
    0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,
    2,   64,  0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   2,   0,   0,
    0,   165, 0,   0,   8,   18,  0,   16,  0,   20,  0,   0,   0,   10,  0,   16,  0,   11,  0,
    0,   0,   6,   112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   165, 0,   0,   8,   34,
    0,   16,  0,   20,  0,   0,   0,   26,  0,   16,  0,   11,  0,   0,   0,   6,   112, 32,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   165, 0,   0,   8,   66,  0,   16,  0,   20,  0,   0,
    0,   42,  0,   16,  0,   11,  0,   0,   0,   6,   112, 32,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   165, 0,   0,   8,   130, 0,   16,  0,   20,  0,   0,   0,   58,  0,   16,  0,   11,
    0,   0,   0,   6,   112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   41,  0,   0,   10,
    242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   2,   64,  0,
    0,   2,   0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   165, 0,
    0,   8,   18,  0,   16,  0,   19,  0,   0,   0,   10,  0,   16,  0,   11,  0,   0,   0,   6,
    112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   165, 0,   0,   8,   34,  0,   16,  0,
    19,  0,   0,   0,   26,  0,   16,  0,   11,  0,   0,   0,   6,   112, 32,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   165, 0,   0,   8,   66,  0,   16,  0,   19,  0,   0,   0,   42,  0,
    16,  0,   11,  0,   0,   0,   6,   112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   165,
    0,   0,   8,   130, 0,   16,  0,   19,  0,   0,   0,   58,  0,   16,  0,   11,  0,   0,   0,
    6,   112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,
    0,   4,   0,   0,   0,   76,  0,   0,   3,   42,  0,   16,  0,   4,   0,   0,   0,   6,   0,
    0,   3,   1,   64,  0,   0,   5,   0,   0,   0,   1,   0,   0,   7,   66,  0,   16,  0,   5,
    0,   0,   0,   58,  0,   16,  0,   2,   0,   0,   0,   1,   64,  0,   0,   16,  0,   0,   0,
    85,  0,   0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,
    0,   166, 10,  16,  0,   5,   0,   0,   0,   139, 0,   0,   15,  242, 0,   16,  0,   11,  0,
    0,   0,   2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,
    0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   43,  0,   0,   5,   242, 0,   16,
    0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,
    16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,
    1,   128, 58,  0,   1,   128, 58,  0,   1,   128, 58,  0,   1,   128, 58,  52,  0,   0,   10,
    242, 0,   16,  0,   20,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,
    0,   0,   0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 85,  0,
    0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   166,
    10,  16,  0,   5,   0,   0,   0,   139, 0,   0,   15,  242, 0,   16,  0,   11,  0,   0,   0,
    2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,
    0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   43,  0,   0,   5,   242, 0,   16,  0,   11,
    0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,
    11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   1,   128,
    58,  0,   1,   128, 58,  0,   1,   128, 58,  0,   1,   128, 58,  52,  0,   0,   10,  242, 0,
    16,  0,   19,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,
    0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 2,   0,   0,   1,
    6,   0,   0,   3,   1,   64,  0,   0,   7,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,
    0,   2,   0,   0,   0,   85,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,
    16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,
    0,   0,   0,   16,  0,   0,   0,   131, 0,   0,   5,   242, 0,   16,  0,   20,  0,   0,   0,
    70,  14,  16,  0,   11,  0,   0,   0,   85,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,
    0,   70,  14,  16,  0,   19,  0,   0,   0,   2,   64,  0,   0,   16,  0,   0,   0,   16,  0,
    0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   131, 0,   0,   5,   242, 0,   16,  0,   19,
    0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   18,  0,   0,   1,   131, 0,   0,   5,
    242, 0,   16,  0,   20,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   131, 0,   0,
    5,   242, 0,   16,  0,   19,  0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   21,  0,
    0,   1,   2,   0,   0,   1,   10,  0,   0,   1,   31,  0,   4,   3,   58,  0,   16,  0,   2,
    0,   0,   0,   54,  0,   0,   8,   242, 0,   16,  0,   20,  0,   0,   0,   2,   64,  0,   0,
    0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  54,  0,   0,
    8,   242, 0,   16,  0,   19,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,
    128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  21,  0,   0,   1,   2,   0,   0,   1,   23,
    0,   0,   1,   18,  0,   0,   1,   76,  0,   0,   3,   42,  0,   16,  0,   4,   0,   0,   0,
    6,   0,   0,   3,   1,   64,  0,   0,   0,   0,   0,   0,   6,   0,   0,   3,   1,   64,  0,
    0,   1,   0,   0,   0,   1,   0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   10,  0,
    16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   16,  0,   0,   0,   55,  0,   0,   9,   66,
    0,   16,  0,   5,   0,   0,   0,   58,  0,   16,  0,   2,   0,   0,   0,   1,   64,  0,   0,
    24,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   85,  0,   0,   7,   242, 0,   16,
    0,   11,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   166, 10,  16,  0,   5,   0,
    0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,
    0,   0,   0,   2,   64,  0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   255, 0,   0,   0,
    255, 0,   0,   0,   86,  0,   0,   5,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,
    0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   20,  0,   0,   0,   70,  14,
    16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   129, 128, 128, 59,  129, 128, 128, 59,  129,
    128, 128, 59,  129, 128, 128, 59,  85,  0,   0,   7,   242, 0,   16,  0,   11,  0,   0,   0,
    70,  14,  16,  0,   19,  0,   0,   0,   166, 10,  16,  0,   5,   0,   0,   0,   1,   0,   0,
    10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,
    0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   86,
    0,   0,   5,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,
    56,  0,   0,   10,  242, 0,   16,  0,   19,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,
    0,   2,   64,  0,   0,   129, 128, 128, 59,  129, 128, 128, 59,  129, 128, 128, 59,  129, 128,
    128, 59,  2,   0,   0,   1,   6,   0,   0,   3,   1,   64,  0,   0,   2,   0,   0,   0,   6,
    0,   0,   3,   1,   64,  0,   0,   10,  0,   0,   0,   6,   0,   0,   3,   1,   64,  0,   0,
    3,   0,   0,   0,   6,   0,   0,   3,   1,   64,  0,   0,   12,  0,   0,   0,   31,  0,   4,
    3,   58,  0,   16,  0,   2,   0,   0,   0,   85,  0,   0,   10,  242, 0,   16,  0,   11,  0,
    0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   30,  0,   0,   0,   30,
    0,   0,   0,   30,  0,   0,   0,   30,  0,   0,   0,   86,  0,   0,   5,   242, 0,   16,  0,
    11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,
    0,   20,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   171, 170,
    170, 62,  171, 170, 170, 62,  171, 170, 170, 62,  171, 170, 170, 62,  85,  0,   0,   10,  242,
    0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   2,   64,  0,   0,
    30,  0,   0,   0,   30,  0,   0,   0,   30,  0,   0,   0,   30,  0,   0,   0,   86,  0,   0,
    5,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,
    0,   10,  242, 0,   16,  0,   19,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,
    64,  0,   0,   171, 170, 170, 62,  171, 170, 170, 62,  171, 170, 170, 62,  171, 170, 170, 62,
    18,  0,   0,   1,   1,   0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,
    0,   5,   0,   0,   0,   1,   64,  0,   0,   20,  0,   0,   0,   32,  0,   0,   10,  50,  0,
    16,  0,   7,   0,   0,   0,   166, 10,  16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   2,
    0,   0,   0,   10,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   60,  0,   0,   7,
    18,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,
    0,   7,   0,   0,   0,   31,  0,   4,   3,   10,  0,   16,  0,   7,   0,   0,   0,   85,  0,
    0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   166,
    10,  16,  0,   5,   0,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,
    70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   255, 3,   0,   0,   255, 3,   0,
    0,   255, 3,   0,   0,   255, 3,   0,   0,   86,  0,   0,   5,   242, 0,   16,  0,   11,  0,
    0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   20,
    0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   8,   32,  128, 58,
    8,   32,  128, 58,  8,   32,  128, 58,  8,   32,  128, 58,  85,  0,   0,   7,   242, 0,   16,
    0,   11,  0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   166, 10,  16,  0,   5,   0,
    0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,
    0,   0,   0,   2,   64,  0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,
    255, 3,   0,   0,   86,  0,   0,   5,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,
    0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   19,  0,   0,   0,   70,  14,
    16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   8,   32,  128, 58,  8,   32,  128, 58,  8,
    32,  128, 58,  8,   32,  128, 58,  18,  0,   0,   1,   85,  0,   0,   7,   242, 0,   16,  0,
    11,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   166, 10,  16,  0,   5,   0,   0,
    0,   1,   0,   0,   10,  242, 0,   16,  0,   21,  0,   0,   0,   70,  14,  16,  0,   11,  0,
    0,   0,   2,   64,  0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255,
    3,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   22,  0,   0,   0,   70,  14,  16,  0,
    11,  0,   0,   0,   2,   64,  0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,
    0,   127, 0,   0,   0,   138, 0,   0,   15,  242, 0,   16,  0,   23,  0,   0,   0,   2,   64,
    0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   2,
    64,  0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,
    70,  14,  16,  0,   11,  0,   0,   0,   135, 0,   0,   5,   242, 0,   16,  0,   24,  0,   0,
    0,   70,  14,  16,  0,   22,  0,   0,   0,   30,  0,   0,   10,  242, 0,   16,  0,   24,  0,
    0,   0,   70,  14,  16,  0,   24,  0,   0,   0,   2,   64,  0,   0,   232, 255, 255, 255, 232,
    255, 255, 255, 232, 255, 255, 255, 232, 255, 255, 255, 55,  0,   0,   12,  242, 0,   16,  0,
    24,  0,   0,   0,   70,  14,  16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   24,  0,   0,
    0,   2,   64,  0,   0,   8,   0,   0,   0,   8,   0,   0,   0,   8,   0,   0,   0,   8,   0,
    0,   0,   30,  0,   0,   11,  242, 0,   16,  0,   25,  0,   0,   0,   70,  14,  16,  128, 65,
    0,   0,   0,   24,  0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
    1,   0,   0,   0,   1,   0,   0,   0,   55,  0,   0,   9,   242, 0,   16,  0,   25,  0,   0,
    0,   70,  14,  16,  0,   23,  0,   0,   0,   70,  14,  16,  0,   23,  0,   0,   0,   70,  14,
    16,  0,   25,  0,   0,   0,   140, 0,   0,   17,  242, 0,   16,  0,   11,  0,   0,   0,   2,
    64,  0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,
    70,  14,  16,  0,   24,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,
    0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,
    64,  0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,
    55,  0,   0,   9,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   23,  0,   0,
    0,   70,  14,  16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   41,  0,
    0,   10,  242, 0,   16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   25,  0,   0,   0,   2,
    64,  0,   0,   23,  0,   0,   0,   23,  0,   0,   0,   23,  0,   0,   0,   23,  0,   0,   0,
    30,  0,   0,   10,  242, 0,   16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   22,  0,   0,
    0,   2,   64,  0,   0,   0,   0,   0,   62,  0,   0,   0,   62,  0,   0,   0,   62,  0,   0,
    0,   62,  41,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,
    0,   0,   0,   2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,
    16,  0,   0,   0,   30,  0,   0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,
    0,   22,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   55,  0,   0,   12,  242, 0,
    16,  0,   20,  0,   0,   0,   70,  14,  16,  0,   21,  0,   0,   0,   70,  14,  16,  0,   11,
    0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   85,  0,   0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,
    0,   19,  0,   0,   0,   166, 10,  16,  0,   5,   0,   0,   0,   1,   0,   0,   10,  242, 0,
    16,  0,   21,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   255,
    3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   1,   0,   0,   10,
    242, 0,   16,  0,   22,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,
    0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   138, 0,
    0,   15,  242, 0,   16,  0,   23,  0,   0,   0,   2,   64,  0,   0,   3,   0,   0,   0,   3,
    0,   0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   2,   64,  0,   0,   7,   0,   0,   0,
    7,   0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   70,  14,  16,  0,   11,  0,   0,
    0,   135, 0,   0,   5,   242, 0,   16,  0,   24,  0,   0,   0,   70,  14,  16,  0,   22,  0,
    0,   0,   30,  0,   0,   10,  242, 0,   16,  0,   24,  0,   0,   0,   70,  14,  16,  0,   24,
    0,   0,   0,   2,   64,  0,   0,   232, 255, 255, 255, 232, 255, 255, 255, 232, 255, 255, 255,
    232, 255, 255, 255, 55,  0,   0,   12,  242, 0,   16,  0,   24,  0,   0,   0,   70,  14,  16,
    0,   22,  0,   0,   0,   70,  14,  16,  0,   24,  0,   0,   0,   2,   64,  0,   0,   8,   0,
    0,   0,   8,   0,   0,   0,   8,   0,   0,   0,   8,   0,   0,   0,   30,  0,   0,   11,  242,
    0,   16,  0,   25,  0,   0,   0,   70,  14,  16,  128, 65,  0,   0,   0,   24,  0,   0,   0,
    2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,
    0,   55,  0,   0,   9,   242, 0,   16,  0,   25,  0,   0,   0,   70,  14,  16,  0,   23,  0,
    0,   0,   70,  14,  16,  0,   23,  0,   0,   0,   70,  14,  16,  0,   25,  0,   0,   0,   140,
    0,   0,   17,  242, 0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   7,   0,   0,   0,
    7,   0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   70,  14,  16,  0,   24,  0,   0,
    0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   11,
    0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   127, 0,   0,   0,
    127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   55,  0,   0,   9,   242, 0,   16,
    0,   11,  0,   0,   0,   70,  14,  16,  0,   23,  0,   0,   0,   70,  14,  16,  0,   22,  0,
    0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   41,  0,   0,   10,  242, 0,   16,  0,   22,
    0,   0,   0,   70,  14,  16,  0,   25,  0,   0,   0,   2,   64,  0,   0,   23,  0,   0,   0,
    23,  0,   0,   0,   23,  0,   0,   0,   23,  0,   0,   0,   30,  0,   0,   10,  242, 0,   16,
    0,   22,  0,   0,   0,   70,  14,  16,  0,   22,  0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   62,  0,   0,   0,   62,  0,   0,   0,   62,  0,   0,   0,   62,  41,  0,   0,   10,  242,
    0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,
    16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   30,  0,   0,
    7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   22,  0,   0,   0,   70,  14,
    16,  0,   11,  0,   0,   0,   55,  0,   0,   12,  242, 0,   16,  0,   19,  0,   0,   0,   70,
    14,  16,  0,   21,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,
    1,   21,  0,   0,   1,   2,   0,   0,   1,   6,   0,   0,   3,   1,   64,  0,   0,   4,   0,
    0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   2,   0,   0,   0,   54,  0,   0,   8,   242,
    0,   16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,
    0,   0,   128, 63,  0,   0,   128, 63,  54,  0,   0,   8,   242, 0,   16,  0,   19,  0,   0,
    0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,
    128, 63,  18,  0,   0,   1,   139, 0,   0,   15,  242, 0,   16,  0,   11,  0,   0,   0,   2,
    64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,
    2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   70,  14,  16,  0,   20,  0,   0,   0,   43,  0,   0,   5,   242, 0,   16,  0,   11,  0,
    0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   11,
    0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   1,   128, 58,
    0,   1,   128, 58,  0,   1,   128, 58,  0,   1,   128, 58,  52,  0,   0,   10,  242, 0,   16,
    0,   20,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   0,   0,
    128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 139, 0,   0,   15,  242,
    0,   16,  0,   11,  0,   0,   0,   2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,
    16,  0,   0,   0,   16,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   43,  0,
    0,   5,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   56,
    0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,
    2,   64,  0,   0,   0,   1,   128, 58,  0,   1,   128, 58,  0,   1,   128, 58,  0,   1,   128,
    58,  52,  0,   0,   10,  242, 0,   16,  0,   19,  0,   0,   0,   70,  14,  16,  0,   11,  0,
    0,   0,   2,   64,  0,   0,   0,   0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 0,
    0,   128, 191, 21,  0,   0,   1,   2,   0,   0,   1,   6,   0,   0,   3,   1,   64,  0,   0,
    6,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   2,   0,   0,   0,   54,  0,   0,
    8,   242, 0,   16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,
    128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  54,  0,   0,   8,   242, 0,   16,  0,   19,
    0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,
    0,   0,   128, 63,  18,  0,   0,   1,   131, 0,   0,   5,   242, 0,   16,  0,   20,  0,   0,
    0,   70,  14,  16,  0,   20,  0,   0,   0,   131, 0,   0,   5,   242, 0,   16,  0,   19,  0,
    0,   0,   70,  14,  16,  0,   19,  0,   0,   0,   21,  0,   0,   1,   2,   0,   0,   1,   10,
    0,   0,   1,   31,  0,   4,   3,   58,  0,   16,  0,   2,   0,   0,   0,   54,  0,   0,   8,
    242, 0,   16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128,
    63,  0,   0,   128, 63,  0,   0,   128, 63,  54,  0,   0,   8,   242, 0,   16,  0,   19,  0,
    0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,
    0,   128, 63,  21,  0,   0,   1,   2,   0,   0,   1,   23,  0,   0,   1,   21,  0,   0,   1,
    31,  0,   4,   3,   58,  0,   16,  0,   3,   0,   0,   0,   54,  32,  0,   5,   242, 0,   16,
    0,   20,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   29,  0,   0,   10,  242, 0,
    16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   2,   64,  0,   0,   193,
    192, 192, 62,  193, 192, 192, 62,  193, 192, 192, 62,  193, 192, 192, 62,  31,  0,   4,   3,
    10,  0,   16,  0,   11,  0,   0,   0,   29,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,
    0,   10,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,
    4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   54,  0,   0,   5,   66,  0,   16,  0,   5,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   60,  54,  0,   0,   5,   18,  0,   16,  0,
    7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 196, 18,  0,   0,   1,   54,  0,   0,
    5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 59,  54,  0,
    0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 195, 21,
    0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,
    10,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,
    3,   26,  0,   16,  0,   7,   0,   0,   0,   54,  0,   0,   5,   66,  0,   16,  0,   5,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   0,   59,  54,  0,   0,   5,   18,  0,   16,  0,   7,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 194, 18,  0,   0,   1,   54,  0,   0,   5,
    66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 58,  54,  0,   0,
    5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   21,  0,
    0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   42,
    0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   20,  0,   0,   0,   50,  0,   0,   9,
    18,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   127, 72,  10,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   66,  0,
    16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   7,
    0,   0,   0,   67,  0,   0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,
    5,   0,   0,   0,   0,   0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,
    0,   5,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   18,  0,
    16,  0,   20,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   8,
    32,  128, 58,  31,  0,   4,   3,   26,  0,   16,  0,   11,  0,   0,   0,   29,  0,   0,   7,
    66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,
    0,   193, 192, 64,  63,  31,  0,   4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   54,  0,
    0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   60,  54,
    0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 196,
    18,  0,   0,   1,   54,  0,   0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   128, 59,  54,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,
    0,   0,   0,   0,   128, 195, 21,  0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   34,
    0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,   0,
    129, 128, 128, 62,  31,  0,   4,   3,   26,  0,   16,  0,   7,   0,   0,   0,   54,  0,   0,
    5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   59,  54,  0,
    0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 194, 18,
    0,   0,   1,   54,  0,   0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   128, 58,  54,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   34,  0,
    16,  0,   7,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   20,
    0,   0,   0,   50,  0,   0,   9,   18,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,
    7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  10,  0,   16,  0,   7,   0,   0,
    0,   56,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,
    0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   67,  0,   0,   5,   66,  0,   16,  0,   5,
    0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   0,   0,   0,   7,   66,  0,   16,  0,
    5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,
    0,   56,  0,   0,   7,   34,  0,   16,  0,   20,  0,   0,   0,   42,  0,   16,  0,   5,   0,
    0,   0,   1,   64,  0,   0,   8,   32,  128, 58,  31,  0,   4,   3,   42,  0,   16,  0,   11,
    0,   0,   0,   29,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,
    20,  0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,   42,  0,   16,
    0,   5,   0,   0,   0,   54,  0,   0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,
    0,   0,   0,   0,   0,   60,  54,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,
    64,  0,   0,   0,   0,   128, 196, 18,  0,   0,   1,   54,  0,   0,   5,   66,  0,   16,  0,
    5,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 59,  54,  0,   0,   5,   18,  0,   16,
    0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 195, 21,  0,   0,   1,   18,  0,
    0,   1,   29,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   42,  0,   16,  0,   20,
    0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,   26,  0,   16,  0,
    7,   0,   0,   0,   54,  0,   0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   0,   59,  54,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,
    0,   0,   0,   0,   128, 194, 18,  0,   0,   1,   54,  0,   0,   5,   66,  0,   16,  0,   5,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 58,  54,  0,   0,   5,   18,  0,   16,  0,
    7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,
    1,   56,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   42,  0,   16,  0,   5,   0,
    0,   0,   42,  0,   16,  0,   20,  0,   0,   0,   50,  0,   0,   9,   18,  0,   16,  0,   7,
    0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,
    10,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,
    0,   42,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   67,  0,
    0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   0,
    0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,
    10,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   66,  0,   16,  0,   20,  0,   0,
    0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   8,   32,  128, 58,  31,  0,
    4,   3,   58,  0,   16,  0,   11,  0,   0,   0,   29,  0,   0,   7,   66,  0,   16,  0,   5,
    0,   0,   0,   58,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,
    31,  0,   4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   54,  0,   0,   5,   66,  0,   16,
    0,   5,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   60,  54,  0,   0,   5,   18,  0,
    16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 196, 18,  0,   0,   1,   54,
    0,   0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 59,
    54,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128,
    195, 21,  0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   34,  0,   16,  0,   7,   0,
    0,   0,   58,  0,   16,  0,   20,  0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,
    0,   4,   3,   26,  0,   16,  0,   7,   0,   0,   0,   54,  0,   0,   5,   66,  0,   16,  0,
    5,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   59,  54,  0,   0,   5,   18,  0,   16,
    0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 194, 18,  0,   0,   1,   54,  0,
    0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 58,  54,
    0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,
    21,  0,   0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,
    0,   42,  0,   16,  0,   5,   0,   0,   0,   58,  0,   16,  0,   20,  0,   0,   0,   50,  0,
    0,   9,   18,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   1,
    64,  0,   0,   0,   0,   127, 72,  10,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,
    66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,
    0,   7,   0,   0,   0,   67,  0,   0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,
    16,  0,   5,   0,   0,   0,   0,   0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,
    0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,
    130, 0,   16,  0,   20,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,
    0,   8,   32,  128, 58,  54,  32,  0,   5,   242, 0,   16,  0,   19,  0,   0,   0,   70,  14,
    16,  0,   19,  0,   0,   0,   29,  0,   0,   10,  242, 0,   16,  0,   11,  0,   0,   0,   70,
    14,  16,  0,   19,  0,   0,   0,   2,   64,  0,   0,   193, 192, 192, 62,  193, 192, 192, 62,
    193, 192, 192, 62,  193, 192, 192, 62,  31,  0,   4,   3,   10,  0,   16,  0,   11,  0,   0,
    0,   29,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   19,  0,
    0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,   42,  0,   16,  0,   5,
    0,   0,   0,   54,  0,   0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   0,   60,  54,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   128, 196, 18,  0,   0,   1,   54,  0,   0,   5,   66,  0,   16,  0,   5,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   128, 59,  54,  0,   0,   5,   18,  0,   16,  0,   7,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 195, 21,  0,   0,   1,   18,  0,   0,   1,
    29,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   19,  0,   0,
    0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,   26,  0,   16,  0,   7,   0,
    0,   0,   54,  0,   0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   0,   59,  54,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   128, 194, 18,  0,   0,   1,   54,  0,   0,   5,   66,  0,   16,  0,   5,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   128, 58,  54,  0,   0,   5,   18,  0,   16,  0,   7,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,
    0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,
    10,  0,   16,  0,   19,  0,   0,   0,   50,  0,   0,   9,   18,  0,   16,  0,   7,   0,   0,
    0,   26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  10,  0,
    16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,
    0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   67,  0,   0,   5,
    66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   0,   0,   0,
    7,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   10,  0,
    16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   18,  0,   16,  0,   19,  0,   0,   0,   42,
    0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   8,   32,  128, 58,  31,  0,   4,   3,
    26,  0,   16,  0,   11,  0,   0,   0,   29,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,
    0,   26,  0,   16,  0,   19,  0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,
    4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   54,  0,   0,   5,   66,  0,   16,  0,   5,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   60,  54,  0,   0,   5,   18,  0,   16,  0,
    7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 196, 18,  0,   0,   1,   54,  0,   0,
    5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 59,  54,  0,
    0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 195, 21,
    0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,
    26,  0,   16,  0,   19,  0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,
    3,   26,  0,   16,  0,   7,   0,   0,   0,   54,  0,   0,   5,   66,  0,   16,  0,   5,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   0,   59,  54,  0,   0,   5,   18,  0,   16,  0,   7,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 194, 18,  0,   0,   1,   54,  0,   0,   5,
    66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 58,  54,  0,   0,
    5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   21,  0,
    0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   42,
    0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   19,  0,   0,   0,   50,  0,   0,   9,
    18,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   127, 72,  10,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   66,  0,
    16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   7,
    0,   0,   0,   67,  0,   0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,
    5,   0,   0,   0,   0,   0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,
    0,   5,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   34,  0,
    16,  0,   19,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   8,
    32,  128, 58,  31,  0,   4,   3,   42,  0,   16,  0,   11,  0,   0,   0,   29,  0,   0,   7,
    66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   19,  0,   0,   0,   1,   64,  0,
    0,   193, 192, 64,  63,  31,  0,   4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   54,  0,
    0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   60,  54,
    0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 196,
    18,  0,   0,   1,   54,  0,   0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   128, 59,  54,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,
    0,   0,   0,   0,   128, 195, 21,  0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   34,
    0,   16,  0,   7,   0,   0,   0,   42,  0,   16,  0,   19,  0,   0,   0,   1,   64,  0,   0,
    129, 128, 128, 62,  31,  0,   4,   3,   26,  0,   16,  0,   7,   0,   0,   0,   54,  0,   0,
    5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   59,  54,  0,
    0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 194, 18,
    0,   0,   1,   54,  0,   0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   128, 58,  54,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   34,  0,
    16,  0,   7,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   19,
    0,   0,   0,   50,  0,   0,   9,   18,  0,   16,  0,   7,   0,   0,   0,   26,  0,   16,  0,
    7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  10,  0,   16,  0,   7,   0,   0,
    0,   56,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,
    0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   67,  0,   0,   5,   66,  0,   16,  0,   5,
    0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   0,   0,   0,   7,   66,  0,   16,  0,
    5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,
    0,   56,  0,   0,   7,   66,  0,   16,  0,   19,  0,   0,   0,   42,  0,   16,  0,   5,   0,
    0,   0,   1,   64,  0,   0,   8,   32,  128, 58,  31,  0,   4,   3,   58,  0,   16,  0,   11,
    0,   0,   0,   29,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   58,  0,   16,  0,
    19,  0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,   42,  0,   16,
    0,   5,   0,   0,   0,   54,  0,   0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,
    0,   0,   0,   0,   0,   60,  54,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,
    64,  0,   0,   0,   0,   128, 196, 18,  0,   0,   1,   54,  0,   0,   5,   66,  0,   16,  0,
    5,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 59,  54,  0,   0,   5,   18,  0,   16,
    0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 195, 21,  0,   0,   1,   18,  0,
    0,   1,   29,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   58,  0,   16,  0,   19,
    0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,   26,  0,   16,  0,
    7,   0,   0,   0,   54,  0,   0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   0,   59,  54,  0,   0,   5,   18,  0,   16,  0,   7,   0,   0,   0,   1,   64,
    0,   0,   0,   0,   128, 194, 18,  0,   0,   1,   54,  0,   0,   5,   66,  0,   16,  0,   5,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 58,  54,  0,   0,   5,   18,  0,   16,  0,
    7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,
    1,   56,  0,   0,   7,   34,  0,   16,  0,   7,   0,   0,   0,   42,  0,   16,  0,   5,   0,
    0,   0,   58,  0,   16,  0,   19,  0,   0,   0,   50,  0,   0,   9,   18,  0,   16,  0,   7,
    0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,
    10,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,
    0,   42,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   67,  0,
    0,   5,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   0,
    0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,
    10,  0,   16,  0,   7,   0,   0,   0,   56,  0,   0,   7,   130, 0,   16,  0,   19,  0,   0,
    0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   8,   32,  128, 58,  21,  0,
    0,   1,   0,   0,   0,   7,   242, 0,   16,  0,   11,  0,   0,   0,   70,  14,  16,  0,   18,
    0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   0,   0,   0,   7,   242, 0,   16,  0,
    19,  0,   0,   0,   70,  14,  16,  0,   15,  0,   0,   0,   70,  14,  16,  0,   19,  0,   0,
    0,   31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,   0,   41,  0,   0,   10,  50,  0,
    16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   8,   0,   0,   0,   2,   64,  0,   0,   1,
    0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   10,
    50,  0,   16,  0,   7,   0,   0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,
    0,   252, 255, 255, 255, 252, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   140, 0,
    0,   17,  50,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   1,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  0,   16,  0,   8,   0,   0,
    0,   70,  0,   16,  0,   7,   0,   0,   0,   30,  0,   0,   10,  50,  0,   16,  0,   8,   0,
    0,   0,   70,  0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   2,   0,   0,   0,   2,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,
    66,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,
    0,   1,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   1,   0,
    0,   10,  50,  0,   16,  0,   7,   0,   0,   0,   6,   0,   16,  0,   8,   0,   0,   0,   2,
    64,  0,   0,   253, 255, 255, 255, 2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    30,  0,   0,   7,   18,  0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,
    0,   1,   64,  0,   0,   2,   0,   0,   0,   41,  0,   0,   7,   66,  0,   16,  0,   5,   0,
    0,   0,   26,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,
    0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,
    1,   64,  0,   0,   252, 255, 255, 255, 140, 0,   0,   11,  66,  0,   16,  0,   5,   0,   0,
    0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   26,  0,
    16,  0,   8,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   30,  0,   0,   7,   34,
    0,   16,  0,   8,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   42,  0,   16,  0,
    5,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   162, 0,   16,
    0,   6,   0,   0,   0,   6,   4,   16,  0,   8,   0,   0,   0,   6,   4,   16,  0,   2,   0,
    0,   0,   86,  13,  16,  0,   6,   0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   7,
    0,   0,   0,   0,   208, 0,   0,   214, 5,   16,  0,   6,   0,   0,   0,   134, 0,   16,  0,
    10,  0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,
    0,   7,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   7,   0,
    0,   0,   30,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   4,
    0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   35,  0,   0,   10,  162, 0,   16,  0,
    6,   0,   0,   0,   6,   4,   16,  128, 65,  0,   0,   0,   7,   0,   0,   0,   6,   8,   16,
    0,   10,  0,   0,   0,   86,  13,  16,  0,   6,   0,   0,   0,   35,  0,   0,   9,   34,  0,
    16,  0,   6,   0,   0,   0,   58,  0,   16,  0,   6,   0,   0,   0,   10,  0,   16,  0,   10,
    0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   41,  0,   0,   7,   34,  0,   16,  0,
    6,   0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,
    0,   35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,
    0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   78,
    0,   0,   8,   0,   208, 0,   0,   18,  0,   16,  0,   20,  0,   0,   0,   42,  0,   16,  0,
    5,   0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,
    0,   8,   0,   0,   0,   41,  0,   0,   10,  162, 0,   16,  0,   6,   0,   0,   0,   86,  13,
    16,  0,   10,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,
    0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   10,  162, 0,   16,  0,   6,   0,   0,   0,
    86,  13,  16,  0,   6,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   252, 255, 255,
    255, 0,   0,   0,   0,   252, 255, 255, 255, 140, 0,   0,   17,  162, 0,   16,  0,   6,   0,
    0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   1,
    0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   86,  13,  16,  0,   10,  0,   0,   0,   86,  13,  16,  0,   6,   0,   0,
    0,   30,  0,   0,   10,  162, 0,   16,  0,   10,  0,   0,   0,   86,  13,  16,  0,   6,   0,
    0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   2,
    0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,
    10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,   4,
    3,   42,  0,   16,  0,   5,   0,   0,   0,   1,   0,   0,   10,  162, 0,   16,  0,   6,   0,
    0,   0,   86,  5,   16,  0,   10,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   253,
    255, 255, 255, 0,   0,   0,   0,   2,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,
    10,  0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   1,   64,  0,   0,   2,   0,   0,
    0,   41,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   58,  0,   16,  0,   10,  0,
    0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   66,  0,   16,  0,   5,
    0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255,
    140, 0,   0,   11,  66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   0,   0,   58,  0,   16,  0,   10,  0,   0,   0,   42,  0,
    16,  0,   5,   0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   10,  0,   0,   0,   58,
    0,   16,  0,   6,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   21,  0,   0,   1,
    21,  0,   0,   1,   35,  0,   0,   9,   162, 0,   16,  0,   6,   0,   0,   0,   86,  13,  16,
    0,   10,  0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   86,  13,  16,  0,   9,   0,
    0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   0,   208, 0,   0,   214,
    5,   16,  0,   6,   0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   35,  0,   0,   9,
    66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,
    0,   0,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   30,  0,   0,   7,   66,  0,
    16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   42,  0,   16,  0,   5,
    0,   0,   0,   35,  0,   0,   10,  162, 0,   16,  0,   6,   0,   0,   0,   6,   4,   16,  128,
    65,  0,   0,   0,   7,   0,   0,   0,   6,   8,   16,  0,   10,  0,   0,   0,   86,  13,  16,
    0,   6,   0,   0,   0,   35,  0,   0,   9,   34,  0,   16,  0,   6,   0,   0,   0,   58,  0,
    16,  0,   6,   0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   26,  0,   16,  0,   6,
    0,   0,   0,   41,  0,   0,   7,   34,  0,   16,  0,   6,   0,   0,   0,   26,  0,   16,  0,
    6,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,   9,   66,  0,   16,
    0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   9,   0,
    0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   78,  0,   0,   8,   0,   208, 0,   0,   34,
    0,   16,  0,   20,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,
    9,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,   0,   41,  0,   0,
    10,  162, 0,   16,  0,   6,   0,   0,   0,   166, 14,  16,  0,   12,  0,   0,   0,   2,   64,
    0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,
    0,   0,   10,  162, 0,   16,  0,   6,   0,   0,   0,   86,  13,  16,  0,   6,   0,   0,   0,
    2,   64,  0,   0,   0,   0,   0,   0,   252, 255, 255, 255, 0,   0,   0,   0,   252, 255, 255,
    255, 140, 0,   0,   17,  162, 0,   16,  0,   6,   0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   166, 14,  16,  0,
    12,  0,   0,   0,   86,  13,  16,  0,   6,   0,   0,   0,   30,  0,   0,   10,  194, 0,   16,
    0,   12,  0,   0,   0,   86,  13,  16,  0,   6,   0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   18,  0,   0,   1,   32,
    0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,
    1,   64,  0,   0,   1,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   5,   0,   0,
    0,   1,   0,   0,   10,  162, 0,   16,  0,   6,   0,   0,   0,   166, 10,  16,  0,   12,  0,
    0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   253, 255, 255, 255, 0,   0,   0,   0,   2,
    0,   0,   0,   30,  0,   0,   7,   66,  0,   16,  0,   12,  0,   0,   0,   26,  0,   16,  0,
    6,   0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,   41,  0,   0,   7,   66,  0,   16,
    0,   5,   0,   0,   0,   58,  0,   16,  0,   12,  0,   0,   0,   1,   64,  0,   0,   1,   0,
    0,   0,   1,   0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,
    0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255, 140, 0,   0,   11,  66,  0,   16,  0,
    5,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,
    0,   58,  0,   16,  0,   12,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   30,  0,
    0,   7,   130, 0,   16,  0,   12,  0,   0,   0,   58,  0,   16,  0,   6,   0,   0,   0,   42,
    0,   16,  0,   5,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,
    162, 0,   16,  0,   6,   0,   0,   0,   166, 14,  16,  0,   12,  0,   0,   0,   6,   4,   16,
    0,   2,   0,   0,   0,   6,   4,   16,  0,   12,  0,   0,   0,   78,  0,   0,   8,   50,  0,
    16,  0,   7,   0,   0,   0,   0,   208, 0,   0,   214, 5,   16,  0,   6,   0,   0,   0,   134,
    0,   16,  0,   10,  0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,
    26,  0,   16,  0,   7,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,
    0,   7,   0,   0,   0,   30,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,
    16,  0,   4,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   35,  0,   0,   10,  162,
    0,   16,  0,   6,   0,   0,   0,   6,   4,   16,  128, 65,  0,   0,   0,   7,   0,   0,   0,
    6,   8,   16,  0,   10,  0,   0,   0,   86,  13,  16,  0,   6,   0,   0,   0,   35,  0,   0,
    9,   34,  0,   16,  0,   6,   0,   0,   0,   58,  0,   16,  0,   6,   0,   0,   0,   10,  0,
    16,  0,   10,  0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   41,  0,   0,   7,   34,
    0,   16,  0,   6,   0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   58,  0,   16,  0,
    4,   0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,
    0,   5,   0,   0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   26,  0,   16,  0,   6,   0,
    0,   0,   78,  0,   0,   8,   0,   208, 0,   0,   66,  0,   16,  0,   20,  0,   0,   0,   42,
    0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   31,  0,   4,   3,
    42,  0,   16,  0,   8,   0,   0,   0,   41,  0,   0,   10,  162, 0,   16,  0,   6,   0,   0,
    0,   6,   4,   16,  0,   13,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   1,   0,
    0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   10,  162, 0,   16,  0,   6,
    0,   0,   0,   86,  13,  16,  0,   6,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,
    252, 255, 255, 255, 0,   0,   0,   0,   252, 255, 255, 255, 140, 0,   0,   17,  162, 0,   16,
    0,   6,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   1,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   6,   4,   16,  0,   13,  0,   0,   0,   86,  13,  16,  0,
    6,   0,   0,   0,   30,  0,   0,   10,  50,  0,   16,  0,   13,  0,   0,   0,   214, 5,   16,
    0,   6,   0,   0,   0,   2,   64,  0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   66,  0,   16,  0,   5,
    0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,
    31,  0,   4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   1,   0,   0,   10,  162, 0,   16,
    0,   6,   0,   0,   0,   6,   0,   16,  0,   13,  0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   0,   253, 255, 255, 255, 0,   0,   0,   0,   2,   0,   0,   0,   30,  0,   0,   7,   18,
    0,   16,  0,   13,  0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   1,   64,  0,   0,
    2,   0,   0,   0,   41,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,
    0,   13,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   66,  0,
    16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   252,
    255, 255, 255, 140, 0,   0,   11,  66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,
    1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   26,  0,   16,  0,   13,  0,   0,
    0,   42,  0,   16,  0,   5,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   13,  0,
    0,   0,   58,  0,   16,  0,   6,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   21,
    0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   162, 0,   16,  0,   6,   0,   0,   0,
    6,   4,   16,  0,   13,  0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   166, 14,  16,
    0,   7,   0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   7,   0,   0,   0,   0,   208,
    0,   0,   214, 5,   16,  0,   6,   0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   35,
    0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,
    10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   30,  0,   0,
    7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   42,  0,
    16,  0,   5,   0,   0,   0,   35,  0,   0,   10,  162, 0,   16,  0,   6,   0,   0,   0,   6,
    4,   16,  128, 65,  0,   0,   0,   7,   0,   0,   0,   6,   8,   16,  0,   10,  0,   0,   0,
    86,  13,  16,  0,   6,   0,   0,   0,   35,  0,   0,   9,   34,  0,   16,  0,   6,   0,   0,
    0,   58,  0,   16,  0,   6,   0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   26,  0,
    16,  0,   6,   0,   0,   0,   41,  0,   0,   7,   34,  0,   16,  0,   6,   0,   0,   0,   26,
    0,   16,  0,   6,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,   9,
    66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,
    0,   9,   0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   78,  0,   0,   8,   0,   208,
    0,   0,   130, 0,   16,  0,   20,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   10,
    0,   16,  0,   9,   0,   0,   0,   30,  0,   0,   7,   242, 0,   16,  0,   7,   0,   0,   0,
    246, 15,  16,  0,   0,   0,   0,   0,   70,  14,  16,  0,   20,  0,   0,   0,   31,  0,   4,
    3,   42,  0,   16,  0,   8,   0,   0,   0,   41,  0,   0,   10,  162, 0,   16,  0,   6,   0,
    0,   0,   6,   4,   16,  0,   14,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   1,
    0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   10,  162, 0,   16,  0,
    6,   0,   0,   0,   86,  13,  16,  0,   6,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,
    0,   252, 255, 255, 255, 0,   0,   0,   0,   252, 255, 255, 255, 140, 0,   0,   17,  162, 0,
    16,  0,   6,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,
    0,   0,   0,   1,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   6,   4,   16,  0,   14,  0,   0,   0,   86,  13,  16,
    0,   6,   0,   0,   0,   30,  0,   0,   10,  50,  0,   16,  0,   14,  0,   0,   0,   214, 5,
    16,  0,   6,   0,   0,   0,   2,   64,  0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   66,  0,   16,  0,
    5,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,
    0,   31,  0,   4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   1,   0,   0,   10,  162, 0,
    16,  0,   6,   0,   0,   0,   6,   0,   16,  0,   14,  0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   253, 255, 255, 255, 0,   0,   0,   0,   2,   0,   0,   0,   30,  0,   0,   7,
    18,  0,   16,  0,   14,  0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   1,   64,  0,
    0,   2,   0,   0,   0,   41,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,
    16,  0,   14,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   66,
    0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,
    252, 255, 255, 255, 140, 0,   0,   11,  66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,
    0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   26,  0,   16,  0,   14,  0,
    0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   14,
    0,   0,   0,   58,  0,   16,  0,   6,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,
    21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   162, 0,   16,  0,   6,   0,   0,
    0,   6,   4,   16,  0,   14,  0,   0,   0,   6,   4,   16,  0,   2,   0,   0,   0,   166, 14,
    16,  0,   13,  0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   8,   0,   0,   0,   0,
    208, 0,   0,   214, 5,   16,  0,   6,   0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,
    35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   8,   0,   0,
    0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   8,   0,   0,   0,   30,  0,
    0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   42,
    0,   16,  0,   5,   0,   0,   0,   35,  0,   0,   10,  162, 0,   16,  0,   6,   0,   0,   0,
    6,   4,   16,  128, 65,  0,   0,   0,   8,   0,   0,   0,   6,   8,   16,  0,   10,  0,   0,
    0,   86,  13,  16,  0,   6,   0,   0,   0,   35,  0,   0,   9,   34,  0,   16,  0,   6,   0,
    0,   0,   58,  0,   16,  0,   6,   0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   26,
    0,   16,  0,   6,   0,   0,   0,   41,  0,   0,   7,   34,  0,   16,  0,   6,   0,   0,   0,
    26,  0,   16,  0,   6,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,
    9,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   42,  0,
    16,  0,   9,   0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   78,  0,   0,   8,   0,
    208, 0,   0,   18,  0,   16,  0,   12,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,
    10,  0,   16,  0,   9,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,
    0,   41,  0,   0,   10,  162, 0,   16,  0,   6,   0,   0,   0,   6,   4,   16,  0,   16,  0,
    0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   1,
    0,   0,   0,   1,   0,   0,   10,  162, 0,   16,  0,   6,   0,   0,   0,   86,  13,  16,  0,
    6,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   252, 255, 255, 255, 0,   0,   0,
    0,   252, 255, 255, 255, 140, 0,   0,   17,  162, 0,   16,  0,   6,   0,   0,   0,   2,   64,
    0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   2,
    64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    6,   4,   16,  0,   16,  0,   0,   0,   86,  13,  16,  0,   6,   0,   0,   0,   30,  0,   0,
    10,  50,  0,   16,  0,   16,  0,   0,   0,   214, 5,   16,  0,   6,   0,   0,   0,   2,   64,
    0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   18,
    0,   0,   1,   32,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,
    4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,
    0,   5,   0,   0,   0,   1,   0,   0,   10,  162, 0,   16,  0,   6,   0,   0,   0,   6,   0,
    16,  0,   16,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   253, 255, 255, 255, 0,
    0,   0,   0,   2,   0,   0,   0,   30,  0,   0,   7,   18,  0,   16,  0,   16,  0,   0,   0,
    26,  0,   16,  0,   6,   0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,   41,  0,   0,
    7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   16,  0,   0,   0,   1,   64,
    0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,
    0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255, 140, 0,   0,   11,
    66,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   0,   0,   26,  0,   16,  0,   16,  0,   0,   0,   42,  0,   16,  0,   5,   0,
    0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   16,  0,   0,   0,   58,  0,   16,  0,   6,
    0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,
    35,  0,   0,   9,   162, 0,   16,  0,   6,   0,   0,   0,   6,   4,   16,  0,   16,  0,   0,
    0,   6,   4,   16,  0,   2,   0,   0,   0,   166, 14,  16,  0,   14,  0,   0,   0,   78,  0,
    0,   8,   50,  0,   16,  0,   8,   0,   0,   0,   0,   208, 0,   0,   214, 5,   16,  0,   6,
    0,   0,   0,   134, 0,   16,  0,   10,  0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,
    5,   0,   0,   0,   26,  0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,
    0,   10,  0,   16,  0,   8,   0,   0,   0,   30,  0,   0,   7,   66,  0,   16,  0,   5,   0,
    0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   35,
    0,   0,   10,  162, 0,   16,  0,   6,   0,   0,   0,   6,   4,   16,  128, 65,  0,   0,   0,
    8,   0,   0,   0,   6,   8,   16,  0,   10,  0,   0,   0,   86,  13,  16,  0,   6,   0,   0,
    0,   35,  0,   0,   9,   34,  0,   16,  0,   6,   0,   0,   0,   58,  0,   16,  0,   6,   0,
    0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   41,
    0,   0,   7,   34,  0,   16,  0,   6,   0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,
    58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,
    0,   42,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   26,  0,
    16,  0,   6,   0,   0,   0,   78,  0,   0,   8,   0,   208, 0,   0,   34,  0,   16,  0,   12,
    0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,
    31,  0,   4,   3,   42,  0,   16,  0,   8,   0,   0,   0,   41,  0,   0,   10,  162, 0,   16,
    0,   6,   0,   0,   0,   6,   4,   16,  0,   17,  0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   10,  162,
    0,   16,  0,   6,   0,   0,   0,   86,  13,  16,  0,   6,   0,   0,   0,   2,   64,  0,   0,
    0,   0,   0,   0,   252, 255, 255, 255, 0,   0,   0,   0,   252, 255, 255, 255, 140, 0,   0,
    17,  162, 0,   16,  0,   6,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   1,   0,
    0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   4,   16,  0,   17,  0,   0,   0,
    86,  13,  16,  0,   6,   0,   0,   0,   30,  0,   0,   10,  50,  0,   16,  0,   17,  0,   0,
    0,   214, 5,   16,  0,   6,   0,   0,   0,   2,   64,  0,   0,   2,   0,   0,   0,   2,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   66,
    0,   16,  0,   5,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,
    1,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   5,   0,   0,   0,   1,   0,   0,
    10,  162, 0,   16,  0,   6,   0,   0,   0,   6,   0,   16,  0,   17,  0,   0,   0,   2,   64,
    0,   0,   0,   0,   0,   0,   253, 255, 255, 255, 0,   0,   0,   0,   2,   0,   0,   0,   30,
    0,   0,   7,   18,  0,   16,  0,   17,  0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,
    1,   64,  0,   0,   2,   0,   0,   0,   41,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,
    0,   26,  0,   16,  0,   17,  0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,
    0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   1,
    64,  0,   0,   252, 255, 255, 255, 140, 0,   0,   11,  66,  0,   16,  0,   5,   0,   0,   0,
    1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   26,  0,   16,
    0,   17,  0,   0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   30,  0,   0,   7,   34,  0,
    16,  0,   17,  0,   0,   0,   58,  0,   16,  0,   6,   0,   0,   0,   42,  0,   16,  0,   5,
    0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   35,  0,   0,   9,   162, 0,   16,  0,
    6,   0,   0,   0,   6,   4,   16,  0,   17,  0,   0,   0,   6,   4,   16,  0,   2,   0,   0,
    0,   166, 14,  16,  0,   16,  0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   8,   0,
    0,   0,   0,   208, 0,   0,   214, 5,   16,  0,   6,   0,   0,   0,   134, 0,   16,  0,   10,
    0,   0,   0,   35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,
    8,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   8,   0,   0,
    0,   30,  0,   0,   7,   66,  0,   16,  0,   5,   0,   0,   0,   26,  0,   16,  0,   4,   0,
    0,   0,   42,  0,   16,  0,   5,   0,   0,   0,   35,  0,   0,   10,  162, 0,   16,  0,   6,
    0,   0,   0,   6,   4,   16,  128, 65,  0,   0,   0,   8,   0,   0,   0,   6,   8,   16,  0,
    10,  0,   0,   0,   86,  13,  16,  0,   6,   0,   0,   0,   35,  0,   0,   9,   34,  0,   16,
    0,   6,   0,   0,   0,   58,  0,   16,  0,   6,   0,   0,   0,   10,  0,   16,  0,   10,  0,
    0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   41,  0,   0,   7,   34,  0,   16,  0,   6,
    0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,
    35,  0,   0,   9,   66,  0,   16,  0,   5,   0,   0,   0,   42,  0,   16,  0,   5,   0,   0,
    0,   42,  0,   16,  0,   9,   0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   78,  0,
    0,   8,   0,   208, 0,   0,   66,  0,   16,  0,   12,  0,   0,   0,   42,  0,   16,  0,   5,
    0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,
    8,   0,   0,   0,   41,  0,   0,   10,  162, 0,   16,  0,   6,   0,   0,   0,   166, 14,  16,
    0,   17,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   1,   0,   0,   0,   1,   0,   0,   10,  162, 0,   16,  0,   6,   0,   0,   0,   86,
    13,  16,  0,   6,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   252, 255, 255, 255,
    0,   0,   0,   0,   252, 255, 255, 255, 140, 0,   0,   17,  162, 0,   16,  0,   6,   0,   0,
    0,   2,   64,  0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   1,   0,
    0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   166, 14,  16,  0,   17,  0,   0,   0,   86,  13,  16,  0,   6,   0,   0,   0,
    30,  0,   0,   10,  194, 0,   16,  0,   17,  0,   0,   0,   86,  13,  16,  0,   6,   0,   0,
    0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   2,   0,
    0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   18,  0,   16,  0,   4,   0,   0,   0,   10,
    0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   31,  0,   4,   3,
    10,  0,   16,  0,   4,   0,   0,   0,   1,   0,   0,   10,  162, 0,   16,  0,   6,   0,   0,
    0,   166, 10,  16,  0,   17,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   253, 255,
    255, 255, 0,   0,   0,   0,   2,   0,   0,   0,   30,  0,   0,   7,   66,  0,   16,  0,   17,
    0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,
    41,  0,   0,   7,   18,  0,   16,  0,   4,   0,   0,   0,   58,  0,   16,  0,   17,  0,   0,
    0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   18,  0,   16,  0,   4,   0,
    0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   252, 255, 255, 255, 140,
    0,   0,   11,  18,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,
    1,   64,  0,   0,   0,   0,   0,   0,   58,  0,   16,  0,   17,  0,   0,   0,   10,  0,   16,
    0,   4,   0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   17,  0,   0,   0,   58,  0,
    16,  0,   6,   0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   21,  0,   0,   1,   21,
    0,   0,   1,   35,  0,   0,   9,   98,  0,   16,  0,   1,   0,   0,   0,   166, 11,  16,  0,
    17,  0,   0,   0,   6,   1,   16,  0,   2,   0,   0,   0,   86,  6,   16,  0,   1,   0,   0,
    0,   78,  0,   0,   8,   162, 0,   16,  0,   6,   0,   0,   0,   0,   208, 0,   0,   86,  9,
    16,  0,   1,   0,   0,   0,   6,   8,   16,  0,   10,  0,   0,   0,   35,  0,   0,   9,   18,
    0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   6,   0,   0,   0,   10,  0,   16,  0,
    0,   0,   0,   0,   26,  0,   16,  0,   6,   0,   0,   0,   30,  0,   0,   7,   18,  0,   16,
    0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   4,   0,
    0,   0,   35,  0,   0,   10,  98,  0,   16,  0,   1,   0,   0,   0,   86,  7,   16,  128, 65,
    0,   0,   0,   6,   0,   0,   0,   6,   2,   16,  0,   10,  0,   0,   0,   86,  6,   16,  0,
    1,   0,   0,   0,   35,  0,   0,   9,   34,  0,   16,  0,   1,   0,   0,   0,   42,  0,   16,
    0,   1,   0,   0,   0,   10,  0,   16,  0,   10,  0,   0,   0,   26,  0,   16,  0,   1,   0,
    0,   0,   41,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   1,
    0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   35,  0,   0,   9,   18,  0,   16,  0,
    0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   9,   0,   0,
    0,   26,  0,   16,  0,   1,   0,   0,   0,   78,  0,   0,   8,   0,   208, 0,   0,   130, 0,
    16,  0,   12,  0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   9,
    0,   0,   0,   30,  0,   0,   7,   242, 0,   16,  0,   8,   0,   0,   0,   246, 15,  16,  0,
    0,   0,   0,   0,   70,  14,  16,  0,   12,  0,   0,   0,   41,  0,   0,   10,  242, 0,   16,
    0,   7,   0,   0,   0,   70,  14,  16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   2,   0,
    0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   165, 0,   0,   8,   18,
    0,   16,  0,   9,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   6,   112, 32,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   165, 0,   0,   8,   34,  0,   16,  0,   9,   0,   0,
    0,   26,  0,   16,  0,   7,   0,   0,   0,   6,   112, 32,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   165, 0,   0,   8,   66,  0,   16,  0,   9,   0,   0,   0,   42,  0,   16,  0,   7,
    0,   0,   0,   6,   112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   165, 0,   0,   8,
    130, 0,   16,  0,   9,   0,   0,   0,   58,  0,   16,  0,   7,   0,   0,   0,   6,   112, 32,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   41,  0,   0,   10,  242, 0,   16,  0,   7,   0,
    0,   0,   70,  14,  16,  0,   8,   0,   0,   0,   2,   64,  0,   0,   2,   0,   0,   0,   2,
    0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   165, 0,   0,   8,   18,  0,   16,  0,
    8,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   6,   112, 32,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   165, 0,   0,   8,   34,  0,   16,  0,   8,   0,   0,   0,   26,  0,
    16,  0,   7,   0,   0,   0,   6,   112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   165,
    0,   0,   8,   66,  0,   16,  0,   8,   0,   0,   0,   42,  0,   16,  0,   7,   0,   0,   0,
    6,   112, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   165, 0,   0,   8,   130, 0,   16,
    0,   8,   0,   0,   0,   58,  0,   16,  0,   7,   0,   0,   0,   6,   112, 32,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   4,   0,   0,   0,   76,
    0,   0,   3,   42,  0,   16,  0,   4,   0,   0,   0,   6,   0,   0,   3,   1,   64,  0,   0,
    5,   0,   0,   0,   1,   0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,
    0,   2,   0,   0,   0,   1,   64,  0,   0,   16,  0,   0,   0,   85,  0,   0,   7,   242, 0,
    16,  0,   7,   0,   0,   0,   70,  14,  16,  0,   9,   0,   0,   0,   6,   0,   16,  0,   0,
    0,   0,   0,   139, 0,   0,   15,  242, 0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,
    16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  14,
    16,  0,   7,   0,   0,   0,   43,  0,   0,   5,   242, 0,   16,  0,   7,   0,   0,   0,   70,
    14,  16,  0,   7,   0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   7,   0,   0,   0,
    70,  14,  16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   1,   128, 58,  0,   1,   128,
    58,  0,   1,   128, 58,  0,   1,   128, 58,  52,  0,   0,   10,  242, 0,   16,  0,   9,   0,
    0,   0,   70,  14,  16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 191, 0,
    0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 85,  0,   0,   7,   242, 0,   16,  0,
    7,   0,   0,   0,   70,  14,  16,  0,   8,   0,   0,   0,   6,   0,   16,  0,   0,   0,   0,
    0,   139, 0,   0,   15,  242, 0,   16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   16,  0,
    0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  14,  16,  0,
    7,   0,   0,   0,   43,  0,   0,   5,   242, 0,   16,  0,   7,   0,   0,   0,   70,  14,  16,
    0,   7,   0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   7,   0,   0,   0,   70,  14,
    16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   1,   128, 58,  0,   1,   128, 58,  0,
    1,   128, 58,  0,   1,   128, 58,  52,  0,   0,   10,  242, 0,   16,  0,   8,   0,   0,   0,
    70,  14,  16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 191, 0,   0,   128,
    191, 0,   0,   128, 191, 0,   0,   128, 191, 2,   0,   0,   1,   6,   0,   0,   3,   1,   64,
    0,   0,   7,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   2,   0,   0,   0,   85,
    0,   0,   10,  242, 0,   16,  0,   7,   0,   0,   0,   70,  14,  16,  0,   9,   0,   0,   0,
    2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,
    0,   131, 0,   0,   5,   242, 0,   16,  0,   9,   0,   0,   0,   70,  14,  16,  0,   7,   0,
    0,   0,   85,  0,   0,   10,  242, 0,   16,  0,   7,   0,   0,   0,   70,  14,  16,  0,   8,
    0,   0,   0,   2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,
    16,  0,   0,   0,   131, 0,   0,   5,   242, 0,   16,  0,   8,   0,   0,   0,   70,  14,  16,
    0,   7,   0,   0,   0,   18,  0,   0,   1,   131, 0,   0,   5,   242, 0,   16,  0,   9,   0,
    0,   0,   70,  14,  16,  0,   9,   0,   0,   0,   131, 0,   0,   5,   242, 0,   16,  0,   8,
    0,   0,   0,   70,  14,  16,  0,   8,   0,   0,   0,   21,  0,   0,   1,   2,   0,   0,   1,
    10,  0,   0,   1,   31,  0,   4,   3,   58,  0,   16,  0,   2,   0,   0,   0,   54,  0,   0,
    8,   242, 0,   16,  0,   9,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,
    128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  54,  0,   0,   8,   242, 0,   16,  0,   8,
    0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,
    0,   0,   128, 63,  21,  0,   0,   1,   2,   0,   0,   1,   23,  0,   0,   1,   18,  0,   0,
    1,   76,  0,   0,   3,   42,  0,   16,  0,   4,   0,   0,   0,   6,   0,   0,   3,   1,   64,
    0,   0,   0,   0,   0,   0,   6,   0,   0,   3,   1,   64,  0,   0,   1,   0,   0,   0,   1,
    0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   5,   0,   0,   0,
    1,   64,  0,   0,   16,  0,   0,   0,   55,  0,   0,   9,   18,  0,   16,  0,   0,   0,   0,
    0,   58,  0,   16,  0,   2,   0,   0,   0,   1,   64,  0,   0,   24,  0,   0,   0,   10,  0,
    16,  0,   0,   0,   0,   0,   85,  0,   0,   7,   242, 0,   16,  0,   7,   0,   0,   0,   70,
    14,  16,  0,   9,   0,   0,   0,   6,   0,   16,  0,   0,   0,   0,   0,   1,   0,   0,   10,
    242, 0,   16,  0,   7,   0,   0,   0,   70,  14,  16,  0,   7,   0,   0,   0,   2,   64,  0,
    0,   255, 0,   0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   86,  0,
    0,   5,   242, 0,   16,  0,   7,   0,   0,   0,   70,  14,  16,  0,   7,   0,   0,   0,   56,
    0,   0,   10,  242, 0,   16,  0,   9,   0,   0,   0,   70,  14,  16,  0,   7,   0,   0,   0,
    2,   64,  0,   0,   129, 128, 128, 59,  129, 128, 128, 59,  129, 128, 128, 59,  129, 128, 128,
    59,  85,  0,   0,   7,   242, 0,   16,  0,   7,   0,   0,   0,   70,  14,  16,  0,   8,   0,
    0,   0,   6,   0,   16,  0,   0,   0,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   7,
    0,   0,   0,   70,  14,  16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   255, 0,   0,   0,
    255, 0,   0,   0,   255, 0,   0,   0,   255, 0,   0,   0,   86,  0,   0,   5,   242, 0,   16,
    0,   7,   0,   0,   0,   70,  14,  16,  0,   7,   0,   0,   0,   56,  0,   0,   10,  242, 0,
    16,  0,   8,   0,   0,   0,   70,  14,  16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   129,
    128, 128, 59,  129, 128, 128, 59,  129, 128, 128, 59,  129, 128, 128, 59,  2,   0,   0,   1,
    6,   0,   0,   3,   1,   64,  0,   0,   2,   0,   0,   0,   6,   0,   0,   3,   1,   64,  0,
    0,   10,  0,   0,   0,   6,   0,   0,   3,   1,   64,  0,   0,   3,   0,   0,   0,   6,   0,
    0,   3,   1,   64,  0,   0,   12,  0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   2,
    0,   0,   0,   85,  0,   0,   10,  242, 0,   16,  0,   7,   0,   0,   0,   70,  14,  16,  0,
    9,   0,   0,   0,   2,   64,  0,   0,   30,  0,   0,   0,   30,  0,   0,   0,   30,  0,   0,
    0,   30,  0,   0,   0,   86,  0,   0,   5,   242, 0,   16,  0,   7,   0,   0,   0,   70,  14,
    16,  0,   7,   0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   9,   0,   0,   0,   70,
    14,  16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   171, 170, 170, 62,  171, 170, 170, 62,
    171, 170, 170, 62,  171, 170, 170, 62,  85,  0,   0,   10,  242, 0,   16,  0,   7,   0,   0,
    0,   70,  14,  16,  0,   8,   0,   0,   0,   2,   64,  0,   0,   30,  0,   0,   0,   30,  0,
    0,   0,   30,  0,   0,   0,   30,  0,   0,   0,   86,  0,   0,   5,   242, 0,   16,  0,   7,
    0,   0,   0,   70,  14,  16,  0,   7,   0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,
    8,   0,   0,   0,   70,  14,  16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   171, 170, 170,
    62,  171, 170, 170, 62,  171, 170, 170, 62,  171, 170, 170, 62,  18,  0,   0,   1,   1,   0,
    0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   5,   0,   0,   0,   1,
    64,  0,   0,   20,  0,   0,   0,   32,  0,   0,   10,  98,  0,   16,  0,   1,   0,   0,   0,
    166, 10,  16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   2,   0,   0,
    0,   10,  0,   0,   0,   0,   0,   0,   0,   60,  0,   0,   7,   130, 0,   16,  0,   0,   0,
    0,   0,   42,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   31,
    0,   4,   3,   58,  0,   16,  0,   0,   0,   0,   0,   85,  0,   0,   7,   242, 0,   16,  0,
    4,   0,   0,   0,   70,  14,  16,  0,   9,   0,   0,   0,   6,   0,   16,  0,   0,   0,   0,
    0,   1,   0,   0,   10,  242, 0,   16,  0,   4,   0,   0,   0,   70,  14,  16,  0,   4,   0,
    0,   0,   2,   64,  0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255,
    3,   0,   0,   86,  0,   0,   5,   242, 0,   16,  0,   4,   0,   0,   0,   70,  14,  16,  0,
    4,   0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   9,   0,   0,   0,   70,  14,  16,
    0,   4,   0,   0,   0,   2,   64,  0,   0,   8,   32,  128, 58,  8,   32,  128, 58,  8,   32,
    128, 58,  8,   32,  128, 58,  85,  0,   0,   7,   242, 0,   16,  0,   4,   0,   0,   0,   70,
    14,  16,  0,   8,   0,   0,   0,   6,   0,   16,  0,   0,   0,   0,   0,   1,   0,   0,   10,
    242, 0,   16,  0,   4,   0,   0,   0,   70,  14,  16,  0,   4,   0,   0,   0,   2,   64,  0,
    0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   86,  0,
    0,   5,   242, 0,   16,  0,   4,   0,   0,   0,   70,  14,  16,  0,   4,   0,   0,   0,   56,
    0,   0,   10,  242, 0,   16,  0,   8,   0,   0,   0,   70,  14,  16,  0,   4,   0,   0,   0,
    2,   64,  0,   0,   8,   32,  128, 58,  8,   32,  128, 58,  8,   32,  128, 58,  8,   32,  128,
    58,  18,  0,   0,   1,   85,  0,   0,   7,   242, 0,   16,  0,   4,   0,   0,   0,   70,  14,
    16,  0,   9,   0,   0,   0,   6,   0,   16,  0,   0,   0,   0,   0,   1,   0,   0,   10,  242,
    0,   16,  0,   7,   0,   0,   0,   70,  14,  16,  0,   4,   0,   0,   0,   2,   64,  0,   0,
    255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   255, 3,   0,   0,   1,   0,   0,
    10,  242, 0,   16,  0,   10,  0,   0,   0,   70,  14,  16,  0,   4,   0,   0,   0,   2,   64,
    0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   138,
    0,   0,   15,  242, 0,   16,  0,   12,  0,   0,   0,   2,   64,  0,   0,   3,   0,   0,   0,
    3,   0,   0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   2,   64,  0,   0,   7,   0,   0,
    0,   7,   0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   70,  14,  16,  0,   4,   0,
    0,   0,   135, 0,   0,   5,   242, 0,   16,  0,   13,  0,   0,   0,   70,  14,  16,  0,   10,
    0,   0,   0,   30,  0,   0,   10,  242, 0,   16,  0,   13,  0,   0,   0,   70,  14,  16,  0,
    13,  0,   0,   0,   2,   64,  0,   0,   232, 255, 255, 255, 232, 255, 255, 255, 232, 255, 255,
    255, 232, 255, 255, 255, 55,  0,   0,   12,  242, 0,   16,  0,   13,  0,   0,   0,   70,  14,
    16,  0,   10,  0,   0,   0,   70,  14,  16,  0,   13,  0,   0,   0,   2,   64,  0,   0,   8,
    0,   0,   0,   8,   0,   0,   0,   8,   0,   0,   0,   8,   0,   0,   0,   30,  0,   0,   11,
    242, 0,   16,  0,   14,  0,   0,   0,   70,  14,  16,  128, 65,  0,   0,   0,   13,  0,   0,
    0,   2,   64,  0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,
    0,   0,   55,  0,   0,   9,   242, 0,   16,  0,   14,  0,   0,   0,   70,  14,  16,  0,   12,
    0,   0,   0,   70,  14,  16,  0,   12,  0,   0,   0,   70,  14,  16,  0,   14,  0,   0,   0,
    140, 0,   0,   17,  242, 0,   16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   7,   0,   0,
    0,   7,   0,   0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   70,  14,  16,  0,   13,  0,
    0,   0,   70,  14,  16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,
    4,   0,   0,   0,   70,  14,  16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   127, 0,   0,
    0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   55,  0,   0,   9,   242, 0,
    16,  0,   4,   0,   0,   0,   70,  14,  16,  0,   12,  0,   0,   0,   70,  14,  16,  0,   10,
    0,   0,   0,   70,  14,  16,  0,   4,   0,   0,   0,   41,  0,   0,   10,  242, 0,   16,  0,
    10,  0,   0,   0,   70,  14,  16,  0,   14,  0,   0,   0,   2,   64,  0,   0,   23,  0,   0,
    0,   23,  0,   0,   0,   23,  0,   0,   0,   23,  0,   0,   0,   30,  0,   0,   10,  242, 0,
    16,  0,   10,  0,   0,   0,   70,  14,  16,  0,   10,  0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   62,  0,   0,   0,   62,  0,   0,   0,   62,  0,   0,   0,   62,  41,  0,   0,   10,
    242, 0,   16,  0,   4,   0,   0,   0,   70,  14,  16,  0,   4,   0,   0,   0,   2,   64,  0,
    0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   30,  0,
    0,   7,   242, 0,   16,  0,   4,   0,   0,   0,   70,  14,  16,  0,   10,  0,   0,   0,   70,
    14,  16,  0,   4,   0,   0,   0,   55,  0,   0,   12,  242, 0,   16,  0,   9,   0,   0,   0,
    70,  14,  16,  0,   7,   0,   0,   0,   70,  14,  16,  0,   4,   0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   85,  0,
    0,   7,   242, 0,   16,  0,   4,   0,   0,   0,   70,  14,  16,  0,   8,   0,   0,   0,   6,
    0,   16,  0,   0,   0,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   7,   0,   0,   0,
    70,  14,  16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   255, 3,   0,   0,   255, 3,   0,
    0,   255, 3,   0,   0,   255, 3,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   10,  0,
    0,   0,   70,  14,  16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   127, 0,   0,   0,   127,
    0,   0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   138, 0,   0,   15,  242, 0,   16,  0,
    12,  0,   0,   0,   2,   64,  0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   3,   0,   0,
    0,   3,   0,   0,   0,   2,   64,  0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   7,   0,
    0,   0,   7,   0,   0,   0,   70,  14,  16,  0,   4,   0,   0,   0,   135, 0,   0,   5,   242,
    0,   16,  0,   13,  0,   0,   0,   70,  14,  16,  0,   10,  0,   0,   0,   30,  0,   0,   10,
    242, 0,   16,  0,   13,  0,   0,   0,   70,  14,  16,  0,   13,  0,   0,   0,   2,   64,  0,
    0,   232, 255, 255, 255, 232, 255, 255, 255, 232, 255, 255, 255, 232, 255, 255, 255, 55,  0,
    0,   12,  242, 0,   16,  0,   13,  0,   0,   0,   70,  14,  16,  0,   10,  0,   0,   0,   70,
    14,  16,  0,   13,  0,   0,   0,   2,   64,  0,   0,   8,   0,   0,   0,   8,   0,   0,   0,
    8,   0,   0,   0,   8,   0,   0,   0,   30,  0,   0,   11,  242, 0,   16,  0,   14,  0,   0,
    0,   70,  14,  16,  128, 65,  0,   0,   0,   13,  0,   0,   0,   2,   64,  0,   0,   1,   0,
    0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   55,  0,   0,   9,   242,
    0,   16,  0,   14,  0,   0,   0,   70,  14,  16,  0,   12,  0,   0,   0,   70,  14,  16,  0,
    12,  0,   0,   0,   70,  14,  16,  0,   14,  0,   0,   0,   140, 0,   0,   17,  242, 0,   16,
    0,   4,   0,   0,   0,   2,   64,  0,   0,   7,   0,   0,   0,   7,   0,   0,   0,   7,   0,
    0,   0,   7,   0,   0,   0,   70,  14,  16,  0,   13,  0,   0,   0,   70,  14,  16,  0,   4,
    0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   1,   0,   0,   10,  242, 0,   16,  0,   4,   0,   0,   0,   70,  14,  16,
    0,   4,   0,   0,   0,   2,   64,  0,   0,   127, 0,   0,   0,   127, 0,   0,   0,   127, 0,
    0,   0,   127, 0,   0,   0,   55,  0,   0,   9,   242, 0,   16,  0,   4,   0,   0,   0,   70,
    14,  16,  0,   12,  0,   0,   0,   70,  14,  16,  0,   10,  0,   0,   0,   70,  14,  16,  0,
    4,   0,   0,   0,   41,  0,   0,   10,  242, 0,   16,  0,   10,  0,   0,   0,   70,  14,  16,
    0,   14,  0,   0,   0,   2,   64,  0,   0,   23,  0,   0,   0,   23,  0,   0,   0,   23,  0,
    0,   0,   23,  0,   0,   0,   30,  0,   0,   10,  242, 0,   16,  0,   10,  0,   0,   0,   70,
    14,  16,  0,   10,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   62,  0,   0,   0,   62,
    0,   0,   0,   62,  0,   0,   0,   62,  41,  0,   0,   10,  242, 0,   16,  0,   4,   0,   0,
    0,   70,  14,  16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   16,  0,   0,   0,   16,  0,
    0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   30,  0,   0,   7,   242, 0,   16,  0,   4,
    0,   0,   0,   70,  14,  16,  0,   10,  0,   0,   0,   70,  14,  16,  0,   4,   0,   0,   0,
    55,  0,   0,   12,  242, 0,   16,  0,   8,   0,   0,   0,   70,  14,  16,  0,   7,   0,   0,
    0,   70,  14,  16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   2,
    0,   0,   1,   6,   0,   0,   3,   1,   64,  0,   0,   4,   0,   0,   0,   31,  0,   4,   3,
    58,  0,   16,  0,   2,   0,   0,   0,   54,  0,   0,   8,   242, 0,   16,  0,   9,   0,   0,
    0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,
    128, 63,  54,  0,   0,   8,   242, 0,   16,  0,   8,   0,   0,   0,   2,   64,  0,   0,   0,
    0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  18,  0,   0,   1,
    139, 0,   0,   15,  242, 0,   16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   16,  0,   0,
    0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   70,  14,  16,  0,   9,
    0,   0,   0,   43,  0,   0,   5,   242, 0,   16,  0,   4,   0,   0,   0,   70,  14,  16,  0,
    4,   0,   0,   0,   56,  0,   0,   10,  242, 0,   16,  0,   4,   0,   0,   0,   70,  14,  16,
    0,   4,   0,   0,   0,   2,   64,  0,   0,   0,   1,   128, 58,  0,   1,   128, 58,  0,   1,
    128, 58,  0,   1,   128, 58,  52,  0,   0,   10,  242, 0,   16,  0,   9,   0,   0,   0,   70,
    14,  16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 191, 0,   0,   128, 191,
    0,   0,   128, 191, 0,   0,   128, 191, 139, 0,   0,   15,  242, 0,   16,  0,   4,   0,   0,
    0,   2,   64,  0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,   0,   0,   16,  0,
    0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   70,  14,  16,  0,   8,   0,   0,   0,   43,  0,   0,   5,   242, 0,   16,  0,
    4,   0,   0,   0,   70,  14,  16,  0,   4,   0,   0,   0,   56,  0,   0,   10,  242, 0,   16,
    0,   4,   0,   0,   0,   70,  14,  16,  0,   4,   0,   0,   0,   2,   64,  0,   0,   0,   1,
    128, 58,  0,   1,   128, 58,  0,   1,   128, 58,  0,   1,   128, 58,  52,  0,   0,   10,  242,
    0,   16,  0,   8,   0,   0,   0,   70,  14,  16,  0,   4,   0,   0,   0,   2,   64,  0,   0,
    0,   0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 0,   0,   128, 191, 21,  0,   0,
    1,   2,   0,   0,   1,   6,   0,   0,   3,   1,   64,  0,   0,   6,   0,   0,   0,   31,  0,
    4,   3,   58,  0,   16,  0,   2,   0,   0,   0,   54,  0,   0,   8,   242, 0,   16,  0,   9,
    0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,
    0,   0,   128, 63,  54,  0,   0,   8,   242, 0,   16,  0,   8,   0,   0,   0,   2,   64,  0,
    0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  18,  0,
    0,   1,   131, 0,   0,   5,   242, 0,   16,  0,   9,   0,   0,   0,   70,  14,  16,  0,   9,
    0,   0,   0,   131, 0,   0,   5,   242, 0,   16,  0,   8,   0,   0,   0,   70,  14,  16,  0,
    8,   0,   0,   0,   21,  0,   0,   1,   2,   0,   0,   1,   10,  0,   0,   1,   31,  0,   4,
    3,   58,  0,   16,  0,   2,   0,   0,   0,   54,  0,   0,   8,   242, 0,   16,  0,   9,   0,
    0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,
    0,   128, 63,  54,  0,   0,   8,   242, 0,   16,  0,   8,   0,   0,   0,   2,   64,  0,   0,
    0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  21,  0,   0,
    1,   2,   0,   0,   1,   23,  0,   0,   1,   21,  0,   0,   1,   31,  0,   4,   3,   58,  0,
    16,  0,   3,   0,   0,   0,   54,  32,  0,   5,   242, 0,   16,  0,   9,   0,   0,   0,   70,
    14,  16,  0,   9,   0,   0,   0,   29,  0,   0,   10,  242, 0,   16,  0,   4,   0,   0,   0,
    70,  14,  16,  0,   9,   0,   0,   0,   2,   64,  0,   0,   193, 192, 192, 62,  193, 192, 192,
    62,  193, 192, 192, 62,  193, 192, 192, 62,  31,  0,   4,   3,   10,  0,   16,  0,   4,   0,
    0,   0,   29,  0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   9,
    0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,   10,  0,   16,  0,
    0,   0,   0,   0,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   60,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 196, 18,  0,
    0,   1,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,
    0,   128, 59,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 195, 21,  0,   0,   1,
    18,  0,   0,   1,   29,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   10,  0,   16,
    0,   9,   0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,   26,  0,
    16,  0,   1,   0,   0,   0,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,
    64,  0,   0,   0,   0,   0,   59,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 194,
    18,  0,   0,   1,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,
    0,   0,   0,   128, 58,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   21,  0,
    0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   10,
    0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   9,   0,   0,   0,   50,  0,   0,   9,
    130, 0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   127, 72,  58,  0,   16,  0,   0,   0,   0,   0,   56,  0,   0,   7,   18,  0,
    16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,
    0,   0,   0,   67,  0,   0,   5,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,
    0,   0,   0,   0,   0,   0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,
    0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   56,  0,   0,   7,   18,  0,
    16,  0,   9,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   8,
    32,  128, 58,  31,  0,   4,   3,   26,  0,   16,  0,   4,   0,   0,   0,   29,  0,   0,   7,
    18,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   9,   0,   0,   0,   1,   64,  0,
    0,   193, 192, 64,  63,  31,  0,   4,   3,   10,  0,   16,  0,   0,   0,   0,   0,   54,  0,
    0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   60,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 196, 18,  0,   0,   1,   54,  0,   0,   8,
    146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 59,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   128, 195, 21,  0,   0,   1,   18,  0,   0,   1,   29,  0,
    0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   9,   0,   0,   0,   1,
    64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,   26,  0,   16,  0,   1,   0,   0,   0,
    54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,
    59,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 194, 18,  0,   0,   1,   54,  0,
    0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 58,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,
    56,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,
    0,   26,  0,   16,  0,   9,   0,   0,   0,   50,  0,   0,   9,   130, 0,   16,  0,   0,   0,
    0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  58,
    0,   16,  0,   0,   0,   0,   0,   56,  0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,
    10,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   67,  0,   0,
    5,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   0,   0,
    0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   58,
    0,   16,  0,   0,   0,   0,   0,   56,  0,   0,   7,   34,  0,   16,  0,   9,   0,   0,   0,
    10,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   8,   32,  128, 58,  31,  0,   4,
    3,   42,  0,   16,  0,   4,   0,   0,   0,   29,  0,   0,   7,   18,  0,   16,  0,   0,   0,
    0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,
    0,   4,   3,   10,  0,   16,  0,   0,   0,   0,   0,   54,  0,   0,   8,   146, 0,   16,  0,
    0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   60,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   128, 196, 18,  0,   0,   1,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,
    0,   0,   2,   64,  0,   0,   0,   0,   128, 59,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   128, 195, 21,  0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   34,  0,   16,  0,
    1,   0,   0,   0,   42,  0,   16,  0,   9,   0,   0,   0,   1,   64,  0,   0,   129, 128, 128,
    62,  31,  0,   4,   3,   26,  0,   16,  0,   1,   0,   0,   0,   54,  0,   0,   8,   146, 0,
    16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   59,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   128, 194, 18,  0,   0,   1,   54,  0,   0,   8,   146, 0,   16,  0,
    0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 58,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   34,  0,
    16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   9,
    0,   0,   0,   50,  0,   0,   9,   130, 0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,
    1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  58,  0,   16,  0,   0,   0,   0,
    0,   56,  0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,
    0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   67,  0,   0,   5,   18,  0,   16,  0,   0,
    0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   0,   0,   0,   7,   18,  0,   16,  0,
    0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,
    0,   56,  0,   0,   7,   66,  0,   16,  0,   9,   0,   0,   0,   10,  0,   16,  0,   0,   0,
    0,   0,   1,   64,  0,   0,   8,   32,  128, 58,  31,  0,   4,   3,   58,  0,   16,  0,   4,
    0,   0,   0,   29,  0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,
    9,   0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,   10,  0,   16,
    0,   0,   0,   0,   0,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,
    0,   0,   0,   0,   0,   60,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 196, 18,
    0,   0,   1,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,
    0,   0,   128, 59,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 195, 21,  0,   0,
    1,   18,  0,   0,   1,   29,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   58,  0,
    16,  0,   9,   0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,   26,
    0,   16,  0,   1,   0,   0,   0,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,
    2,   64,  0,   0,   0,   0,   0,   59,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128,
    194, 18,  0,   0,   1,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,
    0,   0,   0,   0,   128, 58,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   21,
    0,   0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,
    10,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   9,   0,   0,   0,   50,  0,   0,
    9,   130, 0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   1,   64,
    0,   0,   0,   0,   127, 72,  58,  0,   16,  0,   0,   0,   0,   0,   56,  0,   0,   7,   18,
    0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,
    0,   0,   0,   0,   67,  0,   0,   5,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,
    0,   0,   0,   0,   0,   0,   0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,
    16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   56,  0,   0,   7,   130,
    0,   16,  0,   9,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,
    8,   32,  128, 58,  54,  32,  0,   5,   242, 0,   16,  0,   8,   0,   0,   0,   70,  14,  16,
    0,   8,   0,   0,   0,   29,  0,   0,   10,  242, 0,   16,  0,   4,   0,   0,   0,   70,  14,
    16,  0,   8,   0,   0,   0,   2,   64,  0,   0,   193, 192, 192, 62,  193, 192, 192, 62,  193,
    192, 192, 62,  193, 192, 192, 62,  31,  0,   4,   3,   10,  0,   16,  0,   4,   0,   0,   0,
    29,  0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   8,   0,   0,
    0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,   10,  0,   16,  0,   0,   0,
    0,   0,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   60,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 196, 18,  0,   0,   1,
    54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128,
    59,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 195, 21,  0,   0,   1,   18,  0,
    0,   1,   29,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   8,
    0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,   26,  0,   16,  0,
    1,   0,   0,   0,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   59,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 194, 18,  0,
    0,   1,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,
    0,   128, 58,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   1,
    21,  0,   0,   1,   56,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   10,  0,   16,
    0,   0,   0,   0,   0,   10,  0,   16,  0,   8,   0,   0,   0,   50,  0,   0,   9,   130, 0,
    16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   127, 72,  58,  0,   16,  0,   0,   0,   0,   0,   56,  0,   0,   7,   18,  0,   16,  0,
    0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,
    0,   67,  0,   0,   5,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,
    0,   0,   0,   0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,
    0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   56,  0,   0,   7,   18,  0,   16,  0,
    8,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   8,   32,  128,
    58,  31,  0,   4,   3,   26,  0,   16,  0,   4,   0,   0,   0,   29,  0,   0,   7,   18,  0,
    16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   193,
    192, 64,  63,  31,  0,   4,   3,   10,  0,   16,  0,   0,   0,   0,   0,   54,  0,   0,   8,
    146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   60,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   128, 196, 18,  0,   0,   1,   54,  0,   0,   8,   146, 0,
    16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 59,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   128, 195, 21,  0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,
    34,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,
    0,   129, 128, 128, 62,  31,  0,   4,   3,   26,  0,   16,  0,   1,   0,   0,   0,   54,  0,
    0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   59,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 194, 18,  0,   0,   1,   54,  0,   0,   8,
    146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 58,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,
    0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   26,
    0,   16,  0,   8,   0,   0,   0,   50,  0,   0,   9,   130, 0,   16,  0,   0,   0,   0,   0,
    26,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  58,  0,   16,
    0,   0,   0,   0,   0,   56,  0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,
    16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   67,  0,   0,   5,   18,
    0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   0,   0,   0,   7,
    18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,
    0,   0,   0,   0,   0,   56,  0,   0,   7,   34,  0,   16,  0,   8,   0,   0,   0,   10,  0,
    16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   8,   32,  128, 58,  31,  0,   4,   3,   42,
    0,   16,  0,   4,   0,   0,   0,   29,  0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,
    42,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,
    3,   10,  0,   16,  0,   0,   0,   0,   0,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,
    0,   0,   2,   64,  0,   0,   0,   0,   0,   60,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   128, 196, 18,  0,   0,   1,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,
    2,   64,  0,   0,   0,   0,   128, 59,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128,
    195, 21,  0,   0,   1,   18,  0,   0,   1,   29,  0,   0,   7,   34,  0,   16,  0,   1,   0,
    0,   0,   42,  0,   16,  0,   8,   0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,
    0,   4,   3,   26,  0,   16,  0,   1,   0,   0,   0,   54,  0,   0,   8,   146, 0,   16,  0,
    0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   59,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   128, 194, 18,  0,   0,   1,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,
    0,   0,   2,   64,  0,   0,   0,   0,   128, 58,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,  0,   0,   7,   34,  0,   16,  0,
    1,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   8,   0,   0,
    0,   50,  0,   0,   9,   130, 0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   1,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   127, 72,  58,  0,   16,  0,   0,   0,   0,   0,   56,
    0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,
    58,  0,   16,  0,   0,   0,   0,   0,   67,  0,   0,   5,   18,  0,   16,  0,   0,   0,   0,
    0,   10,  0,   16,  0,   0,   0,   0,   0,   0,   0,   0,   7,   18,  0,   16,  0,   0,   0,
    0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   56,
    0,   0,   7,   66,  0,   16,  0,   8,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,
    1,   64,  0,   0,   8,   32,  128, 58,  31,  0,   4,   3,   58,  0,   16,  0,   4,   0,   0,
    0,   29,  0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   8,   0,
    0,   0,   1,   64,  0,   0,   193, 192, 64,  63,  31,  0,   4,   3,   10,  0,   16,  0,   0,
    0,   0,   0,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,
    0,   0,   0,   60,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 196, 18,  0,   0,
    1,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,
    128, 59,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 195, 21,  0,   0,   1,   18,
    0,   0,   1,   29,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,
    8,   0,   0,   0,   1,   64,  0,   0,   129, 128, 128, 62,  31,  0,   4,   3,   26,  0,   16,
    0,   1,   0,   0,   0,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,
    0,   0,   0,   0,   0,   59,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 194, 18,
    0,   0,   1,   54,  0,   0,   8,   146, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,
    0,   0,   128, 58,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,
    1,   21,  0,   0,   1,   56,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   10,  0,
    16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   8,   0,   0,   0,   50,  0,   0,   9,   130,
    0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   127, 72,  58,  0,   16,  0,   0,   0,   0,   0,   56,  0,   0,   7,   18,  0,   16,
    0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,
    0,   0,   67,  0,   0,   5,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,
    0,   0,   0,   0,   0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,
    0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   56,  0,   0,   7,   130, 0,   16,
    0,   8,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   8,   32,
    128, 58,  21,  0,   0,   1,   0,   0,   0,   7,   242, 0,   16,  0,   18,  0,   0,   0,   70,
    14,  16,  0,   9,   0,   0,   0,   70,  14,  16,  0,   11,  0,   0,   0,   0,   0,   0,   7,
    242, 0,   16,  0,   15,  0,   0,   0,   70,  14,  16,  0,   8,   0,   0,   0,   70,  14,  16,
    0,   19,  0,   0,   0,   18,  0,   0,   1,   54,  0,   0,   5,   34,  0,   16,  0,   0,   0,
    0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   56,
    0,   0,   7,   242, 0,   16,  0,   4,   0,   0,   0,   86,  5,   16,  0,   0,   0,   0,   0,
    70,  14,  16,  0,   18,  0,   0,   0,   56,  0,   0,   7,   242, 0,   16,  0,   7,   0,   0,
    0,   86,  5,   16,  0,   0,   0,   0,   0,   70,  14,  16,  0,   15,  0,   0,   0,   32,  0,
    0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   6,   0,   0,   0,   1,
    64,  0,   0,   0,   0,   0,   0,   39,  0,   0,   7,   34,  0,   16,  0,   0,   0,   0,   0,
    10,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   1,   0,   0,
    7,   18,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   0,   0,   0,   0,   10,  0,
    16,  0,   0,   0,   0,   0,   31,  0,   4,   3,   10,  0,   16,  0,   0,   0,   0,   0,   80,
    0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   1,   0,   0,   0,
    1,   64,  0,   0,   2,   0,   0,   0,   31,  0,   4,   3,   10,  0,   16,  0,   0,   0,   0,
    0,   80,  0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   1,   0,
    0,   0,   1,   64,  0,   0,   3,   0,   0,   0,   31,  0,   4,   3,   10,  0,   16,  0,   0,
    0,   0,   0,   54,  0,   0,   5,   66,  0,   16,  0,   4,   0,   0,   0,   58,  0,   16,  0,
    4,   0,   0,   0,   21,  0,   0,   1,   54,  0,   0,   5,   34,  0,   16,  0,   4,   0,   0,
    0,   42,  0,   16,  0,   4,   0,   0,   0,   21,  0,   0,   1,   54,  0,   0,   5,   18,  0,
    16,  0,   4,   0,   0,   0,   26,  0,   16,  0,   4,   0,   0,   0,   21,  0,   0,   1,   35,
    0,   0,   9,   98,  0,   16,  0,   1,   0,   0,   0,   6,   2,   16,  0,   3,   0,   0,   0,
    6,   1,   16,  0,   2,   0,   0,   0,   6,   2,   16,  0,   6,   0,   0,   0,   85,  0,   0,
    7,   18,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   1,   64,
    0,   0,   3,   0,   0,   0,   78,  0,   0,   8,   50,  0,   16,  0,   0,   0,   0,   0,   0,
    208, 0,   0,   134, 0,   16,  0,   1,   0,   0,   0,   70,  0,   16,  0,   2,   0,   0,   0,
    31,  0,   4,   3,   42,  0,   16,  0,   0,   0,   0,   0,   138, 0,   0,   11,  66,  0,   16,
    0,   0,   0,   0,   0,   1,   64,  0,   0,   3,   0,   0,   0,   1,   64,  0,   0,   4,   0,
    0,   0,   42,  128, 48,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   41,
    0,   0,   7,   130, 0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   3,   0,   0,   0,
    1,   64,  0,   0,   5,   0,   0,   0,   42,  0,   0,   10,  162, 0,   16,  0,   1,   0,   0,
    0,   86,  5,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   4,   0,
    0,   0,   0,   0,   0,   0,   3,   0,   0,   0,   42,  0,   0,   7,   130, 0,   16,  0,   2,
    0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,
    85,  0,   0,   7,   130, 0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,
    0,   1,   64,  0,   0,   4,   0,   0,   0,   1,   0,   0,   7,   130, 0,   16,  0,   0,   0,
    0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   254, 7,   0,   0,   35,
    0,   0,   9,   130, 0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   2,   0,   0,   0,
    58,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   85,  0,   0,
    7,   34,  0,   16,  0,   1,   0,   0,   0,   42,  0,   16,  0,   2,   0,   0,   0,   1,   64,
    0,   0,   5,   0,   0,   0,   139, 0,   0,   15,  50,  0,   16,  0,   3,   0,   0,   0,   2,
    64,  0,   0,   27,  0,   0,   0,   29,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    2,   64,  0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   6,   0,   16,  0,   0,   0,   0,   0,   35,  0,   0,   9,   130, 0,   16,  0,   0,   0,
    0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   10,
    0,   16,  0,   3,   0,   0,   0,   41,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,
    26,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   8,   0,   0,   0,   42,  0,   0,
    7,   34,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   1,   64,
    0,   0,   6,   0,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   1,   0,   0,   0,   58,
    0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   2,   0,   0,   0,   140, 0,   0,   11,
    130, 0,   16,  0,   2,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,
    0,   1,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,
    0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   2,   0,   0,   0,   58,  0,   16,  0,   2,
    0,   0,   0,   26,  0,   16,  0,   3,   0,   0,   0,   140, 0,   0,   11,  130, 0,   16,  0,
    2,   0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,
    0,   58,  0,   16,  0,   2,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   140, 0,
    0,   11,  130, 0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,
    64,  0,   0,   0,   0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,
    2,   0,   0,   0,   1,   0,   0,   10,  50,  0,   16,  0,   3,   0,   0,   0,   86,  5,   16,
    0,   1,   0,   0,   0,   2,   64,  0,   0,   16,  0,   0,   0,   8,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   140, 0,   0,   20,  194, 0,   16,  0,   3,   0,   0,   0,   2,
    64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   22,  0,   0,   0,   22,  0,   0,   0,
    2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   8,   0,   0,   0,   11,  0,   0,
    0,   246, 15,  16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   35,  0,   0,   12,  82,  0,   16,  0,   3,
    0,   0,   0,   6,   0,   16,  0,   3,   0,   0,   0,   2,   64,  0,   0,   2,   0,   0,   0,
    0,   0,   0,   0,   16,  0,   0,   0,   0,   0,   0,   0,   166, 11,  16,  0,   3,   0,   0,
    0,   140, 0,   0,   17,  50,  0,   16,  0,   3,   0,   0,   0,   2,   64,  0,   0,   5,   0,
    0,   0,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   86,  5,   16,  0,
    3,   0,   0,   0,   134, 0,   16,  0,   3,   0,   0,   0,   140, 0,   0,   17,  194, 0,   16,
    0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   0,
    0,   0,   2,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,
    0,   0,   0,   9,   0,   0,   0,   166, 10,  16,  0,   0,   0,   0,   0,   6,   4,   16,  0,
    3,   0,   0,   0,   138, 0,   0,   9,   34,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,
    0,   3,   0,   0,   0,   1,   64,  0,   0,   6,   0,   0,   0,   42,  0,   16,  0,   0,   0,
    0,   0,   1,   0,   0,   7,   130, 0,   16,  0,   2,   0,   0,   0,   58,  0,   16,  0,   1,
    0,   0,   0,   1,   64,  0,   0,   6,   0,   0,   0,   140, 0,   0,   11,  130, 0,   16,  0,
    1,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,   0,   1,   64,  0,   0,   8,   0,   0,
    0,   58,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   35,  0,
    0,   9,   34,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   1,
    64,  0,   0,   32,  0,   0,   0,   58,  0,   16,  0,   1,   0,   0,   0,   35,  0,   0,   9,
    34,  0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   2,   0,   0,   0,   1,   64,  0,
    0,   4,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   140, 0,   0,   17,  194, 0,
    16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,
    0,   0,   0,   1,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    4,   0,   0,   0,   7,   0,   0,   0,   86,  5,   16,  0,   0,   0,   0,   0,   166, 14,  16,
    0,   0,   0,   0,   0,   140, 0,   0,   11,  130, 0,   16,  0,   0,   0,   0,   0,   1,   64,
    0,   0,   9,   0,   0,   0,   1,   64,  0,   0,   3,   0,   0,   0,   26,  0,   16,  0,   1,
    0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   140, 0,   0,   11,  66,  0,   16,  0,
    0,   0,   0,   0,   1,   64,  0,   0,   6,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,
    0,   42,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   18,  0,
    0,   1,   139, 0,   0,   15,  162, 0,   16,  0,   1,   0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   27,  0,   0,   0,   0,   0,   0,   0,   29,  0,   0,   0,   2,   64,  0,   0,
    0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   0,   16,
    0,   0,   0,   0,   0,   42,  0,   0,   10,  50,  0,   16,  0,   3,   0,   0,   0,   86,  5,
    16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   5,   0,   0,   0,   2,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   85,  0,   0,   7,   130, 0,   16,  0,   0,   0,   0,   0,
    42,  0,   16,  0,   2,   0,   0,   0,   1,   64,  0,   0,   5,   0,   0,   0,   35,  0,   0,
    9,   130, 0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   3,   0,   0,   0,   58,  0,
    16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   41,  0,   0,   10,  194,
    0,   16,  0,   2,   0,   0,   0,   86,  5,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   7,   0,   0,   0,   41,  0,   0,
    7,   34,  0,   16,  0,   1,   0,   0,   0,   42,  0,   16,  0,   2,   0,   0,   0,   1,   64,
    0,   0,   1,   0,   0,   0,   1,   0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   26,
    0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   96,  0,   0,   0,   140, 0,   0,   11,
    18,  0,   16,  0,   3,   0,   0,   0,   1,   64,  0,   0,   25,  0,   0,   0,   1,   64,  0,
    0,   7,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   1,   0,
    0,   0,   1,   0,   0,   10,  194, 0,   16,  0,   2,   0,   0,   0,   166, 14,  16,  0,   2,
    0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   8,   0,   0,   0,
    0,   8,   0,   0,   30,  0,   0,   7,   18,  0,   16,  0,   3,   0,   0,   0,   10,  0,   16,
    0,   3,   0,   0,   0,   42,  0,   16,  0,   2,   0,   0,   0,   41,  0,   0,   10,  194, 0,
    16,  0,   3,   0,   0,   0,   86,  5,   16,  0,   1,   0,   0,   0,   2,   64,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   3,   0,   0,   0,   2,   0,   0,   0,   140, 0,   0,   17,
    194, 0,   16,  0,   3,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   25,  0,   0,   0,   25,  0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   10,  0,   0,   0,   9,   0,   0,   0,   246, 15,  16,  0,   0,   0,   0,   0,   166,
    14,  16,  0,   3,   0,   0,   0,   35,  0,   0,   12,  194, 0,   16,  0,   3,   0,   0,   0,
    166, 10,  16,  0,   2,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   8,   0,   0,   0,   4,   0,   0,   0,   166, 14,  16,  0,   3,   0,   0,   0,   140, 0,
    0,   17,  210, 0,   16,  0,   3,   0,   0,   0,   2,   64,  0,   0,   1,   0,   0,   0,   0,
    0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   2,   64,  0,   0,   4,   0,   0,   0,
    0,   0,   0,   0,   7,   0,   0,   0,   6,   0,   0,   0,   86,  5,   16,  0,   0,   0,   0,
    0,   6,   14,  16,  0,   3,   0,   0,   0,   140, 0,   0,   11,  130, 0,   16,  0,   0,   0,
    0,   0,   1,   64,  0,   0,   12,  0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   58,
    0,   16,  0,   2,   0,   0,   0,   42,  0,   16,  0,   3,   0,   0,   0,   1,   0,   0,   7,
    34,  0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   3,   0,   0,   0,   1,   64,  0,
    0,   0,   7,   0,   0,   30,  0,   0,   7,   130, 0,   16,  0,   0,   0,   0,   0,   58,  0,
    16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   1,   0,   0,   7,   34,
    0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   3,   0,   0,   0,   1,   64,  0,   0,
    2,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   58,  0,   16,
    0,   1,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   140, 0,   0,   11,  34,  0,
    16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,   1,   64,  0,   0,   6,
    0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,
    30,  0,   0,   7,   130, 0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,
    0,   26,  0,   16,  0,   1,   0,   0,   0,   140, 0,   0,   11,  66,  0,   16,  0,   0,   0,
    0,   0,   1,   64,  0,   0,   6,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   10,
    0,   16,  0,   3,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   21,  0,   0,   1,
    35,  0,   0,   10,  50,  0,   16,  0,   0,   0,   0,   0,   70,  0,   16,  128, 65,  0,   0,
    0,   0,   0,   0,   0,   70,  0,   16,  0,   2,   0,   0,   0,   134, 0,   16,  0,   1,   0,
    0,   0,   38,  0,   0,   8,   0,   208, 0,   0,   130, 0,   16,  0,   0,   0,   0,   0,   26,
    0,   16,  0,   2,   0,   0,   0,   10,  0,   16,  0,   2,   0,   0,   0,   35,  0,   0,   9,
    18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,
    0,   2,   0,   0,   0,   26,  0,   16,  0,   0,   0,   0,   0,   41,  0,   0,   7,   18,  0,
    16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   3,
    0,   0,   0,   35,  0,   0,   9,   18,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,
    0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,
    0,   85,  0,   0,   7,   18,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,
    0,   0,   1,   64,  0,   0,   3,   0,   0,   0,   31,  0,   4,   3,   58,  0,   16,  0,   5,
    0,   0,   0,   52,  0,   0,   7,   34,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,
    4,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 191, 51,  0,   0,   7,   34,  0,   16,
    0,   0,   0,   0,   0,   26,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,
    128, 63,  29,  0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   4,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   55,  0,   0,   9,   66,  0,   16,  0,
    0,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,
    63,  1,   64,  0,   0,   0,   0,   0,   191, 50,  0,   0,   9,   34,  0,   16,  0,   0,   0,
    0,   0,   26,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   254, 66,  42,
    0,   16,  0,   0,   0,   0,   0,   27,  0,   0,   5,   34,  0,   16,  0,   0,   0,   0,   0,
    26,  0,   16,  0,   0,   0,   0,   0,   52,  0,   0,   7,   130, 0,   16,  0,   0,   0,   0,
    0,   26,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 191, 51,  0,
    0,   7,   130, 0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   1,
    64,  0,   0,   0,   0,   128, 63,  29,  0,   0,   7,   18,  0,   16,  0,   1,   0,   0,   0,
    26,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   55,  0,   0,
    9,   18,  0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   1,   0,   0,   0,   1,   64,
    0,   0,   0,   0,   0,   63,  1,   64,  0,   0,   0,   0,   0,   191, 50,  0,   0,   9,   130,
    0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   254, 66,  10,  0,   16,  0,   1,   0,   0,   0,   27,  0,   0,   5,   130, 0,   16,
    0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   52,  0,   0,   7,   18,  0,
    16,  0,   1,   0,   0,   0,   42,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   128, 191, 51,  0,   0,   7,   18,  0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,
    1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 63,  29,  0,   0,   7,   34,  0,   16,
    0,   1,   0,   0,   0,   42,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   0,   0,
    0,   0,   55,  0,   0,   9,   34,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   1,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   63,  1,   64,  0,   0,   0,   0,   0,   191,
    50,  0,   0,   9,   18,  0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   1,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   254, 66,  26,  0,   16,  0,   1,   0,   0,   0,   27,  0,
    0,   5,   18,  0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   1,   0,   0,   0,   52,
    0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,
    1,   64,  0,   0,   0,   0,   128, 191, 51,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,
    0,   26,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   128, 63,  29,  0,
    0,   7,   66,  0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,   1,
    64,  0,   0,   0,   0,   0,   0,   55,  0,   0,   9,   66,  0,   16,  0,   1,   0,   0,   0,
    42,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   63,  1,   64,  0,
    0,   0,   0,   0,   191, 50,  0,   0,   9,   34,  0,   16,  0,   1,   0,   0,   0,   26,  0,
    16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   254, 66,  42,  0,   16,  0,   1,
    0,   0,   0,   27,  0,   0,   5,   34,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,
    1,   0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   66,  0,   16,  0,   0,   0,   0,
    0,   26,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   2,   0,   0,   0,   31,  0,
    4,   3,   42,  0,   16,  0,   0,   0,   0,   0,   52,  0,   0,   7,   130, 0,   16,  0,   0,
    0,   0,   0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,
    51,  0,   0,   7,   130, 0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   127, 67,  0,   0,   0,   7,   130, 0,   16,  0,   0,   0,
    0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   63,  28,
    0,   0,   5,   34,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,
    18,  0,   0,   1,   32,  0,   0,   7,   130, 0,   16,  0,   0,   0,   0,   0,   26,  0,   16,
    0,   5,   0,   0,   0,   1,   64,  0,   0,   3,   0,   0,   0,   31,  0,   4,   3,   58,  0,
    16,  0,   0,   0,   0,   0,   52,  0,   0,   7,   130, 0,   16,  0,   0,   0,   0,   0,   10,
    0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   195, 51,  0,   0,   7,
    130, 0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   254, 66,  29,  0,   0,   7,   18,  0,   16,  0,   1,   0,   0,   0,   10,  0,
    16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   55,  0,   0,   9,   18,
    0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   0,   63,  1,   64,  0,   0,   0,   0,   0,   191, 0,   0,   0,   7,   130, 0,   16,
    0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   1,   0,
    0,   0,   27,  0,   0,   5,   34,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,
    0,   0,   0,   18,  0,   0,   1,   54,  32,  0,   5,   18,  0,   16,  0,   4,   0,   0,   0,
    10,  0,   16,  0,   4,   0,   0,   0,   50,  0,   0,   9,   130, 0,   16,  0,   0,   0,   0,
    0,   10,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 67,  1,   64,
    0,   0,   0,   0,   0,   63,  28,  0,   0,   5,   34,  0,   16,  0,   0,   0,   0,   0,   58,
    0,   16,  0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   31,  0,   4,   3,
    42,  0,   16,  0,   0,   0,   0,   0,   52,  0,   0,   7,   18,  0,   16,  0,   1,   0,   0,
    0,   26,  0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   51,  0,
    0,   7,   18,  0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   1,   0,   0,   0,   1,
    64,  0,   0,   0,   0,   127, 67,  0,   0,   0,   7,   18,  0,   16,  0,   1,   0,   0,   0,
    10,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   63,  28,  0,   0,
    5,   130, 0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   1,   0,   0,   0,   18,  0,
    0,   1,   32,  0,   0,   7,   18,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   5,
    0,   0,   0,   1,   64,  0,   0,   3,   0,   0,   0,   31,  0,   4,   3,   10,  0,   16,  0,
    1,   0,   0,   0,   52,  0,   0,   7,   18,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,
    0,   4,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   195, 51,  0,   0,   7,   18,  0,
    16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   254, 66,  29,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,
    4,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   55,  0,   0,   9,   34,  0,   16,
    0,   1,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,
    0,   63,  1,   64,  0,   0,   0,   0,   0,   191, 0,   0,   0,   7,   18,  0,   16,  0,   1,
    0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   10,  0,   16,  0,   1,   0,   0,   0,
    27,  0,   0,   5,   130, 0,   16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   1,   0,   0,
    0,   18,  0,   0,   1,   54,  32,  0,   5,   34,  0,   16,  0,   4,   0,   0,   0,   26,  0,
    16,  0,   4,   0,   0,   0,   50,  0,   0,   9,   18,  0,   16,  0,   1,   0,   0,   0,   26,
    0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 67,  1,   64,  0,   0,
    0,   0,   0,   63,  28,  0,   0,   5,   130, 0,   16,  0,   0,   0,   0,   0,   10,  0,   16,
    0,   1,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   31,  0,   4,   3,   42,  0,
    16,  0,   0,   0,   0,   0,   52,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   42,
    0,   16,  0,   4,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   51,  0,   0,   7,
    34,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   127, 67,  0,   0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   26,  0,
    16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   63,  28,  0,   0,   5,   18,
    0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   18,  0,   0,   1,
    32,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   5,   0,   0,
    0,   1,   64,  0,   0,   3,   0,   0,   0,   31,  0,   4,   3,   26,  0,   16,  0,   1,   0,
    0,   0,   52,  0,   0,   7,   34,  0,   16,  0,   1,   0,   0,   0,   42,  0,   16,  0,   4,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   195, 51,  0,   0,   7,   34,  0,   16,  0,
    1,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   254,
    66,  29,  0,   0,   7,   66,  0,   16,  0,   1,   0,   0,   0,   42,  0,   16,  0,   4,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   55,  0,   0,   9,   66,  0,   16,  0,   1,
    0,   0,   0,   42,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   63,
    1,   64,  0,   0,   0,   0,   0,   191, 0,   0,   0,   7,   34,  0,   16,  0,   1,   0,   0,
    0,   42,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   27,  0,
    0,   5,   18,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   1,   0,   0,   0,   18,
    0,   0,   1,   54,  32,  0,   5,   66,  0,   16,  0,   4,   0,   0,   0,   42,  0,   16,  0,
    4,   0,   0,   0,   50,  0,   0,   9,   34,  0,   16,  0,   1,   0,   0,   0,   42,  0,   16,
    0,   4,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 67,  1,   64,  0,   0,   0,   0,
    0,   63,  28,  0,   0,   5,   18,  0,   16,  0,   1,   0,   0,   0,   26,  0,   16,  0,   1,
    0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   31,  0,   4,   3,   42,  0,   16,  0,
    0,   0,   0,   0,   52,  0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,
    0,   4,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   51,  0,   0,   7,   66,  0,
    16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   127, 67,  0,   0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,
    0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   63,  28,  0,   0,   5,   34,  0,   16,
    0,   1,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   18,  0,   0,   1,   32,  0,
    0,   7,   66,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   5,   0,   0,   0,   1,
    64,  0,   0,   3,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,  0,   0,   0,   0,   0,
    52,  0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   0,   195, 51,  0,   0,   7,   66,  0,   16,  0,   0,   0,
    0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   254, 66,  29,
    0,   0,   7,   66,  0,   16,  0,   1,   0,   0,   0,   58,  0,   16,  0,   4,   0,   0,   0,
    1,   64,  0,   0,   0,   0,   0,   0,   55,  0,   0,   9,   66,  0,   16,  0,   1,   0,   0,
    0,   42,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   63,  1,   64,
    0,   0,   0,   0,   0,   191, 0,   0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,   42,
    0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   1,   0,   0,   0,   27,  0,   0,   5,
    34,  0,   16,  0,   1,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   18,  0,   0,
    1,   54,  32,  0,   5,   130, 0,   16,  0,   4,   0,   0,   0,   58,  0,   16,  0,   4,   0,
    0,   0,   50,  0,   0,   9,   66,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   4,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 67,  1,   64,  0,   0,   0,   0,   0,   63,
    28,  0,   0,   5,   34,  0,   16,  0,   1,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,
    0,   21,  0,   0,   1,   21,  0,   0,   1,   21,  0,   0,   1,   140, 0,   0,   11,  66,  0,
    16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   8,   0,   0,   0,   1,   64,  0,   0,   8,
    0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,
    140, 0,   0,   11,  34,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   8,   0,   0,
    0,   1,   64,  0,   0,   0,   0,   0,   0,   26,  0,   16,  0,   0,   0,   0,   0,   42,  0,
    16,  0,   0,   0,   0,   0,   140, 0,   0,   11,  66,  0,   16,  0,   0,   0,   0,   0,   1,
    64,  0,   0,   8,   0,   0,   0,   1,   64,  0,   0,   16,  0,   0,   0,   10,  0,   16,  0,
    1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,
    0,   0,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   0,   0,
    0,   0,   140, 0,   0,   17,  210, 0,   16,  0,   1,   0,   0,   0,   2,   64,  0,   0,   8,
    0,   0,   0,   0,   0,   0,   0,   8,   0,   0,   0,   8,   0,   0,   0,   2,   64,  0,   0,
    24,  0,   0,   0,   0,   0,   0,   0,   24,  0,   0,   0,   24,  0,   0,   0,   86,  5,   16,
    0,   1,   0,   0,   0,   86,  5,   16,  0,   0,   0,   0,   0,   31,  0,   4,   3,   58,  0,
    16,  0,   5,   0,   0,   0,   52,  0,   0,   10,  242, 0,   16,  0,   2,   0,   0,   0,   70,
    14,  16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 191, 0,   0,   128, 191,
    0,   0,   128, 191, 0,   0,   128, 191, 51,  0,   0,   10,  242, 0,   16,  0,   2,   0,   0,
    0,   70,  14,  16,  0,   2,   0,   0,   0,   2,   64,  0,   0,   0,   0,   128, 63,  0,   0,
    128, 63,  0,   0,   128, 63,  0,   0,   128, 63,  29,  0,   0,   10,  242, 0,   16,  0,   3,
    0,   0,   0,   70,  14,  16,  0,   7,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   55,  0,   0,   15,  242, 0,   16,
    0,   3,   0,   0,   0,   70,  14,  16,  0,   3,   0,   0,   0,   2,   64,  0,   0,   0,   0,
    0,   63,  0,   0,   0,   63,  0,   0,   0,   63,  0,   0,   0,   63,  2,   64,  0,   0,   0,
    0,   0,   191, 0,   0,   0,   191, 0,   0,   0,   191, 0,   0,   0,   191, 50,  0,   0,   12,
    242, 0,   16,  0,   2,   0,   0,   0,   70,  14,  16,  0,   2,   0,   0,   0,   2,   64,  0,
    0,   0,   0,   254, 66,  0,   0,   254, 66,  0,   0,   254, 66,  0,   0,   254, 66,  70,  14,
    16,  0,   3,   0,   0,   0,   27,  0,   0,   5,   242, 0,   16,  0,   2,   0,   0,   0,   70,
    14,  16,  0,   2,   0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   34,  0,   16,  0,
    0,   0,   0,   0,   26,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   2,   0,   0,
    0,   31,  0,   4,   3,   26,  0,   16,  0,   0,   0,   0,   0,   52,  0,   0,   7,   66,  0,
    16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   0,   0,   51,  0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,
    0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 67,  0,   0,   0,   7,   66,  0,   16,
    0,   0,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,
    0,   63,  28,  0,   0,   5,   18,  0,   16,  0,   2,   0,   0,   0,   42,  0,   16,  0,   0,
    0,   0,   0,   18,  0,   0,   1,   32,  0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,
    26,  0,   16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   3,   0,   0,   0,   31,  0,   4,
    3,   42,  0,   16,  0,   0,   0,   0,   0,   52,  0,   0,   7,   66,  0,   16,  0,   0,   0,
    0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   195, 51,
    0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,
    1,   64,  0,   0,   0,   0,   254, 66,  29,  0,   0,   7,   130, 0,   16,  0,   0,   0,   0,
    0,   10,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   55,  0,
    0,   9,   130, 0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   1,
    64,  0,   0,   0,   0,   0,   63,  1,   64,  0,   0,   0,   0,   0,   191, 0,   0,   0,   7,
    66,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,
    0,   0,   0,   0,   0,   27,  0,   0,   5,   18,  0,   16,  0,   2,   0,   0,   0,   42,  0,
    16,  0,   0,   0,   0,   0,   18,  0,   0,   1,   54,  32,  0,   5,   18,  0,   16,  0,   7,
    0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   50,  0,   0,   9,   66,  0,   16,  0,
    0,   0,   0,   0,   10,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127,
    67,  1,   64,  0,   0,   0,   0,   0,   63,  28,  0,   0,   5,   18,  0,   16,  0,   2,   0,
    0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   31,
    0,   4,   3,   26,  0,   16,  0,   0,   0,   0,   0,   52,  0,   0,   7,   66,  0,   16,  0,
    0,   0,   0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,
    0,   51,  0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   0,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   127, 67,  0,   0,   0,   7,   66,  0,   16,  0,   0,
    0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   63,
    28,  0,   0,   5,   34,  0,   16,  0,   2,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,
    0,   18,  0,   0,   1,   32,  0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,   26,  0,
    16,  0,   5,   0,   0,   0,   1,   64,  0,   0,   3,   0,   0,   0,   31,  0,   4,   3,   42,
    0,   16,  0,   0,   0,   0,   0,   52,  0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,
    26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   195, 51,  0,   0,
    7,   66,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   1,   64,
    0,   0,   0,   0,   254, 66,  29,  0,   0,   7,   130, 0,   16,  0,   0,   0,   0,   0,   26,
    0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   55,  0,   0,   9,
    130, 0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,
    0,   0,   0,   0,   63,  1,   64,  0,   0,   0,   0,   0,   191, 0,   0,   0,   7,   66,  0,
    16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   0,
    0,   0,   0,   27,  0,   0,   5,   34,  0,   16,  0,   2,   0,   0,   0,   42,  0,   16,  0,
    0,   0,   0,   0,   18,  0,   0,   1,   54,  32,  0,   5,   34,  0,   16,  0,   7,   0,   0,
    0,   26,  0,   16,  0,   7,   0,   0,   0,   50,  0,   0,   9,   66,  0,   16,  0,   0,   0,
    0,   0,   26,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 67,  1,
    64,  0,   0,   0,   0,   0,   63,  28,  0,   0,   5,   34,  0,   16,  0,   2,   0,   0,   0,
    42,  0,   16,  0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   31,  0,   4,
    3,   26,  0,   16,  0,   0,   0,   0,   0,   52,  0,   0,   7,   66,  0,   16,  0,   0,   0,
    0,   0,   42,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   51,
    0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,
    1,   64,  0,   0,   0,   0,   127, 67,  0,   0,   0,   7,   66,  0,   16,  0,   0,   0,   0,
    0,   42,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   63,  28,  0,
    0,   5,   66,  0,   16,  0,   2,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   18,
    0,   0,   1,   32,  0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,
    5,   0,   0,   0,   1,   64,  0,   0,   3,   0,   0,   0,   31,  0,   4,   3,   42,  0,   16,
    0,   0,   0,   0,   0,   52,  0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,   42,  0,
    16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   195, 51,  0,   0,   7,   66,
    0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   254, 66,  29,  0,   0,   7,   130, 0,   16,  0,   0,   0,   0,   0,   42,  0,   16,
    0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   55,  0,   0,   9,   130, 0,
    16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,
    0,   0,   63,  1,   64,  0,   0,   0,   0,   0,   191, 0,   0,   0,   7,   66,  0,   16,  0,
    0,   0,   0,   0,   58,  0,   16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,
    0,   27,  0,   0,   5,   66,  0,   16,  0,   2,   0,   0,   0,   42,  0,   16,  0,   0,   0,
    0,   0,   18,  0,   0,   1,   54,  32,  0,   5,   66,  0,   16,  0,   7,   0,   0,   0,   42,
    0,   16,  0,   7,   0,   0,   0,   50,  0,   0,   9,   66,  0,   16,  0,   0,   0,   0,   0,
    42,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 67,  1,   64,  0,
    0,   0,   0,   0,   63,  28,  0,   0,   5,   66,  0,   16,  0,   2,   0,   0,   0,   42,  0,
    16,  0,   0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   31,  0,   4,   3,   26,
    0,   16,  0,   0,   0,   0,   0,   52,  0,   0,   7,   34,  0,   16,  0,   0,   0,   0,   0,
    58,  0,   16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   51,  0,   0,
    7,   34,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   0,   0,   0,   0,   1,   64,
    0,   0,   0,   0,   127, 67,  0,   0,   0,   7,   34,  0,   16,  0,   0,   0,   0,   0,   26,
    0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   63,  28,  0,   0,   5,
    130, 0,   16,  0,   2,   0,   0,   0,   26,  0,   16,  0,   0,   0,   0,   0,   18,  0,   0,
    1,   32,  0,   0,   7,   34,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   5,   0,
    0,   0,   1,   64,  0,   0,   3,   0,   0,   0,   31,  0,   4,   3,   26,  0,   16,  0,   0,
    0,   0,   0,   52,  0,   0,   7,   34,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,
    7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   195, 51,  0,   0,   7,   34,  0,   16,
    0,   0,   0,   0,   0,   26,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,
    254, 66,  29,  0,   0,   7,   66,  0,   16,  0,   0,   0,   0,   0,   58,  0,   16,  0,   7,
    0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   55,  0,   0,   9,   66,  0,   16,  0,
    0,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,
    63,  1,   64,  0,   0,   0,   0,   0,   191, 0,   0,   0,   7,   34,  0,   16,  0,   0,   0,
    0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   0,   0,   0,   0,   27,
    0,   0,   5,   130, 0,   16,  0,   2,   0,   0,   0,   26,  0,   16,  0,   0,   0,   0,   0,
    18,  0,   0,   1,   54,  32,  0,   5,   130, 0,   16,  0,   7,   0,   0,   0,   58,  0,   16,
    0,   7,   0,   0,   0,   50,  0,   0,   9,   34,  0,   16,  0,   0,   0,   0,   0,   58,  0,
    16,  0,   7,   0,   0,   0,   1,   64,  0,   0,   0,   0,   127, 67,  1,   64,  0,   0,   0,
    0,   0,   63,  28,  0,   0,   5,   130, 0,   16,  0,   2,   0,   0,   0,   26,  0,   16,  0,
    0,   0,   0,   0,   21,  0,   0,   1,   21,  0,   0,   1,   21,  0,   0,   1,   140, 0,   0,
    20,  98,  0,   16,  0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   8,   0,
    0,   0,   8,   0,   0,   0,   0,   0,   0,   0,   2,   64,  0,   0,   0,   0,   0,   0,   8,
    0,   0,   0,   16,  0,   0,   0,   0,   0,   0,   0,   86,  6,   16,  0,   2,   0,   0,   0,
    2,   64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   140, 0,   0,   11,  34,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   8,   0,
    0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   10,  0,   16,  0,   2,   0,   0,   0,   26,
    0,   16,  0,   0,   0,   0,   0,   30,  0,   0,   7,   34,  0,   16,  0,   0,   0,   0,   0,
    42,  0,   16,  0,   0,   0,   0,   0,   26,  0,   16,  0,   0,   0,   0,   0,   140, 0,   0,
    11,  34,  0,   16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   8,   0,   0,   0,   1,   64,
    0,   0,   24,  0,   0,   0,   58,  0,   16,  0,   2,   0,   0,   0,   26,  0,   16,  0,   0,
    0,   0,   0,   164, 0,   0,   8,   242, 224, 33,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    6,   0,   16,  0,   0,   0,   0,   0,   70,  14,  16,  0,   1,   0,   0,   0,   62,  0,   0,
    1,   83,  84,  65,  84,  148, 0,   0,   0,   82,  10,  0,   0,   26,  0,   0,   0,   0,   0,
    0,   0,   1,   0,   0,   0,   158, 1,   0,   0,   32,  2,   0,   0,   70,  1,   0,   0,   233,
    0,   0,   0,   232, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   32,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   19,  1,   0,   0,   49,  0,   0,   0,   101, 0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   1,   0,   0,   0};
