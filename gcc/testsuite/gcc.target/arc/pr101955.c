/* { dg-do compile } */
/* { dg-skip-if "avoid conflicts with -mcpu options" { *-*-* } { "-mcpu=*" } { "-mcpu=em" } } */
/* { dg-options "-O2 -mcpu=em" } */

int f(int a)
{
    return (a << 31) >> 31;
}

/* { dg-final { scan-assembler "bmsk_s\\s+r0,r0,0" } } */
/* { dg-final { scan-assembler "neg_s\\s+r0,r0" } } */
